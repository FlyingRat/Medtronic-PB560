/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Graph.hpp			     		                             	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_Graph.cpp					                     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef GraphH
#define GraphH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_Scale.hpp"
#include "HMI_Label.hpp"
#include "HMI_GraphicBox.hpp"
#include "HMI_Pixel.hpp"
#include "HMI_CurveData.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#define MAX_CURVE 1

typedef enum
{
	eLINE,
	eBAR
} 
TKind;

class GraphControl;

class Graph : public GraphicBox
{
private:

	/* Parametres */
	Scale ScaleX, ScaleY;

   static TKind Kind;
   
   CurveData *CurveTable[MAX_CURVE];
   
   GraphControl *GControl;

   TextField LabelX,LabelY,LabelOOL;

   e_BOOL Freezed, OutOfLimit;
   
	UWORD16 CurveNumber;

   UBYTE **TUnit1;
   UBYTE **TUnit2;
   UBYTE **TOutOfLimit;

   /* Methodes*/

protected:

   /* Paramètres */

	/* Methodes */

	void ShowYZeroLine();
   void ShowMaxLine();

public:

	/* Paramètres */
	
	/* Methodes */
	
	Graph();

   void Construct();   
   
   void Init(	UWORD16 Line, 
   				UWORD16 Col,
   				UWORD16 Height, 
   				UWORD16 Width,
               SWORD16 MinX,
               SWORD16 MaxX,
               UWORD16 ZeroPosX,
               UWORD16 MajorTickSpacingX,
               SWORD16 MinY,
               SWORD16 MaxY,
               UWORD16 ZeroPosY,
               UWORD16 MajorTickSpacingY,
               UWORD16 Font,
               UBYTE **Unit1,
               UBYTE **Unit2,
               UBYTE **OutOfLimit);

	Scale* GetScaleX();
   Scale* GetScaleY();
   TextField* GetLabelX();

	SymbolField* GetFIcon();
   TextField* GetFLabel();
  
   static void SetKind(TKind Kind);
   static TKind GetKind();
  
   CurveData** GetCurveTable();
   void SetGControl(GraphControl *GControl);

   void SetCurveNumber(UWORD16 CurveNumber);
   UWORD16 GetCurveNumber();
  
	void SetTUnit1(UBYTE** Name);
   virtual UBYTE* GetTUnit1();
   
   void SetTUnit2(UBYTE** Name);
	virtual UBYTE* GetTUnit2();

   void SetTOutOfLimit(UBYTE** Name);
	virtual UBYTE* GetTOutOfLimit();

   UBYTE** GetTUnit1Ptr();
   UBYTE** GetTUnit2Ptr();
   UBYTE** GetTOutOfLimitPtr();

 	e_BOOL HaveGControl();
   GraphControl * GetGControl();   
   void AddCurve(CurveData *CData);
   void RemoveCurve(CurveData *CData);
   void DataPoint(CurveData* CData);
   void Reset();
   e_BOOL Contains(VPoint& Point);
   void FreezeGraph(e_BOOL Freeze);
      
	virtual void ManageAutoScale();
   virtual void Refresh();
   virtual void Show();
   virtual void Hide();
   virtual void RefreshLanguage();
   virtual void Raz();

};

#include "HMI_GraphControl.hpp"

#endif
