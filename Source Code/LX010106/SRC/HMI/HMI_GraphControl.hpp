/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_GraphControl.hpp	     		                             	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_GraphControl.cpp		                     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef GraphControlH
#define GraphControlH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_Graph.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class Graph;
class GraphControl
{
private:

   /* Parametres */

   Graph *GraphTarget;
   
   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   GraphControl();

   virtual void SetGraphTarget(Graph* GraphTarget);
   Graph* GetGraphTarget();

   virtual void Construct();
   virtual void SetRefreshTime(UWORD16 _RefreshTime);
   virtual UWORD16 GetRefreshTime();
   virtual void InitRefreshTime(UWORD16 RefreshTime);   

   virtual void ManageGraph();
   virtual void Reset();
};

#endif
