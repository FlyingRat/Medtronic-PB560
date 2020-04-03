/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTabTwoValueFlag.cpp 	     	      	 	  					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	d'une valeur mais qui passe a "Non" ou 					*/
/*%C   autre pour un certain flag de la BD												*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelTabTwoValueFlag.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelTabTwoValueFlag::LabelTabTwoValueFlag():LabelTabTwoValueDefault()
{
   IdFlag1 = 0;
   DbIdFlag1 = ADJUST;
   FlagForDefault1 = FALSE;
   IdFlag2 = 0;
   DbIdFlag2 = ADJUST;
   FlagForDefault2 = FALSE;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelTabTwoValueFlag::SetIdFlag1(UWORD16 _IdFlag1)
{
   IdFlag1 = _IdFlag1;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabTwoValueFlag::GetIdFlag1()
{
   return IdFlag1;
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValueFlag::SetDbIdFlag1(e_TYPE_OF_DB_TARGET _DbIdFlag1)
{
   DbIdFlag1 = _DbIdFlag1;
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET LabelTabTwoValueFlag::GetDbIdFlag1()
{
   return DbIdFlag1;
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValueFlag::SetFlagForDefault1(e_BOOL _FlagForDefault1)
{
   FlagForDefault1 = _FlagForDefault1;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTabTwoValueFlag::GetFlagForDefault1()
{
   return FlagForDefault1;
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValueFlag::SetIdFlag2(UWORD16 _IdFlag2)
{
   IdFlag2 = _IdFlag2;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabTwoValueFlag::GetIdFlag2()
{
   return IdFlag2;
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValueFlag::SetDbIdFlag2(e_TYPE_OF_DB_TARGET _DbIdFlag2)
{
   DbIdFlag2 = _DbIdFlag2;
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET LabelTabTwoValueFlag::GetDbIdFlag2()
{
   return DbIdFlag2;
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValueFlag::SetFlagForDefault2(e_BOOL _FlagForDefault2)
{
   FlagForDefault2 = _FlagForDefault2;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTabTwoValueFlag::GetFlagForDefault2()
{
   return FlagForDefault2;
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValueFlag::SetValue1(UWORD16 _Value1)
{
	UWORD16 Value;
	DataBaseAccess::ReadValue(	&Value,
										GetIdFlag1(), 
										GetDbIdFlag1());

	if((Value == GetFlagForDefault1()) &&
		(GetPtrNameDefaultValue1() != NULL))
   {
	   SetValue1IsString(TRUE);

		if(Tools::GetStringPixelSize(GetNameDefaultValue1(),FONT_4) > 45)
		{
			SetFontValue1(FONT_1);
		}
		else
		{
        	SetFontValue1(FONT_4);
		}
		/*%C Set colum just near the table to avoid the message erase the table */
		GetFValue1()-> SetCol(FIRST_VALUE_COLUMN+1);
		GetFValue1()->SetText(GetNameDefaultValue1());
		GetFValue1()-> SetCol(FIRST_VALUE_COLUMN+
							(COLUMN_WIDTH-
                     Tools::GetStringPixelSize
							(GetNameDefaultValue1(),
                     GetFontValue1()))/2);

		GetFValue1()->StoreValue(_Value1);

		if(GetLoupe() != NULL)
      {
         GetLoupe()->SetValue(GetNameDefaultValue1());
		}
	}
	else
   {
      SetValue1IsString(FALSE);
		GetFValue1()->Hide();
      SetFontValue1(FONT_4);
		LabelTabOneValue::SetValue1(_Value1);
	}
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValueFlag::SetValue2(UWORD16 _Value2)
{
	UWORD16 Value;
	DataBaseAccess::ReadValue(	&Value,
										GetIdFlag2(),
										GetDbIdFlag2());

	if((	Value == GetFlagForDefault2()) &&
			(GetPtrNameDefaultValue2() != NULL))
   {
		SetValue2IsString(TRUE);

      if(Tools::GetStringPixelSize( GetNameDefaultValue2(),
                                    FONT_4) > COLUMN_WIDTH)

		{
         SetFontValue2(FONT_1);
		}
      else
		{
        	SetFontValue2(FONT_4);
		}
		/*%C Set colum just near the table to avoid the message erase the table */
		GetFValue2()-> SetCol(THIRD_VALUE_COLUMN+1);
		GetFValue2()->SetText(GetNameDefaultValue2());
		GetFValue2()-> SetCol(THIRD_VALUE_COLUMN+
                     (COLUMN_WIDTH-
							Tools::GetStringPixelSize
							(GetNameDefaultValue2(),
                     GetFontValue2()))/2);

		GetFValue2()->StoreValue(_Value2);

		if(GetLoupe() != NULL)
		{
			GetLoupe()->SetValue(GetNameDefaultValue2());
		}
	}
	else
   {
		SetValue2IsString(FALSE);
		GetFValue2()->Hide();
      SetFontValue2(FONT_4);
		LabelTabTwoValue::SetValue2(_Value2);
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
/*%I		NameDefaultValue1   : nom lorsque valeur1 par defaut 			   		*/
/*%I		IdDefaultFlag1      : Id du flag dans DB						      		*/
/*%I		DbIdFlag1           : DB target du flag						         	*/
/*%I		FlagForDefault1     : valeur1 du flag pour defaut				  		 	*/
/*%I		NameDefaultValue2   : nom lorsque valeur2 par defaut 			   		*/
/*%I		IdDefaultFlag2      : Id du flag dans DB						      		*/
/*%I		DbIdFlag2           : DB target du flag						         	*/
/*%I		FlagForDefault2     : valeur2 du flag pour defaut							*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValueFlag::InitDefaultFlag(  UBYTE** _NameDefaultValue1,
                                             UWORD16 _IdDefaultFlag1,
                                             e_TYPE_OF_DB_TARGET _DbIdFlag1,
                                             e_BOOL _FlagForDefault1,
                                             UBYTE** _NameDefaultValue2,
                                             UWORD16 _IdDefaultFlag2,
                                             e_TYPE_OF_DB_TARGET _DbIdFlag2,
                                             e_BOOL _FlagForDefault2)
{
	LabelTabTwoValueDefault::InitDefaultValue(_NameDefaultValue1,
                                             0,
                                             _NameDefaultValue2,
                                             0);
	IdFlag1 = _IdDefaultFlag1;
	DbIdFlag1 = _DbIdFlag1;
	FlagForDefault1 = _FlagForDefault1;
	IdFlag2 = _IdDefaultFlag2;
	DbIdFlag2 = _DbIdFlag2;
	FlagForDefault2 = _FlagForDefault2;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Increment de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValueFlag::IncreaseValue()
{
	UWORD16 Value;

	switch(GetValueState())
   {
      case 1 : Value = GetValue1();
               break;
		case 2 : Value = GetValue2();
               break;
      default : break;               
	}

	/*%C Pas de verication du retour pour permettre la verification du flag */
   IncreaseValueOk(&Value);
	switch(GetValueState())
   {
		case 1 : SetValue1(Value);
               break;
		case 2 : SetValue2(Value);
               break;
      default : break;               
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Decrement de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValueFlag::DecreaseValue()
{
	UWORD16 Value;

	switch(GetValueState())
   {
		case 1 : Value = GetValue1();
               break;
		case 2 : Value = GetValue2();
               break;
      default : break;
	}

	/*%C Pas de verication du retour pour permettre la verification du flag */
   DecreaseValueOk(&Value);
	switch(GetValueState())
   {
		case 1 : SetValue1(Value);
               break;
		case 2 : SetValue2(Value);
               break;
      default : break;               
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Confirme la modification de la valeur de Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValueFlag::ConfirmModifValue(e_BOOL _Confirm)
{
	if(_Confirm)
   {
		LabelTabTwoValue::ConfirmModifValue(_Confirm);
	}
	else
   {
		/*%C Initialisation du flag */
		UWORD16 Value = GetValueFlagTemp();
		DataBaseAccess::WriteValue(&Value,
											GetIdFlagTemp(), 
											GetDbIdFlagTemp());

		LabelTabTwoValue::ConfirmModifValue(_Confirm);
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la modification d'un Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValueFlag::StartModifMode()
{
	LabelTabTwoValue::StartModifMode();

	UWORD16 Value;
	DataBaseAccess::ReadValue(	&Value, 
										GetIdFlag1(), 
										GetDbIdFlag1());

	SetValueFlagTemp(Value);
	SetIdFlagTemp(GetIdFlag1());
	SetDbIdFlagTemp(GetDbIdFlag1());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Changement de la valeur en modification												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValueFlag::ModifNextValue()
{
	LabelTabTwoValue::ModifNextValue();

	UWORD16 Value;
	DataBaseAccess::ReadValue(	&Value, 
										GetIdFlag2(), 
										GetDbIdFlag2());

   SetValueFlagTemp(Value);
	SetIdFlagTemp(GetIdFlag2());
	SetDbIdFlagTemp(GetDbIdFlag2());
}

