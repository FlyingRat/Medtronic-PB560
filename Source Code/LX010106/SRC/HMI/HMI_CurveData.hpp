/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_CurveData.hpp	     			                                	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_CurveData.cpp	    	                     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef CurveDataH
#define CurveDataH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_VPoint.hpp"
#include "HMI_Scale.hpp"
#include "HMI_Pen.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#define DOTTED_LENGTH 2

class CurveData
{
private:

	/* Parametres */

	VPoint CurrentPoint;
	
	VPoint PreviousPoint;

	Scale *Ex;
	
	Scale	*Ey;

	Pen LocalPen;

	DataBaseLink DBx;
	
	DataBaseLink DBy;

	/*%C MaxX [ 0 : ???] */
	SWORD16 MaxX;
	
	/*%C MaxY [ 0 : ???] */
	SWORD16 MaxY;
	
	/*%C MinX [ 0 : ???] */
	SWORD16 MinX;
	
	/*%C MinY [ 0 : ???] */
	SWORD16 MinY; 

	e_BOOL JustReset; 
	e_BOOL OutOfLimitDis;
	e_BOOL CurveStart;

	/* Méthodes */ 

protected:

	/* Parametres */

	/* Méthodes */

public:

   /* Parametres */

	/* Méthodes */
	void SetCurveStart(e_BOOL _start);
	e_BOOL IsCurveStart(void);
	
	Scale* GetScaleX();
	Scale* GetScaleY();

	void SetScale(Scale *Ex,Scale *Ey);

	
	void Init(Scale *Ex,Scale *Ey);

	UWORD16 GetIdParamY();
	e_TYPE_OF_DB_TARGET GetDbTargetY();

	void InitDbAccess(UWORD16 IdParamY, 
							e_TYPE_OF_DB_TARGET DbTargetY);

	void InitDbAccess(UWORD16 IdParamX, 
							e_TYPE_OF_DB_TARGET DbTargetX,
							UWORD16 IdParamY, 
							e_TYPE_OF_DB_TARGET DbTargetY);
					
 	void StoreNewPoint(SWORD16 X,SWORD16 Y);
	void ResetMinMax();
	void ResetValue();
	void Refresh();

	void SetIdParamX(UWORD16 IdParamX);

	SWORD16 GetMaxX();
	void SetMaxX(SWORD16 MaxX);

	CurveData();
   void Construct();   	
	CurveData(Scale *Ex,Scale *Ey);

	Pen* GetPen();
	VPoint& GetPreviousPoint();
	VPoint& GetCurrentPoint();

	SWORD16 GetMaxY();
	SWORD16 GetMinX();
	SWORD16 GetMinY();

	e_BOOL GetOutOfLimitDis();
   
};

#endif

