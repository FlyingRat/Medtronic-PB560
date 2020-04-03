/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_AutoCalibValue.hpp	                                     	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_AutoCalibValue.cpp	                         	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef AutoCalibValueH
#define AutoCalibValueH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelOneValue.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class AutoCalibValue: public LabelOneValue
{

private:

   /*  Parametres */
	
	e_TYPE_OF_DB_TARGET BdCalibParam;

	/*%C IdCalibParam [ 0 : ???] */
   UWORD16 IdCalibParam;

	/*%C NbSegment [ 0 :  ???] */
   UWORD16 NbSegment;

	/*%C CurrentSegment [ 0 : ??? ] */
	UWORD16 CurrentSegment;

   const UWORD16* SegmentList;
   const e_BOOL* FloatList;

	/* Methodes */

protected:

	/* Parametres */
	
	/* Methodes */

public:
   
   /* Parametres */
	
	/* Methodes */

	AutoCalibValue();

	void InitCalibProperties(  UWORD16 IdCalibParam,
                              e_TYPE_OF_DB_TARGET BdCalibParam,
                              const UWORD16* SegmentList,
                              const e_BOOL* FloatList,
                              UWORD16 NbSegment);

   void SetIdCalibParam(UWORD16 IdCalibParam);
   UWORD16 GetIdCalibParam();

   void SetBdCalibParam(e_TYPE_OF_DB_TARGET BdCalibParam);
   e_TYPE_OF_DB_TARGET GetBdCalibParam();

	void SetSegmentList(const UWORD16* SegmentList);
	UWORD16 GetSegmentListAt(UWORD16 Index);

   void SetFloatList(const e_BOOL* FloatList);
	e_BOOL  GetFloatListAt(UWORD16 Index);

   void SetNbSegment(UWORD16 NbSegment);
   UWORD16 GetNbSegment();

   void SetCurrentSegment(UWORD16 CurrentSegment);
   UWORD16 GetCurrentSegment();

   void StopModifModeConsult();
   void StartModifModeConsult();

   virtual void StartModifMode();
   virtual void StopModifMode();
   virtual void ModifNextValue();

   virtual e_BOOL CalibSegmentOK();
	virtual e_BOOL VerificationCalibCheck();
	virtual e_BOOL StopIfErrorCalib();

   e_BOOL ModifNextValueConsult();
 
};

#endif
