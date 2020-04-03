/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_VDate.hpp 									 		 			  	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_VDate.cpp											     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef VDateH
#define VDateH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_Label.hpp"
#include "HMI_EditableObject.hpp"
#include "HMI_TextField.hpp"
#include "HMI_ValueField.hpp"
#include "HMI_IhmType.hpp"

typedef enum {
   VDATE_EUR_FORMAT = 0,
   VDATE_US_FORMAT
} e_VDATE_FORMAT;

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class VDate : public EditableObject

{

private:

   /* Parametres */

   TextField   FSep,
               FMonth;

   ValueField  FDay,
               FYears;

   UBYTE **NameMonth;

   UWORD16  Month,
            ValueState;

   UWORD16  IdParam2,
            IdParam3,
            IdParamReg1,
            IdParamReg2,
            IdParamReg3;

   UWORD16 ColBackup;            

   e_TYPE_OF_DB_TARGET IdDbParamReg;

   e_VDATE_FORMAT VDateFormat;

   e_BOOL StopMonitoring;

   /* Methodes */

   void SetColBackup(UWORD16 _colbackup);
   UWORD16 GetColBackup();

   void UpdateValues();

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   VDate();

   void InitDbAccess(UWORD16 IdParamDay,
                     e_TYPE_OF_DB_TARGET DbTarget,
                     UWORD16 IdParamMonth ,
                     UWORD16 IdParamYears,
                     UWORD16 IdParamRegDay ,
                     UWORD16 IdParamRegMonth,
                     UWORD16 IdParamRegYears,
                     e_TYPE_OF_DB_TARGET IdDbParamReg);

   void Format();

   void SetVDateFormat(e_VDATE_FORMAT _format);
   e_VDATE_FORMAT GetVDateFormat();      
   
   UBYTE* GetSep(void);
   void SetSep(UBYTE* Separateur);
   
   UBYTE* GetNameMonth(void);
   void SetNameMonth(UBYTE** NameMonth);
   
   UWORD16 GetDay(void);
   void SetDay(UWORD16 Day);
   
   UWORD16 GetYear(void);
   void SetYear(UWORD16 Year);
   
   UWORD16 GetMonth(void);
   void SetMonth(UWORD16 Month);
   
   UWORD16 GetColSep();
   void SetColSep(UWORD16 ColSep);
   
   UWORD16 GetColDate();
   void SetColDate(UWORD16 ColDate);
   
   void SetFontDate(UWORD16 Font);
   
   UWORD16 GetValueState();
   void SetValueState(UWORD16 ValueState);

   void SetDate(int Day,int Month,int Year);

   void SetIdParam2(UWORD16 IdParam2);
   UWORD16 GetIdParam2();
   
   void SetIdParam3(UWORD16 IdParam3);
   UWORD16 GetIdParam3();
   
   void SetIdParamReg1(UWORD16 IdParamReg1);
   UWORD16 GetIdParamReg1();
   
   void SetIdParamReg2(UWORD16 IdParamReg2);
   UWORD16 GetIdParamReg2();
   
   void SetIdParamReg3(UWORD16 IdParamReg3);
   UWORD16 GetIdParamReg3();
   
   void SetIdDbParamReg(e_TYPE_OF_DB_TARGET IdDbParamReg);
   e_TYPE_OF_DB_TARGET GetIdDbParamReg();

   void SetStopMonitoring(e_BOOL Flag);
   e_BOOL IsStopMonitoring();

   /* virtual */
   virtual void StopMonitoringMode();
   virtual void StartMonitoringMode();
   virtual void ConfirmModifValue(e_BOOL Confirm);
   virtual void SetInvertVideo(e_BOOL InvertVideo);
   virtual void Refresh();
   virtual void Show();
   virtual void Hide();
   virtual void Blink(e_BOOL Actif);
   virtual void IncreaseValue();
   virtual void DecreaseValue();
 
   virtual e_BOOL IncreaseValueOk(UWORD16* Val);
   virtual e_BOOL DecreaseValueOk(UWORD16* Val);
 
   virtual void StartModifMode();
   virtual void StopModifMode();
   virtual void ModifNextValue();
   virtual void RefreshLanguage();
   virtual void SetVisible(e_BOOL V);    

};

#endif
