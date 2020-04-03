; *****************************************************************************
	#include P18F6622.inc
; *****************************************************************************

		CODE

		; **********************************************************
		; 				         TEST RAM										
		; **********************************************************

ramtest:
		; Programmation de l'horloge CPU � 32Mhz
 		; Fr�quence oscillateur interne � 8MHz
	 	; PLL *4 activ�
		movlw	0x70
	 	movwf	OSCCON
		movlw	0x40
	 	movwf	OSCTUNE

		; ===== Ecriture de 0xAA dans chaque octet de la RAM =====

		movlw 0x00			; on pointe sur le premier octet de la RAM
		movwf FSR0L, 0
		movlw 0x00
		movwf FSR0H, 0

write_AA_loop:
		movlw	0xAA
		movwf	POSTINC0, 0			; on �crit 0xAA � l'adresse point�e par FSR0, puis on incr�mente FSR0

		; on teste si FSR0 a d�pass� le dernier octet de la RAM (si FSR0 = 0x0F60)

		movf	FSR0H, 0, 0			; on commence par tester si FSR0H = 0x0F
		sublw	0x0F
		bnz	write_AA_loop		; si non, on boucle
										; si oui on va tester FSR0L

		movf	FSR0L, 0, 0			; on teste si FSR0L = 0x60
		sublw	0x60
		bnz	write_AA_loop		; si non on boucle
										; si oui on part relire toute la m�moire


		; ===== Lecture de 0xAA dans chaque octet de la RAM =====

		movlw 0x00					; on pointe sur le premier octet de la RAM
		movwf FSR0L, 0
		movlw 0x00
		movwf FSR0H, 0
	
read_AA_loop:
		movf	POSTINC0, 0, 0		; on lit la valeur point�e par FSR0 et on la met dans w
		sublw	0xAA					; on regarde si elle est �gale � 0xAA
		bnz	read_AA_error		; si la valeur n'est pas �gale � 0XAA, on crie
		
		; on teste si FSR0 a d�pass� le dernier octet de la RAM (si FSR0 = 0x0F60)

		movf	FSR0H, 0, 0			; on commence par tester si FSR0H = 0x0F
		sublw	0x0F
		bnz	read_AA_loop		; si non, on boucle
										; si oui on va tester FSR0L

		movf	FSR0L, 0, 0			; on teste si FSR0L = 0x60
		sublw	0x60
		bnz	read_AA_loop		; si non on boucle
										; si oui on part �crire des 0x55 dans toute la m�moire

		
		; ===== Ecriture de 0x55 dans chaque octet de la RAM =====

		movlw 0x00			; on pointe sur le premier octet de la RAM
		movwf FSR0L, 0
		movlw 0x00
		movwf FSR0H, 0
		
write_55_loop:
		movlw	0X55
		movwf	POSTINC0, 0			; on �crit 0x55 � l'adresse point�e par FSR0, puis on incr�mente FSR0

		; on teste si FSR0 a d�pass� le dernier octet de la RAM (si FSR0 = 0x0F60)

		movf	FSR0H, 0, 0			; on commence par tester si FSR0H = 0x0F
		sublw	0x0F
		bnz	write_55_loop		; si non, on boucle
										; si oui on va tester FSR0L

		movf	FSR0L, 0, 0			; on teste si FSR0L = 0x60
		sublw	0x60
		bnz	write_55_loop		; si non on boucle
										; si oui on part relire toute la m�moire
		
		
		; ===== Lecture de 0x55 dans chaque octet de la RAM =====

		movlw 0x00			; on pointe sur le premier octet de la RAM
		movwf FSR0L, 0
		movlw 0x00
		movwf FSR0H, 0
	
read_55_loop:
		movf	POSTINC0, 0, 0		; on lit la valeur point�e par FSR0 et on la met dans w
		sublw	0x55					; on regarde si elle est �gale � 0x55
		bnz	read_55_error		; si la valeur n'est pas �gale � 0X55, on crie
		
		; on teste si FSR0 a d�pass� le dernier octet de la RAM (si FSR0 = 0x0F60)

		movf	FSR0H, 0, 0			; on commence par tester si FSR0H = 0x0F
		sublw	0x0F
		bnz	read_55_loop		; si non, on boucle
										; si oui on va tester FSR0L

		movf	FSR0L, 0, 0			; on teste si FSR0L = 0x60
		sublw	0x60
		bnz	read_55_loop		; si non on boucle
										; si oui le test de m�moire est termin�

		return					; on sort du test RAM


	; ===== et s'il y a une erreur on fait quoi ? =====
read_AA_error:
read_55_error:

		; on allume les leds ?
		movlw	0xE3
		andwf	TRISB, 1, 0			; on met TRISB en sortie


leds_on:
		movlw 0x1C
		iorwf	PORTB			; on affiche sur PORTB

		rcall	wait500ms
		

leds_off:
		movlw	0xE3
		andwf	PORTB			; on efface sur PORTB

		rcall	wait500ms

		bra		leds_on


wait500ms:
		bcf		T0CON, TMR0ON	; Stop counting
		movlw	0xC2			; on arme le timer pour 1/2 seconde :
		movwf	TMR0H			;	32M /4 / 256 = 31250
		movlw	0xF6			;	125000 / 2 = 15625 = 0x3D09
		clrf	TMR0L			;	0xFFFF - 0x3D09 = 0xC2F6
		bsf		T0CON, TMR0ON	; Start counting
waitT0:
		btfss	INTCON, TMR0IF
		bra		waitT0
		bcf		INTCON, TMR0IF
		bcf		T0CON, TMR0ON	; Stop counting
		return



		GLOBAL	ramtest
		GLOBAL read_AA_error

		END
