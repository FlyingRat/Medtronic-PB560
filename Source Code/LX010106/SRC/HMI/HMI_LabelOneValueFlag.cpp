/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueFlag.cpp  	    	                	 	  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	d'une valeur mais qui passe a	"Non" 						*/
/*%C ou autre pour un certain flag de la BD												*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelOneValueFlag.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelOneValueFlag::LabelOneValueFlag():LabelOneValueDefault()
{
   IdFlag = 0;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelOneValueFlag::SetIdFlag(UWORD16 _IdFlag)
{
   IdFlag = _IdFlag;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValueFlag::GetIdFlag()
{
   return IdFlag;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueFlag::SetDbIdFlag(e_TYPE_OF_DB_TARGET _DbIdFlag)
{
   DbIdFlag = _DbIdFlag;
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET LabelOneValueFlag::GetDbIdFlag()
{
   return DbIdFlag;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueFlag::SetFlagForDefault(e_BOOL _FlagForDefault)
{
   FlagForDefault = _FlagForDefault;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelOneValueFlag::GetFlagForDefault()
{
   return FlagForDefault;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueFlag::SetValue1(UWORD16 _Value1)
{
   UWORD16 Value;

   DataBaseAccess::ReadValue(&Value, GetIdFlag(), GetDbIdFlag());

   if((Value == GetFlagForDefault()) && (GetPtrNameDefaultValue() != NULL))
   {
	  GetFValue1()->Hide();
	  SetValueIsString(TRUE);
	  GetFValue1()->StoreValue(_Value1);
	  GetFValue1()->SetText(GetNameDefaultValue());
	  GetFValue1()->Show();

      if(GetLoupe() != NULL)
      {
         GetLoupe()->SetValue(this->GetNameDefaultValue());
      }
   }
   else
   {
      LabelOneValue::SetValue1(_Value1);
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
/*%I		FlagForDefault     : valeur du flag pour defaut	              			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueFlag::InitDefaultFlag(  UBYTE** _NameDefaultValue,
                                          UWORD16 _IdDefaultFlag,
                                          e_TYPE_OF_DB_TARGET _DbIdFlag,
                                          e_BOOL _FlagForDefault)
{
	/*%C Initialisation */
   LabelOneValueDefault::InitDefaultValue(_NameDefaultValue,0);
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
/*%I	  	NONE	              																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueFlag::IncreaseValue()
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
/*%I	  	NONE	              																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueFlag::DecreaseValue()
{
   UWORD16 Value = GetValue1();

	/*%C Decrease and set value */
   DecreaseValueOk(&Value);
   SetValue1(Value);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Confirme la modification de la valeur de Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE	              																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueFlag::ConfirmModifValue(e_BOOL _Confirm)
{
   if(_Confirm)
   {
      LabelOneValue::ConfirmModifValue(_Confirm);
   }
   else
   {
      /*%C Initialisation du flag */
      UWORD16 Value = GetValueFlagTemp();
      DataBaseAccess::WriteValue(&Value, GetIdFlagTemp(), GetDbIdFlagTemp());
      LabelOneValue::ConfirmModifValue(_Confirm);
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la modification d'un Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE	              																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueFlag::StartModifMode()
{
   LabelOneValue::StartModifMode();

   UWORD16 Value;

   /*%C Read DataBase */
   DataBaseAccess::ReadValue(&Value, GetIdFlag(), GetDbIdFlag());
	/*%C Set value */
   SetValueFlagTemp(Value);
   SetIdFlagTemp(GetIdFlag());
   SetDbIdFlagTemp(GetDbIdFlag());
}
