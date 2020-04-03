/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_Measurement.h			   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description : 	datas declaration for measurement base			*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None			      	                       	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None				            				  		*/
/******************************************************************************/
#ifndef MEASUREMENT_H
#define MEASUREMENT_H
/******************************************************************************/
/*                     ENUM DECLARATION				                         	*/
/******************************************************************************/
/* Measurement base */
typedef enum {
	PATIENT_PRESSURE_CAN_U16=0,
	PATIENT_PRESSURE_PROXI_CAN_U16,
	VALVE_PRESSURE_CAN_U16,
	QI_CAN_U16,
	QE_CAN_U16,
	INFO_SUPPLY_CAN_U16,
	ABS_PRESSURE_CAN_U16,
	O2_PRESSURE_CAN_U16,
	QO2_CAN_U16,
	end_of_db_measurement_table
} e_DB_MEASUREMENT;

#ifdef DECLARATION_MEASUREMENT_BASE
/******************************************************************************/
/*                     CONSTANT DECLARATION			                         	*/
/******************************************************************************/
/* Base Measurement array */
UWORD16 DB_Measurement[end_of_db_measurement_table];
#else
/******************************************************************************/
/*                     CONSTANT DECLARATION			                         	*/
/******************************************************************************/
/* Base Measurement array */
extern UWORD16 DB_Measurement[end_of_db_measurement_table];

#endif

#endif
