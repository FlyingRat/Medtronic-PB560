/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_ManualCalibValue.hpp 				   		          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_ManualCalibValue.cpp 				  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef ManualCalibValueH
#define ManualCalibValueH
								
/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_AutoCalibValue.hpp"
//#include "DataBase.h"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class ManualCalibValue: public AutoCalibValue
{

private:

   /* Parametres */
   
   /* Methodes */
   
   UWORD16 	IdBlow, 
   			IdMesBlow;

	e_TYPE_OF_DB_TARGET 	BdBlow, 
								BdMesBlow;

	e_BOOL FirstModifOnCalibPoint, firstRequest;

protected:
	
	/* Parametres */
   
   /* Methodes */
   
public:

   /* Parametres */
   
   /* Methodes */
   
   ManualCalibValue();
   void InitCalibProperties(  UWORD16 IdCalibParam,
                              e_TYPE_OF_DB_TARGET BdCalibParam,
                              const UWORD16* SegmentList,
                              const e_BOOL* FloatList,
                              UWORD16 NbSegment,
                              UWORD16 IdBlow,
                              e_TYPE_OF_DB_TARGET BdBlow,
                              UWORD16 IdMesBlow,
                              e_TYPE_OF_DB_TARGET BdMesBlow);

   UWORD16 GetIdBlow();
	void SetIdBlow(UWORD16 IdBlow);

   e_TYPE_OF_DB_TARGET GetBdBlow();
   void SetBdBlow(e_TYPE_OF_DB_TARGET BdBlow);

	void SetIdMesBlow(UWORD16 IdMesBlow);
	UWORD16 GetIdMesBlow();
   
   void SetBdMesBlow(e_TYPE_OF_DB_TARGET BdMesBlow);
   e_TYPE_OF_DB_TARGET GetBdMesBlow();					    

	void SetFirstModifOnCalibPoint(e_BOOL Flag);
	e_BOOL IsFirstModifOnCalibPoint();

   virtual void IncreaseValue();
   virtual void DecreaseValue();
   virtual void ModifNextValue();
   virtual void StopModifMode();
	virtual void StartModifMode();

	virtual e_BOOL StopIfErrorCalib();
	virtual e_BOOL VerificationCalibCheck();
   virtual e_BOOL IncreaseValueOk(UWORD16* Val);
   virtual e_BOOL DecreaseValueOk(UWORD16* Val);
};

#endif
