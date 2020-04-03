/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FieldObject.hpp	     		                             	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_FieldObject.cpp	    	                     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef FieldObjectH
#define FieldObjectH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/
extern "C"
{
#include "typedef.h"
}

#include "HMI_DisplayObject.hpp"
#include "HMI_IhmType.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class FieldObject: public DisplayObject
{

private:

   /* Parametres */

	/*%C Font [ 0 : 4 ] */
   UWORD16 Font;

   e_BOOL ReverseVideo;

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:
  
   /* Parametres */

   /* Methodes */

   FieldObject();

   void Init(	UWORD16 Line, 
   				UWORD16 Col, 
   				UWORD16 Font, 
   				e_BOOL ReverseVideo);

   void SetFont(UWORD16 Font);
   UWORD16 GetFont();

   void SetReverseVideo(e_BOOL ReverseVideo);
   e_BOOL GetReverseVideo();

   virtual void Clear();

};

#endif
