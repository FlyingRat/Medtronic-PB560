/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Driver_ADConverter_data.h                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Description fonctionnelle:		 	                        	      */
/*                                                                      	   */
/*%C    Data declaration for AD Converter driver functions                    */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/************************************************************************/
/*                             #DEFINE		                        		*/
/************************************************************************/

#define NUM_PRESSION_INTERNE  	conversion_numerique[15] & 0x3FF
#define NUM_DEBIT_INSPIRATOIRE	conversion_numerique[14] & 0x3FF
#define NUM_TEST_BUZZER         	conversion_numerique[13] & 0x3FF	
#define NUM_PRES_O2	   			conversion_numerique[12] & 0x3FF 
#define NUM_PFI		   			conversion_numerique[11] & 0x3FF 
#define NUM_FIO2	        			conversion_numerique[10] & 0x3FF 
#define NUM_PRESSION_VALVE     	conversion_numerique[9]  & 0x3FF 
#define NUM_DEBIT_EXPIRATOIRE  	conversion_numerique[8]  & 0x3FF
#define NUM_PRESSION_PROX    		conversion_numerique[7]  & 0x3FF
#define NUM_PRESSION_ABSOLUE 		conversion_numerique[6]  & 0x3FF
#define NUM_MES_DEBIT_O2	 		conversion_numerique[5]  & 0x3FF
#define NUM_MES_I_VALVE				conversion_numerique[4]  & 0x3FF
#define NUM_MES_V_BAT				conversion_numerique[3]  & 0x3FF
#define NUM_MES_24V			 		conversion_numerique[2]  & 0x3FF
#define NUM_MES_FLOW_TEMP 			conversion_numerique[1]  & 0x3FF
#define NUM_MES_BLOWER_TEMP 		conversion_numerique[0]  & 0x3FF



#ifdef ADC_DRIVER_DATA_DECLARATION

	#ifndef DRIVER_ADCONVERTER_DATA_H
	#define DRIVER_ADCONVERTER_DATA_H

UWORD16_I conversion_numerique[16]; 
volatile UWORD16 	ErrorNumber = 0;

	#endif
#else
extern UWORD16_I conversion_numerique[16]; 
extern volatile UWORD16 	ErrorNumber;

#endif