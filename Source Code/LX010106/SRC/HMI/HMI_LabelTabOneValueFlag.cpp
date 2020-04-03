/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTabOneValueFlag.cpp 	  		           	 	  				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	d'une valeur mais qui passe a	"Non" ou 					*/
/*%C  autre pour un un certain flag de la BD												*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelTabOneValueFlag.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelTabOneValueFlag::LabelTabOneValueFlag():LabelTabOneValueDefault()
{
   IdFlag1 = 0;
   DbIdFlag1 = ADJUST;
   FlagForDefault1 = FALSE;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelTabOneValueFlag::SetIdFlag1(UWORD16 _IdFlag1)
{
   IdFlag1 = _IdFlag1;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabOneValueFlag::GetIdFlag1()
{
   return IdFlag1;
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValueFlag::SetDbIdFlag1(e_TYPE_OF_DB_TARGET _DbIdFlag1)
{
   DbIdFlag1 = _DbIdFlag1;
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET LabelTabOneValueFlag::GetDbIdFlag1()
{
   return DbIdFlag1;
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValueFlag::SetFlagForDefault1(e_BOOL _FlagForDefault1)
{
   FlagForDefault1 = _FlagForDefault1;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTabOneValueFlag::GetFlagForDefault1()
{
	return FlagForDefault1;
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValueFlag::SetValue1(UWORD16 _Value1)
{
	UWORD16 Value;
	DataBaseAccess::ReadValue(	&Value,
										GetIdFlag1(), 
										GetDbIdFlag1());

	if((Value == 	GetFlagForDefault1()) && 
						(GetPtrNameDefaultValue1() != NULL))
	{
		SetValue1IsString(TRUE);
		
		UWORD16 col = IsValue1Maxi() ? THIRD_VALUE_COLUMN : FIRST_VALUE_COLUMN;
		
		/*%C Set colum just near the table to avoid the message erase the table */
		GetFValue1()->SetCol(col);
		GetFValue1()->SetText(GetNameDefaultValue1());
		GetFValue1()->SetCol(	col+
										(COLUMN_WIDTH-
										Tools::GetStringPixelSize
										(GetNameDefaultValue1(),
										GetFontValue1()))/2);

      _Value1 = _Value1 / GetDivider();
		GetFValue1()->StoreValue(_Value1);

		if(GetLoupe() != NULL)
      {
         GetLoupe()->SetValue(GetNameDefaultValue1());
		}
   }
   else
   {
    	SetValue1IsString(FALSE);
      Value = Value / GetDivider();
      LabelTabOneValue::SetValue1(_Value1);
   }
}


/******************************************************************************/
/*                           METHODES                							      */
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
/*%I		FlagForDefault1     : valeur1 du flag pour defaut						  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValueFlag::InitDefaultFlag(  UBYTE** _NameDefaultValue1,
                                             UWORD16 _IdDefaultFlag1,
                                             e_TYPE_OF_DB_TARGET _DbIdFlag1,
                                             e_BOOL _FlagForDefault1)
{
   LabelTabOneValueDefault::InitDefaultValue(_NameDefaultValue1,0);
   IdFlag1 = _IdDefaultFlag1;
   DbIdFlag1 = _DbIdFlag1;
   FlagForDefault1 = _FlagForDefault1;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Increment de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValueFlag::IncreaseValue()
{
   UWORD16 Value = GetValue1();

   /*%C Access to data base */
   /*%C Pas de verication du retour pour permettre la verification du flag */
   IncreaseValueOk(&Value);
   /*%C Access to data base */
	SetValue1(Value);

}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Decrement de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValueFlag::DecreaseValue()
{
   UWORD16 Value = GetValue1();

   /*%C Access to data base */
   DecreaseValueOk(&Value);
   /*%C Access to data base */
   SetValue1(Value);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Confirme la modification de la valeur de Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValueFlag::ConfirmModifValue(e_BOOL _Confirm)
{
   if(_Confirm)
   {
      LabelTabOneValue::ConfirmModifValue(_Confirm);
   }
   else
   {
      /*%C Initialisation du flag */
      UWORD16 Value = GetValueFlagTemp();
      DataBaseAccess::WriteValue(&Value,
      									GetIdFlagTemp(),
      									GetDbIdFlagTemp());

      LabelTabOneValue::ConfirmModifValue(_Confirm);
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Debut de la modification d'un Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValueFlag::StartModifMode()
{
   LabelTabOneValue::StartModifMode();

   UWORD16 Value;

   DataBaseAccess::ReadValue(	&Value, 
   									GetIdFlag1(), 
   									GetDbIdFlag1());

   SetValueFlagTemp(Value);
   SetIdFlagTemp(GetIdFlag1());
   SetDbIdFlagTemp(GetDbIdFlag1());
}
