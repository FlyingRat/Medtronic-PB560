/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameTendance.hpp                             	  				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_FrameTendance.cpp                   				*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef FrameTendanceH
#define FrameTendanceH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/
#include "HMI_Config.hpp"
#include "HMI_VFrame.hpp"
#include "HMI_Label.hpp"
#include "HMI_TendanceTable.hpp"
#include "HMI_LabelTwoValue.hpp"
#include "HMI_VDate.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class FrameTendance: public VFrame

{

private:

   /* Parametres */

	Label LTendance, TableTitle;
   
	TendanceTable GTable;
#ifdef HMI_CONFIG_TREND_SIGMA
	LabelTwoValue 	LTVVt, LTVVte, LTVLeak, LTVVm, LTVFr,
						LTVPi, LTVSpo2, LTVFc;
#else
	LabelOneValue 	LTVVt, LTVVte, LTVLeak, LTVVm, LTVFr,
						LTVPi, LTVSpo2, LTVFc;
#endif
	LabelOneValue  LOVSpont, LOVContr, LTVIA, LTVTApnea;

   LabelTwoValue  LOVVentMoy;

   VDate Date;

   	LabelOneValue LOVMachine;
	
   LabelTwoValue LTVPatient;

	/* Methodes */

protected:

   /* Paramettres */

   /* Methodes */

public:
   /* Paramettres */

   /* Methodes */

	FrameTendance();

   void SetPressureUnit(UBYTE** _PressureUnit);   
   
   void init();

   virtual void Show();
   virtual void Hide();
   virtual void RefreshLanguage();

};

#endif
