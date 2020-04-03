/********************************************************************************/
/*                                                                            	*/
/* Project N°  :  RB0505                                                      	*/
/*                                                                            	*/
/*----------------------------------------------------------------------------	*/
/*                                                                            	*/
/* Filename  : DRV_COM_Read_Buffer.c                         					*/
/*                                                                            	*/
/*----------------------------------------------------------------------------	*/

/*----------------------------------------------------------------------------*/


/********************************************************************************/
/*%C                     Functionnal description :                            	*/
/*%C                     														*/					
/*%C	SI pas données dans le buffer											*/
/*%C	|	On ne fait rien														*/
/*%C	SINON 																	*/
/*%C	|	SI plus de 20 octets 	dans le buffer 								*/
/*%C	|	|	Indiquer communication occupée									*/
/*%C	|	SINON 																*/
/*%C	|	|	Indiquer communication prête									*/
/*%C	|	FSI																	*/
/*%C	|																		*/
/*%C	|	Recherche de début de trame sans dépasser l'index  d'écriture		*/
/*%C	|																		*/
/*%C	|	SI 5 données dans le buffer											*/
/*%C	|	|	SI  entête de trame												*/
/*%C	|	|	|	 Calculer longueur de la trame à recevoir				   	*/
/*%C	|	|	|	 SI trame complète 											*/
/*%C	|	|	|	 |	SI fin de trame correct									*/
/*%C	|	|	|	 |	|	Attribuer les données recues						*/
/*%C	|	|	|	 |	SINON													*/
/*%C	|	|	|	 |	|	Incrémenter l'index de lecture						*/
/*%C	|	|	|	 |	FSI														*/
/*%C	|	|	|	SINON														*/
/*%C	|	|	|	 |															*/
/*%C	|	|	|	FSI															*/
/*%C	|	|	SINON 															*/
/*%C	|	|	|	Incrémenter l'index de lecture								*/
/*%C	|	|	FSI																*/
/*%C	|	SINON																*/
/*%C	|	|	On ne fait rien													*/
/*%C	|	FSI																	*/
/*%C    FSI                                                                     */
/********************************************************************************/
/*%I Input Parameter : NONE                                                  	*/
/*%IO Input/Output : NONE                                                     	*/
/*%O Output Parameter : NONE                                                  	*/
/********************************************************************************/


/********************************************************************************/
/*                                INCLUDE FILES		                           	*/
/********************************************************************************/


#include "typedef.h"
#include "enum.h"
#include "DB_Control.h"
#include "DRV_COM_Data.h"
#include "DRV_COM_Read_Buffer.h"



/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_COM_Read_Buffer(void)
{
	UBYTE SizeOfFrame = 0; 
	
	/*%C Si pas de donnees dans le buffer, on quitte la fonction */ 
	if (DRV_COM_Ptr_Read_Buffer_Rx == DRV_COM_Ptr_Write_Buffer_Rx) 
	{
			 /*%C pas de fonction */						
	}
	/*%C Sinon on analyse le buffer */
	else
	{
		/*%C si plus de 20 octets 	dans le buffer indiquer communication occupée */
	 	if (((COM_RX_BufferSize - DRV_COM_Ptr_Read_Buffer_Rx + DRV_COM_Ptr_Write_Buffer_Rx)%COM_RX_BufferSize) > COM_NB_MAX_RECEIVED_DATA )
		{
			
			DB_ControlWrite(COM_READY_U16, FALSE);
		}
		/*%C sinon Indiquer communication prête */
		else
		{
			DB_ControlWrite(COM_READY_U16, TRUE);
		}
	 
		/*%C recherche de début de trame sans dépasser l'index  d'écriture */
		while ((DRV_COM_Buffer_Of_Receipt[DRV_COM_Ptr_Read_Buffer_Rx % COM_RX_BufferSize] != START_FRAME_COM_VALUE_1) 
				&& (DRV_COM_Ptr_Read_Buffer_Rx != DRV_COM_Ptr_Write_Buffer_Rx ))
		{
			DRV_COM_Ptr_Read_Buffer_Rx =(UBYTE) ((DRV_COM_Ptr_Read_Buffer_Rx + 1) % COM_RX_BufferSize);
		}
	
		/*%C si entête complète,indentifiant commande de trame,nombre d'arguments	présent dans le buffer */
		if (((COM_RX_BufferSize - DRV_COM_Ptr_Read_Buffer_Rx + DRV_COM_Ptr_Write_Buffer_Rx)	% COM_RX_BufferSize) > COM_RX_NB_ARG )
		{ 
	
			/*%C si  entête de trame */
		 	if ((DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + COM_RX_B1_START_FRAME) % COM_RX_BufferSize] == START_FRAME_COM_VALUE_1 )
			   && (DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + COM_RX_B2_START_FRAME) % COM_RX_BufferSize] == START_FRAME_COM_VALUE_2)
			   && (DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + COM_RX_B3_START_FRAME) % COM_RX_BufferSize] == START_FRAME_COM_VALUE_3)
			   )
			  {
				/*%C calculer longueur de la trame à recevoir */
				switch (DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + COM_RX_COMMAND) % COM_RX_BufferSize])
				{
					case CMD_TRANSMIT_DATABASE	    :{SizeOfFrame = (UBYTE)(2*DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + COM_RX_NB_ARG)% COM_RX_BufferSize]+8);
														DRV_COM_NbParamDb = (UBYTE)(DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + COM_RX_NB_ARG) % COM_RX_BufferSize]);break;}
					case CMD_TRANSMIT_DATABASE_FULL_SPEED  :{SizeOfFrame = (UBYTE)(2*DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + COM_RX_NB_ARG)% COM_RX_BufferSize]+8);
														DRV_COM_NbParamDb = (UBYTE)(DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + COM_RX_NB_ARG) % COM_RX_BufferSize]);break;}
					case CMD_RECEIVE_DATABASE  		:{SizeOfFrame = 12;	break;}
					case CMD_RECEIVE_SERIAL_NUMBER	:{SizeOfFrame = 19;	break;}
					case CMD_RECEIVE_MACHINE_COUNTER:{SizeOfFrame = 9; 	break;}
					case CMD_START_TRANSMIT_DETAILLED_MONITORING_ON_KEY:{SizeOfFrame = 8; 
														DRV_COM_Param = (UBYTE)(DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + COM_RX_COMMAND + 1) % COM_RX_BufferSize]);break;}
					default							:{SizeOfFrame = 7;	break;}
				}
	
				/*%C  si trame complète */ 
			   	if (((COM_RX_BufferSize - DRV_COM_Ptr_Read_Buffer_Rx + DRV_COM_Ptr_Write_Buffer_Rx)	% COM_RX_BufferSize) >= SizeOfFrame)
				{ 
			   		/*%C si fin de trame correct */
				 	if ((DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + SizeOfFrame-3) % COM_RX_BufferSize] == END_FRAME_COM_VALUE_1 )
					   && (DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + SizeOfFrame-2) % COM_RX_BufferSize] == END_FRAME_COM_VALUE_2)
					   && (DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + SizeOfFrame-1) % COM_RX_BufferSize] == END_FRAME_COM_VALUE_3)
					   )
					{
					   /*%C traitement des données recues */
					   DRV_COM_Treatment_Buffer();
					   /*%C Incrémenter l'index de lecture de la taille de trame */
					   DRV_COM_Ptr_Read_Buffer_Rx = (UBYTE)((DRV_COM_Ptr_Read_Buffer_Rx+SizeOfFrame) % COM_RX_BufferSize);

					}
					else
					{
						/*%C Incrémenter l'index de lecture	*/
						DRV_COM_Ptr_Read_Buffer_Rx = (UBYTE)((DRV_COM_Ptr_Read_Buffer_Rx+1) % COM_RX_BufferSize);
	
					}
				}
				else
				{
					/*%C pas de fonction */
				}
			}
			else
			{
				/*%C Incrémenter l'index de lecture */
				DRV_COM_Ptr_Read_Buffer_Rx = (UBYTE)((DRV_COM_Ptr_Read_Buffer_Rx+1) % COM_RX_BufferSize);
			}
		}
		else
		{
			/*%C pas de fonction */
		}
	}
}

