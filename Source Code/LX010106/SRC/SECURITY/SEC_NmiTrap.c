/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_NmiTrap.c                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  This function is the non masquable interrupt                            */
/*                                                                            */
/******************************************************************************/
/*%I  Input Parameter :   NONE                                                */
/*%IO Input/Output :      NONE                                                */
/*%O  Output Parameter :  NONE                                                */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#ifndef _TASKING
	#include "LH_ST10F276.h"
	#include <intrins.h>
#else	    
 	#include "regf276e.h"
#endif 	
#include "io_declare.h"
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "define.h"
#include "DRV_VarEeprom.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "DB_Rtc.h"
#include "DB_Event.h"
#include "DB_PowerSupply.h"
#include "DB_EventMngt.h"
#include "Ventilation_Constants.h"
#include "SEC_NmiTrap.h"
#include "Main_Data.h"
#include "Flash_Monit_Data.h"
#include "CRC16_Table.h"
#include "PUST.h"


#ifndef MCB167
	#ifndef _TASKING
void SEC_Nmitrap (void) interrupt 0x02 
	#else	    
interrupt 0x02
void SEC_Nmitrap (void) 
	#endif 	
{
	UWORD16 adresse = 0;
	UWORD16 AdrFlashMsb = 0 ;
	UWORD16 AdrFlashLsb = 0 ;
	UWORD16 Concaten16bit = 0 ;
	UWORD32 i = 0 ;
	UWORD16 xhuge *adr_flash = 0; 
	UWORD16 xhuge *adr_flash_erase = 0; 
	e_DRV_EVENT_STATE NMI_State_Flash =0;
	UBYTE Array_Event_trap[10];
	UWORD16 id_read_event = 0 ;
	UWORD16 VentilReq = DB_ConfigRead(VENTIL_REQ_U16);
	UWORD16 CurrentMachineCounterHourMsb = 0;
    UWORD16 CurrentMachineCounterHourLsb = 0;   
	UWORD16 CurrentMachineCounterMin = 0;
	UWORD16 CurrentPatientCounterHourMsb = 0;
	UWORD16 CurrentPatientCounterHourLsb = 0;
	UWORD16 CurrentPatientCounterMin = 0;
	UWORD16 EraseState = 0;
 /*%C memorization of the unvoluntary stop	*/
	if (VentilReq == TRUE)
	{
		ARRET_INVOLONTAIRE = 1;
	}
	else
	{
		ARRET_INVOLONTAIRE = 0;
	}

	/*%C Finish the current operation into NAND Flash */
if((DRV_NAND_Flash_State == NAND_MONIT_READ)
||(DRV_NAND_Flash_State == NAND_TREND_READ))
{
/*%C   Reset for the Read operation */
		DRV_NAND_CommandInput(0xFF) ;
		CMD_ME1 = 0;

}
else if((DRV_NAND_Flash_State == NAND_MONIT_WRITE)
||(DRV_NAND_Flash_State == NAND_TREND_WRITE))
{
/*%C   finish the write operation */
		DRV_NAND_CommandInput(0x10) ;
		CMD_ME1 = 0; 

}
else if(DRV_NAND_Flash_State == NAND_ERASE)
{
/*%C   finish the Erase operation */
		DRV_NAND_CommandInput(0xD0) ;
		CMD_ME1 = 0;
}
else
{
/*%C   Reset for the Read operation */
		DRV_NAND_CommandInput(0xFF) ;
		CMD_ME1 = 0;

}


/*%C Remaining energy management, all actuators are set on security mode:     */
/*%C The blower is set off by PWM                                             */
	BLOWER_CMD = cBLOWER_CMD_OFF;	  
/*%C The blower is set off by the microprocessor port                         */
	CONS_VIT	= 0;	
/*%C The valve is set off                                                     */
 	VALVE_CMD = cVALVE_CMD_OFF;		
/*%C The valve is set off directly by the microprocessor port                 */
	CD_VALVE = 0;						  	
/*%C The backlight is set off                                                 */
/*%C Demande d'ouverture de l'afficheur */
	DRV_DIS_HostRequest ( 1 ) ;
	/*%C Lancement du timer permettant de controler le temps d'excution */
	/*%C RAZ du flag underflow timer 2 */
	T2IR = 0;		
	T2IC = 0;
	/*%C 5000*200ns, duree du timer2 = 1 ms Temps alloué a l'exécution */
	T2 = 5000;   	
	/*%C count down,Prescaller 200nS FCPU/8, start timer */
	T2CON  = 0x00C0;   
	while (MASTERBUSY && (T2IR == 0));
	/*%C stop Timer2 */
	T2CON = 0x0000;     
/*%C The backlight is set off  */
  	DRV_DIS_grBackLight(SWITCH_OFF); 
/*%C Demande de fermeture de l'afficheur */
	DRV_DIS_HostRequest ( 0 ) ;
/*%C Watchdog activation to avoid the device reset if the initialization is   */
/*%C not over (min is 200ms, it's the internal watchdog value)                */
	_srvwdt_();
 	WDOG = !WDOG;

/*%C Eeprom initialization (record only if during device initialization,      */
/*%C the flash erase has not been interrupted                                 */

/*%C Clock DS1305 chip select active for the level 1                          */
	DRV_OutputPort(CE_RTC1, 0); /*%C Desactivation chip enable RTC																*/

	//Initialisation des variables
	CurrentMachineCounterHourMsb =
					(DB_ControlRead(CURRENT_MACHINE_COUNTER_HOUR_U16) >> 8);
	CurrentMachineCounterHourLsb = 
					(DB_ControlRead(CURRENT_MACHINE_COUNTER_HOUR_U16) & 0x00FF);
	

	CurrentMachineCounterMin = 
					(DB_ControlRead(CURRENT_MACHINE_COUNTER_MIN_U16) & 0x00FF);
	
	CurrentPatientCounterHourMsb = 
					(DB_ControlRead (CURRENT_PATIENT_COUNTER_HOUR_U16) >> 8);
	CurrentPatientCounterHourLsb = 
					(DB_ControlRead (CURRENT_PATIENT_COUNTER_HOUR_U16) & 0x00FF);
	
	CurrentPatientCounterMin = 
					(DB_ControlRead(CURRENT_PATIENT_COUNTER_MIN_U16) & 0x00FF);



/* Before writting a new data , we must wait for the end of previous write	 */
   
   do
   {
/*%C  Check eeprom disponibility (no writing in progress)                     */
/*%C  Activate chip enable eeprom                                             */
		DRV_OutputPort(CE_EEP, 0); /*%C Activation chip enable EEPROM */
/*%C  Buffer management with RDSR instruction                                 */
		SSCTB  = 0x0005;          
/*%C  End of transmission waiting on the SPI bus                              */
		DRV_EEP_WaitEndTransmit();
/*%C  SCLK_SPI_CPU clock generating for the eeprom reading                        */
		SSCTB  = 0x0000;	        
/*%C  End of transmission waiting on the SPI bus                              */
		DRV_EEP_WaitEndTransmit();
/*%C  Desactivate chip enable eeprom                                          */
		DRV_OutputPort(CE_EEP, 1); /*%C Desactivation chip enable EEPROM */
/*%C  Tempo of 800 ns ( /CS disable time min is 500 ns)                       */
      DRV_EEP_tempo_CE();		  
   }
/*%C Writing in progress check                                                */
	while ((SSCRB & 0x0001)  != 0x00); 
	
		

/*%C Eeprom chip enable activation                                            */
	DRV_OutputPort(CE_EEP, 0); /*%C Activation chip enable EEPROM */
/*%C Writing activation (WREN instruction is given)                           */
	SSCTB   = 0x0006;         	
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();	
	DRV_OutputPort(CE_EEP, 1); /*%C Desactivation chip enable EEPROM */
/*%C Tempo of 800 ns ( /CS disable time min is 500 ns)                        */
	DRV_EEP_tempo_CE();       	
/*%C Eeprom chip enable activation                                            */
	DRV_OutputPort(CE_EEP, 0); /*%C Activation chip enable EEPROM */
/*%C BAD_ERASE data address compute                                           */
	adresse  = (UWORD16)(((UWORD32)&EEP_DB_Config[BAD_ERASE_U16] 
	                     - BEGIN_RAM_ADRESS_OF_EEP_DATA)*2); 

/*%C Writing instruction sending                                              */
	SSCTB  = 0x0002;     			
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();	  
/*%C MSB address sending                                                      */
	SSCTB  = adresse >> 8; 			 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();		
/*%C LSB address sending                                                      */
	SSCTB  = adresse & 0x00FF; 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();
/******************************************************************************/			
/*%C Writing erasing state                                                    */
	EraseState = DB_ConfigRead(BAD_ERASE_U16);
	SSCTB  = (UBYTE) (EraseState >> 8);
/*%C End of transmission waiting on the SPI bus                               */
 	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Data recording with page change check in eeprom                          */
	DRV_CheckPageAndRetransmitAddress(adresse); 
	SSCTB  = (UBYTE) (EraseState & 0x00FF);
/*%C End of transmission waiting on the SPI bus                               */
 	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Data recording with page change check in eeprom                          */
	DRV_CheckPageAndRetransmitAddress(adresse);
/*%C Writing erasing state                                                    */
	EraseState = ~EraseState;
	SSCTB  = (UBYTE) (EraseState >> 8);
/*%C End of transmission waiting on the SPI bus                               */
 	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Data recording with page change check in eeprom                          */
	DRV_CheckPageAndRetransmitAddress(adresse); 
	SSCTB  = (UBYTE) (EraseState & 0x00FF);
/*%C End of transmission waiting on the SPI bus                               */
 	DRV_EEP_WaitEndTransmit();

/******************************************************************************/
/*%C End of writing eeprom waiting                                            */
/*%C Disable chip select temporization                                        */
   DRV_EEP_tempo_CE();		  
/*%C Desactivate chip enable eeprom                                           */
	DRV_OutputPort(CE_EEP, 1); /*%C Desactivation chip enable EEPROM */
/*%C Disable chip select temporization                                        */
 	DRV_EEP_tempo_CE();       
/*%C Activate chip enable eeprom                                              */
	DRV_OutputPort(CE_EEP, 0); /*%C Activation chip enable EEPROM */

	do
   {
/*%C  Check eeprom disponibility (no writing in progress)                     */
/*%C  Activate chip enable eeprom                                             */
		DRV_OutputPort(CE_EEP, 0); /*%C Activation chip enable EEPROM */
/*%C  Buffer management with RDSR instruction                                 */
		SSCTB  = 0x0005;          
/*%C  End of transmission waiting on the SPI bus                              */
		DRV_EEP_WaitEndTransmit();
/*%C  SCLK_SPI_CPU clock generating for the eeprom reading                        */
		SSCTB  = 0x0000;	        
/*%C  End of transmission waiting on the SPI bus                              */
		DRV_EEP_WaitEndTransmit();
/*%C  Desactivate chip enable eeprom                                          */
		DRV_OutputPort(CE_EEP, 1); /*%C Desactivation chip enable EEPROM */
/*%C  Tempo of 800 ns ( /CS disable time min is 500 ns)                       */
      DRV_EEP_tempo_CE();		  
   }
/*%C Writing in progress check                                                */
	while ((SSCRB & 0x0001)  != 0x00); 	

/*%C  If power falls down or disapears with initialization not finished       */
/*%C Si coupure ou baisse  de l'alimentation alors que l'init n'est pas terminée => ne pas executer le trap
/*%C et attendre le retour de l'alimentation   */
	if (MAIN_End_of_init == FALSE)
		{		  
/*%C Memorizing of unvoluntary stop */
		ARRET_INVOLONTAIRE = 1;
/*%C Call of the function looking for supply return */
		DRV_ResetOnReturnSupply();
		}
/* %C Check if there's a POST Event						*/ 
if ( PUST_ERROR != PUST_ERR_OK)
	{
/*%C When Init is stopped, storage of associated POST event */
	if (PUST_ERROR == PUST_ERR_CRC)        
	{
		Array_Event_trap[EVENT_NB_ID] =(UBYTE)EVENT_FLASH_CHECKSUM_POST_ERROR;
	}
	if ((PUST_ERROR == PUST_ERR_DATA_BUS) ||
        (PUST_ERROR == PUST_ERR_ADDRESS_BUS) ||
        (PUST_ERROR == PUST_ERR_DEVICE) )
	{
		Array_Event_trap[EVENT_NB_ID] =(UBYTE)EVENT_RAM_CHECKSUM_POST_ERROR;  
	}
 	if ( PUST_ERROR == PUST_ERR_REF_VOLTAGE)
	{
		Array_Event_trap[EVENT_NB_ID] =(UBYTE)EVENT_VOLT_REFERENCE_POST_ERROR;
	}
	if ( PUST_ERROR == PUST_ERR_EEPROM)
	{
		Array_Event_trap[EVENT_NB_ID] =(UBYTE)EVENT_EEPROM_POST_ERROR;
	}
	if ( PUST_ERROR == PUST_ERR_SOFT_VERSION)
	{
		Array_Event_trap[EVENT_NB_ID] =(UBYTE)EVENT_POST_VERSION_ERROR;	
	}   

	}
else 
	{  
/*%C Event storage  */
	if (VentilReq == TRUE)
		{
/*%C When ventilation is runing, storage of unvoluntary stop event */
		Array_Event_trap[EVENT_NB_ID] =(UBYTE)EVENT_UNVOLUNTARY_STOP_VENTIL;
		}
	else
/*%C if ventilation is stoped, storage of hour and counters*/ 
		{
		Array_Event_trap[EVENT_NB_ID] =(UBYTE)EVENT_MODIF_STOP_DEVICE;
		}
	}
	Array_Event_trap[EVENT_DAY_ID] 				  
										 = (UBYTE)DB_RTCRead(DB_RTC_DAY_U16);
	Array_Event_trap[EVENT_MON_ID] 				  
										 = (UBYTE)DB_RTCRead(DB_RTC_MONTH_U16);
	Array_Event_trap[EVENT_YEA_ID] 				   
										 = (UBYTE)DB_RTCRead(DB_RTC_YEAR_U16);
	Array_Event_trap[EVENT_HOU_ID] 				   
										 = (UBYTE)DB_RTCRead(DB_RTC_HOUR_U16);
	Array_Event_trap[EVENT_MIN_ID] 				   
										 = (UBYTE)DB_RTCRead(DB_RTC_MINUTE_U16);
	Array_Event_trap[EVENT_SCD_ID] 				   
										 = (UBYTE)DB_RTCRead(DB_RTC_SECOND_U16);
	Array_Event_trap[EVENT_CPTMACHHOURMSB_ID] 	
										 = (UBYTE)CurrentMachineCounterHourMsb;
	Array_Event_trap[EVENT_CPTMACHHOURLSB_ID] 	
										 = (UBYTE)CurrentMachineCounterHourLsb;

	Array_Event_trap[EVENT_MODE_ID] 	 = (UBYTE) DB_ControlRead(CURRENT_MODE_U16); 

    
/*%C Reading Flash operations state */
	NMI_State_Flash = DRV_EVENT_TransStateFlash();
	
/*%C Reading Flash adress of event index */
	adr_flash = DRV_EVENT_TransPtrMemory();
	
/*%C Reading Flash identifier */
	id_read_event = DRV_EVENT_TransfIdent();
	
/*%C Checking to be sure the last event is ended */
	if ((UWORD32)adr_flash % EVENT_Last_Event_Parameter != 0)
		{
	  
/*% CWhen minute patient counter is not reached, programation of missings id */
	  	if (id_read_event < EVENT_CPTMACHHOURLSB_ID+1)
			{				 
			for(i = id_read_event; i < EVENT_CPTMACHHOURLSB_ID+1; i +=2)
				{
/*%C			Waiting flash freeing */
				_nop_();
				_nop_();
				_nop_();
				while(BUSY_MEM2 == 0);
				
/*%C		    Storage  of Month + Year		*/
/*%C		    Left shift of 8 bits to obtain most significative byte */
				Concaten16bit = Array_Event_trap[i+1] << 8;
/*%C Logical Or between first and second event */
/*%C with a shift to do a 16 bits word */
				Concaten16bit = Concaten16bit | Array_Event_trap[i];
/*%C			Programation of data */
			  	DRV_EVENT_Program_Flash(Concaten16bit, 
			 		(UWORD16 xhuge *)((UWORD32)adr_flash + EVENT_FLASH_START_ADDRESS));
/*%C			Incréasing programing adress */
				adr_flash++;
				}
			}
/*%C Index on the next event adress */
		adr_flash = (UWORD16 xhuge *)((((UWORD32)adr_flash / EVENT_Last_Event_Parameter) * EVENT_Last_Event_Parameter)
																						 + EVENT_Last_Event_Parameter);
		}
 
/*%C  Check to be sure to store a whole ebvent */
	if ((UWORD32)adr_flash + EVENT_Last_Event_Parameter 
			>= EVENT_FLASH_END_ADDRESS - EVENT_FLASH_START_ADDRESS)  
		{
		adr_flash = 0;			  
		}
/*%C  When an erazing is runing, the erazing sequence is interupted */ 
	if (NMI_State_Flash == DRV_EVENT_ERASE)
		{
		adr_flash_erase = DRV_EVENT_TransAdressErase();
		*adr_flash_erase = 0x00B0;
		}
/*%C  24.8µs delay : waiting erazing validation    	*/
/*%C  Delay validated with oscilloscope					*/
	for (i=0;i<165;i++) 
		{
		_nop_();
		}
/*%C  waiting flash freeing */
	while(BUSY_MEM2 == 0);

/*%C Programing the 10 necessary bytes */ 
	for(i = EVENT_NB_ID; i < EVENT_CPTMACHHOURLSB_ID+1; i +=2)
		{
/*%C  waiting flash freeing */
		_nop_();
		_nop_();
		_nop_();
		while(BUSY_MEM2 == 0);
		
/*%C   Storage  of the Month + Year			  */
/*%C   8 bits left shift -> to obtain the most significative byte		*/
		Concaten16bit = Array_Event_trap[i+1] << 8;
/*%C Logical Or between first and second event */
/*%C with a shift to do a 16 bits word */
		Concaten16bit = Concaten16bit | Array_Event_trap[i];
/*%C	Programation of data */
		DRV_EVENT_Program_Flash(Concaten16bit, 
					(UWORD16 xhuge *)((UWORD32)adr_flash + EVENT_FLASH_START_ADDRESS));
/*%C	Incréasing programing adress */
		adr_flash = adr_flash +1;
		}
/*%C Index on the next event adress */
	adr_flash = (UWORD16 xhuge *)((((UWORD32)adr_flash / EVENT_Last_Event_Parameter) * EVENT_Last_Event_Parameter)
																						 + EVENT_Last_Event_Parameter);
	 	 	 
/*%C  Check to be sure to store a whole ebvent */
	if ((UWORD32)adr_flash + EVENT_Last_Event_Parameter 
			>= EVENT_FLASH_END_ADDRESS - EVENT_FLASH_START_ADDRESS)  
		{
		adr_flash = 0;
	 	}
/*%C Separation of the adress into two 16 bits words */
	AdrFlashMsb = (UWORD16)((UWORD32) adr_flash /  65536);
	AdrFlashLsb = (UWORD16)((UWORD32) adr_flash %  65536);
	
/******************************************************************************/
/* Programing of patient & machine counters, of flash event index             */
/******************************************************************************/
/*%C Init of EEprom for recording */
	DRV_OutputPort(CE_RTC1, 0); /*%C Desactivation chip enable RTC																*/
	DRV_OutputPort(CE_EEP, 0); /*%C Activation chip enable EEPROM */
	SSCTB   = 0x0006;        // Chargement buffer avec instruction WREN
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();
	DRV_OutputPort(CE_EEP, 1); /*%C Desactivation chip enable EEPROM */
	DRV_EEP_tempo_CE();      // tempo Chip select disable
	DRV_OutputPort(CE_EEP, 0); /*%C Activation chip enable EEPROM */
/*%C Compute EEprom adress for  data from machine and patient counters*/
	adresse  = (UWORD16)(((UWORD32)&EEP_DB_Config[SAVED_PATIENT_COUNTER_HOUR_U16] - BEGIN_RAM_ADRESS_OF_EEP_DATA)*2); 
	SSCTB  = 0x0002;     			// Envoi de l'instruction WRITE
/*%C End of transmission waiting on the SPI bus                             */
	DRV_EEP_WaitEndTransmit();
/*%C Sending the uper part of the adress */		
	SSCTB  = adresse >> 8; 			
/*%C End of transmission waiting on the SPI bus                             */
	DRV_EEP_WaitEndTransmit();
/*%C Sending the lower part of the adress */		
	SSCTB  = adresse & 0x00FF;    
/*%C End of transmission waiting on the SPI bus                             */
	DRV_EEP_WaitEndTransmit();
/*********************************************************************************/
/*%C Sending MSB for Patient Hour counter */
	SSCTB  = CurrentPatientCounterHourMsb;
	/*%C End of transmission waiting on the SPI bus                          */
	DRV_EEP_WaitEndTransmit();		
	adresse ++;
/*%c Recording data */ 
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);
/*%C Sending LSB for Patient Hour counter */	
	SSCTB  = CurrentPatientCounterHourLsb;			  
/*%C End of transmission waiting on the SPI bus                            */
  	DRV_EEP_WaitEndTransmit();						
  	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);

/*%C Sending MSB for Patient Hour counter */
	SSCTB  = ~CurrentPatientCounterHourMsb;
	/*%C End of transmission waiting on the SPI bus                          */
	DRV_EEP_WaitEndTransmit();		
	adresse ++;
/*%c Recording data */ 
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);
/*%C Sending LSB for Patient Hour counter */	
	SSCTB  = ~CurrentPatientCounterHourLsb;			  
/*%C End of transmission waiting on the SPI bus                            */
  	DRV_EEP_WaitEndTransmit();						
  	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);
/*********************************************************************************/
/*%C Sending MSB for Patient Minute counter */ 
	SSCTB  = 0;											
/*%C End of transmission waiting on the SPI bus                             */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);
/*%C Sending LSB for Patient Minute counter */ 
 	SSCTB  = CurrentPatientCounterMin;				  
/*%C End of transmission waiting on the SPI bus                             */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);

/*%C Sending MSB for Patient Minute counter */ 
	SSCTB  = 0xFF; /* complément de 0 */											
/*%C End of transmission waiting on the SPI bus                             */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);
/*%C Sending LSB for Patient Minute counter */ 
 	SSCTB  = ~CurrentPatientCounterMin;				  
/*%C End of transmission waiting on the SPI bus                             */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);
/*********************************************************************************/
/*%C Sending the uper part of Machine hour counter */
  SSCTB  = CurrentMachineCounterHourMsb;		 
/*%C End of transmission waiting on the SPI bus                             */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);
/*%C Sending LSB for Machine Hour counter */ 
	SSCTB  = CurrentMachineCounterHourLsb;		  
/*%C End of transmission waiting on the SPI bus                             */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
 	DRV_CheckPageAndRetransmitAddress(adresse);

/*%C Sending the uper part of Machine hour counter */
  	SSCTB  = ~CurrentMachineCounterHourMsb;		 
/*%C End of transmission waiting on the SPI bus                             */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);
/*%C Sending LSB for Machine Hour counter */ 
	SSCTB  = ~CurrentMachineCounterHourLsb;		  
/*%C End of transmission waiting on the SPI bus                             */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
 	DRV_CheckPageAndRetransmitAddress(adresse);
/*********************************************************************************/
/*%C Sending LSB for Machine Minute counter */ 
 	SSCTB  = 0;										  
/*%C End of transmission waiting on the SPI bus                             */
	DRV_EEP_WaitEndTransmit();					   
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);
/*%C Sending LSB for Machine Minute counter */  
	SSCTB  = CurrentMachineCounterMin;			  
/*%C End of transmission waiting on the SPI bus                               */
 	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 

/*%C Sending LSB for Machine Minute counter */ 
 	SSCTB  =0xFF; /* complément de 0 */										  
/*%C End of transmission waiting on the SPI bus                             */
	DRV_EEP_WaitEndTransmit();					   
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);
/*%C Sending LSB for Machine Minute counter */  
	SSCTB  = ~CurrentMachineCounterMin;			  
/*%C End of transmission waiting on the SPI bus                               */
 	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*********************************************************************************/
/*%C Memorizing the writing index on the event flash */ 
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(AdrFlashMsb >> 8);		  
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending LSB low Adress	*/
	SSCTB  = (UBYTE)(AdrFlashMsb & 0x00FF); 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 

	AdrFlashMsb = ~AdrFlashMsb;
	SSCTB  = (UBYTE)(AdrFlashMsb >> 8);		  
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending LSB low Adress	*/
	SSCTB  = (UBYTE)(AdrFlashMsb & 0x00FF); 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);

/*********************************************************************************/
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(AdrFlashLsb >> 8);	   
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
 	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending LSB low Adress	*/
	SSCTB  = (UBYTE)(AdrFlashLsb & 0x00FF);   
/*%C End of transmission waiting on the SPI bus                            	*/
	DRV_EEP_WaitEndTransmit();	
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);

	AdrFlashLsb = ~AdrFlashLsb;
	SSCTB  = (UBYTE)(AdrFlashLsb >> 8);	   
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
 	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending LSB low Adress	*/
	SSCTB  = (UBYTE)(AdrFlashLsb & 0x00FF);   
/*%C End of transmission waiting on the SPI bus                            	*/
	DRV_EEP_WaitEndTransmit();	
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);

/*********************************************************************************/

/******************************************************************************/
/*%C 					Recording of NAND flash indexes 					*/

/*%C************			Monitoring detailled records         *************/ 
/*%C Memorizing the writing index on the event flash */ 
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_MONIT_Address_Start_Read_Flash_Recording.Block >> 8);		 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending LSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_MONIT_Address_Start_Read_Flash_Recording.Block & 0x00FF); 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);
	
 	DRV_MONIT_Address_Start_Read_Flash_Recording.Block = ~DRV_MONIT_Address_Start_Read_Flash_Recording.Block;
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_MONIT_Address_Start_Read_Flash_Recording.Block >> 8);		 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending LSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_MONIT_Address_Start_Read_Flash_Recording.Block & 0x00FF); 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);
/*********************************************************************************/

/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_MONIT_Address_Start_Read_Flash_Recording.Page >> 8);  
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_MONIT_Address_Start_Read_Flash_Recording.Page & 0x00FF); 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 

	DRV_MONIT_Address_Start_Read_Flash_Recording.Page = ~DRV_MONIT_Address_Start_Read_Flash_Recording.Page;
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_MONIT_Address_Start_Read_Flash_Recording.Page >> 8);  
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_MONIT_Address_Start_Read_Flash_Recording.Page & 0x00FF); 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*********************************************************************************/
/*%C Memorizing the writing index on the event flash */ 
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_MONIT_Address_Start_Read_Flash_Recording.Column >> 8);		 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending LSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_MONIT_Address_Start_Read_Flash_Recording.Column & 0x00FF);
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);

	DRV_MONIT_Address_Start_Read_Flash_Recording.Column = ~DRV_MONIT_Address_Start_Read_Flash_Recording.Column;
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_MONIT_Address_Start_Read_Flash_Recording.Column >> 8);		 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending LSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_MONIT_Address_Start_Read_Flash_Recording.Column & 0x00FF);
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);
/*********************************************************************************/
/*%C************			Trend records         *************/ 
/*%C Memorizing the writing index on the event flash */ 
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_TREND_Address_Start_Read_Flash_Recording.Block >> 8);		 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending LSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_TREND_Address_Start_Read_Flash_Recording.Block & 0x00FF); 
/*%C Save into RAM Array too (For CRC Compute) */
	EEP_DB_Config[FLASH_TREND_WRITE_BLOCK_U16] = DRV_TREND_Address_Start_Read_Flash_Recording.Block;
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);

	DRV_TREND_Address_Start_Read_Flash_Recording.Block = ~DRV_TREND_Address_Start_Read_Flash_Recording.Block;
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_TREND_Address_Start_Read_Flash_Recording.Block >> 8);		 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending LSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_TREND_Address_Start_Read_Flash_Recording.Block & 0x00FF); 
/*%C Save into RAM Array too (For CRC Compute) */
	EEP_DB_Config[FLASH_TREND_WRITE_BLOCK_U16] = DRV_TREND_Address_Start_Read_Flash_Recording.Block;
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);
	
/*********************************************************************************/	
																				   	 
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_TREND_Address_Start_Read_Flash_Recording.Page >> 8);    
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_TREND_Address_Start_Read_Flash_Recording.Page & 0x00FF); 
/*%C Save into RAM Array too (For CRC Compute) */
	EEP_DB_Config[FLASH_TREND_WRITE_PAGE_U16] = DRV_TREND_Address_Start_Read_Flash_Recording.Page;   
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);

	DRV_TREND_Address_Start_Read_Flash_Recording.Page = ~DRV_TREND_Address_Start_Read_Flash_Recording.Page;
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_TREND_Address_Start_Read_Flash_Recording.Page >> 8);    
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_TREND_Address_Start_Read_Flash_Recording.Page & 0x00FF); 
/*%C Save into RAM Array too (For CRC Compute) */
	EEP_DB_Config[FLASH_TREND_WRITE_PAGE_U16] = DRV_TREND_Address_Start_Read_Flash_Recording.Page;   
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);

/*********************************************************************************/ 
/*%C Memorizing the writing index on the event flash */ 
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_TREND_Address_Start_Read_Flash_Recording.Column >> 8);		 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending LSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_TREND_Address_Start_Read_Flash_Recording.Column & 0x00FF); 
/*%C Save into RAM Array too (For CRC Compute) */
	EEP_DB_Config[FLASH_TREND_WRITE_COLUMN_U16] = DRV_TREND_Address_Start_Read_Flash_Recording.Column;
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 

	DRV_TREND_Address_Start_Read_Flash_Recording.Column = ~DRV_TREND_Address_Start_Read_Flash_Recording.Column;
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_TREND_Address_Start_Read_Flash_Recording.Column >> 8);		 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending LSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_TREND_Address_Start_Read_Flash_Recording.Column & 0x00FF); 
/*%C Save into RAM Array too (For CRC Compute) */
	EEP_DB_Config[FLASH_TREND_WRITE_COLUMN_U16] = DRV_TREND_Address_Start_Read_Flash_Recording.Column;
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*********************************************************************************/
/*%C Memorizing the writing index on the event flash */ 
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_MONIT_Partition_Full >> 8);		 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending LSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_MONIT_Partition_Full & 0x00FF);
/*%C Save into RAM Array too (For CRC Compute) */
	EEP_DB_Config[FLASH_FIRST_PARTITION_FULL_U16] = DRV_MONIT_Partition_Full; 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);

	DRV_MONIT_Partition_Full = ~DRV_MONIT_Partition_Full;
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_MONIT_Partition_Full >> 8);		 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending LSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_MONIT_Partition_Full & 0x00FF);
/*%C Save into RAM Array too (For CRC Compute) */
	EEP_DB_Config[FLASH_FIRST_PARTITION_FULL_U16] = DRV_MONIT_Partition_Full; 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);
	
 /*********************************************************************************/
/*%C Memorizing the writing index on the event flash */ 
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_TREND_Partition_Full >> 8);		 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending LSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_TREND_Partition_Full & 0x00FF); 
/*%C Save into RAM Array too (For CRC Compute) */
	EEP_DB_Config[FLASH_SECOND_PARTITION_FULL_U16] = DRV_TREND_Partition_Full; 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);

	DRV_TREND_Partition_Full = ~DRV_TREND_Partition_Full;
/*%C sending MSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_TREND_Partition_Full >> 8);		 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();						
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse); 
/*%C sending LSB low Adress	*/
	SSCTB  = (UBYTE)(DRV_TREND_Partition_Full & 0x00FF); 
/*%C Save into RAM Array too (For CRC Compute) */
	EEP_DB_Config[FLASH_SECOND_PARTITION_FULL_U16] = DRV_TREND_Partition_Full; 
/*%C End of transmission waiting on the SPI bus                               */
	DRV_EEP_WaitEndTransmit();
	adresse ++;
/*%C Checking for a new EEPROM page */ 
	DRV_CheckPageAndRetransmitAddress(adresse);
 /*********************************************************************************/
/*%C End of writing eeprom waiting                                            */
/*%C Disable chip select temporization                                        */
   DRV_EEP_tempo_CE();		  
/*%C Desactivate chip enable eeprom                                           */
	DRV_OutputPort(CE_EEP, 1); /*%C Desactivation chip enable EEPROM */
/*%C Disable chip select temporization                                        */
 	DRV_EEP_tempo_CE();       
/*%C Activate chip enable eeprom                                              */
	DRV_OutputPort(CE_EEP, 0); /*%C Activation chip enable EEPROM */

	do
   {
/*%C  Check eeprom disponibility (no writing in progress)                     */
/*%C  Activate chip enable eeprom                                             */
		DRV_OutputPort(CE_EEP, 0); /*%C Activation chip enable EEPROM */
/*%C  Buffer management with RDSR instruction                                 */
		SSCTB  = 0x0005;          
/*%C  End of transmission waiting on the SPI bus                              */
		DRV_EEP_WaitEndTransmit();
/*%C  SCLK_SPI_CPU clock generating for the eeprom reading                        */
		SSCTB  = 0x0000;	        
/*%C  End of transmission waiting on the SPI bus                              */
		DRV_EEP_WaitEndTransmit();
/*%C  Desactivate chip enable eeprom                                          */
		DRV_OutputPort(CE_EEP, 1); /*%C Desactivation chip enable EEPROM */
/*%C  Tempo of 800 ns ( /CS disable time min is 500 ns)                       */
      DRV_EEP_tempo_CE();		  
   }
/*%C Writing in progress check                                                */
	while ((SSCRB & 0x0001)  != 0x00); 


/*%C Unactivation chip enable EEPROM  */						
	DRV_OutputPort(CE_EEP, 1); /*%C Desactivation chip enable EEPROM */




/*%C Call of the function looking for supply return */
	DRV_ResetOnReturnSupply();

}
#endif

