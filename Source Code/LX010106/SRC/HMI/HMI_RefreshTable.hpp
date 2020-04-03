/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_RefreshTable.hpp 						 		 			  	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_RefreshTable.cpp 	 							     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef RefreshTableH
#define RefreshTableH							

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelSymbol.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#define XAlway 4

class RefreshTable
{

private:

   /* Parametres */

   DisplayObject **TableRefresh[2];

   UWORD16  IndexEndAlway0,
            IndexEndInsp0,
            IndexEndExp0,
            IndexEndXAlway0,
            IndexEndAlway1,
            IndexEndInsp1,
            IndexEndExp1,
            IndexEndXAlway1;

  	/* Methodes */

protected:

   /* Parametres */

  	/* Methodes */

public:
   
   /* Parametres */

  	/* Methodes */
   
   RefreshTable();
   void SetTable(DisplayObject **Table);
   
   void InitIndice(UWORD16 IdTable, DisplayObject **TableRefresh);
   
   void ResetTable();
   
   void RefreshRange(UWORD16 Begin, UWORD16 End, DisplayObject **Table);
   
   void MakeRefresh();
   
   void MakeRefreshInsp();
   
   void MakeRefreshExp();

};

#endif
