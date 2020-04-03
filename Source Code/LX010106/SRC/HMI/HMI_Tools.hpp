/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Tools.hpp 	 								 		 			  	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_Tools.cpp 				 						     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef ToolsH
#define ToolsH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

extern "C"
{
#include "typedef.h"
#include "enum.h"
#include "Db_PowerSupply.h"
}
#include "HMI_IhmType.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/
#define cARRAY_SIZE     100
#define cMAX_CHARACTER  33
#define cMAX_LINE       3

#define DISPLAY_WINDOW_WIDTH  320
#define DISPLAY_WINDOW_HEIGHT 240

typedef enum
{
   PANIC_MODULE_VENTIL = 0,
   PANIC_MODULE_ALARM,
   PANIC_MODULE_GRAPH,
   PANIC_MODULE_EVENT_NODE_VENTIL,
   PANIC_MODULE_EVENT_NODE_ALARM,
   PANIC_MODULE_EVENT_NODE_MAINT_CALIB,
   PANIC_MODULE_FRAME_GRAPH,
   PANIC_MODULE_UNKNOWN,
   PANIC_MODULE_MAX
} ePANIC_MODULE;

class Tools
{

private:

	/* Parametres */

	/* Methodes */

protected:

	/* Parametres */

	/* Methodes */

public:

	/* Parametres */

	/* Methodes */
   static e_BOOL CheckInfoNodeTable(UWORD16 _FirstNode, UWORD16 _LastNode);

   static UWORD16 GetInfoNodeIndex(UWORD16 _NodeId);    

   static void Panic(ePANIC_MODULE _panic_module);   

	static UWORD16 GetNumFrame(UWORD16 IdNode);

	static e_BOOL IsVisibleWhithMode(UWORD16 NodeId,
                                    e_MODE_TYPES Mode);

	static e_BOOL IsLockWhithLock(UWORD16 NodeId);

   static UWORD16 GetOrderWithMode(UWORD16 _NodeId, e_MODE_TYPES _Mode);

   static UWORD16 GetIdFromOrder(UWORD16 _Order,
                              e_MODE_TYPES _Mode,
                              UWORD16 _FirstNode,
                              UWORD16 _LastNode);

   static void SwitchDisplayConfigForOneMode(   UWORD16 _First,
                                                UWORD16 _Second,
                                                e_MODE_TYPES _Mode);

   static void SwitchDisplayConfigForAllModes(  UWORD16 _First,
                                                UWORD16 _Second);

	static UWORD16 FindNbDigit(UWORD16 Number);

	static e_BOOL IsModifyNode(UWORD16 IdNode);

	static UWORD16 StrLen(UBYTE* Text);

	static UBYTE* StrCpy(UBYTE* Dest, UBYTE* Src);

	static UBYTE* GetVersionSoft();

   static UBYTE* GetVersionSoftSupply();

   static UBYTE* GetProductSerialNumber();      

	static UWORD16 GetStringPixelSize(UBYTE* Text, UWORD16 Font);

	static UWORD16 GetNumberPixelSize(  UWORD16 Number,
                                       UWORD16 Font,
                                       e_BOOL IsFloat);

   static e_BOOL IsFloat(SWORD16 F);

	static SWORD32 Abs(SWORD32 S);

   static UBYTE* BuildMessage(UBYTE* Text ,
                              UWORD16 SizeBox ,
                              UWORD16 BoxFont);

   static void SetFontConfigForLang(UWORD16 _Lang);
	
   static UBYTE* GetFontWidthConfig(); 
   
	static void ShortBipRequest(void);                                

};

#endif
