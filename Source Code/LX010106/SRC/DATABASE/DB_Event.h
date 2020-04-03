/****************************************************************************/
/*																			*/
/* Project Number	: 	RB0505     			     		              	  	*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*                                                             			  	*/
/* Filename	: DB_Event.h 													*/
/*                                                       				  	*/
/*--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/****************************************************************************/
/*%C Functionnal description : 	data declaration for Event base             */
/*                                                        				  	*/
/****************************************************************************/
/*%I 	Input Parameter : 			None			                       	*/
/*%IO Input/Output Parameter : 		None 	        	                   	*/
/*%O 	Output Parameter : 			None			 	  				  	*/
/****************************************************************************/
#ifndef DB_EVENT_H
#define DB_EVENT_H

#include "typedef.h"


/****************************************************************************/
/*                     ENUM DECLARATION				                        */
/****************************************************************************/
/* Base EVENT */
typedef enum {
 	/* Evènements de réglages */
	NO_EVENT = 0,	/* Event number:	0	*/
	EVENT_START,	/* Event number:	1	*/
	EVENT_VENTIL,	/* Event number:	2	*/
	EVENT_VOLUNTARY_STOP_VENTIL,	/* Event number:	3	*/
	EVENT_MODIF_PEEP,	/* Event number:	4	*/
	EVENT_MODIF_BACKUP_R,	/* Event number:	5	*/
	EVENT_RESET_PATIENT_COUNTER,	/* Event number:	6	*/
	EVENT_MODIF_CONTROL_R,	/* Event number:	7	*/
	RESERVED_8,	/* Event number:	8	*/
	EVENT_MODIF_VOL_CONTROL, 	/* Event number:	9	*/
	EVENT_MODIF_RAMP,	/* Event number:	10	*/
	EVENT_MODIF_IE,	/* Event number:	11	*/
	RESERVED_12,	/* Event number:	12	*/
	EVENT_MODIF_STOP_DEVICE, 	/* Event number:	13	*/
	EVENT_MODIF_INSP_SENS, 	/* Event number:	14	*/
	EVENT_MODIF_MODE,	/* Event number:	15	*/
	EVENT_MODIF_RISE_TIME,	/* Event number:	16	*/
	EVENT_MODIF_P_SUPPORT,	/* Event number:	17	*/
	EVENT_MODIF_VTC,	/* Event number:	18	*/
	EVENT_MODIF_PIMAX,	/* Event number:	19	*/
	EVENT_MODIF_IT,	/* Event number:	20	*/
	RESERVED_21,	/* Event number:	21	*/
	EVENT_MODIF_EXH_SENS,	/* Event number:	22	*/
	EVENT_MODIF_APNEA_TIME,	/* Event number:	23	*/
	EVENT_MODIF_LOW_PIP,	/* Event number:	24	*/
	EVENT_MODIF_HIGH_PIP,	/* Event number:	25	*/
	EVENT_MODIF_HIGH_R,	/* Event number:	26	*/
	EVENT_MODIF_LOW_VTE,	/* Event number:	27	*/
	RESERVED_28,	/* Event number:	28	*/
	RESERVED_29,	/* Event number:	29	*/
	EVENT_MODIF_LOW_VTI,	/* Event number:	30	*/
	EVENT_MODIF_HIGH_VTI,	/* Event number:	31	*/
 	RESERVED_32,	/* Event number:	32	*/
	RESERVED_33,	/* Event number:	33	*/
	RESERVED_34,	/* Event number:	34	*/
	RESERVED_35,	/* Event number:	35	*/
 	EVENT_UNVOLUNTARY_STOP_VENTIL,	/* Event number:	36	*/
	RESERVED_37,	/* Event number:	37	*/
	RESERVED_38,	/* Event number:	38	*/
	RESERVED_39, 	/* Event number:	39	*/
	EVENT_EXH_FLOW_CALIB,	/* Event number:	40	*/
	RESERVED_41,	/* Event number:	41	*/
	EVENT_MODIF_FIO2,	/* Event number:	42	*/
	EVENT_FIO2_CALIB,	/* Event number:	43	*/
	EVENT_MODIF_MAX_LEAK,	/* Event number:	44	*/
	EVENT_INSP_FLOW_CALIB,	/* Event number:	45	*/
	EVENT_O2_FLOW_CALIB, 	/* Event number:	46	*/
	EVENT_PATIENT_PRESS_CALIB,	/* Event number:	47	*/
	RESERVED_48,	/* Event number:	48	*/
	EVENT_MODIF_SPO2_MAXI,	/* Event number:	49	*/
	EVENT_MODIF_SPO2_MINI,	/* Event number:	50	*/
	EVENT_MODIF_TI_MAXI,	/* Event number:	51	*/
	EVENT_MODIF_TI_MINI,	/* Event number:	52	*/
	EVENT_VALVE_PRESS_CALIB,	/* Event number:	53	*/
	EVENT_AC_RETURN,	/* Event number:	54	*/
	EVENT_O2_PRESS_CALIB,	/* Event number:	55	*/
	EVENT_ALARM_INHIBITION,	/* Event number:	56	*/
	EVENT_DC_RETURN,	/* Event number:	57	*/
	EVENT_CIRCUIT_CHECK_MENU_ACCESS,	/* Event number:	58	*/
	EVENT_MAINTENANCE_MENU_ACCESS,	/* Event number:	59	*/
	EVENT_ALARM_CANCELLATION,	/* Event number:	60	*/
 	EVENT_MODIF_P_CONTROL,	/* Event number:	61	*/
 	EVENT_MODIF_TI_CONTROL,	/* Event number:	62	*/
 	RESERVED_63,	/* Event number:	63	*/
	RESERVED_64,	/* Event number:	64	*/
	EVENT_MODIF_HIGH_VTE,	/* Event number:	65	*/
 	EVENT_MODIF_TIME,	/* Event number:	66	*/
	EVENT_MODIF_DATE,	/* Event number:	67	*/
 	EVENT_USB_TOO_MANY_KEYS_CONNECTED,	/* Event number:	68	*/
	EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION,	/* Event number:	69	*/
 	EVENT_USB_TRANSFER_ERROR,	/* Event number:	70	*/
 	EVENT_USB_ERASE_KEY_ERROR,	/* Event number:	71	*/
	EVENT_USB_SETTINGS_INCOMPATIBLES,	/* Event number:	72	*/
	EVENT_USB_SETTINGS_FILE_ERROR,	/* Event number:	73	*/
	EVENT_USB_KEY_FULL,	/* Event number:	74	*/
	EVENT_USB_SETTINGS_TRANSFER_FROM_KEY,	/* Event number:	75	*/
	EVENT_MODIF_FIO2_MAXI,	/* Event number:	76	*/
	EVENT_MODIF_FIO2_MINI,	/* Event number:	77	*/
	EVENT_MODIF_DISCONNECTION_DELAY,	/* Event number:	78	*/
	EVENT_MODIF_SIGHT_COUNT,	/* Event number:	79	*/
	EVENT_MODIF_SIGHT_COEF,	/* Event number:	80	*/
	EVENT_FLASH_CHECKSUM_POST_ERROR,	/* Event number:	81	*/
	EVENT_RAM_CHECKSUM_POST_ERROR,	/* Event number:	82	*/
 	EVENT_VOLT_REFERENCE_POST_ERROR,	/* Event number:	83	*/
 	EVENT_EEPROM_POST_ERROR,	/* Event number:	84	*/
 	EVENT_POST_VERSION_ERROR,	/* Event number:	85	*/
 	EVENT_USB_CONTINUOUS_TRANSFER_START,	/* Event number:	86	*/
 	EVENT_USB_CONTINUOUS_TRANSFER_STOP,	/* Event number:	87	*/
 	RESERVED_88,	/* Event number:	88	*/
 	Start_Alarm,	/* Event number:	89	*/
 	EVENT_AL_HIGH_PRESS,	/* Event number:	90	*/
 	EVENT_AL_DISCONNECTION,	/* Event number:	91	*/
 	EVENT_AL_HIGH_RATE,	/* Event number:	92	*/
 	EVENT_AL_LOW_VTI,	/* Event number:	93	*/
 	EVENT_AL_HIGH_VTI,	/* Event number:	94	*/
 	EVENT_AL_LOW_VTE,	/* Event number:	95	*/
 	EVENT_AL_VALVE_LEAKAGE,	/* Event number:	96	*/
 	EVENT_AL_APNEA,	/* Event number:	97	*/
 	EVENT_AL_LOW_FIO2,	/* Event number:	98	*/
 	EVENT_AL_HIGH_FIO2,	/* Event number:	99	*/
	EVENT_AL_CHECK_PRESSURE,	/* Event number:	100	*/
	EVENT_AL_CHECK_VALVE,	/* Event number:	101	*/
	EVENT_AL_AC_POWER_FAIL,	/* Event number:	102	*/
	EVENT_AL_DC_POWER_FAIL,	/* Event number:	103	*/
	EVENT_AL_LOW_BATTERY,	/* Event number:	104	*/
	EVENT_AL_END_OF_BATTERY,	/* Event number:	105	*/
	EVENT_AL_CHECK_BATTERY,	/* Event number:	106	*/
	EVENT_AL_HIGH_SPO2,  	/* Event number:	107	*/
	EVENT_AL_NO_FIO2_SENSOR,	/* Event number:	108	*/
	EVENT_AL_LEAKAGE,	/* Event number:	109	*/
	EVENT_AL_LEAK_OCCLUSION,	/* Event number:	110	*/
	EVENT_AL_LOW_SPO2,  	/* Event number:	111	*/
	EVENT_AL_NO_BATTERY,  	/* Event number:	112	*/
	EVENT_AL_NO_PROXI,  	/* Event number:	113	*/
	EVENT_AL_O2_LEAKAGE,  	/* Event number:	114	*/
	EVENT_AL_CHECK_VOLUME,	/* Event number:	115	*/
	EVENT_AL_CHECK_BUZZER,	/* Event number:	116	*/
	EVENT_AL_CHECK_FIO2,	/* Event number:	117	*/
	EVENT_AL_CHECK_O2,	/* Event number:	118	*/
	EVENT_AL_CHECK_O2_SUPPLY,	/* Event number:	119	*/
	EVENT_AL_CHECK_PROXIMAL, 	/* Event number:	120	*/
	EVENT_AL_CHECK_REMOTE_ALARM,	/* Event number:	121	*/
	EVENT_AL_CHECK_SUPPLY,	/* Event number:	122	*/
	RESERVED_123,	/* Event number:	123	*/
	EVENT_AL_CONNECT_VALVE,	/* Event number:	124	*/
	EVENT_AL_CONNECT_VALVE_CHANGE_PI_PE,	/* Event number:	125	*/
	EVENT_AL_DISCONNECT_VALVE,	/* Event number:	126	*/
	EVENT_AL_DISCONNECT_VALVE_CHANGE_PI_PE,	/* Event number:	127	*/
	EVENT_AL_PROXIMAL_DISCONNECTION,	/* Event number:	128	*/
	EVENT_AL_TECHNICAL_PROBLEM,    	/* Event number:	129	*/
	EVENT_AL_CHECK_VALVE_PRESSURE,	/* Event number:	130	*/
	EVENT_AL_SPO2_SENSOR_DISCONNECTED, 	/* Event number:	131	*/
	EVENT_AL_MISSING_O2_SUPPLY,	/* Event number:	132	*/
	EVENT_AL_CONTROLLED_CYCLES,	/* Event number:	133	*/
	RESERVED_134,	/* Event number:	134	*/
	EVENT_AL_100_PER_CENT_O2,	/* Event number:	135	*/
	EVENT_AL_UNKNOWN_BATTERY,	/* Event number:	136	*/
	EVENT_AL_CHECK_BATTERY_CHARGE,	/* Event number:	137	*/
 	RESERVED_138,	/* Event number:	138	*/
 	RESERVED_139,	/* Event number:	139	*/
	RESERVED_140,	/* Event number:	140	*/
 	RESERVED_141,	/* Event number:	141	*/
	EVENT_AL_NEW_VERSION,	/* Event number:	142	*/
	EVENT_AL_EEPROM_OUT_OF_RANGE,	/* Event number:	143	*/
	EVENT_AL_EEPROM_LOOSING_PARAM,	/* Event number:	144	*/
	RESERVED_145,	/* Event number:	145	*/
	EVENT_AL_HIGH_VTE,	/* Event number:	146	*/
	EVENT_AL_KEYBOARD,	/* Event number:	147	*/
	EVENT_AL_CALIBRATION,	/* Event number:	148	*/
	EVENT_AL_COOLING_FAN,	/* Event number:	149	*/
	EVENT_AL_AMBIENT_TEMP,	/* Event number:	150	*/
 	EVENT_AL_BAT_TEMP,	/* Event number:	151	*/
	EVENT_AL_SUPPLY_MEASURE,	/* Event number:	152	*/
	EVENT_AL_FAILURE_24V,	/* Event number:	153	*/
	EVENT_AL_TURBINE_OVERHEAT,	/* Event number:	154	*/
	EVENT_AL_OCCLUSION,	/* Event number:	155	*/
	EVENT_AL_CPU_REFERENCE,	/* Event number:	156	*/
	RESERVED_157,	/* Event number:	157	*/
	EVENT_AL_BREATH_TIME_CYCLED,	/* Event number:	158	*/
	EVENT_AL_INSP_FLOW_FAILURE,	/* Event number:	159	*/
	EVENT_AL_LOW_BUZZER_BATTERY,	/* Event number:	160	*/
	RESERVED_161,  /* EVENT_AL_BUZZER_BATTERY_FAILURE */	/* Event number:	161	*/
	EVENT_AL_BUZZER_BATTERY_CHARGE_FAILURE,	/* Event number:	162	*/
	EVENT_AL_NEEDED_FIO2_CALIB,	/* Event number:	163	*/
	EVENT_AL_VOLUNTARY_STOP,	/* Event number:	164	*/
	RESERVED_165,	/* Event number:	165	*/
	RESERVED_166,	/* Event number:	166	*/
 	RESERVED_167,	/* Event number:	167	*/
 	End_Event_Alarm,	/* Event number:	168	*/
 	Start_End_Of_Alarm,	/* Event number:	169	*/
 	EVENT_AL_END_OF_APNEA ,	/* Event number:	170	*/
 	EVENT_AL_END_OF_CHECK_BATTERY,	/* Event number:	171	*/
 	EVENT_AL_END_OF_DISCONNECTION,	/* Event number:	172	*/
	EVENT_AL_END_OF_CHECK_FIO2,	/* Event number:	173	*/
 	EVENT_AL_END_OF_CHECK_O2,	/* Event number:	174	*/
	EVENT_AL_END_OF_CHECK_O2_SUPPLY,	/* Event number:	175	*/
	EVENT_AL_END_OF_CHECK_PRESSURE,	/* Event number:	176	*/
	EVENT_AL_END_OF_CHECK_PROXIMAL,	/* Event number:	177	*/
	RESERVED_178,	/* Event number:	178	*/
	RESERVED_179,	/* Event number:	179	*/
	EVENT_AL_END_OF_CHECK_SUPPLY,	/* Event number:	180	*/
	EVENT_AL_END_OF_CHECK_VALVE,	/* Event number:	181	*/
	EVENT_AL_END_OF_LEAK_OCCLUSION,	/* Event number:	182	*/
	EVENT_AL_END_OF_CHECK_VOLUME,	/* Event number:	183	*/
	EVENT_AL_END_OF_CONNECT_VALVE,	/* Event number:	184	*/
	EVENT_AL_END_OF_CONNECT_VALVE_CHANGE_PI_PE,	/* Event number:	185	*/
	EVENT_AL_END_OF_DISCONNECT_VALVE,	/* Event number:	186	*/
	EVENT_AL_END_OF_DISCONNECT_VALVE_CHANGE_PI_PE,	/* Event number:	187	*/
	EVENT_AL_END_OF_HIGH_FIO2,	/* Event number:	188	*/
	EVENT_AL_END_OF_HIGH_PRESSURE,	/* Event number:	189	*/
	EVENT_AL_END_OF_HIGH_RATE,	/* Event number:	190	*/
	EVENT_AL_END_OF_HIGH_SPO2,	/* Event number:	191	*/
	EVENT_AL_END_OF_HIGH_VTI,	/* Event number:	192	*/
	EVENT_AL_END_OF_LEAKAGE,    	/* Event number:	193	*/
	EVENT_AL_END_OF_LOW_FIO2,	/* Event number:	194	*/
	EVENT_AL_END_OF_LOW_SPO2,	/* Event number:	195	*/
	EVENT_AL_END_OF_LOW_VTE,	/* Event number:	196	*/
 	EVENT_AL_END_OF_LOW_VTI,	/* Event number:	197	*/
	EVENT_AL_END_OF_NO_BATTERY,	/* Event number:	198	*/
	EVENT_AL_END_OF_NO_FIO2_SENSOR,	/* Event number:	199	*/
	EVENT_AL_END_OF_NO_PROXI,	/* Event number:	200	*/
	EVENT_AL_END_OF_O2_LEAKAGE,	/* Event number:	201	*/
	EVENT_AL_END_OF_PROXI_DISCONNECTION,	/* Event number:	202	*/
	EVENT_AL_END_OF_TECHNICAL_PROBLEM,	/* Event number:	203	*/
	EVENT_AL_END_OF_VALVE_LEAKAGE,	/* Event number:	204	*/
	EVENT_AL_END_OF_HIGH_VTE,	/* Event number:	205	*/
	EVENT_AL_END_KEYBOARD,	/* Event number:	206	*/
	EVENT_AL_END_CHECK_VALVE_PRESSURE,	/* Event number:	207	*/
	EVENT_AL_END_SPO2_SENSOR_DISCONNECTED, 	/* Event number:	208	*/
	EVENT_AL_END_MISSING_O2_SUPPLY,	/* Event number:	209	*/
 	EVENT_AL_END_CONTROLLED_CYCLES,	/* Event number:	210	*/
 	RESERVED_211,	/* Event number:	211	*/
	EVENT_AL_END_OF_100_PER_CENT_O2,	/* Event number:	212	*/
	EVENT_AL_END_OF_UNKNOWN_BATTERY,	/* Event number:	213	*/
	EVENT_AL_END_OF_CHECK_BATTERY_CHARGE,	/* Event number:	214	*/
 	RESERVED_215,	/* Event number:	215	*/
 	RESERVED_216,	/* Event number:	216	*/
	RESERVED_217,	/* Event number:	217	*/
	RESERVED_218,	/* Event number:	218	*/
	EVENT_AL_END_COOLING_FAN,	/* Event number:	219	*/
	EVENT_AL_END_AMBIENT_TEMP,	/* Event number:	220	*/
 	EVENT_AL_END_BAT_TEMP,	/* Event number:	221	*/
	EVENT_AL_END_SUPPLY_MEASURE,	/* Event number:	222	*/
	EVENT_AL_END_FAILURE_24V,	/* Event number:	223	*/
	RESERVED_224,	/* Event number:	224	*/
	EVENT_AL_END_OCCLUSION,	/* Event number:	225	*/
	EVENT_AL_END_CPU_REFERENCE,	/* Event number:	226	*/
	RESERVED_227,	/* Event number:	227	*/
	EVENT_AL_END_BREATH_TIME_CYCLED,	/* Event number:	228	*/
	EVENT_AL_END_OF_INSP_FLOW_FAILURE,	/* Event number:	229	*/
	EVENT_AL_END_LOW_BUZZER_BATTERY,	/* Event number:	230	*/
	RESERVED_231,  /* EVENT_AL_END_BUZZER_BATTERY_FAILURE, */	/* Event number:	231	*/
 	EVENT_AL_END_BUZZER_BATTERY_CHARGE_FAILURE,	/* Event number:	232	*/
 	EVENT_AL_END_OF_VOLUNTARY_STOP,	/* Event number:	233	*/
 	RESERVED_234,	/* Event number:	234	*/
 	RESERVED_235,	/* Event number:	235	*/
 	End_Alarm,	/* Event number:	236	*/
 	Start_Anomalies,	/* Event number:	237	*/
	RESERVED_238,	/* Event number:	238	*/
	EVENT_ALT_INSP_FLOW_OFFSET,	/* Event number:	239	*/
	EVENT_ALT_EXH_FLOW_OFFSET,	/* Event number:	240	*/
	EVENT_ALT_VALVE_PRESSURE_OFFSET, 	/* Event number:	241	*/
	EVENT_ALT_INT_PRESS_OFSSET,	/* Event number:	242	*/
	EVENT_ALT_SPEED,	/* Event number:	243	*/
	EVENT_ALT_CLOCK, 	/* Event number:	244	*/
	EVENT_ALT_PROXI_PRESS_OFSSET,	/* Event number:	245	*/
	EVENT_ALT_VERY_LOW_PROXI_PRESS,	/* Event number:	246	*/
	EVENT_ALT_VERY_LOW_INT_PRESS,	/* Event number:	247	*/
	EVENT_ALT_VERY_LOW_VALVE_PRESS,	/* Event number:	248	*/
	EVENT_ALT_LOOSE_FLASH_POINTER,	/* Event number:	249	*/
	EVENT_ALT_FIO2_OFFSET,	/* Event number:	250	*/
	EVENT_ALT_O2_FLOW_OFFSET,	/* Event number:	251	*/
	EVENT_ALT_O2_PRESSURE_OFFSET,	/* Event number:	252	*/
 	RESERVED_253,	/* Event number:	253	*/
	RESERVED_254,	/* Event number:	254	*/
	End_Anomalie	/* Event number:	255	*/
} e_EVENT_ENUM;                                                                            



#endif
