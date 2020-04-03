/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_BarGraph.hpp	   		                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  */
/*%C Classe declaration for HMI_BarGraph.cpp	       		               	  */
/*%C			                                                              */
/******************************************************************************/

#ifndef BarGraphH
#define BarGraphH

/******************************************************************************/
/*                           	INCLUDE                    	      			  */
/******************************************************************************/

#include "HMI_DisplayObject.hpp"
#include "HMI_TextField.hpp" 

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/
class BarGraph: public DisplayObject
{

private:
   
   /* Parametres */

	/*%C Position [ 0 : ???] */
   UWORD16  Position;

	/*%C Value [ 0 : ???] */
   UWORD16  Value;

	/*%C Pep [ 0 : ???] */
   UWORD16  Pep;

	/*%C Pmax [ 0 : ???] */
	UWORD16  Pmax;
	
	/*%C firstShow [ 0 : ???] */
	UWORD16  firstShow;

	/*%C IdPep [ 0 : ???] */
	UWORD16  IdPep;

	/*%C IdPmax [ 0 : ???] */
	UWORD16	IdPmax;

	/*%C Divider [ 0 : ???] */
	UWORD16	Divider;

   /*%C le nom de l'unité */
   UBYTE **NameUnit;

   TextField TFUnit;

   /* Methodes */

	void DisplayBargraph(SWORD16 value,
                        SWORD16 Pmax,SWORD16 Pep,
                        UBYTE position,
                        UBYTE printon,
                        UBYTE page);

   void RefreshUnitDisplay(void);                        

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

	BarGraph();

	void Init(  UWORD16 Line,
               UWORD16 Col,
               UWORD16 Position,
               UWORD16 Value,
               UBYTE** _NameUnit);

	void InitDbAccess(UWORD16 IdParam,
                     e_TYPE_OF_DB_TARGET DbTarget,
                     UWORD16 IdPmax,
                     UWORD16 IdPep);

	void SetValue(UWORD16 Value);
	UWORD16 GetValue();

   void SetPep(UWORD16 Pep);
	UWORD16 GetPep();

 	void SetPmax(UWORD16 Pmax);
	UWORD16 GetPmax();

	void SetPosition(UWORD16 Position);
	UWORD16 GetPosition();

	void SetDivider(UWORD16 _Divider);
	UWORD16 GetDivider();

   void SetNameUnit(UBYTE** _NameUnit);
   UBYTE* GetNameUnit();      

	virtual void Refresh();
	virtual void Show();
	virtual void Hide();

};

#endif
