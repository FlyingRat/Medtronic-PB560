/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_WobGraphControl.hpp                  	 	  						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Classe declaration for HMI_WobGraphControl.cpp	              				*/
/*		                                                                   	 	*/
/******************************************************************************/

#ifndef WobGraphControlH
#define WobGraphControlH

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_GraphControl.hpp"
#include "HMI_DatabaseAccess.hpp"

/******************************************************************************/
/*                           CLASSE DECLARATION                    	      	*/
/******************************************************************************/

class WobGraphControl : public GraphControl
{
private:

   /* Parametres */

	/*%C VentilState [ 251 : 254] */
   e_VentilState VentilState;

   /* Méthodes */

protected:

   /* Parametres */

   /* Méthodes */

public:

   /* Parametres */

   /* Méthodes */

   WobGraphControl();

   void Init();

   virtual void ManageGraph();
   virtual void Reset();

};

#endif
