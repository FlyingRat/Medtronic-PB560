/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_EventNode.hpp	     		                              	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_EventNode.cpp	    	                     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef EventNodeH
#define EventNodeH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

extern "C"
{
#include "typedef.h"
}

#include "HMI_Controller.hpp"
#include "HMI_GlobalEventNode.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class EventNode
{

private:

	/* Parametres */

	UWORD16 Id;
   UWORD16 LinkedMenuControlNodeId;
   
   UWORD16 IdNodeOnUp;
   UWORD16 IdNodeOnDown;
   UWORD16 IdNodeOnTimeOut;
   UWORD16 IdNodeOnValid;
 	UWORD16 IdNodeOnLongValid;
 	UWORD16 IdNodeOnMonitor;

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:
     
   /* Parametres */

	Controller::PController OnButtonUp,
									OnButtonDown,
									OnTimeOut,
									OnButtonValid, 
									OnButtonMonitor, 
									OnButtonLongValid;

   /* Methodes */

   EventNode();
 	void Init(	UWORD16 Id,
               UWORD16 LinkedMenuControlNodeId,
					Controller::PController OnButtonUp, 
					Controller::PController OnButtonDown,
               Controller::PController OnTimeOut, 
               Controller::PController OnButtonValid,
               Controller::PController OnButtonMonitor, 
               Controller::PController OnButtonLongValid,
               UWORD16 IdNodeOnUp,
               UWORD16 IdNodeOnDown,
               UWORD16 IdNodeOnTimeOut,
               UWORD16 IdNodeOnValid,
               UWORD16 IdNodeOnMonitor,
               UWORD16 IdNodeOnLongValid);

   void SetLinkedMenuControlNodeId(UWORD16 Id);
   UWORD16 GetLinkedMenuControlNodeId() const;
                  
	void SetId(UWORD16 Id);
   UWORD16 GetId() const;

	void SetIdNodeOnUp(UWORD16 IdNodeOnUp);
	UWORD16 GetIdNodeOnUp() const;

	void SetIdNodeOnDown(UWORD16 IdNodeOnDown);
	UWORD16 GetIdNodeOnDown() const;
   
   void SetIdNodeOnTimeOut(UWORD16 IdNodeOnTimeOut);
	UWORD16 GetIdNodeOnTimeOut() const;
   
   void SetIdNodeOnValid(UWORD16 IdNodeOnValid);
	UWORD16 GetIdNodeOnValid() const;
   
   void SetIdNodeOnLongValid(UWORD16 IdNodeOnLongValid);
	UWORD16 GetIdNodeOnLongValid() const;
   
   void SetIdNodeOnMonitor(UWORD16 IdNodeOnMonitor);
	UWORD16 GetIdNodeOnMonitor() const;

	void SetOnButtonUp(Controller::PController OnButtonUp);
   void SetOnButtonDown(Controller::PController OnButtonDown);
   void SetOnTimeOut(Controller::PController OnTimeOut);
   void SetOnButtonValid(Controller::PController OnButtonValid);
   void SetOnButtonMonitor(Controller::PController OnButtonMonitor);
   void SetOnButtonLongValid(Controller::PController OnButtonLongValid);

};

#endif
