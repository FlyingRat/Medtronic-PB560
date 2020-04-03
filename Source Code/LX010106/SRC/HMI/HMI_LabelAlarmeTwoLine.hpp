/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelAlarmeTwoLine.hpp  	                             	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelAlarmeTwoLine.cpp     	               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelAlarmeTwoLineH
#define LabelAlarmeTwoLineH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelAlarme.hpp"
#include "HMI_TextField.hpp"
#include "HMI_Tools.hpp"
#include "HMI_MessageList.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelAlarmeTwoLine: public LabelAlarme
{

private:

   /* Parametres */

   TextField FLine2;

   UBYTE TextLine[cMAX_LINE][cMAX_CHARACTER];

   UWORD16 WBox;

   MessageList AlarmList;
   
   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Paramettres */

   /* Methodes */

   LabelAlarmeTwoLine();

   virtual void Show();
   virtual void Hide();

   void Init(  e_SYMBOL Icon,
               UBYTE **Name,
               UWORD16 Line,
               UWORD16 Col);

   void SetText(UBYTE* Text);
   void SetAlarmId(UWORD16 AlarmId);
   void SetWhithBox(UWORD16 WBox);
   void SetInvertVideo(e_BOOL Actif);
   void RemoveAlarmId(UWORD16 AlarmId);
   void RemoveAllAlarms(void);   

};

#endif
