/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueSign.cpp  	    	                	 	  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage d'une valeur avec un signe										*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelOneValueSign.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#define LOCAL_MAX_SIGN_SIZE 3200

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelOneValueSign::LabelOneValueSign():LabelOneValue()
{
   SetColSep(72);
   SetColSign(80);
   SetColValue1(91);
   SetColUnit1(112);
   SetSignFont(FONT_4);

	FSign.SetParent(this);
   this->CachedSignSize = LOCAL_MAX_SIGN_SIZE;
}
/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelOneValueSign::SetSign(UBYTE *_Sign)
{
   UWORD16 value;
   FSign.SetText(_Sign);
   value = GetSignSize();  /* To force sign size calculation and cache storage */
   value = value; /* to avoid warning */
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelOneValueSign::GetSign()
{
   return FSign.GetText();
}
/*----------------------------------------------------------------------------*/
TextField* LabelOneValueSign::GetFSign()
{
   return &FSign;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueSign::SetSignFont(UWORD16 _Font)
{
   FSign.SetFont(_Font);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValueSign::GetSignFont()
{
   return FSign.GetFont();
}
/*----------------------------------------------------------------------------*/
void LabelOneValueSign::SetColSign(UWORD16 _ColSign)
{
   FSign.SetCol(_ColSign);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValueSign::GetColSign()
{
   return FSign.GetCol();
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValueSign::GetSignSize()
{
   UWORD16 rvalue;
   if(CachedSignSize != LOCAL_MAX_SIGN_SIZE)
      rvalue = this->CachedSignSize;
   else
   {
      rvalue = Tools::GetStringPixelSize(this->GetSign(), this->GetFSign()->GetFont());
      this->CachedSignSize = rvalue;
   }
   return(rvalue);
}
/*----------------------------------------------------------------------------*/
void LabelOneValueSign::SetValue1(UWORD16 _Value1)
{
   LabelOneValue::SetValue1(_Value1);
   SetValueIsString(FALSE);
   if(GetLoupe() != NULL)
   {
      if(GetFloatValue1() == 0)
      {
         GetLoupe()->SetValue(_Value1);
      }
      else
      {
         GetLoupe()->SetValue(_Value1,1);
      }
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
void LabelOneValueSign::Init( e_SYMBOL _Icon,
                              UBYTE **_Name,
                              UWORD16 _Line,
                              UWORD16 _Col,
                              UWORD16 _Value1,
                              UBYTE **_NameUnit1,
                              UBYTE *_Sign)
{
	/*%C Initialisation */
   SetSign(_Sign);
   LabelOneValue::Init(_Icon, _Name, _Line, _Col, _Value1, _NameUnit1);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Permet de savoir quel type de valeur est affiché Int|String					*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Flag   : si TRUE la valeur est un string				 			      	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueSign::SetValueIsString(e_BOOL _Flag)
{
   LabelOneValue::SetValueIsString(_Flag);
   if(_Flag)
   {
      FSign.Hide();
      GetFValue1()->SetCol(GetFSep()->GetCol() + 4);
   }
   else
   {
      //GetFValue1()->SetCol(GetFSign()->GetCol() + 8);
      GetFValue1()->SetCol(GetFSign()->GetCol() + GetSignSize()+ 2);
      FSign.Show();
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Passage en invertion video																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	InvertVideo   : invertion si TRUE						 			      	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueSign::setInvertVideo(e_BOOL _InvertVideo)
{
   /*%C Invert video */
   LabelOneValue::SetInvertVideo(_InvertVideo);
   FSign.SetReverseVideo(_InvertVideo);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																 			      	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueSign::Show()
{
   LabelOneValue::Show();
   if(!IsValueIsString())
   {
      FSign.Show();
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet			 															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																 			      	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueSign::Hide()
{
   FSign.Hide();
   LabelOneValue::Hide();   
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Blink de l'Objet			 																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																 			      	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueSign::Blink(e_BOOL _Actif)
{
   LabelOneValue::Blink(_Actif);
}

