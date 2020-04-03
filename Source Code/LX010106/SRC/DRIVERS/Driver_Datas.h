/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Driver_Datas.h                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    Global variables of "DRIVER"                          */
/*                                                                            */
/******************************************************************************/
/*%I  Input Parameter : NONE                                                  */
/*%IO Input/Output Parameter : NONE                                           */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/
/************************************************************************/
/*                        CONSTANT DECLARATION	                        */
/************************************************************************/
#define NB_SOUND 					11
#define SEQUENCE_MAX 			  	60
#define SEQUENCE_FAST 				SEQUENCE_MAX
#define SEQUENCE_SLOW 				6
#define SEQUENCE_VERY_SLOW			4
#define SEQUENCE_BATT				2
#define SEQUENCE_STOP_BIP			4
#define SEQUENCE_START_BIP			2
#define SEQUENCE_BIP_SHORT			3
#define SEQUENCE_BIP_LONG			2
#define SEQUENCE_BIP_VERY_LONG	3
#define SEQUENCE_USB_CONNECT		5
#define SEQUENCE_USB_DISCONNECT	5

/* Buzzer Low voltage level threshold to the power on test*/
#define BUZZER_LOW_VOLTAGE_THRESHOLD_POWER_ON	600//mV 
/* Buzzer Low voltage level threshold to alarm detection*/
#define BUZZER_LOW_VOLTAGE_THRESHOLD			400//mV						
/* Buzzer Low voltage level thresholds to alarm detection*/
#define COEF_SLOPE								200
#define COEF_OFFSET								0
#define PERCENT_LEVEL_THRESHOLD					88 //%
/* Hysteresis voltage */
#define HYSTERESIS_BUZZER_VOLTAGE				10//mV
#define HYSTERESIS_BATTERY_BUZZER_VOLTAGE		100//mV

/* Battery Buzzer Low voltage level threshold */
#define BATTERY_BUZZER_LOW_VOLTAGE_THRESHOLD	4800 //mV	
/* Short circuit battery Buzzer voltage level threshold */
#define BATTERY_BUZZER_CC_THRESHOLD				3000 //mV	
#define END_BATTERY_BUZZER_CC_THRESHOLD			4600 //mV	
/* Open circuit battery Buzzer voltage swing level threshold */
#define BATTERY_BUZZER_CO_SWING					1000 //mV
/* Battery voltage divider R24 - R25 - R59*/
/*Le Hard divise la tension batterie par 2 */	
#define BATTERY_VOLTAGE_DIVIDER					20

/* PWM3 sound level setting (rate Hz)*/
#define FREQUENCY_SOUND_LEVEL	120000

		 
/* Buzzer rate in Hz */
/* compliant wth 60601-1-1-8 specifically the 4 harmonic requirements */
#define COMPLIANT_FREQUENCY_BUZZER 		805
/* classic alarm tone that is a bit louder than the compliant frequency
   due to the nature of the part (sweet spot close to value chosen) */
#define CLASSIC_FREQUENCY_BUZZER 		960

#define SKIP 0xdead
#define RAMP_TIME  23  // 11ms plus 12ms offset.

#define TAILLE_BUFFER 10

#ifdef DECLARATION_DRIVER_DATAS

   #ifndef DRIVER_DATAS_H
   #define DRIVER_DATAS_H

///
///  WARNING when modifying table ensure the timers that lock
///  out how long the sound is made is also modified
///  Update timers to be consistent in Timer_Data.h
///  
//  all tones must begin with active sound duration then followed by inactive sound duration 
//  
/* Buzzer burst command (time in ms)   */
const UWORD32 cDRV_IHM_SIGNAL_BUZ[NB_SOUND][SEQUENCE_MAX]=
{
/* Short bip command (one bip during 200ms) 		*/
 {200, 1000, 0,   0,  0,  0,  0,  0,   0,   0,   0,  0,   0,  0,   0,
    0,   0,   0,  0,  0},  
/* Long bip command (one bip during 600ms) 		*/
 {600, 1000, 0,   0,   0,  0,   0,  0,   0,   0,   0,  0,   0,  0,   0,
    0,   0,   0,  0,  0},
/* Very Long bip command (one bip during 3000ms) 		*/
  {2500, 1500, 0,   0,   0,  0,   0,  0,   0,   0,   0,  0,   0,  0,   0,
    0,   0,   0,  0,  0},   
/* Start bip command (one bip during 200ms, stopped by NO_SOUND command) 		*/
 { 200, 1500, 0,   0,   0,  0,   0,   0,   0,   0,  0,   0,  0,   0,
    0,   0,   0,  0,   0,  0},  
/* Stop Bip command (two bip of 200ms, stopped by NO_SOUND command)				*/
 { 200, 150, 200,  1500,   0,  0,   0,  0,   0,   0,  0,   0,  0,   0,
    0,   0,   0,    0,   0,   0},  
/* Battery buzzer burst command (one bip each 5 minutes)*/
 {200, 300000, 0,   0,   0,  0,   0,  0,   0,   0,   0,  0,   0,  0,   0,
    0,   0,   0,    0,   0},
 //
 // The low, medium and High priority alarms use two ramp and skip logic
 // to perform 1 ramp; this elimnates the creation of a spike before 
 // the sound is made;  the addition of the skips at the end of the 
 // tone allow for the sound to be turned off and treated properly
 //
/* Low priority buzzer burst command (one bip and silence for 30 sec)*/
   {RAMP_TIME, SKIP, RAMP_TIME, SKIP, 150, 30000, 
    SKIP     , SKIP,      SKIP, SKIP, SKIP, SKIP,
    SKIP     , SKIP,      SKIP, SKIP, SKIP, SKIP,
    SKIP     , SKIP,      SKIP, SKIP, SKIP, SKIP,
    SKIP     , SKIP,      SKIP, SKIP, SKIP, SKIP,
    SKIP     , SKIP,      SKIP, SKIP, SKIP, SKIP,
    SKIP     , SKIP,      SKIP, SKIP, SKIP, SKIP,
    SKIP     , SKIP,      SKIP, SKIP, SKIP, SKIP,
    SKIP     , SKIP,      SKIP, SKIP, SKIP, SKIP,
    SKIP     , SKIP,      SKIP, SKIP, SKIP, SKIP},

/* Medium priority buzzer burst command (three bips and 7.5 sec of silence)*/
   {RAMP_TIME, SKIP, RAMP_TIME, SKIP, 145, 150, 
    RAMP_TIME, SKIP, RAMP_TIME, SKIP, 145, 150, 
    RAMP_TIME, SKIP, RAMP_TIME, SKIP, 145,  7500,   
    SKIP     , SKIP,      SKIP, SKIP, SKIP, SKIP,
    SKIP     , SKIP,      SKIP, SKIP, SKIP, SKIP,
    SKIP     , SKIP,      SKIP, SKIP, SKIP, SKIP,
    SKIP     , SKIP,      SKIP, SKIP, SKIP, SKIP,
    SKIP     , SKIP,      SKIP, SKIP, SKIP, SKIP,
    SKIP     , SKIP,      SKIP, SKIP, SKIP, SKIP,
    SKIP     , SKIP,      SKIP, SKIP, SKIP, SKIP},
/* High priority buzzer burst command (10 bips and 2.6 seconds of silence) */
 {  RAMP_TIME, SKIP, RAMP_TIME, SKIP, 140,  60,  
     RAMP_TIME, SKIP, RAMP_TIME, SKIP,140,  60, 
     RAMP_TIME, SKIP, RAMP_TIME, SKIP,140,  280,  
     RAMP_TIME, SKIP, RAMP_TIME, SKIP,140, 60, 
     RAMP_TIME, SKIP, RAMP_TIME, SKIP,140, 750, 
     RAMP_TIME, SKIP, RAMP_TIME, SKIP,140, 60, 
     RAMP_TIME, SKIP, RAMP_TIME, SKIP,140, 60, 
     RAMP_TIME, SKIP, RAMP_TIME, SKIP,140, 280, 
     RAMP_TIME, SKIP, RAMP_TIME, SKIP, 140, 60, 
     RAMP_TIME, SKIP, RAMP_TIME, SKIP,140, 2600},
/* Connect Usb Key secance buzz */
 {200, 100, 200,   100,  200,  0,  0,  0,   0,   0,   0,  0,   0,  0,   0,
    0,   0,   0,  0,  0},  
/* DisConnect Usb Key secance buzz */
 {200, 100, 200,   100,  200,  0,  0,  0,   0,   0,   0,  0,   0,  0,   0,
    0,   0,   0,  0,  0}
};

  
/******************************************************************************/
/*                      VARIABLES DECLARATION     	                        	*/
/******************************************************************************/
t_AD_Digit AD_Digit;
volatile UWORD16 DRV_Acquisition_Disponible = FALSE ;
/*  Turn counter for buzzer command */
volatile UWORD32 CounterOfTurn = 0;
volatile UWORD32  NumberOfTurn;
volatile UWORD32  LastLoad;	
volatile e_BOOL EndOfOverflow = FALSE;
volatile e_BOOL StartOfOverflow = FALSE;
volatile UWORD16 Id_StatusSignal = 0; 
volatile e_TYPE_SOUND SoundActive = NO_SOUND;
volatile e_BOOL Active = FALSE;
volatile UWORD16 rampdex = 0;

/* Orange and leds command declaration */
volatile e_BOOL Id_Led_Orange = FALSE; 
volatile e_BOOL Id_Led_Red = FALSE; 
volatile e_BOOL Id_Led_White = FALSE;
volatile e_BOOL Led_White_On = FALSE;
volatile UBYTE CounterBlink = 0; 

/*%C tableau des captures du timer 1 sur front du signal du capteur 	  */
/*%C		de mesure de la vitesse de la turbine								  */
volatile UWORD32 Timer1Measure[2];
volatile UBYTE CaptureNumber = 0; 
volatile UBYTE   Cpt_Timer1_Overflow = 0;  
/*%C Mesure de la vitesse disponible (Oui Non)								  */
volatile UWORD16 AvailableSpeedBlowerDigit = FALSE;
volatile UWORD32 SpeedBlowerDigit = 0;

/*%C Retrieval events  - Events buffer	*/

volatile UBYTE EventEnvironment[TAILLE_BUFFER][End_Of_Table_Events];


 
UWORD16 ALARM_CheckBuzzerFlag = FALSE;
UWORD16 ALARM_CheckRemoteFlag = FALSE;
 
SWORD32 TemperatureValue = 0;
   #endif
#else
   #ifndef DRIVER_DATAS_H
   #define DRIVER_DATAS_H

/************************************************************************/
/*             EXTERNAL CONSTANT DECLARATION	                           */
/************************************************************************/
/* Buzzer burst command (time in ms)   */
extern const UWORD32 cDRV_IHM_SIGNAL_BUZ[NB_SOUND][SEQUENCE_MAX];
extern volatile e_TYPE_SOUND SoundActive ;
/******************************************************************************/
/*           EXTERNAL VARIABLES DECLARATION     	                        	*/
/******************************************************************************/
extern t_AD_Digit AD_Digit;
extern volatile UWORD16 DRV_Acquisition_Disponible ;
/*  Turn counter for buzzer command */
extern volatile UWORD32 CounterOfTurn;
extern volatile UWORD32 NumberOfTurn;
extern volatile UWORD32 LastLoad;	 
extern volatile e_BOOL EndOfOverflow;
extern volatile e_BOOL StartOfOverflow;
extern volatile UWORD16 Id_StatusSignal; 
extern volatile e_BOOL Active;
extern volatile UWORD16 rampdex;

/* Orange and leds command declaration */
extern volatile e_BOOL Id_Led_Orange; 
extern volatile e_BOOL Id_Led_Red; 
extern volatile e_BOOL Id_Led_White;
extern volatile e_BOOL Led_White_On; 
extern volatile UBYTE CounterBlink; 

extern volatile UWORD32 Timer1Measure[];
extern volatile UBYTE CaptureNumber; 
extern volatile UBYTE   Cpt_Timer1_Overflow ;
extern volatile UWORD16 AvailableSpeedBlowerDigit;
extern volatile UWORD32 SpeedBlowerDigit;


/*%C Retrieval events  - Events buffer	*/

extern UBYTE EventEnvironment[TAILLE_BUFFER][End_Of_Table_Events];
extern UWORD16 ALARM_CheckBuzzerFlag;
extern UWORD16 ALARM_CheckRemoteFlag;
extern SWORD32 TemperatureValue ;


		
   #endif
#endif