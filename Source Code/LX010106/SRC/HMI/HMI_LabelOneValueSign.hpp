/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueSign.hpp 	 		                          	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelOneValueSign.cpp  	    		           	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelOneValueSignH
#define LabelOneValueSignH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelOneValue.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelOneValueSign: public LabelOneValue
{

private:

   TextField FSign;
   UWORD16 CachedSignSize;

protected:

public:

   /* Parametres */

   /* Methodes */

   LabelOneValueSign();

   void Init(  e_SYMBOL Icon,
               UBYTE **Name,
               UWORD16 Line,
               UWORD16 Col,
               UWORD16 Value1,
               UBYTE **NameUnit1,
               UBYTE *Sign);

   void SetSign(UBYTE *Sign);
   UBYTE* GetSign();
   TextField* GetFSign();
   UWORD16 GetSignSize();

   void SetSignFont(UWORD16 Font);
   UWORD16 GetSignFont();

   void SetColSign(UWORD16 Col);
   UWORD16 GetColSign();

   virtual void SetValueIsString(e_BOOL Flag);
   virtual void SetValue1(UWORD16 Value1);
   virtual void setInvertVideo(e_BOOL InvertVideo);

   virtual void Blink(e_BOOL Actif);
   virtual void Show();
   virtual void Hide();

};

#endif
