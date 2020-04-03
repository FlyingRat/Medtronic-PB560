/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Scale.hpp 									 		 			  	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_Scale.cpp 	 									     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef ScaleH
#define ScaleH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_FieldObject.hpp"
#include "HMI_DataBaseLink.hpp"
#include "HMI_TextField.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

typedef enum{eHOR,eVERT}TOrientation;

typedef enum{eTOP,eBOTTOM}TSide;

class CurveData;

class Scale: public FieldObject
{
private:

   /* Parametres */

   TOrientation Orientation;
   
   SWORD32 Width,Heigth,MajorTickSpacing,ZeroPos,FirstX;
   
   SWORD32 Min,Max;
   
   SWORD32 Pas;
   
   e_BOOL 	TickVisible,
   			DoubleTick,
   			NumberVisible, 
   			AutoScale, 
   			Symetric, 
   			FirstRefresh;

   TSide NumberSide;

   DataBaseLink DBMax;

   /* Methodes */
   
   void ManagePas();
   void RefreshValue();

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   Scale();

   void Init(  UWORD16 Line,
               UWORD16 Col,
               SWORD16 Min,
               SWORD16 Max,
               UWORD16 MajorTickSpacing,
               UWORD16 Width,
               UWORD16 ZeroPos,
               TOrientation Orientation,
               UWORD16 Font);

   void InitDbAccess(UWORD16 IdMax, e_TYPE_OF_DB_TARGET DbMax);
   UWORD16 GetIdMax();
   e_TYPE_OF_DB_TARGET GetDbMax();

   e_BOOL IsAutoScale();

   void SetSymetric(e_BOOL Symetric);
   e_BOOL GetSymetric();

   UWORD16 GetZeroPos();
   SWORD32 GetMin();
   SWORD32 GetMax();
   SWORD32 GetWidth();

   void SetMajorTickSpacing(SWORD32 MajorTickSpacing);

   SWORD32 GetMajorTickSpacing();

   e_BOOL ManageAutoScale(CurveData **CurveTable, UWORD16 NbCurve);

   UWORD16 ValToPoint(SWORD32 Val);

   virtual void Refresh();
   virtual void Show();
   virtual void Hide();
};

#include "HMI_CurveData.hpp"

#endif
