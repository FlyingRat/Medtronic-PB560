/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_PerformanceGraphControl.hpp 			 		 			  	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_PerformanceGraphControl.cpp		  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef PerformanceGraphControlH
#define PerformanceGraphControlH								

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_GraphControl.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class PerformanceGraphControl : public GraphControl
{
private:
   
   /* Parametres */
   
   UWORD16 RefreshTime;

   UWORD16 CurrentTime;

   /* Méthodes */

protected:

   /* Parametres */

   /* Méthodes */

public:

   /* Parametres */

   /* Méthodes */

   PerformanceGraphControl();
   
   virtual void Construct();
   virtual void SetRefreshTime(UWORD16 _RefreshTime);
   virtual UWORD16 GetRefreshTime();
   
   virtual void InitRefreshTime(UWORD16 RefreshTime);
   
   virtual void SetGraphTarget(Graph* GraphTarget);
   virtual void ManageGraph();
   virtual void Reset();

};

#endif
