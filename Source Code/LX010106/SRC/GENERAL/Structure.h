/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: Structure.h   				   					               		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description : 	Structure Type redéfinition       				*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None		       			                  	*/
/*%IO Input/Output Parameter :   None                                		  	*/
/*%O 	Output Parameter : 			None     	                				  		*/
/******************************************************************************/
#ifndef STRUCTURE_H
#define STRUCTURE_H
/******************************************************************************/
typedef struct{
	UWORD16 Second;
	UWORD16 Minute;
	UWORD16 Hour;
	UWORD16 Day;
	UWORD16 Month;
	UWORD16 Year;
}t_RTC_TIME_DATE;

typedef struct {
	UWORD16 *ptr_data; 
	e_DRV_RTC_REGISTER regist;	 
	e_DRV_RTC_ACCESS_STATE state;	  
} t_RTC_ACCESS_CONTROL;


typedef struct
{
	UWORD16 value;
	UWORD16 type;
	e_BOOL activate;
}t_TIM_TAB_DEF_ELEMENT;

typedef struct
{
	UWORD32 value;
	UWORD16 type;
	e_BOOL activate;
	e_BOOL autoreload;
	UWORD32 autovalue;
}t_TIM_MINUTE_TAB_DEF_ELEMENT;

#ifndef _BORLAND
typedef struct 
	{
	UWORD16 mini;
	UWORD16 current;
	UWORD16 maxi;
	}
   idata t_MEASURES_TIMES;
#else
typedef struct 
	{
	UWORD16 mini;
	UWORD16 current;
	UWORD16 maxi;
	}
   t_MEASURES_TIMES;
#endif

typedef struct {
	UWORD16 DisplayFunction;
	UWORD16 Param1;
	UWORD16 Param2;
	UWORD16 Param3;
	UWORD16 Param4;
	UWORD16 Param5;
	UWORD16 Param6;
	UWORD16 Param7;
	UWORD16 Param8;
	UWORD16 Param9;
	UWORD16 Param10;
	UWORD16 Param11;
	UWORD16 Param12;
}t_DisplayAccess;

typedef struct
	{
  	UWORD16 PatientPressure;
  	UWORD16 FlowInsp;
  	UWORD16 TestBuzzer;
  	UWORD16 Pfi;
  	UWORD16 Fio2;
  	UWORD16 ValvePressure;
	UWORD16 FlowExh;
	UWORD16 ProxPressure;
	UWORD16 MesAbsPressure;
	UWORD16 FlowO2;
  	UWORD16 MesIValve;
	UWORD16 MesVBat;
  	UWORD16 Volt24;
  	UWORD16 O2Pressure;
  	UWORD16 InfoSupply;
 	UWORD16 MesBlowerTemp;
	} t_AD_Digit;

typedef struct {
	e_EEP_ACCESS_STATE state;
	UWORD16 xhuge *ptr_DataRam;
} t_EEP_ACCESS_CONTROL;

typedef struct {
	UWORD16 mini;
	UWORD16 maxi;
	UWORD16 step;
	UWORD16 defvalue;
} t_TEST_EEPROM_DB;

typedef struct {	
	t_TEST_EEPROM_DB cDB_TEST_DB;
	UWORD16 issigned;
} t_TEST_EEPROM_DB_SATURATE;

 /* Event management record parameters */
typedef enum {
	FULL,
	MSB,
	LSB,
	STORAGE_CONSTANT
} e_StorageType;

 /* Common parameters structure*/
typedef struct {
   e_DataBaseType DataBaseType;
   UBYTE DataId;
	e_StorageType StorageType;
} t_DB_CommonEventMngtParam;

typedef struct {
   UBYTE DataId;
	e_StorageType StorageType;
} t_DB_EventMngtParam;

typedef struct {
   UBYTE Status;
   UBYTE HeartRate;
   UBYTE Spo2;
} t_DataSpo2;

typedef struct {
	SWORD16 Block;
	SWORD16	Page;
	SWORD16 Column;
}t_FlashParam;

/******************************************************************************/
#endif

