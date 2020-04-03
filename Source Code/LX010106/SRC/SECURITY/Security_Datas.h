/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Security_Datas.h                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            									                                    */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

// ISO 80601-2-72 allows maximum pressure settings to be 90 cmH2O
#define cHIGH_PRESSURE 900

#ifdef DECLARATION_SECURITY_DATAS
#ifndef SECURITY_DATAS_H
#define SECURITY_DATAS_H
/************************************************************************/
/*                    VARIABLE DECLARATION       			             	*/
/************************************************************************/

/*e_VentilState VentilState;		  */
/*e_VentilState MemoState;		*/
/* registres de Priorité des différentes alarmes ( Buzz & leds)		 */
/* 1 bit correspond à une alame										 */
/* 1 registre Haute priorité										 */
/* 2 registres Moyenne priorité										 */
/* 1 registre basse priorité										 */

UWORD16 SEC_High_Priority_1= 0x0000; 
/*Bit 0  Disconnection												 */
/*Bit 1  High Pressure												 */
/*Bit 2  High VTI													 */
/*Bit 3  Low battery												 */
/*Bit 4  End of battery												 */
/*Bit 5  Check pressure												 */
/*Bit 6  No Valve													 */
/*Bit 7  Check Valve												 */
/*Bit 8  Check Volume												 */
/*Bit 9  Keyboard anomaly										     */
/*Bit 10 Supply Measure 										     */
/*Bit 11 Turbine Overheat 										     */
/*Bit 12 Occlusion		 										     */
/*Bit 13 CPU reference		 										 */

UWORD16 SEC_High_Priority_2 = 0x0000; 
/*Bit 0  Buzzer Battery Failure								  		*/
/*Bit 1  Buzzer Battery Charge Failure								*/
/*Bit 2	 Leak Occlusion                                              */
/*Bit 3  No Fio2 Sensor												  */
/*Bit 4  Inspiration Flow Default 			*/
/*Bit 5   */
/*Bit 6   */
/*Bit 7   */
/*Bit 8   Connecter valve changer Pi Pe*/
/*Bit 9   Retirer valve changer Pi Pe*/
/*Bit 10  Utiliser valve*/
/*Bit 11  Retirer Valve*/
/*Bit 12  Check Valve Pressure*/
/*Bit 13  Voluntary Stop*/
 
UWORD16 SEC_High_Priority_3 = 0x0000; 
/*Bit 0  Check FIO2								  		*/
/*Bit 1  Leakage*/
/*Bit 2	 */
/*Bit 3  */
/*Bit 4  */
/*Bit 5  */
/*Bit 6   */
/*Bit 7   */
/*Bit 8   */
/*Bit 9   */
/*Bit 10  */
/*Bit 11  */
/*Bit 12  */
/*Bit 13  */

UWORD16 SEC_Medium_Priority_1 = 0x0000;
/*Bit 0  Apnéa														 */
/*Bit 1  Low VTI													 */
/*Bit 2  Low VTE													 */
/*Bit 3 */
/*Bit 4   */
/*Bit 5  Free												 */
/*Bit 6  High Rate													 */
/*Bit 7  AC Power fail												 */
/*Bit 8  DC power fail												 */
/*Bit 9  Check supply												 */
/*Bit 10 Check battery												 */
/*Bit 11 No battery													 */
/*Bit 12 Check buzzer												 */
/*Bit 13 technical problem											 */
/*Bit 14 Reserved      												 */
/*Bit 15 reversed I:E												 */

																	 
UWORD16 SEC_Medium_Priority_2 = 0x0000;
/*Bit 0  Check proximal												 */
/*Bit 1  Proxi deconnection										     */
/*Bit 2  No proximal											     */
/*Bit 3  Valve leakage												 */
/*Bit 4  Check remote alarm										     */						
/*Bit 5  Unknown battery											 */						
/*Bit 6  Check Battery Charge										 */
/*Bit 7  High Vte												     */
/*Bit 8  Calibration failure										 */
/*Bit 9  Cooling fan failure                              */
/*Bit 10 Ambient temperature out of bounds                */
/*Bit 11 Battery temperature out of bounds                */
/*Bit 12 ALARM_EEPROM_LOOSING_PARAM_U16 */
/*Bit 13 ALARM_EEPROM_OUT_OF_RANGE_U16 */
/*Bit 14 ALARM_NEW_VERSION_U16 */
/*Bit 15 ALARM_ERROR_VERSION_U16 */

UWORD16 SEC_Medium_Priority_3 = 0x0000;
/*Bit 0  24V Failure    											 */
/*Bit 1  */
/*Bit 2  */
/*Bit 3  */
/*Bit 4  */						
/*Bit 5  */						
/*Bit 6  Low Fio2*/
/*Bit 7  High Fio2*/
/*Bit 8  Breath Time Cycled*/
/*Bit 9  Low Mandatory Rate*/
/*Bit 10 Low Buzzer battery voltage*/
/*Bit 11 Needed fio2 calibration*/
/*Bit 12 */
/*Bit 13 */
/*Bit 14 */
/*Bit 15 */

UWORD16 SEC_Low_Priority = 0x0000;
/*Bit 0  Battery periodical signal*/
/*Bit 1  AC Power fail            */
/*Bit 2  DC Power fail            */
/*Bit 3  Low Battery when AC is connected*/
/*Bit 4  Empty Battery when AC is connected */
/*Bit 5 */
/*Bit 6 */
/*Bit 7 */
/*Bit 8 */
/*Bit 9 */
/*Bit 10*/
/*Bit 11*/
/*Bit 12*/
/*Bit 13*/
/*Bit 14*/
/*Bit 15*/

/* End speed test flag*/
UWORD16 SEC_SpeedTestEnded = FALSE;

#endif
#else
#ifndef SECURITY_DATAS_H
#define SECURITY_DATAS_H    

/************************************************************************/
/*                   EXTERNAL VARIABLE DECLARATION                    	*/
/************************************************************************/

/*extern e_VentilState VentilState;	 */
/*extern e_VentilState MemoState;  */
/* registres de Priorité des différentes alarmes ( Buzz & leds)		 */
/* 1 bit correspond à une alame										 */
/* 1 registre Haute priorité										 */
/* 2 registres Moyenne priorité										 */
/* 1 registre basse priorité										 */

extern UWORD16 SEC_High_Priority_1;
/*Bit 0  Disconnection												 */
/*Bit 1  High Pressure												 */
/*Bit 2  High VTI													 */
/*Bit 3  Low battery													 */
/*Bit 4  End of battery												 */
/*Bit 5  Check pressure												 */
/*Bit 6  No Valve													 */
/*Bit 7  Check Valve													 */
/*Bit 8  Check Volume												 */
/*Bit 9  Keyboard anomaly										 */
/*Bit 10 Supply Measure 										 */
/*Bit 11 Turbine Overheat 										 */
/*Bit 12 Occlusion		 										 */
/*Bit 13 CPU reference											  */


extern UWORD16 SEC_High_Priority_2; 
/*Bit 0  Buzzer Battery Failure								  		*/
/*Bit 1  Buzzer Battery Charge Failure								*/
/*Bit 2	 Leak Occlusion                                              */
/*Bit 3  No Fio2 Sensor												  */
/*Bit 4  Inspiration Flow Default 			*/
/*Bit 5   */
/*Bit 6   */
/*Bit 7   */
/*Bit 8   Connecter valve changer Pi Pe*/
/*Bit 9   Retirer valve changer Pi Pe*/
/*Bit 10  Utiliser valve*/
/*Bit 11  Retirer Valve*/
/*Bit 12  Check Valve Pressure*/
/*Bit 13  Voluntary Stop*/
	 						
extern UWORD16 SEC_High_Priority_3; 
/*Bit 0  Check FIO2								  		*/
/*Bit 1  */
/*Bit 2	 */
/*Bit 3  */
/*Bit 4  */
/*Bit 5  */
/*Bit 6   */
/*Bit 7   */
/*Bit 8   */
/*Bit 9   */
/*Bit 10  */
/*Bit 11  */
/*Bit 12  */
/*Bit 13  */
				
extern UWORD16 SEC_Medium_Priority_1;
/*Bit 0  Apnéa														 */
/*Bit 1  Low VTI													 */
/*Bit 2  Low VTE													 */
/*Bit 3  High VM													 */
/*Bit 4  low VM														 */
/*Bit 5  Low Rate													 */
/*Bit 6  High Rate													 */
/*Bit 7  AC Power fail												 */
/*Bit 8  DC power fail												 */
/*Bit 9  Check supply												 */
/*Bit 10 Check battery												 */
/*Bit 11 No battery													 */
/*Bit 12 Check buzzer												 */
/*Bit 13 technical problem											 */
/*Bit 14 Check Settings												 */
/*Bit 15 reversed I:E												 */
																	 
extern UWORD16 SEC_Medium_Priority_2;
/*Bit 0 Check proximal												 */
/*Bit 1 Proxi deconnection											 */
/*Bit 2 No proximal													 */
/*Bit 3 Valve leakage												 */
/*Bit 4 Check remote alarm											 */						
/*Bit 5 Unknown battery												 */						
/*Bit 6 Check Battery Charge										 */
/*Bit 7 High Vte														 */
/*Bit 8  Calibration failure										 */
/*Bit 9  Cooling fan failure                              */
/*Bit 10 Ambient temperature out of bounds                */
/*Bit 11 Battery temperature out of bounds                */
/*Bit 12 ALARM_EEPROM_LOOSING_PARAM_U16 */
/*Bit 13 ALARM_EEPROM_OUT_OF_RANGE_U16 */
/*Bit 14 ALARM_NEW_VERSION_U16 */
/*Bit 15 ALARM_ERROR_VERSION_U16 */

extern UWORD16 SEC_Medium_Priority_3;
/*Bit 0  24V Failure    											 */
/*Bit 1  Connecter valve changer Pi Pe*/
/*Bit 2  Retirer valve changer Pi Pe*/
/*Bit 3  Utiliser valve*/
/*Bit 4  Retirer Valve*/						
/*Bit 5  Leakage*/						
/*Bit 6  Low Fio2*/
/*Bit 7  High Fio2*/
/*Bit 8  */
/*Bit 9  */
/*Bit 10 */
/*Bit 11 Needed fio2 calibration*/
/*Bit 12 */
/*Bit 13 */
/*Bit 14 */
/*Bit 15 */

extern UWORD16 SEC_Low_Priority;
/*Bit 0  Battery periodical signal*/
/*Bit 1 */
/*Bit 2 */
/*Bit 3 */
/*Bit 4 */
/*Bit 5 */
/*Bit 6 */
/*Bit 7 */
/*Bit 8 */
/*Bit 9 */
/*Bit 10*/
/*Bit 11*/
/*Bit 12*/
/*Bit 13*/
/*Bit 14*/
/*Bit 15*/

extern UWORD16 SEC_SpeedTestEnded;

/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                    */
/************************************************************************/
/* Lancement de la securité	*/
extern void SEC_Launch (void);
/* Lancement de l'init du module security	  */
extern void SEC_Init(void);


#endif

/************************************************************************/
/*                    CONSTANT DECLARATION                           	*/
/************************************************************************/
#define cVERY_NEGATIVE -100
/* Delta de variation pour débit constant */
#define cDELTA_FLOW_LMN  40	
/* Pressure declaration */
#define cTHIRTY_PRESSURE_THRESHOLD 300U
/* Apnea time min */
#define cApneaTimeMin 17000


#endif
