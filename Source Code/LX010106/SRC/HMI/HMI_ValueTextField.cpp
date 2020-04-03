/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_ValueTextField.cpp 								 						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage d'une valeur|String								 			  	*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_ValueTextField.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/

#include "HMI_InterfaceCppC.hpp"

#include "HMI_Tools.hpp"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
ValueTextField::ValueTextField():ValueField()
{
	Text = NULL;
	IsString = FALSE;
}
/*----------------------------------------------------------------------------*/
ValueTextField::ValueTextField(DisplayObject *_Parent)
{
	ValueTextField();
	ValueField::SetParent(_Parent);
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void ValueTextField::SetValue(UWORD16 _Value)
{
	/*%C affectation */
	if((IsString) || (GetValue() != _Value))
   {
		if(IsString)
      {
			Clear();
			IsString = FALSE;
			ValueField::ForceValue(_Value);
		}
		else
      {
			ValueField::SetValue(_Value);
		}
	}
}
/*----------------------------------------------------------------------------*/
void ValueTextField::SetText(UBYTE* _Text)
{
	/*%C effacement de la valeur precedante */
	Clear();
	
	/*%C affectation */
	Text = _Text;
	IsString = TRUE;

	/*%C affichage */
	if(IsVisible())
   {
		Show();
	}
}
/*----------------------------------------------------------------------------*/
UBYTE* ValueTextField::GetText()
{
	if(Text != NULL)
   {
		return (Text);
	}
	else
      return (UBYTE *)"???";
}
/*----------------------------------------------------------------------------*/
UBYTE ValueTextField::GetPixelSize()
{
	if(IsString)
	{
		return Tools::GetStringPixelSize(Text, GetFont());
	}
   else if(IEDisplay)
	{
		return Tools::GetStringPixelSize((UBYTE *)"1/",
                                       GetFont()) + 
                                       Tools::GetNumberPixelSize(
                                       GetValue(),
                                       GetFont(),
                                       GetFloat());
	}
   else
	{
		return Tools::GetNumberPixelSize(GetValue(), GetFont(), GetFloat());
	}
}

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Enregistrment de la valeur sans affichage			 							  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Text : Texte a afficher																*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ValueTextField::SetTextOnly(UBYTE* _Text)
{
	/*%C effacement de la valeur precedante */
	Clear();

	/*%C affectation */
	Text = _Text;
   IsString = TRUE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet										 							  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ValueTextField::Show()
{
   if(!HaveParent() || GetParent()->IsVisible())
   {
		if(IsString)
      {
			FieldObject::Show();

			UWORD16 ColTmp, LineTmp;
			LineTmp = GetLine();
			ColTmp = GetCol();

			if(HaveParent())
         {
				LineTmp = LineTmp + GetParent()->GetLine();
				ColTmp  = ColTmp + GetParent()->GetCol();
			}

			InterfaceCppC::DisplayString( GetText(),
										         GetFont(),
         										GetReverseVideo(),
			         							LineTmp,
						         				ColTmp,
									         	1,
         										GetPage());
		}
		else
      {
			ValueField::Show();
		}
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet									 							  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ValueTextField::Hide()
{
    if(!HaveParent() || GetParent()->IsVisible())
    {
	    if(IsVisible())
        {
		    if(!IsString)
            {
			    ValueField::Hide();
    		}
	    	else
            {
			    /*%C Clear before hide !! */
			    Clear();
			    FieldObject::Hide();
		    }
	    }
    }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Efface la valeur courante							 							  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ValueTextField::Clear()
{
	 if(!HaveParent() || GetParent()->IsVisible())
     {
        if(IsVisible())
        {
		    if(!IsString)
            {
			    ValueField::Clear();
		    }
		    else
            {
			    UWORD16 ColTmp, LineTmp;
			    LineTmp = GetLine();
			    ColTmp = GetCol();

			    if(HaveParent())
                {
				    LineTmp = LineTmp+ GetParent()->GetLine();
				    ColTmp  = ColTmp + GetParent()->GetCol();
			    }

                if(ChildBackgroundEqualParent)
				    InterfaceCppC::DisplayString(   GetText(),
				         							GetFont(),
											        GetReverseVideo(),
         											LineTmp,
			         								ColTmp,
						         					0,
									         		GetPage());
                else
				    InterfaceCppC::DisplayString(   GetText(),
											        GetFont(),
         											(e_BOOL)!GetReverseVideo(),
         											LineTmp,
      			   								    ColTmp,
		         									0,
						         					GetPage());
		    }
        }
	}
}
