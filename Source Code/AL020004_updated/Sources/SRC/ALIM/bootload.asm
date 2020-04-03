; *****************************************************************************
; 
;	Ce programme est une adaptation du bootloader fourni par Microchip
;
;	Modifications :
;		- communication sur PORTG
;		- au démarrage, le programme attend 1/2 avant de passer en exécution normale
;			si avant la demi seconde, le pic reçoit une trame (<STX><STX>...<ETX>), il passe en mode bootloader
;
;
; Memory Map
;	-----------------
;	|    0x0000	|
;	|    0x0002 |	Boot vector
;   |    0x0004	|	Unlock & write vector
;	|    		|	
;	|		|
;	|  Boot Block 	|	(this program)
; 	|		|
;	|    0x0800	|	Re-mapped Reset Vector
;	|    0x0808	|	Re-mapped High Priority Interrupt Vector
;	|    0x0818	|	Re-mapped Low Priority Interrupt Vector
;	|		|
;	|	|	|
;	|		|
;    	|  Code Space 	|	User program space
;	|		|
;	|	|	|
;	|		|
;	|   0xXXXXXX    |
;	-----------------
;
;
; Incomming data format:
;
;	<STX><STX><DATA><CHKSUM><ETX>
;		  /    \
;	 ________/      \____________________________
;	/	                                     \
;	<COMMAND><DLEN><ADDRL><ADDRH><ADDRU><DATA>...
;
; Definitions:
;
; 	STX	-	Start of packet indicator
;	ETX	-	End of packet indicator
; 	LEN 	-	Length of incomming packet
; 	DATA	-	General data up to 255 bytes
; 	CHKSUM 	- 	The 8-bit two's compliment sum of LEN & DATA
; 	COMMAND - 	Base command
; 	DLEN	-	Length of data associated to the command
; 	ADDR	-	Address up to 24 bits
; 	DATA 	-	Data (if any)
;
;
; Commands:
;
; 	RD_VER		0x00	Read Version Information
; 	RD_MEM		0x01	Read Program Memory
; 	WR_MEM		0x02	Write Program Memory
; 	ER_MEM		0x03	Erase Program Memory
; 	RD_EE		0x04	Read EEDATA Memory 
; 	WR_EE		0x05	Write EEDATA Memory 
; 	RD_CONFIG	0x06	Read Config Memory 
; 	WT_CONFIG	0x07	Write Config Memory 
;
; *****************************************************************************

 

; *****************************************************************************
	#include P18F6622.inc
; *****************************************************************************



; *****************************************************************************
#define	MINOR_VERSION	0x00		; Version
#define	MAJOR_VERSION	0x01

#define	RC_DLE		0x01
#define	RC_STX		0x02

#define	STX		0x0F
#define	ETX		0x04
#define	DLE		0x05



; *****************************************************************************
CHKSUM		equ	0x00		; Checksum accumulator
COUNTER		equ	0x01		; General counter
ABTIME_H	equ	0x02
ABTIME_L	equ	0x03
RXDATA		equ	0x04
TXDATA		equ	0x05

; Frame Format
;
;  <STX><STX>[<COMMAND><DATALEN><ADDRL><ADDRH><ADDRU><...DATA...>]<CHKSUM><ETX>

DATA_BUFF	equ	0x08		; Start of receive buffer
	
COMMAND		equ	0x08		; Data mapped in receive buffer
DATA_COUNT	equ	0x09	
ADDRESS_L	equ	0x0A
ADDRESS_H	equ	0x0B
ADDRESS_U	equ	0x0C
PACKET_DATA	equ	0x0D

WRITE_MASK1	equ	0xF5E		; the two last RAM bytes
WRITE_MASK2	equ	0xF5F
	
; *****************************************************************************




; *****************************************************************************
pmwtpi macro				; tblwt*+ macro for PIC18Fxx20 bug
 IFDEF TBLWT_BUG
	tblwt	*
	tblrd	*+
 ELSE
	tblwt	*+
 ENDIF
	endm
; *****************************************************************************


 
; *****************************************************************************
	ORG	0x0000			; Re-map Reset vector
	bra	Setup	
	

	ORG	0x0008
VIntH
	goto	RVIntH			; Re-map Interrupt vector

	ORG	0x0018
VIntL
	goto	RVIntL			; Re-map Interrupt vector
; *****************************************************************************

 

; *****************************************************************************
; Setup the appropriate registers.
Setup

;	movlw 0xE3
;	andwf 0xF93, 1, 0			; on met TRISB en sortie
;	movlw 0x1C
;	iorwf 0xF81, 1, 0			; on affiche sur PORTB
;	movlw 0xEB
;	andwf 0xF81, 1, 0

	

	; Programmation de l'horloge CPU à 32Mhz
 	; Fréquence oscillateur interne à 8MHz
 	; PLL *4 activé
	movlw	0x70
 	movwf	OSCCON
	movlw	0x40
 	movwf	OSCTUNE

	movlw	0x55
	movwf	WRITE_MASK1
	movlw	0xAA
	movwf	WRITE_MASK2

	bcf	TRISG, 1		; Setup tx pin
	bsf	TRISG, 2		; Setup rx pin

	movlw	b'10000000'		; Setup rx and tx
	movwf	RCSTA2
	movlw	b'00100110'		
	movwf	TXSTA2

;	movlw	b'00001000'
;	movwf	BAUDCON2

	movlw	0x00
	movwf	SPBRGH2
	movlw	0x10
	movwf	SPBRG2

	movlw	b'00000111'		; x256 Prescale
	movwf	T0CON

	rcall	ReloadTimer;;;



; *****************************************************************************




; *****************************************************************************

Autobaud

	bcf	RCSTA2, CREN		; Stop receiving

	rcall	WaitForRise
	rcall	WaitForRise

	btfsc	INTCON, TMR0IF
	bra		ExecutionMode

	bsf	RCSTA2, CREN		; Start receiving

	movf	RCREG2, W		; Empty the buffer
	movf	RCREG2, W

	bra	StartOfLine


ExecutionMode
	bcf		INTCON, TMR0IF		;
	clrf	RCSTA2
	clrf	TXSTA2
	clrf	WRITE_MASK1
	clrf	WRITE_MASK2
	goto	RVReset				; et on démarre en mode normal


		
; *****************************************************************************



; *****************************************************************************
; Read and parse the data.
StartOfLine

	rcall	RdRS232			; Get second <STX>
	xorlw	STX
	bnz		Autobaud		; Otherwise go back for another character

	lfsr	0, DATA_BUFF		; Point to the buffer

	clrf	CHKSUM			; Reset checksum		
	clrf	COUNTER			; Reset buffer count
		
GetNextDat				
	rcall	RdRS232			; Get the data
	xorlw	STX			; Check for a STX
	bz	StartOfLine		; Yes, start over	

NoSTX	movf	RXDATA, W
	xorlw	ETX			; Check for a ETX
	bz	CheckSum		; Yes, examine checksum		

NoETX	movf	RXDATA, W
	xorlw	DLE			; Check for a DLE
	bnz	NoDLE

	rcall	RdRS232			; Yes, Get the next byte
	
NoDLE	movf	RXDATA, W

	addwf	CHKSUM, F		; Get sum
	movwf	POSTINC0		; Store the data

	dcfsnz	COUNTER, F		; Limit buffer to 256 bytes
	bra	Autobaud

	bra	GetNextDat

CheckSum	
	movf	CHKSUM			; Checksum test
	bnz	Autobaud
; ***********************************************



; ***********************************************
; Pre-setup, common to all commands.
	movf	ADDRESS_L, W		; Set all possible pointers
	movwf	TBLPTRL
	movwf	EEADR
	movf	ADDRESS_H, W
	movwf	TBLPTRH
	movwf	EEADRH
	movff	ADDRESS_U, TBLPTRU

	lfsr	FSR0, PACKET_DATA

	movf	DATA_COUNT, W 		; Setup counter
	movwf	COUNTER
	btfsc	STATUS, Z
	reset				; Non valid count (Special Command)
; ***********************************************

 

; ***********************************************
; Test the command field and sub-command.
CheckCommand

	;rcall	ReloadTimer;;;
	bcf	T0CON, TMR0ON ; si on a reçu une commande dans le temps imparti, c'est bon on reste en bootloader

	movf	COMMAND, W		; Test for a valid command			
	sublw	0x08
	bnc	Autobaud

	clrf	PCLATH			; Setup for a calculated jump
	clrf	PCLATU
		
	rlncf	COMMAND, W		; Jump
	addwf	PCL, F
	
	bra	ReadVersion
	bra	ReadProgMem
	bra	WriteProgMem
	bra	EraseProgMem
	bra	ReadEE
	bra	WriteEE
	bra	ReadProgMem	;ReadConfig
	bra	WriteConfig
	bra	ResetPic
; ***********************************************



; ***********************************************
; Commands
; 
; In:	<STX><STX>[<0x00><0x02>]<0xFF><ETX>
; OUT:	<STX><STX>[<0x00><VERL><VERH>]<CHKSUM><ETX>
ReadVersion
	movlw	MINOR_VERSION
	movwf	DATA_BUFF + 2
	movlw	MAJOR_VERSION
	movwf	DATA_BUFF + 3

	movlw	0x04
	bra	WritePacket


; In:	<STX><STX>[<0x01><DLEN><ADDRL><ADDRH><ADDRU>]<CHKSUM><ETX>
; OUT:	<STX><STX>[<0x01><DLEN><ADDRL><ADDRH><ADDRU><DATA>...]<CHKSUM><ETX>
ReadProgMem
	tblrd	*+			; Fill buffer
	movff	TABLAT, POSTINC0

	decfsz	COUNTER, F		
	bra	ReadProgMem		; Not finished then repeat

	movf	DATA_COUNT, W		; Setup packet length
	addlw	0x05
				
	bra	WritePacket


; In:	<STX><STX>[<0x02><DLENBLOCK><ADDRL><ADDRH><ADDRU><DATA>...]<CHKSUM><ETX>
; OUT:	<STX><STX>[<0x02>]<CHKSUM><ETX>
WriteProgMem
	movlw	b'11111000'		; Force a boundry
	andwf	TBLPTRL, F
 
	movlw	0x08

Lp1	movff	POSTINC0, TABLAT	; Load the holding registers

	pmwtpi				; Same as tblwt *+

	decfsz	WREG, F
	bra	Lp1
 
	tblrd	*-			; Point back into the block

	movlw	b'10000100'		; Setup writes
	movwf	EECON1
	rcall	StartWrite		; Write the data

	tblrd	*+			; Point to the beginning of the next block

	decfsz	COUNTER, F		
	bra	WriteProgMem		; Not finished then repeat

	bra	SendAcknowledge		; Send acknowledge


; In:	<STX><STX>[<0x03><DLENROW><ADDRL><ADDRH><ADDRL>]<CHKSUM><ETX>
; OUT:	<STX><STX>[<0x03>]<CHKSUM><ETX>
EraseProgMem
	movlw	b'10010100'		; Setup writes
	movwf	EECON1

	rcall	StartWrite		; Erase the row

	movlw	0x40			; Point to next row
	addwf	TBLPTRL, F
	clrf	WREG
	addwfc	TBLPTRH, F
	addwfc	TBLPTRU, F

	decfsz	COUNTER, F
	bra	EraseProgMem	

	bra	SendAcknowledge		; Send acknowledge


; In:	<STX><STX>[<0x04><DLEN><ADDRL><ADDRH><0x00>]<CHKSUM><ETX>
; OUT:	<STX><STX>[<0x04><DLEN><ADDRL><ADDRH><0x00><DATA>...]<CHKSUM><ETX>
ReadEE
	clrf	EECON1 

	bsf	EECON1, RD		; Read the data
	movff	EEDATA, POSTINC0
	
	infsnz	EEADR, F		; Adjust EEDATA pointer
	incf	EEADRH, F

	decfsz	COUNTER, F
	bra	ReadEE			; Not finished then repeat

	movf	DATA_COUNT, W		; Setup packet length
	addlw	0x05
				
	bra	WritePacket


; In:	<STX><STX>[<0x05><DLEN><ADDRL><ADDRH><0x00><DATA>...]<CHKSUM><ETX>
; OUT:	<STX><STX>[<0x05>]<CHKSUM><ETX>
WriteEE	

	movff	POSTINC0, EEDATA

	movlw	b'00000100'		; Setup for EEData
	movwf	EECON1
	rcall	StartWrite		
	btfsc	EECON1, WR		; Write and wait
	bra	$ - 2

	infsnz	EEADR, F		; Adjust EEDATA pointer
	incf	EEADRH, F

	decfsz	COUNTER, F		
	bra	WriteEE			; Not finished then repeat

	bra	SendAcknowledge		; Send acknowledge
 

; In:	<STX><STX>[<0x06><DLEN><ADDRL><ADDRH><ADDRU>]<CHKSUM><ETX>
; OUT:	<STX><STX>[<0x06><DLEN><ADDRL><ADDRH><ADDRU><DATA>...]<CHKSUM><ETX>
;ReadConfig
;	movlw	b'11000000'
;	movwf	EECON1
;
;Lp5	tblrd	*+
;	movff	TABLAT, POSTINC0
;
;	decfsz	COUNTER, F
;	bra	Lp5			; Not finished then repeat
;
;	movf	DATA_COUNT, W		; Setup packet length
;	addlw	0x05
;
;	bra	WritePacket


; In:	<STX><STX>[<0x07><DLEN><ADDRL><ADDRH><ADDRU><DATA>...]<CHKSUM><ETX>
; OUT:	<STX><STX>[<0x07>]<CHKSUM><ETX>
WriteConfig
	movlw	b'11000100'
	movwf	EECON1

	movff	POSTINC0, TABLAT	; Write to config area
	tblwt	*

	rcall	StartWrite

	tblrd	*+

	decfsz	COUNTER, F
	bra	WriteConfig		; Not finished then repeat
		
	bra	SendAcknowledge		; Send acknowledge



; ***********************************************
ResetPic
	RESET

; ***********************************************


; ***********************************************
; Send the data buffer back.
;
; <STX><STX>[<DATA>...]<CHKSUM><ETX>

SendAcknowledge
	movlw	0x01			; Send acknowledge

WritePacket
	movwf	COUNTER

	movlw	STX			; Send start condition
	rcall	WrRS232
	rcall	WrRS232

	clrf	CHKSUM			; Reset checksum

	lfsr	FSR0, DATA_BUFF		; Setup pointer to buffer area	
	
SendNext				; Send DATA
	movf	POSTINC0, W
	addwf	CHKSUM
	rcall	WrData
	decfsz	COUNTER, F
	bra	SendNext

	negf	CHKSUM			; Send checksum
	movf	CHKSUM, W
	rcall	WrData

	movlw	ETX			; Send stop condition
	rcall	WrRS232

	bra	Autobaud
; *****************************************************************************




; *****************************************************************************
; Write a byte to the serial port.

WrData
	movwf	TXDATA			; Save the data
 
	xorlw	STX			; Check for a STX
	bz	WrDLE			; No, continue WrNext

	movf	TXDATA, W		
	xorlw	ETX			; Check for a ETX
	bz	WrDLE			; No, continue WrNext

	movf	TXDATA, W		
	xorlw	DLE			; Check for a DLE
	bnz	WrNext			; No, continue WrNext

WrDLE
	movlw	DLE			; Yes, send DLE first
	rcall	WrRS232

WrNext
	movf	TXDATA, W		; Then send STX

WrRS232
	clrwdt
	btfss	PIR3, TX2IF		; Write only if TXREG is ready
	bra	$ - 2
	
	movwf	TXREG2			; Start sending

	return
; *****************************************************************************




; *****************************************************************************
RdRS232
	clrwdt

	btfsc	RCSTA2, OERR		; Reset on overun
	reset

	btfss	PIR3, RC2IF		; Wait for data from RS232
	bra	$ - 2	

	movf	RCREG2, W		; Save the data
	movwf	RXDATA
 
	return
; *****************************************************************************





; *****************************************************************************
; Unlock and start the write or erase sequence.

StartWrite
	clrwdt

	movf	WRITE_MASK1, W		; Unlock
	movwf	EECON2
	movf	WRITE_MASK2, W
	movwf	EECON2
	bsf	EECON1, WR		; Start the write
	nop

	return
; *****************************************************************************




; *****************************************************************************
;	ORG	0x000A

WaitForRise
	btfsc	INTCON, TMR0IF	; si le timer déborde;;;
	return;;;

	btfsc	PORTG, 2		; Wait for a falling edge
	bra	WaitForRise

	clrwdt

WtSR

	btfsc	INTCON, TMR0IF	; si le timer déborde;;;
	return;;;

	btfss	PORTG, 2		; Wait for starting edge
	bra	WtSR

	return
; *****************************************************************************

ReloadTimer
	bcf	T0CON, TMR0ON		; Start counting
	movlw	0xC2			; on arme le timer pour 1/2 seconde :
	movwf	TMR0H			;	32M /4 / 256 = 31250
	movlw	0xF6			;	125000 / 2 = 15625 = 0x3D09
	clrf	TMR0L			;	0xFFFF - 0x3D09 = 0xC2F6
	bsf	T0CON, TMR0ON		; Start counting
	return



; *****************************************************************************
	ORG	0x800
RVReset

	ORG	0x808
RVIntH

	ORG	0x818
RVIntL
; *****************************************************************************


	END
