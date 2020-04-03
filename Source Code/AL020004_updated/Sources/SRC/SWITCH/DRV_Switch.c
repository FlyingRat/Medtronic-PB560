/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_Switch.c                                                   */
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               MOS transistors switch control						      		*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "p18f6622.h"
#include "IO_Declare.h"
#include "typedef.h"
#include "define.h"
#include "enum.h"
#include "DB_Control.h"
#include "DB_PowerSupply.h"
#include "DRV_Switch.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_Switch(UBYTE Supply_Cmd)
{
	/*%C Commutation on the selected supply type 										*/
	switch(Supply_Cmd)
	{
		/*%C When AC supply is detected 														*/
		case AC_SUPPLY:
		{
			/*%C Apply diode on DC and battery 												*/
			SHUNT_DIODE_DC = FALSE;
			SHUNT_DIODE_BAT = FALSE;
			
			/*%C Waiting for the end of MOS Switch _ 30 microSec 						*/
			T3CON&=0xFE;	//Stop Timer3		
			TMR3H = 0xFF; 	//load Timer3
			TMR3L = 0x0F; 
			PIR2bits.TMR3IF = 0;
			T3CON|=0x01;	//Start Timer3
			while (PIR2bits.TMR3IF == 0);
				
			/*%C Switch on the AC and switch off the DC and the battery 				*/
			COMMUT_AC = FALSE;
			COMMUT_DC = TRUE;
			COMMUT_BAT = TRUE;

			/*%C Waiting for the end of MOS Switch _ 30 microSec 						*/
			T3CON&=0xFE;	//Stop Timer3		
			TMR3H = 0xFF; 	//load Timer3
			TMR3L = 0x0F; 
			PIR2bits.TMR3IF = 0;
			T3CON|=0x01;	//Start Timer3
			while (PIR2bits.TMR3IF == 0);

			/*%C By pass the AC diode 															*/
			SHUNT_DIODE_AC = TRUE;		

			/*%C AC interrupt authorization 													*/
			INTCON3bits.INT1IF = 0;			
			INTCON3bits.INT1IE = 1;
			
			/*%C DC interrupt inhibition 													*/
			INTCONbits.INT0IE = 0;

			break;
		}
	
		/*%C When DC supply is detected 														*/
		case DC_SUPPLY:
		{
			/*%C Apply diode on AC and battery 												*/
			SHUNT_DIODE_AC = FALSE;
			SHUNT_DIODE_BAT = FALSE;
			SHUNT_DIODE_CHARGEUR = FALSE ;

			/*%C Waiting for the end of MOS Switch _ 30 microSec 						*/
			T3CON&=0xFE;	//Stop Timer3		
			TMR3H = 0xFF; 	//load Timer3
			TMR3L = 0x0F; 
			PIR2bits.TMR3IF = 0;
			T3CON|=0x01;	//Start Timer3
			while (PIR2bits.TMR3IF == 0);

			/*%C Switch on the DC and switch off the AC and the battery 				*/
			COMMUT_DC = FALSE;
			COMMUT_AC = TRUE;
			COMMUT_BAT = TRUE;
			COMMUT_CHARGEUR = FALSE ;

			/*%C Waiting for the end of MOS Switch _ 30 microSec 						*/
			T3CON&=0xFE;	//Stop Timer3		
			TMR3H = 0xFF; 	//load Timer3
			TMR3L = 0x0F; 
			PIR2bits.TMR3IF = 0;
			T3CON|=0x01;	//Start Timer3
			while (PIR2bits.TMR3IF == 0);

			/*%C By pass the DC diode 															*/
			SHUNT_DIODE_DC = TRUE;

			/*%C DC interrupt authorization 													*/
			INTCONbits.INT0IF = 0;			
			INTCONbits.INT0IE = 1;
			
			/*%C AC interrupt inhibition 													*/
			INTCON3bits.INT1IE = 0;

			/*%C Update battery state in database		 										*/
			DB_PowerSupply_Write(BAT_STATE_U16,BAT_IDLE);

			break;
		}
	
		/*%C When Battery supply is detected 														*/	
		case BAT_SUPPLY:
		{
			/*%C Apply diode on AC and DC		 												*/
			SHUNT_DIODE_AC = FALSE;
			SHUNT_DIODE_DC = FALSE;
			SHUNT_DIODE_CHARGEUR = FALSE ;

			/*%C Waiting for the end of MOS Switch _ 30 microSec 						*/
			T3CON&=0xFE;	//Stop Timer3		
			TMR3H = 0xFF; 	//load Timer3
			TMR3L = 0x0F; 
			PIR2bits.TMR3IF = 0;
			T3CON|=0x01;	//Start Timer3
			while (PIR2bits.TMR3IF == 0);

			/*%C Switch on the battery and switch off the AC and the DC				*/	
			COMMUT_BAT = FALSE;
			COMMUT_AC = TRUE;
			COMMUT_DC = TRUE;
			COMMUT_CHARGEUR = FALSE ;

			/*%C Waiting for the end of MOS Switch _ 30 microSec 						*/
			T3CON&=0xFE;	//Stop Timer3		
			TMR3H = 0xFF; 	//load Timer3
			TMR3L = 0x0F; 
			PIR2bits.TMR3IF = 0;
			T3CON|=0x01;	//Start Timer3
			while (PIR2bits.TMR3IF == 0);

			/*%C By pass the battery diode 														*/	
			SHUNT_DIODE_BAT = TRUE;		

			/*%C Update battery state in database		 										*/
			DB_PowerSupply_Write(BAT_STATE_U16,BAT_DISCHARGE);	
			DB_Control_Write(DISCHARGE_BAT_STATE,TRUE);

			break;
		}
	
		/*%C On power supply transition					 									*/
		case AC_DC_BAT:
		{
			/*%C Apply diode on AC, DC and battery											*/
			SHUNT_DIODE_DC = FALSE;
			SHUNT_DIODE_BAT = FALSE;
			SHUNT_DIODE_AC = FALSE;
			SHUNT_DIODE_CHARGEUR = FALSE ;

			/*%C Waiting for the end of MOS Switch _ 30 microSec 						*/
			T3CON&=0xFE;	//Stop Timer3		
			TMR3H = 0xFF; 	//load Timer3
			TMR3L = 0x0F; 
			PIR2bits.TMR3IF = 0;
			T3CON|=0x01;	//Start Timer3
			while (PIR2bits.TMR3IF == 0);

			/*%C Switch on the battery, the AC and the DC									*/
			COMMUT_AC = FALSE;
			COMMUT_DC = FALSE;
			COMMUT_BAT = FALSE;
			COMMUT_CHARGEUR = FALSE ;

			break;
		}
		default :
		{
			break ;
		}
	}
}
