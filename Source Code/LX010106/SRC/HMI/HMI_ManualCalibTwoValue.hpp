/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_ManualCalibTwoValue.hpp 				   	          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_ManualCalibTwoValue.cpp 			  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef ManualCalibTwoValueH
#define ManualCalibTwoValueH


/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_ManualCalibValue.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class ManualCalibTwoValue: public ManualCalibValue
{

private:
 
   /* Parametres */
   
   /* Methodes */

    LabelOneValue Value2;

protected:
 
   /* Parametres */
   
   /* Methodes */

public:
 
   /* Parametres */
   
   /* Methodes */

   ManualCalibTwoValue();

   virtual void SetLine(UWORD16 Line);

   void SetNameUnit2(UBYTE** _NameUnit2);
   void SetVisible(e_BOOL V);      

   virtual void InitValue2(UWORD16 IdCalibParam,
                           e_TYPE_OF_DB_TARGET BdCalibParam,
                           UBYTE **Name,
                           UWORD16 Line,
                           UWORD16 Col,
                           UBYTE **NameUnit,
                           UBYTE **Sep,
						   UWORD16 ColSep);

   void SetMaxDisplayValue2(UWORD16 _MaxDisplayValue);						   

   virtual void StopMonitoringMode();
   virtual void StartMonitoringMode();
   virtual void Refresh();
   virtual void Show();
   virtual void Hide();
   virtual void Blink(e_BOOL Actif);
   virtual void RefreshLanguage();

   virtual void ModifNextValue();
   virtual void StopModifMode();
	virtual void StartModifMode();
   virtual void StartModifModeConsult();
   virtual void StopModifModeConsult();
   virtual e_BOOL ModifNextValueConsult();

};

#endif
