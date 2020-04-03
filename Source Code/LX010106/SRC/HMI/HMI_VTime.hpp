/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_VTime.hpp                            	 	  						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Classe declaration for HMI_VTime.cpp	                         				*/
/*		                                                                   	 	*/
/******************************************************************************/

#ifndef VTimeH
#define VTimeH

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_Label.hpp"
#include "HMI_EditableObject.hpp"
#include "HMI_TextField.hpp"
#include "HMI_ValueField.hpp"
#include "HMI_IhmType.hpp"

typedef enum {
   VTIME_24H_FORMAT = 0,
   VTIME_12H_FORMAT
} e_VTIME_FORMAT;

/******************************************************************************/
/*                           CLASSE DECLARATION                    	      	*/
/******************************************************************************/
class VTime : public EditableObject
{
private:

   /* Parametres */
	typedef enum {AM = 0, PM} e_PERIOD;

	/*%C SecVisible [ 0 : 1] */
   e_BOOL SecVisible; 
	/*%C Suffixe [ 0 : 1] */
   e_PERIOD Suffixe;

   e_BOOL ForcedSuffixUpdate;

	/*%C FSep [ ? : ?] */
   TextField FSep;
	/*%C FSepHours [ ? : ?] */
   TextField FSepHours;
	/*%C FSepMin [ ? : ?] */
   TextField FSepMin;
	/*%C FSuffixe [ ? : ?] */
   TextField FSuffixe;

	/*%C FHours [ ? : ?] */
   ValueField FHours;
	/*%C FMin [ ? : ?] */
   ValueField FMin;
	/*%C FSec [ ? : ?] */
   ValueField FSec;

	/*%C ValueState [ 1 : 3] */
   UWORD16 ValueState;

	/*%C IdParam2 [ 0 : 65535] */
   UWORD16 IdParam2;
	/*%C IdParam3 [ 0 : 65535] */
   UWORD16 IdParam3;
	/*%C IdParamReg1 [ 0 : 65535] */
   UWORD16 IdParamReg1;
	/*%C IdParamReg2 [ 0 : 65535] */
   UWORD16 IdParamReg2;
	/*%C IdParamReg3 [ 0 : 65535] */
   UWORD16 IdParamReg3;

   e_VTIME_FORMAT VTimeFormat;

   e_BOOL StopMonitoring;

   /* Méthodes */

protected:

   /* Parametres */

   /* Méthodes */

public:

   /* Parametres */

   /* Méthodes */

   VTime();
   void Format();

   void SetVTimeFormat(e_VTIME_FORMAT _format);
   e_VTIME_FORMAT GetVTimeFormat();

   UBYTE* GetSep(void);
   void SetSep(UBYTE* Sep);

   UBYTE* GetTextSuffixe(void);
   void SetTextSuffixe(UBYTE* Suffixe);


   UBYTE* GetSepHours(void);
   void SetSepHours(UBYTE* SepHours);
   e_BOOL GetSecVisible();
   void SetSecVisible (e_BOOL SecVisible);
   UWORD16 GetHours(void);
   void SetHours(UWORD16 Hours);
   UWORD16 GetMin(void);
   void SetMin(UWORD16 Min);
   UWORD16 GetSec(void);
   void SetSec(UWORD16 Sec);
   UWORD16 getColSep();
   void SetColSep(UWORD16 ColSep);
   UWORD16 getColHours();
   void SetColHours(UWORD16 ColHours);
   void SetFontHours(UWORD16 Font);
   e_BOOL IsSecVisible();
   UWORD16 GetValueState();
   void SetValueState(UWORD16 ValueState);

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

   void InitDbAccess(UWORD16 IdParamHours,
                     e_TYPE_OF_DB_TARGET DbTarget,
                     UWORD16 IdParamMin ,
                     UWORD16 IdParamSec,
                     UWORD16 IdParamRegHours ,
                     UWORD16 IdParamRegSec,
                     UWORD16 IdParamRegMin);

   void SetStopMonitoring(e_BOOL Flag);
   e_BOOL IsStopMonitoring();

   /* virtual */
   virtual void StopMonitoringMode();
   virtual void StartMonitoringMode();
   virtual void ConfirmModifValue(e_BOOL Confirm);
   virtual void Refresh();
   virtual void Show();
   virtual void Hide();
   virtual void Blink(e_BOOL Actif);
   virtual void IncreaseValue();
   virtual void DecreaseValue();
   virtual e_BOOL IncreaseValueOk(UWORD16* Val);
   virtual e_BOOL DecreaseValueOk(UWORD16* Val);
   virtual void StartModifMode();
   virtual void ModifNextValue();
   virtual void SetVisible(e_BOOL V);   
};
//---------------------------------------------------------------------------
#endif
