/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INTERRUPT_HighPriority.c                                       */
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          High priority interrupt management                             	*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "p18f6622.h"
#include "IO_declare.h"
#include "typedef.h"
#include "define.h"
#include "enum.h"
#include "DB_Control.h"
#include "DB_PowerSupply.h"
#include "CHARGE_Data.h"
#include "INTERRUPT_HighPriority.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

#pragma interrupt INTERRUPT_HighPriority

void INTERRUPT_HighPriority(void) 
{
	UWORD16 Supply_State = DB_Control_Read(SUPPLY_STATE);


/*%C Timer0 _ Toutes les 1ms lancement d'une interruption 							*/
/*%C 	- 10 par pas de scheduler																*/
/*%C 	- aquisistion d'une voie de CAN														*/
	if ( (INTCONbits.TMR0IF == 1) 	
	  && (INTCONbits.TMR0IE == 1) )
 	{  
		/*%C Compteur (255 - 133 - 3 = 125) * (Fosc/64) = 8µs							*/
		/*%C Le -3 est du au rechargement du timer dans l'interruption          */
		TMR0L = 133; 
  		INTCONbits.TMR0IF = 0;
		/*%C Acquisistion d'une voie de CAN 												*/
		CAN_Channel_Acquisition();
		/*%C Incrémentation de compteur 1ms (scheduler toutes les 10ms) 			*/
		MAIN_activate_tasks();
	}
/*%C Commutation (perte AC)																	*/
	if (	(INTCON3bits.INT1IF == 1)
	  	&& (INTCON3bits.INT1IE == 1))
	{
	
		SHUNT_DIODE_BAT = FALSE;
		SHUNT_DIODE_DC = FALSE;
		SHUNT_DIODE_AC = FALSE;
		SHUNT_DIODE_CHARGEUR = FALSE ;

		/*%C Waiting for the end of MOS Switch _ 30 microSec 						*/
		T3CON&=0xFE;	//Stop Timer3		
		TMR3H = 0xFF; 	//load Timer3
		TMR3L = 0x0F; 
		PIR2bits.TMR3IF = 0;
		T3CON|=0x01;	//Start Timer3
		while (PIR2bits.TMR3IF == 0);

		COMMUT_CHARGEUR = FALSE ;	
		COMMUT_DC = FALSE;
		COMMUT_BAT = FALSE;

		/*%C Start timer of transition */
		TIM_StartDecounter16(TIM_NO_COMMUT,TIME_NO_COMMUT);
	
		INTCON3bits.INT1IF = 0;
		INTCON3bits.INT1IE = 0;

		DB_PowerSupply_Write(POWER_TYPE_U16,AC_DC_BAT);
		DB_Control_Write(SUPPLY_STATE,AC_DC_BAT);

		/*%C Reset counter CHARGE_Init */
		Init_Chargeur_Autorisation = FALSE ;
	}

/*%C Commutation (perte DC)																	*/
	if (	(INTCONbits.INT0IF == 1)
	  	&& (INTCONbits.INT0IE == 1))
	{
		SHUNT_DIODE_BAT = FALSE;
		SHUNT_DIODE_AC = FALSE;
		SHUNT_DIODE_DC = FALSE;

		/*%C Waiting for the end of MOS Switch _ 30 microSec 						*/
		T3CON&=0xFE;	//Stop Timer3		
		TMR3H = 0xFF; 	//load Timer3
		TMR3L = 0x0F; 
		PIR2bits.TMR3IF = 0;
		T3CON|=0x01;	//Start Timer3
		while (PIR2bits.TMR3IF == 0);

		COMMUT_AC = FALSE;
		COMMUT_BAT = FALSE;
		
		/*%C Start timer of transition */
		TIM_StartDecounter16(TIM_NO_COMMUT,TIME_NO_COMMUT);

		/*%C Update interrupt DC_LOW_LEVEL_FLAG 											*/
		DB_Control_Write(DC_LOW_LEVEL_FLAG,TRUE);

		INTCONbits.INT0IF = 0;
		INTCONbits.INT0IE = 0;

		DB_PowerSupply_Write(POWER_TYPE_U16,AC_DC_BAT);
		DB_Control_Write(SUPPLY_STATE,AC_DC_BAT);
	}

/*%C Interruption emission RS232																*/
	if ( (PIR3bits.RC2IF == 1) 			
	  && (PIE3bits.RC2IE == 1) )
	{
	 	DRV_RS232_InterruptReceive();
	}

/*%C Détection de fin de transmission RS232												*/
	if ( (PIR3bits.TX2IF == 1)
	  && (PIE3bits.TX2IE == 1) )
	{
		DRV_RS232_InterruptTransmit();
	}	

/*%C Interruption SPI_CPU 																		*/
	if ( (PIR1bits.SSP1IF == 1) 
	  && (PIE1bits.SSP1IE == 1) )
	{
		/*%C Start decounter to control SPI frame 										*/
		TIM_StartDecounter16(TIM_NO_FRAME,TIME_NO_FRAME);
		/*%C Call the interrupt SPI recive 													*/
		DRV_SPI_ST10_Interrupt();	
	}

/*Détection d'une reception UART																*/
	if ( (PIR1bits.RC1IF == 1)	
	  && (PIE1bits.RC1IE == 1) )
	{
		DRV_EEPROM_BAT_Interrupt();
	}
/* Détection d'une capture ECCP1																*/
	if ( (PIR1bits.CCP1IF == 1) 
	  && (PIE1bits.CCP1IE == 1) )
	{
		FAN_Acquisition();
	}
}
