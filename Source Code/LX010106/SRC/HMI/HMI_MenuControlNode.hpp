/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_MenuControlNode.hpp 				   		          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_MenuControlNode.cpp 				  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef MenuControlNodeH
#define MenuControlNodeH
								
/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/
extern "C"
{
#include "typedef.h"
#include "enum.h"
}

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class EventNode;
class DisplayObject;

class MenuControlNode
{

private:

   /* Parametres */
   
   /* Methodes */
   
   e_BOOL 	Visible,
   			Lock;

   DisplayObject *Object;

   EventNode* Param;


protected:

   /* Parametres */
   
   /* Methodes */
   
public:

   /* Parametres */
   
   /* Methodes */
   
   MenuControlNode();

   void Init(  e_BOOL Visible,
               e_BOOL Lock,
               DisplayObject *Object,
               EventNode* Param);

   void SetVisible(e_BOOL Visible);
   e_BOOL GetVisible();
	e_BOOL IsVisible();


   void SetLock(e_BOOL Lock);
   e_BOOL GetLock();
   e_BOOL IsLock();

   void SetObject(DisplayObject *Object);
   DisplayObject* GetObject();

   void SetEventNode(EventNode* Param);
   
   EventNode* GetEventNode();

   e_BOOL IsValid();

};

#include "HMI_EventNode.hpp"
#include "HMI_DisplayObject.hpp"

#endif

