/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_DataBaseAccess.cpp                                  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Gestion DB																			      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_InterfaceCppC.hpp"
extern "C"
{
#include "DB_IhmAccessParaDatabase.h"
}


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/

/******************************************************************************/
/*                           ACCESSEURS						                	   */
/******************************************************************************/

/******************************************************************************/
/*                           METHODES                							      */
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Incremente la valeur																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Value : Valeur a incrementer											 			*/
/*%I 		Id : Id DB																	 			*/
/*%I 		DbType : DB Target														 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
e_BOOL DataBaseAccess::IncrementValue( UWORD16 *_Value,
                                       UWORD16 _Id,
                                       e_TYPE_OF_DB_TARGET _DbType)
{
   UWORD16 ValueOk;

	ValueOk = InterfaceCppC::DB_Request(_Value ,
												_Id,
												_DbType,
												INCREASE);
   ValueOk = ValueOk;   /* Pour éviter le warning à la compil */

   return TRUE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Decremente la valeur																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Value : Valeur a decrementer											 			*/
/*%I 		Id : Id DB																	 			*/
/*%I 		DbType : DB Target														 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
e_BOOL DataBaseAccess::DecrementValue( UWORD16 *_Value,
                                       UWORD16 _Id,
                                       e_TYPE_OF_DB_TARGET _DbType)
{
   UWORD16 ValueOk;

	ValueOk = InterfaceCppC::DB_Request(_Value,
												_Id, 
												_DbType,
												DECREASE);

   ValueOk = ValueOk;   /* Pour éviter le warning à la compil */

   return TRUE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Lecture de la valeur																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Value : Valeur a lire													 			*/
/*%I 		Id : Id DB																	 			*/
/*%I 		DbType : DB Target														 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
e_BOOL DataBaseAccess::ReadValue(UWORD16 *_Value,
                                 UWORD16 _Id,
                                 e_TYPE_OF_DB_TARGET _DbType)
{
   UWORD16 ValueOk;

	ValueOk = InterfaceCppC::DB_Request(_Value,
												_Id,
												_DbType,
												READ);
                                    
   ValueOk = ValueOk;   /* Pour éviter le warning à la compil */

   return TRUE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      	  */
/*%C                                                                          */
/*%C Lecture de l'info associée à la valeur (poids forts, en particulier sur  */
/*%C les alarmes)															  */
/*%C                                                                          */
/*%I Input Parameter : 														  */
/*%I 		Value : Valeur a lire											  */
/*%I 		Id : Id DB														  */
/*%I 		DbType : DB Target												  */
/*%IO Input/Output : 														  */
/*%IO		NONE															  */
/*%O Output Parameter : 													  */
/*%O 		NONE												  			  */
/******************************************************************************/
e_BOOL DataBaseAccess::ReadInfo(UWORD16 *_Value,
								 UWORD16 _Id,
								 e_TYPE_OF_DB_TARGET _DbType)
{
   UWORD16 ValueOk;

   ValueOk = InterfaceCppC::DB_Request(_Value,
										_Id,
										_DbType,
										READ_INFO);
   ValueOk = ValueOk;   /* Pour éviter le warning à la compil */

   return TRUE;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Ecriture de la valeur																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Value : Valeur a ecrire													 			*/
/*%I 		Id : Id DB																	 			*/
/*%I 		DbType : DB Target														 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
e_BOOL DataBaseAccess::WriteValue(  UWORD16 *_Value,
                                    UWORD16 _Id,
                                    e_TYPE_OF_DB_TARGET _DbType)
{
   UWORD16 ValueOk;

	ValueOk = InterfaceCppC::DB_Request(_Value,
												_Id, 
												_DbType, 
												WRITE);

   ValueOk = ValueOk;   /* Pour éviter le warning à la compil */
                                       
   return TRUE;
}
/******************************************************************************/
/*%C                       Functionnal description :                      	  */
/*%C                                                                          */
/*%C Ecriture de l'info associée à la valeur (poids forts, en particulier sur */
/*%C les alarmes)															  */
/*%C                                                                          */
/*%I Input Parameter : 														  */
/*%I 		Value : Valeur a ecrire											  */
/*%I 		Id : Id DB														  */
/*%I 		DbType : DB Target												  */
/*%IO Input/Output : 														  */
/*%IO		NONE															  */
/*%O Output Parameter : 													  */
/*%O 		NONE												  			  */
/******************************************************************************/
e_BOOL DataBaseAccess::WriteInfo(  UWORD16 *_Value,
                                    UWORD16 _Id,
                                    e_TYPE_OF_DB_TARGET _DbType)
{
   UWORD16 ValueOk;

   ValueOk = InterfaceCppC::DB_Request(_Value,
										_Id,
										_DbType,
									   	WRITE_INFO);
   ValueOk = ValueOk;   /* Pour éviter le warning à la compil */

   return TRUE;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Lecture de la valeur min du paramètre												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Id : Id DB																	 			*/
/*%I 		DbType : DB Target														 			*/
/*%IO Input/Output : 																			*/
/*%IO		Value : Valeur du min															  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
UWORD16 DataBaseAccess::GetMin(  UWORD16 _Id,
                                 e_TYPE_OF_DB_TARGET _DbType)
{
	UWORD16 Value;

	/* Return the min value else None */
	if(InterfaceCppC::DB_Request(	&Value, 
											_Id, _DbType, 
											MIN))
	{
		return Value;
	}
	else
	{
   	return NONE;
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Lecture de la valeur max du paramètre												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Id : Id DB																	 			*/
/*%I 		DbType : DB Target														 			*/
/*%IO Input/Output : 																			*/
/*%IO		Value : Valeur du max															  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
UWORD16 DataBaseAccess::GetMax(  UWORD16 _Id,
                                 e_TYPE_OF_DB_TARGET _DbType)
{
	UWORD16 Value;

  	/* Return the max value else None */
	if(InterfaceCppC::DB_Request(	&Value , 
											_Id, _DbType, 
											MAX))
	{
		return Value;
	}
   else
	{
		return NONE;
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Lecture de la valeur step du paramètre												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Id : Id DB																	 			*/
/*%I 		DbType : DB Target														 			*/
/*%IO Input/Output : 																			*/
/*%IO		Value : Valeur du step															  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
UWORD16 DataBaseAccess::GetStep( UWORD16 _Id,
                                 e_TYPE_OF_DB_TARGET _DbType)
{
	UWORD16 Value;

	/*%C Return ths step value */
	if(InterfaceCppC::DB_Request(	&Value, 
											_Id, 
											_DbType, STEP))
	{
		return Value;
	}
	else
	{
		return NONE;
	}
}
