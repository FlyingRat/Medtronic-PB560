/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_MessageDelayed.hpp 	 		  			 		          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_MessageDelayed.cpp					  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef MessageDelayedH
#define MessageDelayedH

								
/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "typedef.h"
#include "HMI_VTimer.hpp"
#include "HMI_MessageDialog.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/
#define MAX_FIFO 6

class MessageDelayed
{
private:
   typedef struct 
   {
	UBYTE* Body;
	UWORD32 Delay;
	} FifoMessage;

   /* Parametres */

   e_BOOL Configured;

   UWORD32 TimerLoad;

   UWORD16 TimerId;

	VTimer* TimerPtr;

	MessageDialog* MessDiagPtr;

   FifoMessage MessageFifo[MAX_FIFO];

   UWORD16 ReadIndex;

   UWORD16 WriteIndex;

   /* Methodes */

   void SetMessDiagPtr(MessageDialog* _MessaDiagPtr);
   MessageDialog* GetMessDiagPtr();

   void SetTimerPtr(VTimer* _TimerPtr);
   VTimer* GetTimerPtr();

   void SetTimerLoad(UWORD32 _TimerLoad);
   UWORD32 GetTimerLoad();

   void SetTimerId(UWORD16 _TimerId);
   UWORD16 GetTimerId();

   void SetConfigured(e_BOOL _Configured);
   e_BOOL GetConfigured();

   void ResetFifo();

	void DisplayMessageFromQueue(e_BOOL _DisplayFlag);

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   MessageDelayed();

   void Init(  VTimer* _TimerPtr,
               MessageDialog* _MessaDiagPtr,
               UWORD16 _TimedId);

   void TimerHandler(e_BOOL _DisplayFlag);

   UWORD16 AddMessageToQueue(	UBYTE* _Message, 
								UWORD32 _Delay,	
								e_BOOL _DisplayFlag);

   UWORD16 GetNbOfMessagesInQueue();                        

};

#endif
