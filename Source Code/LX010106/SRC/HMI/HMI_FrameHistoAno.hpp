/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameHistoAno.hpp	     			                       	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_FrameHistoAno.cpp    				             	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef FrameHistoAnoH
#define FrameHistoAnoH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_VFrame.hpp"
#include "HMI_Label.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/
typedef enum {
   ANO_EUR_FORMAT = 0,
   ANO_US_FORMAT
} e_ANO_DATE_FORMAT;

typedef enum {
   ANO_24H_FORMAT = 0,
   ANO_12H_FORMAT
} e_ANO_TIME_FORMAT;

class FrameHistoAno : public VFrame

{

private:

   /* Parametres */

   Label LHistoAno;

   e_ANO_DATE_FORMAT AlarmDateFormat;
   e_ANO_TIME_FORMAT AlarmTimeFormat;

   /* Methodes */

   e_ANO_DATE_FORMAT GetDateFormat(void);
   void SetDateFormat(e_ANO_DATE_FORMAT _format);

   void SetTimeFormat(e_ANO_TIME_FORMAT _format);
   e_ANO_TIME_FORMAT GetTimeFormat(void);

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

	FrameHistoAno();

   void init();

   virtual void Show();
   virtual void Hide();
   virtual void RefreshLanguage();

   e_BOOL SeekEnd();

};

#endif
