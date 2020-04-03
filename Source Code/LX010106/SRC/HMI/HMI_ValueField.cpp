/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_ValueField.cpp									 						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage d'une valeur											 			  	*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_ValueField.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/

#include "HMI_InterfaceCppC.hpp"
#include "HMI_Tools.hpp"

extern "C"
{
#include "stdfile.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR	                	   	*/
/******************************************************************************/
ValueField::ValueField():FieldObject()
{
	Value = 0;
	NbDigit = 0;
	DisplayZero = FALSE;
	Float = FALSE;
	SignValue = FALSE;
	IEDisplay = FALSE;
	ChildBackgroundEqualParent = TRUE;
   SetDivider(1);
}
/*----------------------------------------------------------------------------*/
ValueField::ValueField(DisplayObject *_Parent)
{
	ValueField();
	SetParent(_Parent);
	ChildBackgroundEqualParent = TRUE;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void ValueField::SetValue(UWORD16 _Value)
{
	if(GetValue() != _Value)
   {
		/*%C effacement de la valeur precedante si nb car != */
		if(Tools::FindNbDigit(GetValue()) != Tools::FindNbDigit(_Value))
		{
			Clear();
		}
		/*%C affectation */
		Value = _Value;
		/*%C affichage */
		if(IsVisible())
      {
			Show();
		}
	}
}
/*----------------------------------------------------------------------------*/
UWORD16 ValueField::GetValue()
{
   return Value;
}
/*----------------------------------------------------------------------------*/
void ValueField::SetNbDigit(UWORD16 _NbDigit)
{
	NbDigit = _NbDigit;
}
/*----------------------------------------------------------------------------*/
UWORD16 ValueField::GetNbDigit()
{
	return NbDigit;
}
/*----------------------------------------------------------------------------*/
void ValueField::SetDivider(UWORD16 _Divider)
{
   Divider =_Divider;
}
/*----------------------------------------------------------------------------*/
UWORD16 ValueField::GetDivider()
{
   return(Divider);
}
/*----------------------------------------------------------------------------*/
void ValueField::SetDisplayZero(e_BOOL _DisplayZero)
{
   DisplayZero = _DisplayZero;

	if(IsVisible())
   {
		Show();
	}
}
/*----------------------------------------------------------------------------*/
e_BOOL ValueField::GetDisplayZero()
{
	return DisplayZero;
}
/*----------------------------------------------------------------------------*/
void ValueField::SetFloat(e_BOOL _Float)
{
	if(IsVisible())
	{
		Clear();
	}

	Float = _Float;

	if(IsVisible())
	{
		Show();
	}
}
/*----------------------------------------------------------------------------*/
e_BOOL ValueField::GetFloat()
{
	return Float;
}
/*----------------------------------------------------------------------------*/
void ValueField::SetSignValue(e_BOOL _SignValue)
{
	SignValue = _SignValue;
}
/*----------------------------------------------------------------------------*/
e_BOOL ValueField::IsSignValue()
{
	return (e_BOOL)(SignValue == TRUE);
}
/*----------------------------------------------------------------------------*/
void ValueField::SetChildBackgroundEqualParent(e_BOOL _Value)
{
	ChildBackgroundEqualParent = _Value;
}
/*----------------------------------------------------------------------------*/
void ValueField::SetIEDisplay(e_BOOL _Value)
{
	IEDisplay = _Value;
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
/*%I		Line         : ligne 											            	*/
/*%I		Col          : colonne 										            		*/
/*%I		ReverseVideo : TRUE si en reverse video			     		         	*/
/*%I		Font		   : font								     		            		*/
/*%I		Value		   : valeur a afficher					     		         		*/
/*%I		NbNbDigit	   : nombre de digit					     		            	*/
/*%I		DisplayZero  : TRUE si affichage de zero			     		      		*/
/*%I		Float		   : TRUE si la valeur est un float									*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE																						*/
/******************************************************************************/
void ValueField::Init(  UWORD16 _Line,
                        UWORD16 _Col,
                        UWORD16 _Font,
                        e_BOOL _ReverseVideo,
                        UWORD16 _Value,
                        UWORD16 _NbNbDigit,
                        e_BOOL _DisplayZero,
                        e_BOOL _Float)
{
	FieldObject::Init(_Line, _Col, _Font, _ReverseVideo);
	SetNbDigit(_NbNbDigit);
	SetDisplayZero(_DisplayZero);
	SetFloat(_Float);
	SetValue(_Value);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation																				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Value	: Valeur a enregistrer														*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE																						*/
/******************************************************************************/
void ValueField::ForceValue(UWORD16 _Value)
{
	/*%C effacement de la valeur precedante */
	/*%C affectation */
   Value = _Value;

	/*%C affichage */
	if(IsVisible())
   {
      Show();
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Enregistre la valeur mais ne l'affiche pas											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE																						*/
/******************************************************************************/
void ValueField::StoreValue(UWORD16 _Value)
{
   Value = _Value;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Blink de l'Objet																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE																						*/
/******************************************************************************/
void ValueField::Blink(e_BOOL _Actif)
{
	if(_Actif)
   {
		Hide();
	}
	else
   {
		Show();
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Affichage de l'Objet			  															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE																						*/
/******************************************************************************/
void ValueField::Show()
{
	if(!HaveParent() || GetParent()->IsVisible())
   {
		FieldObject::Show();
		UWORD16 ColTmp, LineTmp;
		LineTmp = GetLine();
		ColTmp = GetCol();
		SWORD32 Value;

		if(HaveParent())
      {
			LineTmp = LineTmp+ GetParent()->GetLine();
			ColTmp  = ColTmp + GetParent()->GetCol();
		}

		if(IsSignValue())
      {
			Value = (SWORD16)(GetValue() * GetDivider());
         Value = Value / GetDivider();
		}
		else
      {
			Value = (UWORD16)GetValue();
		}

		if(IEDisplay)
		{
         InterfaceCppC::DisplayString( (UBYTE *)"1/",
			   					            GetFont(),
         			   						GetReverseVideo(),
			          							LineTmp,
							            		ColTmp,
            									1,
				        						   GetPage());

			   ColTmp  = ColTmp + Tools::GetStringPixelSize((UBYTE *)"1/",GetFont());
      }
		InterfaceCppC::DisplayNumber( Value,
									         GetFloat(),
									         GetReverseVideo(),
         									LineTmp,
			         						ColTmp,
									         GetFont(),
									         GetNbDigit(),
									         GetDisplayZero(),
                                    1,
									         GetPage());
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Effacement de l'Objet		  															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE																						*/
/******************************************************************************/
void ValueField::Hide()
{
	if(IsVisible())
   {
		/*%C  Clear before hide !! */
		Clear();
		FieldObject::Hide();
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Efface la valeur courante	  															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE																						*/
/******************************************************************************/
void ValueField::Clear()
{
	e_BOOL ReverseVideo;

	if(IsVisible())
   {
		UWORD16 ColTmp, LineTmp;
		SWORD32 Value;
		LineTmp = GetLine();
		ColTmp = GetCol();

		if(HaveParent())
      {
			LineTmp = LineTmp+ GetParent()->GetLine();
			ColTmp  = ColTmp + GetParent()->GetCol();
		}

		if(IsSignValue())
      {
			Value = (SWORD16)(GetValue() * GetDivider());
         Value = Value / GetDivider();
		}
		else
      {
			Value = (UWORD16)GetValue();
		}

		if(ChildBackgroundEqualParent)
	        ReverseVideo = GetReverseVideo();
        else
	        ReverseVideo = (e_BOOL)!GetReverseVideo();

		if(IEDisplay)
		{
         InterfaceCppC::DisplayString( (UBYTE *)"1/",
			         							GetFont(),
         										ReverseVideo,
			         							LineTmp,
         										ColTmp,
         										0,
			         							GetPage());
         ColTmp  = ColTmp + Tools::GetStringPixelSize((UBYTE *)"1/",GetFont());
      }

		InterfaceCppC::DisplayNumber( Value,
		         							GetFloat(),
         									ReverseVideo,
			         						LineTmp,
         									ColTmp,
         									GetFont(),
         									GetNbDigit(),
         									GetDisplayZero(),
			            					0,
							         		GetPage());
    }
}
