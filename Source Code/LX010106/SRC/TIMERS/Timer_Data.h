/******************************************************************************/
/*                                                                            */
/* Project N  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Timer_Data.h                                                 	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    Global variables of "TIMER"                          */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*                                                                            */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/
#ifndef TIMER_DATA_H
#define TIMER_DATA_H

#define PERIOD_OF_TIM_LAUNCH_CALL 10 

/************************************************************************/
/*            Tag timer definition in ms                                */
/************************************************************************/

/* Tag counter < 60s  */
/*%C Time USB Initialize */
#define TIME_WAIT_USB_BUSY_AFTER_RESET			10000	//ms
#define TIME_WAIT_USB_BUSY_LONG_COMMAND			30000	//ms
#define TIME_WAIT_USB_BUSY_VERY_LONG_COMMAND	300000	//ms (5min)
#define TIME_USB_WAIT_READ_FIFO 				1000	//ms
												
#define TIME_USB_CONNECT_DISCONNECT_KEY			500
/*%C Time USB to open a file */
#define TIME_RECORDING_MONIT				40

#define TIME_WAIT_DISPLAY_BATTERY_GAUGE	15000	//ms

#define TIME_OUT_ACK_RETRIEVAL			500
/* Time out of speed measure between 2 pulse */
#define TIME_OUT_SPEED						200 		
/* Max time for auto-calibration of one exhalation flow sensor point */
#define TIME_OUT_CALIB						20000
/* Do not put a value under the average time of the digitalized values */
/* (80*5ms) */
/* Pressure stabilization time for FAS valve calibration */
#define TIME_FAS_VALVE_EXTREMES_CALIB	3000
/* Valve current stabilization time for FAS valve calibration */
#define TIME_FAS_VALVE_CURRENT_CALIB	27720
/* Flow stabilization time to ensure auto calibration*/
#define TIME_AUTO_CALIB						5000		
/* Low pressure delay */
#define TIME_LOW_PRESS						15000		
/* High pressure low delay */
#define TIME_SEC_HIGH_LEVEL_PEP_SHORT	45000		
/* DC loss delay */
#define TIME_FAIL_DC							5000		
/* AC loss delay */
#define TIME_FAIL_AC							5000		
#define TIME_FAIL_AC_VENTIL				3000		
/* Keyboard failure delay */
#define TIME_KEYBOARD						20000		
/* Speed blower default delay; worst case scenario for blower test was measured at
   1.5 seconds; using 3 seconds will gives us twice the margin */
#define TIME_SPEED_BLOW						3000		
/* Valv detection delay */
#define TIME_VALVE							800	
/* Power commutation delay during init */
#define TIME_WAIT_STARTING					1500		
/* Very low battery level detection delay */
#define TIME_BAT_VERY_LOW_LEVEL			100		
/* Low battery level detection delay */
#define TIME_BAT_LOW_LEVEL					100		
#define TIME_ANO_KEYB						45000
/* Power type detection delay */
#define TIME_SUPPLY_CHANGE					500	
/* Battery Buzzer voltage etablishment delay */
#define TIME_INT_MEASURE_BUZZER					100 //ms
#define TIME_DETECTION_BATTERY_FAILURE_CO_BUZ	1000 //ms
#define TIME_VALIDATION_BATTERY_FAILURE			9000 //ms
#define TIME_BATTERY_FAILURE_CO_BUZ				10000//ms
#define TIME_CANCEL_BATTERY_FAILURE_CO_BUZ	10000 //ms		
#define TIME_BATTERY_FAILURE_CC_BUZ		     	90000//ms
/* Battery Alamr timer */ 
#define TIME_BATTERY_BUZ_READ_LONG              900000     //15 min 
#define TIME_BATTERY_BUZ_READ_MEDIUM			120000	   //2 min
#define TIME_BATTERY_BUZ_READ_SHORT				5000	   //5 s
/* Proximal sensor detection delay */
#define TIME_PRESSURE_CHOICE				400		
#define TIME_PRESSURE_CHOICE_INT			50		
/* Proximal to internal switch delay */
#define TIME_PROXIMAL_TO_INTERNAL_SWITCH 	50		
/* Check Proximal delay to allow the pressure switch */
#define TIME_CHECK_PROXIMAL_FOR_PRESSURE_SWITCH 	50		
/* Check Proximal delay to allow the pressure switch */
#define TIME_CHECK_PRESSURE_FOR_PRESSURE_SWITCH 	400		


/* Check proximal detection delay */
#define TIME_CHECK_PROXI					15000		
/* Check pressure detection delay */
#define TIME_CHECK_PRESSURE            15000		
/* Check battery cancellation delay */
#define TIME_RAZ_CHECK_BAT				   15000		
/* Validation bip delay for menu entry */
#define TIME_BIP_SHORT				      1200		
/* Validation bip valid delay for menu entry */
#define TIME_BIP_SHORT_VALID		      1200		
/* Validation bip delay for menu exit */
#define TIME_BIP_LONG				      1600
/* Start ventilation bip sequence  */
#define TIME_BIP_START_VENTIL	      	1200
/* Stop ventilation bip sequence  */
#define TIME_BIP_STOP_VENTIL	      	1550
#define TIME_BIP_BATT	      			1200
#define TIME_BIP_VERY_LONG				   4600
 

#define TIME_HIGH_PRESSURE_DETECT                   100
#define TIME_HIGH_PRESSURE							100
#define TIME_CPAP_HIGH_PRESSURE						200
#define TIME_HIGH_PRESSURE_ALARM					100
#define TIME_NO_BATTERY								1000
#define TIME_SEC_VALVE_CST							15000
#define TIME_SEC_PROXI_CST							15000
#define TIME_SEC_INT_CST							15000
#define TIME_SEC_CHECK_VALVE						15000
#define TIME_SEC_LEAK_OCCLUSION						15000
#define TIME_VALVE_PRESS							15000
#define TIME_INHIB_CHECK_REMOTE					30000
#define TIME_APNEA									15000
#define TIME_CANCEL_HIGH_PRESSURE				2000 
#define TIME_CHECK_SUPPLY							5000
#define TIME_CHECK_PRESS							15000
#define TIME_CHECK_PROXI							15000
#define TIME_CHECK_REMOTE							1000
#define TIME_BAT_P_S									5000
#define TIME_PROX_DISCONNECTION					17000

// timers used to lock out any tones until alarm is completed playing
// add up time in Driver_Datas.h tones then add some buffer typically 200 ms.
#define TIME_LOW_PRIORITY_BURST				   400
#define TIME_MEDIUM_PRIORITY_BURST				1004
#define TIME_HIGH_PRIORITY_BURST			 	   1910

#define TIME_DOUBLE_PULSE				         3000
#define TIME_MIN_FLOW	         				5000
#define TIME_INHIBITION_ADAPTATION	         5000
#define TIME_DETECT_FIO2							2000		
#define TIME_NO_PROX	         			 		1000
#define TIME_DISCONNECTION_OBSERVATION			14000
#define TIME_CALIB_FIO2					   		45000
#define TIME_SEC_CHECK_VALVE_PRESSURE			15000
#define TIME_LEAKAGE									15000
#define TIME_CHECK_FIO2								15000
#define TIME_LOW_FIO2								45000
#define TIME_HIGH_FIO2								45000
#define TIME_FRAMES_SPI_RECEIVE    		420  //ms correspond à 3.5trames ; une trame = 40bytes * 3ms = 120ms
#define TIME_INHIB_O2    							30000  //ms
#define TIME_CPU_REFERNCE_FAILURE				2000  	//ms
#define TIME_SEC_100_FIO2							60000
#define TIME_BLOWER_OVERHEAT	         		5000
#define TIME_BOOST_FREQ						 30
#define TIME_CONFIRM_VENT_STOP_TIMEOUT			 5000


// exemple : #define TIME_1MIN	    				60000  		

/* One minute counter for patient and device counter  */
#define TIME_1MINPAT							60000		
/* Constant flow delay  */
#define TIME_SEC_FLOW						60000		
/* Constant inspiratory flow delay */
#define TIME_1MIN_FLOWCST					60000		
/* Buzzer inhibition timer */
#define TIME_INHIB_BUZZER					60000		
/* Buzzer timer silence (5 min) */
#define TIME_BUZZER_SILENCE      	  300000
/* One minute buzzer timer */
#define TIME_ONE_MINUTE_BUZZER        	60000
/* Two minute buzzer timer */
#define TIME_TWO_MINUTE_BUZZER        120000
/* Battery periodical timer */
#define TIME_PERIODICAL_BIP			  300000
/* Buzzer timer silence (5 min) */
#define TIME_BUZZER_SILENCE      	  300000
/* USB Recording a horodatage frame during a continuous transfer */
/* every 15 minutes */
#define TIME_USB_RECORDING_DETAILLED_HORODATAGE      	  900000



#ifdef DECLARATION_TIMER_DATA
const UBYTE cTIM_TimePeriodMs = PERIOD_OF_TIM_LAUNCH_CALL;

t_TIM_TAB_DEF_ELEMENT  TIM_TableOfCntAndDecnt[end_of_table_cnt_decnt];
t_TIM_MINUTE_TAB_DEF_ELEMENT  
					TIM_MinuteTableOfCntAndDecnt[end_of_minute_table_cnt_decnt]; 	

UWORD32  nbre_de_debordement_timer; 
volatile UWORD32  cpt_de_debordement_timer;
UWORD32  dernier_chargement_T2;	
volatile UWORD16 temporisation_terminee;
#else
extern const UBYTE cTIM_TimePeriodMs;

extern t_TIM_TAB_DEF_ELEMENT  TIM_TableOfCntAndDecnt[];
extern t_TIM_MINUTE_TAB_DEF_ELEMENT  
					TIM_MinuteTableOfCntAndDecnt[];

extern UWORD32  nbre_de_debordement_timer; 
extern volatile UWORD32  cpt_de_debordement_timer;
extern UWORD32  dernier_chargement_T2;	
extern volatile UWORD16 temporisation_terminee;

#endif
#endif
