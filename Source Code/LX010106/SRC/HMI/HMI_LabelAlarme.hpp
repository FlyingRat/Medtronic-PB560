/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelAlarme.hpp 		  		                             	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelAlarme.cpp   		   	               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelAlarmeH
#define LabelAlarmeH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_Label.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelAlarme: public Label
{

private:
    
   /* Parametres */
   
   /* Methodes */

protected:
   
   /* Parametres */

   UWORD16 AlarmId;
   
   /* Methodes */
	
public:
    
   /* Parametres */
   
   /* Methodes */

   LabelAlarme();

   virtual UBYTE* GetName();

   virtual void SetAlarmId(UWORD16 AlarmId);
	UWORD16 GetAlarmId();

   virtual void RemoveAlarmId(UWORD16 AlarmId);

   virtual void RefreshLanguage();

};

#endif
