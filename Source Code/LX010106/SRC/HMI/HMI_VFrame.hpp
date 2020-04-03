/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_VFrame.hpp 	 							 		 			  	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_VFrame.cpp 	 									     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef VFrameH
#define VFrameH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_DisplayObject.hpp"      
#include "HMI_Loupe.hpp"
#include "HMI_LoupeAlarm.hpp"
#include "HMI_Config.hpp"
extern "C"
{
#include "typedef.h"
}

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/
 
class VFrame: public DisplayObject
{

private:

   /* Parametres */

	LoupeAlarm LoupeA;

   Loupe *LoupeObject, LoupeV;

	e_BOOL   MonitorOn,
            MessageOn,
            ImpactDisplay;

   tInfo* InfoTablePtr;
   UWORD16 MaxObjects;
   UWORD16 SpaceHeight;
   UWORD16 SpaceFirstLine;

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   VFrame();

   virtual DisplayObject** GetRefreshTable();

	virtual void SetMessageOn(e_BOOL Flag);
	virtual e_BOOL IsMessageOn();

  	virtual void SetImpactDisplay(e_BOOL _ImpactDisplay);
	virtual e_BOOL GetImpactDisplay();

	void SelectLoupeAlarm();

   virtual void SetMonitorOn(e_BOOL Flag);

	virtual e_BOOL IsMonitorOn();

   virtual void Show();
   virtual void Hide();
   virtual void ShowLoupe();
   virtual void HideLoupe();

   virtual Loupe* GetLoupeObject();

   virtual void SetMode(e_MODE_TYPES Mode);
   virtual void ShowMonitoring();
   virtual void HideMonitoring();

   void SetInfoTable(   tInfo* _InfoTablePtr,
                        UWORD16 _MaxObjects,
                        UWORD16 _SpaceHeight,
                        UWORD16 _SpaceFirstLine);
   tInfo* GetInfoTable();

   e_BOOL CheckInfoTable(void);
   tInfo* GetPtrFromOrder(UWORD16 _Order, e_MODE_TYPES _Mode);
   UWORD16 GetOrderFromPtr(tInfo* _ptr, e_MODE_TYPES _Mode);
   void SwitchDisplayConfigForOneMode(  e_OBJECT _First,
                                        e_OBJECT _Second,
                                        e_MODE_TYPES _Mode);
   void SwitchDisplayConfigForAllModes( e_OBJECT _First,
                                        e_OBJECT _Second);
   virtual void RebuildFrameTree(e_MODE_TYPES Mode);
   void ObjectsShow(e_MODE_TYPES _Mode);
   virtual void ObjectsHide(e_MODE_TYPES _Mode);
   void ObjectsShow(e_MODE_TYPES _Mode, e_OBJECT _ObjectId);
   virtual void ObjectsHide(e_MODE_TYPES _Mode, e_OBJECT _ObjectId);                                                    
   void ObjectsRefreshEnable(e_BOOL _Enable);
   void ObjectsRefreshLanguage(e_MODE_TYPES _Mode);
   void ObjectsStopMonitoringMode(void);
   virtual void ObjectsStartMonitoringMode(void);   

};

#endif
