/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTabTwoValueTwoLabels.hpp 	   			   	         */
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelTabTwoValueTwoLabels.cpp    	  			  	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelTabTwoValueTwoLabelsH
#define LabelTabTwoValueTwoLabelsH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_Label.hpp"
#include "HMI_LabelTabtwoValue.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelTabTwoValueTwoLabels: public LabelTabTwoValue
{

private:
   
   /* Parametres */
   
   Label FLabel2;

   UWORD16 ColOffset;
   UWORD16 LineOffset;   
   
   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   LabelTabTwoValueTwoLabels();

   void Init(  e_SYMBOL Icon,
               UBYTE **Name,
               UBYTE **Name2,               
               UWORD16 Line,
               UWORD16 Col,
               UWORD16 Value1,
               UWORD16 ValueRefresh,
               UWORD16 Value2);

   void SetNameLabel2(UBYTE** _Name);
   UBYTE* GetNameLabel2();   

   void SetLabel2ColOffset(UWORD16 _ColOffset);
   void SetLabel2LineOffset(UWORD16 _LineOffset);   

   UWORD16 GetLabel2ColOffset(void);
   UWORD16 GetLabel2LineOffset(void);

   virtual void SetLine(UWORD16 Line);
   virtual void SetCol(UWORD16 Col);   
   virtual void Show();
   virtual void Hide();

};

#endif
