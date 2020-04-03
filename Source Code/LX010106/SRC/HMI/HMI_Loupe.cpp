/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Loupe.cpp 						   	      	 	  					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage de la loupe										 					*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_Loupe.hpp"
#include "HMI_FrameVentilation.hpp"
#include "enum.h"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                     	   */
/******************************************************************************/


/******************************************************************************/
/*                        VARIABLE DECLARATION		                	   		*/
/******************************************************************************/

UBYTE *Vide = (UBYTE *)"";

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
Loupe::Loupe():DisplayObject()
{
   FValueS.SetParent(this);
	FValueI.SetParent(this);
	MonitorBox.SetParent(this);

   SetValue((UWORD16)0);
   SetColValue(8);
	SetLineValue(90);

   FValueI.SetReverseVideo(TRUE);
   FValueS.SetReverseVideo(TRUE);

   FValueI.SetFont(FONT_5);
   FValueS.SetFont(FONT_5);

	Message.SetParent				(this);

   Message.SetWhithBox			(WHITH_VENTILBOX);

	Message.InitGraphicBox		(146,
										195,
										35,
										WHITH_VENTILBOX,
                              FALSE,
                              FALSE,
										TRUE);

	Message.SetLineLine1			(14);

	Message.SetLineLine2			(29);

	Message.SetLineLine3			(44);

	MonitorBox.Init(33,COL_VENTILBOX,151,WHITH_VENTILBOX,TRUE,TRUE,TRUE);
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void Loupe::SetColValue(UWORD16 _ColValue)
{
   FValueI.SetCol(_ColValue);
   FValueS.SetCol(_ColValue);
}
/*----------------------------------------------------------------------------*/
void Loupe::SetLineValue(UWORD16 _LineValue)
{
   FValueI.SetLine(_LineValue);
   FValueS.SetLine(_LineValue);
}
/*----------------------------------------------------------------------------*/
UWORD16 Loupe::GetValue()
{
   return FValueI.GetValue();
}
/*----------------------------------------------------------------------------*/
void Loupe::SetValue(UWORD16 _Value)
{
   FValueS.Hide();
   FValueI.Hide();
   FValueI.SetValue(_Value);
   FValueI.SetFloat(FALSE);
   Format(eValue);
   SetDataType(eValue);
}
/*----------------------------------------------------------------------------*/
void Loupe::SetValue(UWORD16 _Value, UWORD16 _dec)
{
   /* Pour éviter les warnings */
   _dec = _dec;

   FValueS.Hide();
   FValueI.Hide();
   FValueI.SetValue(_Value);
   FValueI.SetFloat(TRUE);
   Format(eValue);
   SetDataType(eValue);
}
/*----------------------------------------------------------------------------*/
void Loupe::SetValue(UBYTE *_Sign, UWORD16 _Value)
{
   FValueS.Hide();
   FValueI.Hide();
   FValueS.SetText(_Sign);
   FValueI.SetValue(_Value);
   FValueI.SetFloat(FALSE);
   Format(eValueSign);
   SetDataType(eValueSign);
}
/*----------------------------------------------------------------------------*/
UWORD16 Loupe::GetFloat()
{
   return FValueI.GetFloat();
}
/*----------------------------------------------------------------------------*/
void Loupe::SetValue(UBYTE *_Sign, UWORD16 _Value, UWORD16 _dec)
{
   /* Pour éviter les warnings */
   _dec = _dec;

   FValueS.Hide();
   FValueI.Hide();
   FValueS.SetText(_Sign);
   FValueI.SetValue(_Value);
   FValueI.SetFloat(TRUE);
   Format(eValueSign);
   SetDataType(eValueSign);
}
/*----------------------------------------------------------------------------*/
void Loupe::SetValue(UBYTE *_ValueString)
{
   FValueS.Hide();
   FValueI.Hide();
   FValueS.SetText(_ValueString);
   Format(eString);
   SetDataType(eString);
}
/*----------------------------------------------------------------------------*/
/* Can used for SetFText Accessor */
void Loupe::SetMessage(UBYTE *_Text)
{
   Message.SetMessage(_Text, NO);
}
/*----------------------------------------------------------------------------*/
DataType Loupe::GetDataType()
{
   return Dtype;
}
/*----------------------------------------------------------------------------*/
void Loupe::SetDataType(DataType _Type)
{
   Dtype = _Type;
   switch(_Type)
   {
      case eValue  : FValueS.Hide();
                     FValueI.Show();
                     break;

      case eString : FValueI.Hide();
                     FValueS.Show();
                     break;

      case eValueSign : FValueI.Show();
                        FValueS.Show();
                        break;
      default : break;                        
   }
}
/*----------------------------------------------------------------------------*/
e_BOOL Loupe::IsHaveMessage()
{
   return (e_BOOL)(HaveText == TRUE);
}
/*----------------------------------------------------------------------------*/
void Loupe::DisplayMessage(e_BOOL _Val)
{
   HaveText = _Val;

   if(_Val)
   {
      Message.Show();
   }
   else
   {
      Message.Hide();
   }
}
/*----------------------------------------------------------------------------*/
TextField* Loupe::GetFValueS()
{
   return &this->FValueS;
}
/*----------------------------------------------------------------------------*/
ValueField* Loupe::GetFValueI()
{
   return &this->FValueI;
}

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void Loupe::Show()
{
   /*%C effacement de la derniere valeur */
   SetValue(Vide);

   DisplayObject::Show();

	/*%C affichage des boites */
   MonitorBox.Show();
   
   FValueI.Hide();
   FValueS.Show();

   if(IsHaveMessage())
   {
      Message.Show();
   }
   else
   {
      Message.Hide();
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void Loupe::Hide()
{
   FValueS.Hide();
   FValueI.Hide();
   Message.Hide();
   DisplayObject::Hide();   
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Blink de l'Objet																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void Loupe::Blink(e_BOOL _Actif)
{
   switch(GetDataType())
	{
      case eValue  : FValueI.Blink(_Actif);
                     break;

      case eString : FValueS.Blink(_Actif);
                     break;

      case eValueSign : FValueI.Blink(_Actif);
                        FValueS.Blink(_Actif);
                        break;
      default : break;                        
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Permet de centrer la valeur en fct du type											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Type : type de la valeur															*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void Loupe::Format(DataType _Type)
{
   UWORD16 length = 0;

   switch(_Type)
   {
      case eValue  :
        length = Tools::FindNbDigit(GetValue());
        if((length == 1) && GetFloat())
            length = 2;  
      	switch(length)
	      {
   	      case 1 : SetColValue(48);
      	            break;
         	case 2 : SetColValue(32);
	                  break;
   	      case 3 : SetColValue(24);
      	            break;
	         case 4 : SetColValue(8);
   	               break;
            default : break;                     
      	}
     	 	break;

      case eString :  length = Tools::StrLen(FValueS.GetText());
      	switch(length)
	      {
   	      case 1 :  this->SetColValue(40); break;
      	   case 2 :  this->SetColValue(24); break;
	         case 3 :  this->SetColValue(16); break;
   	      case 4 :  this->SetColValue(7); break;
      	   /*%C Cas unique pour le message " 1 (p) " */
         	case 5 :  this->SetColValue(17); break;
            default : break;
	      }
   	   break;

      case eValueSign : if( FValueS.GetText()[0] == 'x')
                        {
                           FValueI.SetCol(48);
                        }
                        else
                        {
                           FValueI.SetCol(40);
                        }
                        FValueS.SetCol(8);
                        break;
      default : break;                        
	}
}


