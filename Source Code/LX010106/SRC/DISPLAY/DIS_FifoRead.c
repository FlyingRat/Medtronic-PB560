/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DIS_FifoRead.c 																*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  																			*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE      													 		*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#ifndef _BORLAND
   #ifndef _TASKING
      #include "LH_ST10F276.h"
      #include <intrins.h>
   #else
      #include "regf276e.h"
   #endif
#endif
#include "typedef.h"
#include "io_declare.h"
#include "enum.h"
#include "Structure.h"
#include "Display_Data.h"
#include "Main_Data.h"
#include "DIS_FifoRead.h"
			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DIS_FifoRead(void)
	{
	UBYTE DisplayFunction;
	UBYTE *StringAddress;
	UWORD32 StringAddressCompute;
	UWORD32 ValueCompute;

	// Si la FIFO n'est pas vide on effectue le traitement sinon on ne fait rien
	if(DIS_FifoIdxWrite != DIS_FifoIdxRead)
		{
		//Lancement du timer permettant de controler le temps d'excution
		T2IR = 0;		// RAZ du flag underflow timer 3
		T2IC = 0;
		T2 = 1000;   	// 1000*200ns, duree du timer3 = 200us Temps alloué a l'exécution
							// plus maxi le temps pour une commande
		T2CON  = 0x00C0;   // count down,Prescaller 200nS FCPU/8, start timer
		//Si données dans la fifo et temps alloué à l'execution non terminé*/
	
		//Demande d'ouverture de l'afficheur
		DRV_DIS_HostRequest ( 1 ) ;
		// Délai imposé par la carte graphique de façon à attendre la libération du bus
		DRV_DIS_Delay_us(1);
		if(MASTERBUSY == FALSE)
			{
			while((DIS_FifoIdxWrite != DIS_FifoIdxRead) && (T2IR == 0))
				{
			
				DisplayFunction = (UBYTE)  DIS_FifoDisplay[DIS_FifoIdxRead].DisplayFunction;
			
				switch (DisplayFunction)
					{
					case	DRV_INIT	:
						{
	
						}
						break;
					case	DRV_LOAD_TABLE	:	
						{
						}			
						break;
					case	DRV_BACKLIHGHTADJUST :
						{
						DRV_DIS_grBackLight(DIS_FifoDisplay[DIS_FifoIdxRead].Param1);
						}			
						break;
					
					case	DRV_BRITHNESSAJUST:
						{
						DRV_DIS_grSetContrast(DIS_FifoDisplay[DIS_FifoIdxRead].Param1);
						}			
						break;
					
					case	DRV_NEGATIVE_CAR:
						{
						DRV_DIS_grNegative(DIS_FifoDisplay[DIS_FifoIdxRead].Param1);
						}			
						break;
					
					case	DRV_DISPLAY_PAGE:	
						{
						DIS_DisplayPage((UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param1, 4); 
						}			
						break;
					
					case	DRV_STRING:				
						{
						StringAddressCompute = ((UWORD32)DIS_FifoDisplay[DIS_FifoIdxRead].Param1 << 16) & 0xFFFF0000;
						StringAddressCompute |= (UWORD32)DIS_FifoDisplay[DIS_FifoIdxRead].Param2 & 0x0000FFFF; 
						StringAddress = (UBYTE *)StringAddressCompute; 
						DIS_String(StringAddress,
										(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param3,
										(SWORD16)DIS_FifoDisplay[DIS_FifoIdxRead].Param4,
										(UWORD16)DIS_FifoDisplay[DIS_FifoIdxRead].Param5,
										(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param6,
										(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param7);
						}			
						break;
					
					case  DRV_NUMBER:				
						{
						ValueCompute = ((UWORD32)DIS_FifoDisplay[DIS_FifoIdxRead].Param1 << 16) & 0xFFFF0000;
						ValueCompute |= (UWORD32)DIS_FifoDisplay[DIS_FifoIdxRead].Param2 & 0x0000FFFF;
								
						DIS_Number((SWORD32)ValueCompute,
										(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param3,
										(SWORD16)DIS_FifoDisplay[DIS_FifoIdxRead].Param4,
										(UWORD16)DIS_FifoDisplay[DIS_FifoIdxRead].Param5,
										(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param6,
										(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param7,
										DIS_FifoDisplay[DIS_FifoIdxRead].Param8,
										(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param9,
										(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param10); 
						}			
						break;
					
					case	DRV_SYMBOL:
						{
						DIS_Symbol((UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param1,
										(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param2,
										DIS_FifoDisplay[DIS_FifoIdxRead].Param3,
										(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param4);
						}			
						break;
					
					case	DRV_PIXEL:					
						{
			 			DIS_Pixel((UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param1,
									(UWORD16)DIS_FifoDisplay[DIS_FifoIdxRead].Param2,
									(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param3,
									(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param6);
						}			
						break;
	
					case	DRV_LINE:					
						{
			 			DIS_Line((UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param1,
									(UWORD16)DIS_FifoDisplay[DIS_FifoIdxRead].Param2,
									(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param3,
									(UWORD16)DIS_FifoDisplay[DIS_FifoIdxRead].Param4,
									(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param5,
									(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param6);
						}			
						break;
					
					case	DRV_BOX:					
						{
						DIS_Box((UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param1,
									(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param2,
									(UWORD16)DIS_FifoDisplay[DIS_FifoIdxRead].Param3,
									(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param4,
									(UWORD16)DIS_FifoDisplay[DIS_FifoIdxRead].Param5,
									(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param6,
									(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param7);
						}			
						break;
	
					case	DRV_ERASE_ZONE:			
						{
					   DIS_EraseZone((UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param1,
											(UWORD16)DIS_FifoDisplay[DIS_FifoIdxRead].Param2,
											(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param3,
											(UWORD16)DIS_FifoDisplay[DIS_FifoIdxRead].Param4,
											(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param5,
											(UBYTE)DIS_FifoDisplay[DIS_FifoIdxRead].Param6);
						}			
						break;
					
					case	DRV_ERASE_PAGE	:		
						{
						DIS_ErasePage(DIS_FifoDisplay[DIS_FifoIdxRead].Param1); 
						}			
						break;
	
					default:
						break; 	
					}
			DIS_FifoIdxRead++	;
			if (DIS_FifoIdxRead >= FIFO_DISPLAY_SIZE) DIS_FifoIdxRead = 0; 
			}
		}
		//Fermeture de l'afficheur
		DRV_DIS_HostRequest (0) ;
		T2CON = 0x0000;     // stop Timer2
	}
}
