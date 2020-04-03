/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameHistoAlarme.hpp	     		                       	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_FrameHistoAlarme.cpp    			             	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef FrameHistoAlarmeH
#define FrameHistoAlarmeH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_VFrame.hpp"
#include "HMI_Label.hpp"
#include "HMI_FrameAlarme.hpp"
#include "HMI_Config.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class FrameHistoAlarme : public VFrame
{

private:

   /* Parametres */

   Label LHistoAlarm;

   e_ALARM_DATE_FORMAT AlarmDateFormat;
   e_ALARM_TIME_FORMAT AlarmTimeFormat;

   /* Methodes */

   e_ALARM_DATE_FORMAT GetDateFormat(void);
   void SetDateFormat(e_ALARM_DATE_FORMAT _format);

   void SetTimeFormat(e_ALARM_TIME_FORMAT _format);
   e_ALARM_TIME_FORMAT GetTimeFormat(void);

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

	FrameHistoAlarme();

   void init();

   virtual void Show();
   virtual void Hide();
   virtual void RefreshLanguage();

   e_BOOL SeekEnd();

};

#endif
