/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : IO_Declare.h																	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                 Declaration Input/Output Pin name								*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef _IO_DECLARE_H	
#define _IO_DECLARE_H

#ifdef UNIT_TEST
	#ifdef TEST_MPLAB
/******************************************************************************/
/*                            Redefined for Test RT             					*/
/******************************************************************************/
	
	unsigned char TEMP_BAT;
	
	unsigned char MES_3V3;
	unsigned char MES_5V;
	unsigned char MES_VACDC;
	
	unsigned char PRESENCE_AC;
	unsigned char PRESENCE_DC;
	unsigned char LED_ETAT_BAT;
	
	unsigned char COMMUT_IFC;
	unsigned char SCK_SPI;
	unsigned char SDI_SPI;
	unsigned char SDO_SPI;
	unsigned char TX_UART_EEP;
	unsigned char RX_UART_EEP;
	
	unsigned char SHUNT_DIODE_DC;
	
	unsigned char COMMUT_DC;
	unsigned char SHUNT_DIODE_AC;
	unsigned char COMMUT_AC;
	
	unsigned char COMMUT_CHARGEUR;
	unsigned char COMMUT_BAT;
	unsigned char SHUNT_DIODE_BAT;
	unsigned char SHUNT_DIODE_CHARGEUR;
	unsigned char COMMAND_VENTIL;
	
	unsigned char MES_I_BAT;
	unsigned char MES_VCHARGE;
	unsigned char MES_TEMP_AMB;
	unsigned char MES_VDC;
	unsigned char MES_24VUTIL;
	unsigned char MES_VBAT;
	
	unsigned char SS;
	
	unsigned char REGLAGE_VCHARGE;
	unsigned char REGLAGE_ICHARGE;
	
	unsigned char PWM_VCHARGE ;
	unsigned char PWM_ICHARGE ;

	unsigned char PST_2 ;
	unsigned char PST_3 ;
	unsigned char PST_4 ;
	unsigned char PST_5 ;

	#else
	
	extern unsigned char TEMP_BAT;
	
	extern unsigned char MES_3V3;
	extern unsigned char MES_5V;
	extern unsigned char MES_VACDC;
	
	extern unsigned char PRESENCE_AC;
	extern unsigned char PRESENCE_DC;
	extern unsigned char LED_ETAT_BAT;
	
	extern unsigned char COMMUT_IFC;
	extern unsigned char SCK_SPI;
	extern unsigned char SDI_SPI;
	extern unsigned char SDO_SPI;
	extern unsigned char TX_UART_EEP;
	extern unsigned char RX_UART_EEP;
	
	extern unsigned char SHUNT_DIODE_DC;
	
	extern unsigned char COMMUT_DC;
	extern unsigned char SHUNT_DIODE_AC;
	extern unsigned char COMMUT_AC;
	
	extern unsigned char COMMUT_CHARGEUR;
	extern unsigned char COMMUT_BAT;
	extern unsigned char SHUNT_DIODE_BAT;
	extern unsigned char SHUNT_DIODE_CHARGEUR;
	extern unsigned char COMMAND_VENTIL;
	
	extern unsigned char MES_I_BAT;
	extern unsigned char MES_VCHARGE;
	extern unsigned char MES_TEMP_AMB;
	extern unsigned char MES_VDC;
	extern unsigned char MES_24VUTIL;
	extern unsigned char MES_VBAT;
	
	extern unsigned char SS;
	
	extern unsigned char REGLAGE_VCHARGE;
	extern unsigned char REGLAGE_ICHARGE;
	
	extern unsigned char PWM_VCHARGE ;
	extern unsigned char PWM_ICHARGE ;

	extern unsigned char PST_2 ;
	extern unsigned char PST_3 ;
	extern unsigned char PST_4 ;
	extern unsigned char PST_5 ;

	#endif
#else
	/******************************************************************************/
	/*                             #DEFINE		                        				*/
	/******************************************************************************/

	#define TEMP_BAT PORTAbits.RA0
	#define MES_3V3 PORTAbits.RA2
	#define MES_VACDC PORTAbits.RA5
	
	#define INTERRUPT_VDC PORTBbits.RB0
	#define INTERRUPT_VACDC PORTBbits.RB1
	#define PRESENCE_AC PORTBbits.RB2
	#define PRESENCE_DC  PORTBbits.RB3
	#define LED_ETAT_BAT PORTBbits.RB4
	
	#define SCK_SPI PORTCbits.RC3
	#define SDI_SPI PORTCbits.RC4
	#define SDO_SPI PORTCbits.RC5
	#define TX_UART_EEP PORTCbits.RC6
	#define RX_UART_EEP PORTCbits.RC7
	
	#define SHUNT_DIODE_DC PORTDbits.RD0	
	#define COMMUT_DC PORTDbits.RD1
	#define SHUNT_DIODE_AC PORTDbits.RD2
	#define COMMUT_AC PORTDbits.RD3
	#define PST_2 PORTDbits.RD4
	#define PST_3 PORTDbits.RD5
	#define PST_4 PORTDbits.RD6
	#define PST_5 PORTDbits.RD7
	
	#define COMMUT_IFC PORTEbits.RE2
	#define COMMUT_CHARGEUR PORTEbits.RE3
	#define COMMUT_BAT PORTEbits.RE4
	#define SHUNT_DIODE_BAT PORTEbits.RE5
	#define SHUNT_DIODE_CHARGEUR PORTEbits.RE6
	#define COMMAND_VENTIL PORTEbits.RE7
	
	#define MES_I_BAT PORTFbits.RF0
	#define MES_VCHARGE PORTFbits.RF1
	#define MES_TEMP_AMB PORTFbits.RF2
	#define MES_VDC PORTFbits.RF3
	#define MES_24VUTIL PORTFbits.RF4
	#define MES_5V PORTFbits.RF5
	#define MES_VBAT PORTFbits.RF6
	
	#define SS PORTFbits.RF7
	
	#define REGLAGE_VCHARGE PORTGbits.RG3
	#define REGLAGE_ICHARGE PORTGbits.RG4
	
	#define PWM_VCHARGE 		CCPR4L
	#define PWM_ICHARGE 		CCPR5L
	#define PWM_CMD_VENTIL 	CCPR2L	


#endif
#endif
