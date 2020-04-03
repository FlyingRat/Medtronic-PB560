/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : define.h                                                       */
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                             #DEFINE		                            	  		*/
/******************************************************************************/

#ifndef DEFINE_H
#define DEFINE_H


/******************************************************************************/
/* Scheduler	                            	  											*/
/******************************************************************************/
/* Definition des TASK_ID 																		*/
#define TASK_1             		1
#define TASK_2             		2
#define TASK_3             		4
#define TASK_4             		8
#define TASK_5            			16
#define TASK_6            			32
#define TASK_7           	 		64
#define TASK_8 	   	  			128
#define TASK_9     	     			256
#define TASK_10    	     			512
#define TASK_11   	    			1024
#define TASK_12   	    			2048
#define TASK_13   	    			4096
#define TASK_14   	    			8192
#define TASK_15  	   				16384
#define TASK_16  	   				32768
#define TASK_17      				1*65536
#define TASK_18      				2*65536
#define TASK_19      				4*65536
#define TASK_20      				8*65536
#define TASK_21     					16*65536
#define TASK_22     					32*65536
#define TASK_23     					64*65536
#define TASK_24    					128*65536
#define TASK_25    					256*65536
#define TASK_26    					512*65536
#define TASK_27   					1024*65536
#define TASK_28   					2048*65536
#define TASK_29   					4096*65536
#define TASK_30   					8192*65536


/* 10 interruption par pas de scheduler */
#define NB_INTERRUPTS_BY_SCHEDULER_STEP 		10U




/******************************************************************************/
/*%C Assignation 																					*/
/******************************************************************************/

#define NULL   										0




/******************************************************************************/
/*%C Periode define (ms)																		*/
/******************************************************************************/

/* Period of TIM_Lauch call		 															*/
#define PERIOD_OF_TIM_LAUNCH_CALL 				10

/* Temps nécessaire pour copier le scratchpad dans l'EEPROM							*/
#define TIME_EEPROM_COPY_SCRATCHPAD_TIME_OUT	20

/* Periode d'envoi du monitorage 															*/
#define RS232_MONITORING_PERIOD					400 	

/* Periode de detection de trame SPI 														*/
#define TIME_NO_FRAME 								25

/* Délai de reception de deux trames SPI 													*/
#define TIME_TWO_FRAMES_SPI_RECEIVE				150

/* Délai de stabilisation des mesures avant le premier changement d'état 		*/
#define TIME_SAMPLING_READY_DELAY				1000  

/* Délai de détection des alarmes sur évaluation des mesures 						*/
#define TIME_SEC_VALID_MESURES					3000	

/* Delai de prise en compte pour defaut de charge 										*/
#define TIME_CHARGE_RUNNING						12000  

/* Delai de clignotement des LEDs */
#define TIME_BLINK_BAT_LED_CHARGE_MIN			500
#define TIME_BLINK_BAT_LED_CHARGE_MAX			125

/* Delai de validation du defaut de charge 												*/
#define TIME_CHARGE_FAIL							5000

/* Delai de validation de perte batterie													*/
#define TIME_NO_BAT									500

/* Delai de validation abnormal I_BAT														*/
#define TIME_ABNORMAL_IBAT							3000

/* Delai de validation Unknow_Battery														*/
#define TIME_UNKNOW_BATTERY						5000

/* Delai de validation de tension batterie hors plage									*/
#define TIME_MEASURES_OUT_OF_BOUNDS				300

/*%C Delai d'interdiction commutation 														*/
/* Temps minimum afin de prendre en compte le retard du comparateur				*/
/* LIMIT_COMMUT_DC, c'est à dire ne pas commuter le soft avant que le hard 	*/
/* disponible 																						*/
#define TIME_NO_COMMUT								2000

/*%C Delai d'interdiction de commutation dans le cas d'un Open Pack 				*/
/* Permet une commutation plus rapide sur DC si la tension presente				*/
/* semble provenir d'un Open Pack ( > DC_PACK_LEVEL)									*/
/* Cela permet à l'Open Pack de ne pas repasser en état de veille 				*/
#define TIME_NO_COMMUT_PACK						1000
#define DC_PACK_LEVEL   							2000

/* Delai de validation defaut alimentation 												*/
#define TIME_5V_FAIL									500
#define TIME_24V_FAIL								500
#define TIME_VACDC_FAIL								500
#define TIME_VDC_FAIL								500
#define TIME_BAT_OPENED								2000

#define TIME_COOLING_FAN_FAIL						4000

/*%C Delai d'échantillonage  des tensions  et courants pour le calcul de l'impédance */
#define TIME_IMPEDANCE_MEASURE_DELAY			12000
#define TIME_IMPEDANCE_PHASE_DELAY			   500

/*Temps maximum pour effecter 1 tour de ventilateur de refroidissement  		*/
/*Toutes les vitesses < 1000tr/min seront cosidérées comme nulles					*/
#define TIME_FAN_SPEED_MEASURE_OVERFLOW		60 //ms

/******************************************************************************/
/*%C Compteur > 60s (ms)																		*/
/******************************************************************************/

/*%C Délai entre reception d'une commande et l'arret auto transmission RS232	*/
#define RS232_TIME_OUT_WAIT						120000	//ms

/* Délai entre reception d'un commande de control de la carte 						*/
#define RS232_CONTROL_TIME_OUT_WAIT				2500		//ms

/*%C 15 minutes 																					*/
#define TIME_ACCESS_EEPROM_WRITE_TIME_OUT		900000	//ms

/*%C Temps nécessaire au calcul de la jauge minute 									*/
#define TIME_GAUGE_MINUTE_READY_DELAY			120000	//ms

/*%C Delai de calcul avant le premier calcul du bat ageing							*/
#define TIME_BAT_AGEING_DELAY						120000	//ms

/*%C Delai de calcul avant l'ancement du calcul du bat cycle						*/
#define TIME_BAT_CYCLE_READY_DELAY				120000	//ms

/*%C Delai de calcul de la gauge par coulomb-metre 									*/
#define TIME_COULOMB_COMPUTE_DELAY				60000		//ms

/*%C Temps nécessaire à l'effondrement de la tension battery 						*/
#define TIME_BATTERY_VOLTAGE_OBSERVATION_PERIOD	30000	//ms

/******************************************************************************/
/*%C Rs232 Frame 																					*/
/******************************************************************************/

/*%C Start and End of monitoring frame */
#define MSB_START_FRAME_VALUE	 0xEB
#define LSB_START_FRAME_VALUE	 0x90
#define END_FRAME_VALUE  	 	 0xFA



/*%C Recive command of monitoring frame */
#define CMD_COMMUT_CH			0x10
#define CMD_SHUNT_DIODE_CH		0x11
#define CMD_COMMUT_BAT			0x12
#define CMD_SHUNT_DIODE_BAT	0x13
#define CMD_COMMUT_DC			0x14
#define CMD_SHUNT_DIODE_DC		0x15
#define CMD_COMMUT_AC			0x16
#define CMD_SHUNT_DIODE_AC		0x17
#define CMD_LED_PRESENCE_AC	0x18
#define CMD_LED_ETAT_BAT		0x20
#define CMD_COMMUT_IFC			0x21
#define CMD_VENTIL  				0x22
#define CMD_REGLAGE_VCHARGE	0x23
#define CMD_REGLAGE_ICHARGE	0x24
#define CMD_RESET_CPU			0x27

/*%C State monitoring frame */
#define CMD_START_MONIT 		0x55
#define CMD_STOP_COM  			0x56
#define CMD_CONTROL  			0x58



/******************************************************************************/
/*%C Sampling Level (en 100 éme de V)																				*/
/******************************************************************************/

/*%C For Sampling Filtering */
#define NB_SAMPLES 									10U
#define NB_SAMPLES_VACDC							80U

/*%C Seuil permettant de détecter la presence du secteur								*/
#define AC_DETECTION_LEVEL   						3000

/*%C Seuil permettant de détecter le changement d'alimentation DC 				*/
#define DC_ZERO_LEVEL   							200

/*%C Seuil permettant de détecter la perte du DC 										*/
#define DC_DETECTION_LOW_LEVEL   				900

/*%C Seuil permettant de détecter la presence du DC 									*/
#define DC_DETECTION_HIGH_LEVEL   				1050	

/*%C Seuil permettant de détecter la reprise du DC 									*/
#define DC_DETECTION_RESUME_LEVEL				1280

/*%C Seuil permettant de détecter le presence Batterie 								*/
#define VBAT_DETECTION_LEVEL   					2500




/******************************************************************************/
/*%C Supply And Bat State																		*/
/******************************************************************************/

/* Supply States */
#define AC_DC_BAT 									0
#define AC_SUPPLY 									1U
#define DC_SUPPLY 									2
#define BAT_SUPPLY 									3

/* Battery_State																					*/
#define BAT_IDLE										0
#define BAT_CHARGE									1U
#define BAT_DISCHARGE								2U


/* 29.4V +/- 0.5% */
#define VCHARGE_LOW_LEVEL 							2926UL
#define VCHARGE_HIGH_LEVEL 						2954UL

/* Vcharge setpoint 29.4V */
#define VBAT_CHARGE_SETPOINT 						2940UL

/* Tension batterie de démarrage de charge */
#define VBAT_STARTING_CHARGE						2850UL

/* Seuil de tension ,en 100ième V,de détection  de présence  de la batterie */
#define TENSION_BAT_RETURN_LEVEL					1600UL

/* Seuil maximun au dessous duquel le courant de charge est constant en 100ième de V */
#define TENSION_LEVEL_FOR_CONSTANT_CURRENT	2850UL

/* Tension maximale autorisée sur la batterie */
#define BAT_MAX_LEVEL								2975UL

/* Tension batterie de fin de charge en 100ième de V */
#define END_OF_CHARGE_VOLTAGE						2940UL

/*%C Delta de tension significatif pour effectuer un calcul de capacité totale en 100ième de V */
#define DELTA_MEANINGFUL_VOLTAGE 				100	// 1 V

/******************************************************************************/
/*%C Bat Current (en 10éme de mA) 															*/
/******************************************************************************/

/*Seuil de détection d'un courant négatif */
#define ZERO_NEGATIVE_LEVEL						-3000

/* Seuil de détection d'un courant positif */
#define ZERO_POSITIVE_LEVEL						3000

/* Seuil de détection d'un courant de décharge anormal */
#define DISCHARGE_MIN_POSITIVE_LEVEL			-1000 

/* Courant de coupure de la charge de la batterie */
#define ICHARGE_CUT_OFF								1500

/* Courant minimum permettant de detecter une charge sur batterie correcte */
#define ICHARGE_MIN_BAT_OK							1000

/* Courant de charge minimun que l'on doit atteindre pendant une charge */
#define ICHARGE_MIN_LEVEL							2000

/******************************************************************************/

/******************************************************************************/

/* Valeur maximale  (PWM) de la commande du ventilateur de refroidissement */
#define FAN_COMMAND_MAX								0x3F

/* Delta d'erreur autorisé sur le courant de charge par rapport à la consigne du courant de charge, en %.*/
#define ICHARGE_SETPOINT_TOLERANCE				20


/* Consigne PWM pour charge distincte */

/* Formule Schematic */
/* VProg = ((VCC * R91) + (V_PwmICharge * R85)) / (R91 + R85) 		*/
/* Vid	= (Vcc - VProg) / 10													*/
/* I_Bat = Vid / RShunt															*/

/* Formule Rapide */
/* Valeur du PwM = (- 42 * ICharge(A)) + 64 								*/
/* Soit pour une charge à 500 mA : PwmICharge = (-42 * 0.5) + 64	*/
/* PwmICharge = 43 soit 0x2B 													*/

/* Consigne maximale du courant de charge = 1.5 A */
#define ICHARGE_SETPOINT_MAX						0x00

/* Consigne du courant de charge = 500 mA */

/* Prise en charge de la dérive du LT1620 pour une valeur de 		*/
/* résistance de pont != 0,8v (valeur préconisé pour utilisation) */
/* Soit d'après les courbes issues de la datasheet composant 		*/
/* l'erruer estimé à 50mA d'ou une consigne corrigé de 0x29 		*/
#define ICHARGE_SETPOINT_MIN						0x29



/******************************************************************************/
/*%C Battery Identifiant																		*/
/******************************************************************************/

/*%C Battery supplier	*/
#define UNKNOWN_SUPPLIER							0
#define SAFT_SUPPLIER								1
#define ACCUTRONICS_SUPPLIER								2

/******************************************************************************/
/*%C Battery EEPROM, Compute Capacity and gauge											*/
/******************************************************************************/

/* Seuil de détection de capacité maximale qui ne peut être délivré à la batterie en mA/h */
#define CAPACITY_MAX_LEVEL_7S2P						                  7200000
#define CAPACITY_MAX_LEVEL_7S1P						                  3600000

/* Veillissement par defaut si la batterie n'est pa reconnue						*/
#define BAT_AGEING_DEFAULT						               	90

/* Seuil de veillissement MIN	*/
#define BAT_AGEING_MIN 													50

/* Seuil de veillissement MAX	*/
#define BAT_AGEING_MAX 													110

/* Impédance (mOhm) par defaut si la batterie n'est pa reconnue					*/
#define BAT_IMPEDANCE_DEFAULT						500

/* Impedance Battery MIN */
#define BAT_IMPEDANCE_MIN 												200

/* Impedance Battery MAX */
#define BAT_IMPEDANCE_MAX 											   1500

/*Facteur correctif de la jauge en minute */
#define SECURITY_OFFESET_GAUGE_MINUTE								25

/*Capacité min et max des différentes batteries*/
#define CAPACITY_7S2P	4800
#define CAPACITY_7S1P	2400

/*%C Niveau de tension minimun pour calculer le veillissement */
#define MIN_BAT_VOLTAGE_TO_COMPUTE_AGEING 		2650

/* Seuil de gauge batterie ,en minute ,d'activation de l'alarme fin batterie */
#define END_OF_BATTERY_DETECTION_MINUTE_LEVEL					10

/* Seuil de gauge ,en %, d'activation  de l'alarme fin batterie */
#define END_OF_BATTERY_DETECTION_PERCENTAGE_LEVEL				3

/* Seuil de gauge ,en minute d'activation de l'alarme batterie faible */
#define LOW_BATTERY_DETECTION_MINUTE_LEVEL						30

/* Seuil de gauge ,en pourcentage d'activation de l'alarme batterie faible */
#define LOW_BATTERY_DETECTION_PERCENTAGE_LEVEL 					8

/******************************************************************************/
/*%C Temperature																					*/
/******************************************************************************/

/* Seuil de température ambiante ,dans l'appareil, admissible , en 100ième de °C */
#define AMBIENT_TEMP_MAX							6000

/* Seuil de température 25°C, dans l'appareil, en 100ième de °C */
#define AMBIENT_TEMP_MIN_LEVEL					2500

/* Hystérésis pour la detection de température ambiance */
#define AMBIANT_TEMP_HYSTERESIS					500

/*Seuil de détection de température minimale du défaut du capteur de température ambiante en 100ième de °C */
#define TEMP_SENSOR_FAILURE_MIN					-2500

/*Seuil de détection de température maximale du défaut du capteur de température ambiante en 100ième de °C */
#define TEMP_SENSOR_FAILURE_MAX					7500

/* Seuil de température minimum,en 100ième°C, interdisant la charge de la batterie */
#define BATTERY_NO_CHARGE_MIN_TEMP_LEVEL		0

/* Seuil de température maximum,en 100ième °C, interdisant la charge de la batterie */
#define BATTERY_NO_CHARGE_MAX_TEMP_LEVEL		4500

/* Seuil de température minimum,en 100ième °C, autorisant la charge de la batterie */
#define BATTERY_CHARGE_MIN_TEMP_LEVEL			500

/* Seuil de température maximum,en 100ième °C, autorisant la charge de la batterie */
#define BATTERY_CHARGE_MAX_TEMP_LEVEL			4000

/* Seuil de température minimum,en 100ième  °C, interdisant la décharge de la batterie */
#define BATTERY_NO_DISCHARGE_MIN_TEMP_LEVEL	-1000

/* Seuil de température maximum,en 100ième°C, interdisant la décharge de la batterie */
#define BATTERY_NO_DISCHARGE_MAX_TEMP_LEVEL	6000

/* Seuil de température minimum,en 100ième°C, autorisant la décharge de la batterie */
#define BATTERY_DISCHARGE_MIN_TEMP_LEVEL		-500

/* Seuil de température maximum,en 100ième°C, autorisant la décharge de la batterie */ 
#define BATTERY_DISCHARGE_MAX_TEMP_LEVEL		5500

/*Seuil de température ,en 100ième°C,de détection d'absence de la batterie */
#define BATTERY_ABSENT_TEMP_LEVEL				-2500

/* Seuil de tension ,en 100ième V,de détection d'absence de la batterie */
#define BATTERY_ABSENT_TENSION_LEVEL			1400

/* Seuil de température ,en 100ième°C,de détection de présence de la batterie */
#define TEMP_BAT_RETURN_LEVEL						-2000






/******************************************************************************/
/*%C Typical Value and tolerance																*/
/******************************************************************************/



/* Valeur de tension  nominale de l'alimentation ACDC */
#define TYPICAL_VACDC_VALUE						3300

/* Valeur de tension  nominale de l'alimentation 24VUTIL */
#define TYPICAL_24VUTIL_VALUE						2400

/* Valeur de tension  nominale de l'alimentation V */
#define TYPICAL_5V_VALUE							500

/* Tension minimale de l'alimentation DC */
#define LOW_VDC_LEVEL								1000

/* Tension maximale de l'alimentation DC */
#define HIGH_VDC_LEVEL								3300

/* Tolérance de la tension VACDC en % */
#define MEASURE_VACDC_TOLERANCE					6

/* Tolérance de la tension 24V en % */
#define MEASURE_24VUTIL_TOLERANCE				5

/* Tolérance de la tension 5V en % */
#define MEASURE_5V_TOLERANCE						5

/* Tolerance sur l'écart consigne mesure du ventilateur de refroidissement*/
#define FAN_SPEED_TOLERANCE 						20

/* Tolérance de la tension de batterie fin de charge en % */
#define END_OF_CHARGE_VOLTAGE_TOLERANCE		1




/******************************************************************************/
/*%C CAN Channel																					*/
/******************************************************************************/

/*%C  Channel to convert */
#define BATTERY_TEMP_CHANNEL 		0x03	/*channel AN0*/
#define MEASURE_3V3_CHANNEL 		0x0B	/*channel AN2*/
#define MEASURE_VACDC_CHANNEL 	0x13	/*channel AN4*/
#define I_BAT_CHANNEL 				0x17	/*channel AN5*/
#define MEASURE_VCHARGE_CHANNEL 	0x1B	/*channel AN6*/
#define TEMP_AMB_CHANNEL 			0x1F	/*channel AN7*/
#define MEASURE_VDC_CHANNEL 		0x23	/*channel AN8*/
#define MEASURE_24VUTIL_CHANNEL 	0x27	/*channel AN9*/
#define MEASURE_5V_CHANNEL 		0x2B	/*channel AN10*/
#define MEASURE_VBAT_CHANNEL 		0x2F	/*channel AN11*/


/******************************************************************************/
/*%C Version Number																				*/
/******************************************************************************/

/*%C Number Version */
#define FIRST_IDENTIFIANT_VERSION				0x02
#define SECOND_IDENTIFIANT_VERSION				0x00
#define THIRD_IDENTIFIANT_VERSION				0x04





#endif
