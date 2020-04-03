/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_Interfaces_Init.c                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C       It launches the interface initializations.                         */
/*%C       It is done in two phases, and it is important to respect the       */
/*%C			call order.													  						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif
#include "typedef.h"
#include "io_declare.h"
#include "enum.h"
#include "Structure.h"
#include "define.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_Rtc.h"
#include "DB_Compute.h"
#include "DB_Current.h"
#include "DB_PowerSupply.h"
#include "DB_EventMngt.h"
#include "DB_IhmAccessParaDataBase.h"
#include "MAIN_Interfaces_Init.h"
#include "Main_Data.h"
#include "PUST.h"
#include "SCHED_Ventilation_Main.h"	
#include "SCHED_Ventilation_Scheduler_Config.h"	

/*********************************************************/
#include "Driver_Display_Data.h"
#include "DIS_FifoRead.h"
/*********************************************************/

	#define EEPROM_DATA_DECLARATION
#include "Driver_Eeprom_Data.h"

	#define DECLARATION_COM_DATA
#include "DRV_COM_Data.h"

	#define DECLARATION_DRIVER_DATAS
#include "Driver_Datas.h"	

	#define DECLARATION_DRV_SPI_POWER_DATA
#include "DRV_SPI_POWER_Data.h"

 #include "DRV_VarEeprom.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


void MAIN_Interfaces_Init(void)
{
	UWORD16 CRC16 = 0;	
	UWORD16 TmpReadEeprom = 0;
	UWORD16 EepromAddress = 0;
	UWORD16 i = 0;
	UWORD16 VersionNumber = 0;
	UWORD16 EepromErrorCounter = 0;	
	e_DRV_RTC_ERROR DRV_RTC_Status;
	
	UBYTE DRV_EEP_CounterTimeOutWrite;

	static UWORD16 TimerIncrement = 0 ;

/*********************************************************/
	UWORD16 cnt = 0;
	UWORD16 count = 0;
	UWORD16 value = 0;
/**********************************************************/


if(MAIN_Interfaces_Second_Init == FALSE)
{	
	//initialisation du timer T4 pour le  driver de  leds
// Configuration du timer 4
// Registre de controle du timer T4
	// Prédiviseur = 1024 T4I = 111  
	// Mode timer 	   T4M = 000
	// Timer en marche T4R = 1
	// Direction "décomptage" sans tenir compte de l'entrée T4 T4EUD = 01
	// Contrôle de la sortie T4OUT P31 	non utilisée.T6OE = 0
	// latch de la sortie T4OL = 0
	// Bit 9 10 11 12  13 14 15 non utilisés = 0000000
	// Controle du mode reload pas de reload à partir de CAPREL	 T4SR = 0
	// T4CON =  00000 0 0 01 1 000 000 = 0000000011000111 b = 0xC7
T4CON = 0xC7;

// Registre de contrôle de l'interruption
	// Revoir sa localisation dans le projet voir peut etre pour un 
	// module de gestion des niveaux de priorité des interruptions 
	// et de gestion des PEC
		// Priorité  des interruptions T4
		/*%IR = 0 ,IE = 0; ILVL  = 12 ,GLVL = 3 	 */
		T4IC = 0x33;// Marche du timer
T4R = 1;
// Interruption timer 4
T4IE =1;
// Chargement du timer - 0.5s
// T4 = seconde / 25.6µs;
T4 = 19531;


		 /**************************************************/
	// Init des mesures de tâches

	//initilisation des valeurs maxi et mini du temps des taches
	for (i=0;i < cVENTILATION_NUMBER_OF_TASKS;i++)
			{
			Ventilation_TimesOfTask[i].maxi = 0X0	;	//0;
			Ventilation_TimesOfTask[i].current =0X0;	//0;
			Ventilation_TimesOfTask[i].mini   = 0XFFFF; 	//65535;
	 		}
	
	//Résolution de mesure 800ns à 40Mhz
		T78CON &= 0x00FF;
		T78CON |= 0x02FF;

	// init registre de reload 	T1REL = 0; 
		T8REL = 0x0000;
		T8R = 1;	// démarrage du timer 8

 /**************************************************/

/*%C control register for timer T0 et T1				*/
/*%C less significative byte of timer 0 not programed		*/
/*%C Prédivideur = 32 T1I = 010 résolution 800ns		*/
/*%C Mode timer 	   T1M = 0									*/
/*%C Timer OFF T1R = 0 									*/
/*%C T01CON = 00000010xxxxxxxx								*/
	T01CON &= 0x00FF;
/*%CInterrupt timer1 overflow level   */
	T1IC = 0x3B;
/*%C init register for reload 	T1REL = 0; 			 */
	T1REL = 0x0000;
/*%CCapture compare mode register CCM0					 */

/*%C ACC0 assigned to timer 1								 */
/*%C CCMOD0  capture on positive transition			 */
/*%C ACC1,ACC2,CCMOM1,CCMOD2 non programmés			 */
/*%C ==> CCM0 = xxxx xxxx xxxx 1001 = 0x0009			 */
	CCM0 &= 0xFFF0;
	CCM0 |= 0x0009;
	/*%C Capture interruption register CC0IC			  */
	/*%CCC0IR = 0 ,CC0IE = 0; ILVL  = 14 ,GLVL = 1 ==> PEC canal 1		 */
	CC0IC = 0x39;
	T1R = 1; /*%C  timer 1 starting  							 */
	CC0IE = 1; /*%C capture interruption allowed				*/

	/*%C	Init interruption XIR0SEL (bit7)	 */
		//XIR0SEL = 0x8000;

	
		// Configuration des ports P8.7 & P8.6 
		// P8.7 Output,Hight level,push/pull
		// P8.6 Input 
		XS1PORT = 0x18; 
		// registre d'interruption sur émission 
		/*%IR = 0 ,IE = 0; ILVL  = 13 ,GLVL = 1 	 */
		XP0IC = 0x35; 



		// registre de configuration de la liaison série SS0
			// S0M asynchrone  8bits sans parité  = 001
			// S0STP 1 bit de stop = 0
			// S0REN Réception autorisée = 1
			// S0PEN Test de parité en reception  non autorisée = 0
			// S0FEN Test de reception du stop non autrisé = 0
			// S0OEN Test d'ecrassement des data en réception  non autorisé = 0
			// S0PE  Flag d'erreur de parité = 0
			// S0FE 	Flag d'erreur sur stop	 = 0
			// S0OE  Flag d'écrasemement = 0
			// S0ODD parité paire = 0
			// S0BRS mode de calcul du baud rate  = 0
			// S0LB Loop back mode non autorisé = 0
			// S0R générateur de baud rate activé = 1
			// ==> S0CON = 100000000000001  = 0x8011;
		//XS1CON =  0x8011;
		//Activation de l'interruption de reception sur XP0INT
		//XIR0SEL |= 0x8000;
		// registre de générateur de baudrate = 0x81 pour 9600 baud
		//	XS1BG =(UWORD16) ((UWORD32)FCPU * (UWORD32)1E6) / ((UWORD32)32 *(UWORD32)9600) - 1;

		//XS1BG = 129; 
		
		
		
		

 	//Initialisation des drivers EEPROM ,RTC et du bus SPI
	SSCCON = 0x0000;		/*%C Unactivation of SPI										 */
/*%C	Init of Chanels level SCLK et TSR  on SPI  bus	 */
	SPI_PORT |= 0x2200;    
	DRV_OutputPort(CE_EEP, 1); /*%C Desactivation chip enable EEPROM */
	DRV_OutputPort(CE_RTC1, 0); /*%C Desactivation chip enable RTC																*/
	SSCTIC = 0x0000;     /*%C interruption unactive													 */
	SSCRIC = 0x0000;     /*%C interruption unactive													 */
	SSCCON = 0xC057;     /*%C activation SPI & configuration into mode master full duplex */
	DRV_RTC_Status = DRV_RTC_NO_ERROR;


/*%C unactivation SPI		  */
	SSCCON = 0x0000;
// prépositionement des niveaux des lignes SCLK et TSR  sur le bus SPI 	  
	SPI_PORT |= 0x2200;    
	DRV_OutputPort(CE_RTC1, 0); /*%C Desactivation chip enable RTC																*/
	DRV_OutputPort(CE_EEP, 1); /*%C Desactivation chip enable EEPROM */
	SSCTIC = 0x0000;     /*%C interruption unactive														*/
	SSCRIC = 0x0000;     /*%C interruption unactive														*/
	SSCCON = 0xC057;     /*%C activation SPI & configuration into: mode master full duplex	*/
/*%CConfiguration of the bus speed SPI 1.8Mhz															*/
	SSCBR = 0x000A;	
	DRV_EEP_CounterTimeOutWrite =0;
	DRV_EEP_WriteStatus = DRV_EEP_NO_ERROR;
/*%CInit sequence of the status registrer of EEPROM						*/
/*%CUnlock of memory																			*/
	DRV_EEP_tempo_CE();
	DRV_OutputPort(CE_EEP, 0); /*%C Activation chip enable EEPROM */
	SSCTB  = 0x0006;    			/*%C sending instruction activating the writing             */   	
	DRV_EEP_WaitEndTransmit();	/*%C  waiting end of transmission on  SPI					*/
	DRV_OutputPort(CE_EEP, 1); /*%C Desactivation chip enable EEPROM */
 	DRV_EEP_tempo_CE();			/*%C Time out for unactivation of chip select							*/
	DRV_OutputPort(CE_EEP, 0); /*%C Activation chip enable EEPROM */
	SSCTB  = 0x0001;    			/*%C send to status register the mode writing               */ 	
	DRV_EEP_WaitEndTransmit();	/*%C  waiting end of transmission on  SPI					*/
	SSCTB = 0x0000;				/*%C eraze of WPEN,BP1,BP0,	Unlock of memory			*/
	DRV_EEP_WaitEndTransmit();	/*%C  waiting end of transmission on  SPI					*/
	DRV_OutputPort(CE_EEP, 1); /*%C Desactivation chip enable EEPROM */
 	DRV_EEP_tempo_CE();			/*%C Time out for unactivation of the chip select							*/
	DRV_OutputPort(CE_EEP, 0); /*%C Activation chip enable EEPROM */
	SSCTB   = 0x0004;         	/*%C sending of the instruction WRDI disable write					*/
	DRV_EEP_WaitEndTransmit();	/*%C  waiting end of transmission on  SPI					*/
	DRV_OutputPort(CE_EEP, 1); /*%C Desactivation chip enable EEPROM */
	DRV_EEP_tempo_CE();			/*%C Time out for unactivation of chip select							*/
/*%C Waiting freeing of the eeprom																		*/
	do
		{
		DRV_OutputPort(CE_EEP, 0); /*%C Activation chip enable EEPROM */
	 	SSCTB  = 0x0005;          		  	/*%C Envoi de l'instruction RDSR lecture du status de l'eeprom				 */
	 	DRV_EEP_WaitEndTransmit();			/*%C  waiting end of transmission on  SPI									 */
		SSCTB  = 0x0000;	        			/*%C generation horloge SCLK_SPI_CPU pour la lecture du status EEPROM			 */
		DRV_EEP_WaitEndTransmit();			/*%C  waiting end of transmission on  SPI									 */
		DRV_OutputPort(CE_EEP, 1); /*%C Desactivation chip enable EEPROM */
		DRV_EEP_tempo_CE();		    		/*%C tempo Chip select disable														 */
		}
  	while ((SSCRB & 0x0001) != 0x00);


  
/*******************************************************************************/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! Do not Modify it, it is an EEPROM check !!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*******************************************************************************/


/*%c Reading of tthe EEPROM to perform self test and to transfert data */
///*%c through the RS232 */
		for (EepromAddress = 0;EepromAddress < COM_EEPROM_BUFFER_SIZE;EepromAddress++)
		{
//Lecture de l'eeprom avant modification pour transfer via la RS232 		
			EepromData[EepromAddress] = DRV_EEP_ReadWord(2*EepromAddress);
			It_watchdog();
		}
		for(EepromAddress = 0;EepromAddress<(UWORD16)((UWORD32)&End_Of_Database - BEGIN_RAM_ADRESS_OF_EEP_DATA);EepromAddress+=2)
		{
			if(EepromData[EepromAddress]!= ~EepromData[EepromAddress + 1])
			{
				EepromErrorCounter = EepromErrorCounter + 1;

			}
			It_watchdog();
		}

		if(EepromErrorCounter>0)
		{
/*%C Block the execution if the EEPROM is corrupted */
			MAIN_CrcEepromTrouble = TRUE;

		  /*********************************************/
/* If there is a trouble, we send all the Eeprom data via the RS232 com */			
			S0CON =  0x8017;
/*%C  Baudrate generator register	 */
/*%C  (UWORD16)((400000UL / (32UL * Speed_Com / 100)) - 1)	*/
			S0BG = 10;	   			  			
			
			for (EepromAddress = 0;EepromAddress < COM_EEPROM_BUFFER_SIZE;EepromAddress++)
			{
				S0TBIR = 0;
				S0TBUF = (UBYTE)(EepromData[EepromAddress]>>8);

				while(S0TBIR==0);
				S0TBIR = 0;
				S0TBUF = (UBYTE)(EepromData[EepromAddress]& 0xFF);
				while(S0TBIR==0);
				It_watchdog();
			}
		  /*********************************************/
		} 


 /********************   End of EEPROM self test  ****************************/
/******************************************************************************/


/********************************************************************************/

  	// ATTENTION: 	

	// l'activation de cette fonction lance certains drivers
	// Vérifier qu'à cet instant tous les drivers sont initialisés
	// Init Interrupt6 - 1ms
	//	InitInterruptT6();
	// Registre de controle du timer T6
		// Prédiviseur = 4 T6I = 000 horloge à 100ns pour un ST269 à 40Mhz
		// Mode timer 	   T6M = 000
		// Timer en marche T6R = 1
		// Direction "décomptage" sans tenir compte de l'entrée T6 T6EUD = 001
		// Contrôle de la sortie T6OUT P31 	non utilisée.T6OE = 0
		// latch de la sortie T6OL = 0
		// Bit 11 12  13 non utilisés = 000
		// Controle du mode reload Reload à partir de CAPREL	 T6SR = 1
 		// T6CON = 1 000 0 0 001 1 000 000 = 1000000011000000b = 0x80C0
 	T6CON = 0x80C0;
	// Registre de reload CAPREL 
		/*%C CAPREL = 1ms/100nS = */
 	CAPREL= 10000;

	// Registre de contrôle de l'interruption
		/*%C IR = 0 ,IE = 1; ILVL  = 13 ,GLVL = 3 	 */
	T6IC = 0x77;

/******************************************************************************/
/*	Update DB Power Supply 																		*/
/******************************************************************************/

	/*%C Delay of 378 ms to let SPI Power Base Reload */
	/*%C Neccessary time to extract 3 frame */
 	TIM_Temporize(378000); 

	/*%C Update PowerSupply DataBase in reading buffer */
	do
	{ 
		DRV_SPIPowerSupplyUpdate();
		TIM_Temporize(1000);
		TimerIncrement = TimerIncrement + 1 ;
	}
	/*%C Exit when DB is updating or on 5s time out */
	while((PowerSupplyFrame != TRUE) && (TimerIncrement < 5000));



/******************************************************************************/
/*	Initialisation de la base de donnée														*/
/******************************************************************************/

	//Initialisation de la base de donnée
	DB_StartInitDb();

	// Initialisation du driver Buzzer (la base doit être initialisée)
	DRV_BuzInit();	

 		/**************************************************/
 		/**************************************************/

	// Initialisation du convertisseur analogique numérique
	DRV_ADC_ConvertInit();

 		/**************************************************/

}
else
{
// Initialisation de la com RS232 aprés la lecture de la base pour 
//disponibilité de SPEEDCOM
// configuration des patte de  port P3.10(TXD)  P3.11(RXD)
 
	SPI_PORT |= 0x0400;  // TXD = 1;

	// registre d'interruption sur émission
		/*%IR = 0 ,IE = 0; ILVL  = 14 ,GLVL = 2 ==> PEC canal 2		 */
		S0TBIC = 0x3A;


		// registre d'interruption sur reception 
		/*%IR = 0 ,IE = 1; ILVL  = 15 ,GLVL = 1 ==> PEC canal 5		 */
		S0RIC = 0x7D;  



// registre de configuration de la liaison série SS0
	// S0M asynchrone  8bits + parité  = 111
	// S0STP 1 bit de stop = 0
	// S0REN Réception autorisée = 1
	// S0PEN Test de parité en reception  non autorisée = 0
	// S0FEN Test de reception du stop non autrisé = 0
	// S0OEN Test d'ecrassement des data en réception  non autorisé = 0
	// S0PE  Flag d'erreur de parité = 0
	// S0FE 	Flag d'erreur sur stop	 = 0
	// S0OE  Flag d'écrasemement = 0
	// S0ODD parité paire = 0
	// S0BRS mode de calcul du baud rate  = 0
	// S0LB Loop back mode non autorisé = 0
	// S0R générateur de baud rate activé = 1
	// ==> S0CON = 100000000000111  = 0x8017;
	S0CON =  0x8017;
	
	/*%C  Baudrate generator register	 */
	/*%C  (UWORD16)((400000UL / (32UL * Speed_Com / 100)) - 1)	*/
	S0BG = 10;	   			  			
   
   	DRV_COM_End_of_Transmit = TRUE;
	Communication_State = COM_TRANSMIT_STOP; 


}

}
