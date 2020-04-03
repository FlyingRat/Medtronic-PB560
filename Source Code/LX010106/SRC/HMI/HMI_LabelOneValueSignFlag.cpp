/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueSignFlag.cpp  	      	           	 	  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage d'une valeur mais qui passe a "Non"	 						*/
/*%C ou autre pour un certain flag de la BD												*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelOneValueSignFlag.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelOneValueSignFlag::LabelOneValueSignFlag():LabelOneValueSignDefault()
{
   IdFlag = 0;
}
/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelOneValueSignFlag::SetIdFlag(UWORD16 _IdFlag)
{
   IdFlag = _IdFlag;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValueSignFlag::GetIdFlag()
{
   return IdFlag;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueSignFlag::SetDbIdFlag(e_TYPE_OF_DB_TARGET _DbIdFlag)
{
   DbIdFlag = _DbIdFlag;
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET LabelOneValueSignFlag::GetDbIdFlag()
{
   return DbIdFlag;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueSignFlag::SetFlagForDefault(e_BOOL _FlagForDefault)
{
   FlagForDefault = _FlagForDefault;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelOneValueSignFlag::GetFlagForDefault()
{
   return FlagForDefault;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueSignFlag::SetValue1(UWORD16 _Value1)
{
   UWORD16 Value;

   DataBaseAccess::ReadValue(&Value, GetIdFlag(), GetDbIdFlag());

   if((Value == GetFlagForDefault()) && (GetPtrNameDefaultValue() != NULL))
   {
      SetValueIsString(TRUE);
      GetFValue1()->StoreValue(_Value1);
      GetFValue1()->SetText(GetNameDefaultValue());
      if(GetLoupe() != NULL)
      {
         GetLoupe()->SetValue(GetNameDefaultValue());
      }
   }
   else
   {
      LabelOneValueSign::SetValue1(_Value1);
      SetValueIsString(FALSE);
   }
}


/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation																				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NameDefaultValue   : nom lorsque valeur par defaut 			      	*/
/*%I		IdDefaultFlag      : Id du flag dans DB						         	*/
/*%I		DbIdFlag           : DB target du flag						         		*/
/*%I		FlagForDefault     : valeur du flag pour defaut		  		         	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueSignFlag::InitDefaultFlag( UBYTE** _NameDefaultValue,
                                             UWORD16 _IdDefaultFlag,
                                             e_TYPE_OF_DB_TARGET _DbIdFlag,
                                             e_BOOL _FlagForDefault)
{
   LabelOneValueSignDefault::InitDefaultValue(_NameDefaultValue,0);
	/*%C Initialisation */
   IdFlag = _IdDefaultFlag;
   DbIdFlag = _DbIdFlag;
   FlagForDefault = _FlagForDefault;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Increment de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																  		         	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueSignFlag::IncreaseValue()
{
   UWORD16 Value = GetValue1();

   /*%C Increase and set value */
   IncreaseValueOk(&Value);
   SetValue1(Value);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Decrement de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																  		         	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueSignFlag::DecreaseValue()
{
   UWORD16 Value = GetValue1();

   /*%C Increase and set value */
   DecreaseValueOk(&Value);
   SetValue1(Value);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Confirme la modification de la valeur de Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																  		         	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueSignFlag::ConfirmModifValue(e_BOOL _Confirm)
{
   if(_Confirm)
   {
      LabelOneValueSign::ConfirmModifValue(_Confirm);
   }
   else
   {
      UWORD16 Value = GetValueFlagTemp();
      DataBaseAccess::WriteValue(&Value, GetIdFlagTemp(), GetDbIdFlagTemp());
      LabelOneValueSign::ConfirmModifValue(_Confirm);
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la modification d'un Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																  		         	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueSignFlag::StartModifMode()
{
   LabelOneValueSign::StartModifMode();

   UWORD16 Value;
	/*%C Read DataBase */
   DataBaseAccess::ReadValue(&Value, GetIdFlag(), GetDbIdFlag());
	/*%C Set value */
   SetValueFlagTemp(Value);
   SetIdFlagTemp(GetIdFlag());
   SetDbIdFlagTemp(GetDbIdFlag());
}
