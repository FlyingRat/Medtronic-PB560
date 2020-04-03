/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_Database.c                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          				Send database data via UART									*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#ifndef _TASKING
#include <intrins.h>
#include "LH_ST10F276.h"
#else
#include "regf276e.h"
#endif	 
#include "typedef.h"
#include "enum.h"
#include "DB_Config.h"
#include "DRV_COM_Data.h"
#include "DRV_COM_Transmit_Database.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_COM_Transmit_Database(void) 
{ 
	UWORD16 Compute_U16 = 0;
	UWORD16 Compute_CRC = 0;
	UBYTE Database_Data = 0xAA;
	UBYTE Database_Id = 0xAA;
	UBYTE Id;
   /*%C Feed the frame with the 3 start bytes							*/
	Array_Read_Database [COM_TX_START_FRAME_1] = START_FRAME_COM_VALUE_1;
	Array_Read_Database [COM_TX_START_FRAME_2] = START_FRAME_COM_VALUE_2;
	Array_Read_Database [COM_TX_START_FRAME_3] = START_FRAME_COM_VALUE_3;
  	
  	/*%C The read database frame ID */
  	Array_Read_Database [COM_TX_ID_FRAME] = ID_READ_DATABASE;
  	Compute_CRC = START_FRAME_COM_VALUE_1 
					^ START_FRAME_COM_VALUE_2 
					^ START_FRAME_COM_VALUE_3
					^ ID_READ_DATABASE;

	for(Id = 0; Id < 2*DRV_COM_NbParamDb; Id = Id + 2)
	{
		Database_Id = DRV_COM_Database_Parameter[Id ];
		Database_Data = DRV_COM_Database_Parameter[Id + 1];
		/*%C Feed the frame with data bytes									*/
		DB_IhmAccessParaDataBase(&Compute_U16,
								 Database_Data, 
								 Database_Id, 
								 READ);
	 
		Array_Read_Database[COM_TX_DATABASE_MSB + COM_TX_DATA_FRAME + Id] 
															= (UBYTE)(Compute_U16 >> 8);
		Array_Read_Database[COM_TX_DATABASE_LSB + COM_TX_DATA_FRAME + Id] 
															= (UBYTE)(Compute_U16 & 0x00FF);

	   /*%C CRC Compute */
		Compute_CRC = Compute_CRC 
						^ ((UBYTE)(Compute_U16 >> 8)) 
						^ ((UBYTE)(Compute_U16 & 0x00FF));

	}

	/*%CFeed the frame with 1 CRC bytes */
	Array_Read_Database [COM_TX_MSB_CRC_FRAME +	(2 * DRV_COM_NbParamDb) - 1] 
				   		=	(UBYTE)(Compute_CRC & 0x00FF);


	/*%C Feed the frame with the 3 stop frame bytes					   	*/
	Array_Read_Database [COM_TX_END_FRAME_1	+ (2 * DRV_COM_NbParamDb) - 2] = END_FRAME_COM_VALUE_1; 
	Array_Read_Database [COM_TX_END_FRAME_2	+ (2 * DRV_COM_NbParamDb) - 2] = END_FRAME_COM_VALUE_2; 
	Array_Read_Database [COM_TX_END_FRAME_3	+ (2 * DRV_COM_NbParamDb) -	2] = END_FRAME_COM_VALUE_3;
	
  	S0TBIR = 0;
	/* Origin index increasing - sending a byte */
	PECC2 = 0x0500; 
	/* Size of array to transmit	    */
	PECC2 |= End_Of_Table_Com_TX_Remote - 2 + (2 * DRV_COM_NbParamDb)  ; 
	/*%C Origin index on array							*/
	SRCP2 = _sof_(&Array_Read_Database); 	
	/*%C Index transformation in adress  0 segment				*/
	/*%C Destination index on  RS232 transmit register	  		*/
	DSTP2 = (UWORD16) &S0TBUF; 
	/*%C Sending datas allowed									*/
	S0TBIE = 1;
	S0TBIR = 1;
	/*%C End of transmition  				    */
 	if (DRV_COM_Transmit_Database_Full_Speed == FALSE)
	{
 	Communication_State = COM_TRANSMIT_STOP;
	}
	else
	{
/*%C No Function */
	}
	
}

