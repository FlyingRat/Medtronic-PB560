/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_InterfaceCppC.hpp	  		                             	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_InterfaceCppC.cpp  	    	               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef INTERFACECPPCH
#define INTERFACECPPCH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/
#include "HMI_IhmType.hpp"
extern "C"
{
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_Rtc.h"
#include "DB_Current.h"
#include "DB_Compute.h"
#include "DB_PowerSupply.h"
#include "DB_EventMngt.h"
#include "DIS_DisplayPage.h"
}


 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class InterfaceCppC
{
private:

	/* Methodes */

protected:

	/* Parametres */
	
	/* Methodes */
	
public:

	/* Paramettres */
	
	/* Methodes */

	static e_BOOL DB_Request(				UWORD16 *Value , 
													UWORD16 Id, 
													e_TYPE_OF_DB_TARGET DbType, 
													e_DATA_OPERATION DataOp);

	static void DisplayPixel(				UWORD16 Line,
													UWORD16 Column,
													UWORD16 PrintOn,
													UWORD16 Page);

	static void DisplayCross(	UWORD16 Line,
								 UWORD16 Column,
								 UWORD16 Line1Size,
								 UWORD16 Line2Size,
								 UWORD16 PrintOn,
								 UWORD16 Page);


	static void DisplaySymbol(				UWORD16 Symbol,
													UWORD16 Line,
													UWORD16 Column,
													UWORD16 Page); 

	static void DisplayString(				UBYTE *ptr_char,
													UWORD16 Font,
													e_BOOL ReverseVideo,
													UWORD16 Line,
													UWORD16 Column,
													UWORD16 PrintOn,
													UWORD16 Page); 

	static void DisplayNumber(				SWORD32 Value,
													UWORD16 Nature,
													e_BOOL ReverseVideo,
													UWORD16 Line,
													UWORD16 Column,
													UWORD16 Font,
													UWORD16 Nb_Digit,
													e_BOOL Zero,
													UWORD16 PrintOn,
													UWORD16 Page);

	static void DisBox(						UWORD16 Line, 
													UWORD16 Column,
													UWORD16 Heigth, 
													UWORD16 Width,
													e_BOOL FloodBlack,
													UWORD16 PrintOn, 
													UWORD16 Page);

	static void EraseZone(					UWORD16 Line, 
													UWORD16 Column,
													UWORD16 Heigth, 
													UWORD16 Width,
													UWORD16 PrintOn, 
													UWORD16 Page);

	static void DisplayLine(				SWORD16 Line, 
													SWORD16 Column,
													SWORD16 Heigth, 
													SWORD16 Width,
													UWORD16 PrintOn, 
													UWORD16 Page);

	static void DisplayHorDottetLine(	UWORD16 Line, 
													UWORD16 Column, 
													SWORD16 Length,
													UWORD16 IndentLength, 
													UWORD16 BlankLength, 
													UWORD16 PrintOn, 
													UWORD16 Page);

	static void DisplayDottetLine(		UWORD16 Line, 
													UWORD16 Column,
													SWORD16 Heigth, 
													SWORD16 Width,
													UWORD16 PrintOn, 
													UWORD16 Page,
													UWORD16 EmptyLength,
													UWORD16 FullLength);

	static void ErazePage(UWORD16 NumPage);
	static void DisplayPage(UWORD16 NumPage);
	static void DisplayBrithness(UWORD16 Value);

 	static void ActiveLed(e_TYPE_OF_LED Led, e_BOOL On);
	static void ActiveLed(e_TYPE_OF_LED Led, e_TYPE_BLINK Blink);
   static void ActiveBuzzer(e_TYPE_SOUND sound, e_NUMBER_BUZ NumBuzzer);   
	
	static UWORD16 GetDriverFont(UWORD16 PrgFont,e_BOOL ReverseVideo);
	static UWORD16 GetDriverPrintOn(UWORD16 PrgPrintOn);
	static UWORD16 GetDriverNature(UWORD16 PrgNature);
	static UWORD16 GetDriverPage(UWORD16 PrgPage);
	static UWORD16 GetDriverColor(UWORD16 PrgColor);
	
	static UWORD16 FlashReadEvent(UWORD16 NumEvent,
													      e_EVENT_PARAMETERS IdEvent,
													      UWORD16 *PtrRetrieval);

    static void FlashWriteEvent(UWORD16 NumEvent);

	static void MaintEraseFlashMngt(void);

	static void EraseNANDFlashMngt(void);

	static e_BOOL IsOneAlarmActive();    
			
};

extern "C" void DB_ControlWrite(e_DB_CONTROL Id,
							UWORD16 Value);

extern "C" UWORD16 DB_ControlRead(e_DB_CONTROL Id); 


extern "C" UWORD16 DB_ConfigWrite(e_DB_CONFIG Id,
							  UWORD16 Value);

extern "C" void DIS_FifoWrite(UWORD16 DisplayFunction,
                          UWORD16 Param1,
                          UWORD16 Param2,
                          UWORD16 Param3,
                          UWORD16 Param4,
													UWORD16 Param5,
													UWORD16 Param6,
													UWORD16 Param7,
													UWORD16 Param8,
													UWORD16 Param9,
													UWORD16 Param10,
													UWORD16 Param11,
													UWORD16 Param12);


extern "C" e_DRV_EVENT_STATE DRV_EVENT_TransStateFlash(void);

extern "C" UBYTE DRV_EVENT_Read_Event(UWORD16 num_event,
                                  e_EVENT_PARAMETERS id_event,
                                  UWORD16 xhuge *Ptr_retrieval);

extern "C" void DB_EventMngt (UWORD16 Value);
extern "C" UWORD16 DB_IhmAccessParaDataBase(UWORD16 *Value,
													              UWORD16 Id,
													              e_TYPE_OF_DB_TARGET DbType,
													              e_DATA_OPERATION DataOperation);

extern "C" void DRV_EVENT_RazPointerSector(void);

extern "C" e_BOOL DB_AlarmIsOneActive(void);

extern "C" void DRV_NAND_Erase_Flash(void);


#endif
