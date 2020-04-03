/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_DataBaseAccess.hpp	  	                                  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_DataBaseAccess.cpp	   	                    	*/
/*%C			                                                                  */
/******************************************************************************/
    
#ifndef DataBaseAccessH
#define DataBaseAccessH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/


extern "C"
{
#include "typedef.h"
#include "enum.h"
}

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class DataBaseAccess
{
private:
   
   /* Parametres */

   /* Methodes */

protected:
 	
 	/* Parametres */

   /* Methodes */

public:

	/* Parametres */

   /* Methodes */

   static e_BOOL IncrementValue(	UWORD16 *Value, 
   										UWORD16 Id, 
   										e_TYPE_OF_DB_TARGET DbType);

   static e_BOOL DecrementValue(	UWORD16 *Value, 
   										UWORD16 Id, 
   										e_TYPE_OF_DB_TARGET DbType);

   static e_BOOL ReadValue(UWORD16 *Value, 
   								UWORD16 Id, 
   								e_TYPE_OF_DB_TARGET DbType);

   static e_BOOL ReadInfo(UWORD16 *_Value,
								 UWORD16 _Id,
								 e_TYPE_OF_DB_TARGET _DbType);

   static e_BOOL WriteValue(	UWORD16 *Value, 
   									UWORD16 Id, 
   									e_TYPE_OF_DB_TARGET DbType);

   static e_BOOL WriteInfo(	UWORD16 *Value,
 									UWORD16 Id,
									e_TYPE_OF_DB_TARGET DbType);

   static UWORD16 GetMin(	UWORD16 Id, 
   								e_TYPE_OF_DB_TARGET DbType);

   static UWORD16 GetMax(	UWORD16 Id, 
   								e_TYPE_OF_DB_TARGET DbType);

   static UWORD16 GetStep(	UWORD16 Id, 
   								e_TYPE_OF_DB_TARGET DbType);
};

#endif
