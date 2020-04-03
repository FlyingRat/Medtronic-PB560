/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_MonitoringObjectWithRecall.cpp 	    	 	  						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(dérivé de MonitoringObject)				 					*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_MonitoringObjectWithRecall.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"
#include "HMI_Tools.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION		                			*/
/******************************************************************************/
#define FIRST_LINE			12
#define THIRD_LINE			37
#define BORDER_WIDTH		   2

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
MonitoringObjectWithRecall::MonitoringObjectWithRecall():MonitoringObject()
{
   VTFLimit[0].SetParent(this);
	VTFLimit[0].Init(FIRST_LINE, 30, FONT_2, FALSE,0, 0,FALSE, FALSE);
   VTFLimit[1].SetParent(this);
	VTFLimit[1].Init(THIRD_LINE, 30, FONT_2, FALSE,0, 0,FALSE, FALSE);

	SetDbTarget(ADJUST);
	SetIdParam(0);
   SetInvertVideo(FALSE);
   LimitDisplay[0] = FALSE;
	LimitDisplay[1] = FALSE;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
UWORD16 MonitoringObjectWithRecall::GetBlinkTarget(void)
{
   return BlinkTarget;
}
/*----------------------------------------------------------------------------*/
void MonitoringObjectWithRecall::SetBlinkTarget(UWORD16 _BlinkTarget)
{
   BlinkTarget = _BlinkTarget;
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
/*%I		Line   : ligne 																		*/
/*%I		Col    : colonne																		*/
/*%I		Name    : Name																			*/
/*%I		Value  : Valeur 																		*/
/*%I		ValueFloat : Valeur 																  	*/
/*%I		Text : Texte		 																  	*/
/*%I		TextHeadOn : Texte  																  	*/
/*%I		Centered : Centre	  																  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/

void MonitoringObjectWithRecall::Init( UWORD16 _Line,
                                       UWORD16 _Col,
                                       UBYTE **_Name,
                                       UWORD16 _Value,
                                       e_BOOL _ValueFloat,
                                       UBYTE ** _Text,
                                       e_BOOL _TextHeadOn,
                                       e_BOOL _Centered)
{
	MonitoringObject::Init( NO,
                           _Line,
                           _Col,
                           _Name,
                           _Value,
                           _ValueFloat,
                           _Text,
                           _TextHeadOn,
                           _Centered);

	for(int i=0; i<RECALL_NB; i++)
   {
      VTFLimit[i].SetIEDisplay(_TextHeadOn);
	   VTFLimit[i].SetFloat(_ValueFloat);
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des paramettres d'acce a DB											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		IdParam : Id DB												              	 	*/
/*%I		DbTarget : Target DB										            			*/
/*%I		IdParamLimit : Id DB de la valeur limite						      		*/
/*%I		DbTargetLimit : Target DB de la valeur limite					      	*/
/*%I		FirstLimitDisplay : Flag indiquant si c'est la 1ère limite	  			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObjectWithRecall::InitDbAccess1( 
												UWORD16 _IdParamRefresh,
                                    e_TYPE_OF_DB_TARGET _DbTargetRefresh,
											   UWORD16 _IdParamLimit,
                                    e_TYPE_OF_DB_TARGET _DbTargetLimit,
											   e_BOOL _FirstLimitDisplay)
{
	MenuObject::InitDbAccess(_IdParamRefresh, _DbTargetRefresh);

   if(_FirstLimitDisplay)
   {
      LimitDisplay[0] = TRUE;
      VTFLimit[0].InitDbAccess(_IdParamLimit, _DbTargetLimit);
   }
   else
   {
      LimitDisplay[1] = TRUE;
      VTFLimit[1].InitDbAccess(_IdParamLimit, _DbTargetLimit);
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des paramettres d'acce a DB											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		IdParam : Id DB												              	 	*/
/*%I		DbTarget : Target DB										            			*/
/*%I		IdParamLimit1 : Id DB de la 1ère valeur limite				      		*/
/*%I		DbTargetLimit1 : Target DB de la 1ère valeur limite			      	*/
/*%I		IdParamLimit1 : Id DB de la 2ème valeur limite				      		*/
/*%I		DbTargetLimit1 : Target DB de la 2ème valeur limite			      	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE									  											 		*/
/******************************************************************************/
void MonitoringObjectWithRecall::InitDbAccess2( 
												UWORD16 _IdParamRefresh,
                                    e_TYPE_OF_DB_TARGET _DbTargetRefresh,
												UWORD16 _IdParamLimit1,
                                    e_TYPE_OF_DB_TARGET _DbTargetLimit1,
   				   						UWORD16 _IdParamLimit2,
                                    e_TYPE_OF_DB_TARGET _DbTargetLimit2)
{
   MenuObject::InitDbAccess(_IdParamRefresh, _DbTargetRefresh);
   LimitDisplay[0] = TRUE;
	LimitDisplay[1] = TRUE;
	VTFLimit[0].InitDbAccess(_IdParamLimit1, _DbTargetLimit1);
	VTFLimit[1].InitDbAccess(_IdParamLimit2, _DbTargetLimit2);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation d'une limite	(si présence d'un flag)								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		FlagNb : Nb of flag (0 or 1)                                    		*/
/*%I		NameDfltValue : Text of default value							      		*/
/*%I		IdDfltFlag : Database flag ID									         		*/
/*%I		DbIdFlag : Database ID										            		*/
/*%I		FlagForDflt : Flag default value			      								*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE									  											 		*/
/******************************************************************************/
void MonitoringObjectWithRecall::InitDefaultFlag(  
												UBYTE _FieldNb,
                                    UBYTE** _NameDfltValue,
                                    UWORD16 _IdDfltFlag,
                                    e_TYPE_OF_DB_TARGET _DbIdFlag,
                                    e_BOOL _FlagForDflt)
{
	if(_FieldNb >= RECALL_NB)	
	{
		return;
	}

	DefaultFlag[_FieldNb] = TRUE;
	NameDefaultValue[_FieldNb] = _NameDfltValue;
	IdDefaultFlag[_FieldNb] = _IdDfltFlag;
	DbIdFlag[_FieldNb] = _DbIdFlag;
	FlagForDefault[_FieldNb] = _FlagForDflt;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Passage en invertion video																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		InvertVideo   : invertion si TRUE		      								*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE									  											 		*/
/******************************************************************************/
void MonitoringObjectWithRecall::SetInvertVideo(e_BOOL _InvertVideo)
{
	MonitoringObject::SetInvertVideo(_InvertVideo);

	for(int i=0; i<2; i++)
	{
    	VTFLimit[i].SetReverseVideo(_InvertVideo);
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE												      								*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE									  											 		*/
/******************************************************************************/
void MonitoringObjectWithRecall::Show()
{
	UWORD16 Value;

	MonitoringObject::Show();

	for(int i=0; i<2; i++)
   {
	   VTFLimit[i].Hide();
		if(LimitDisplay[i])
    	{
        	if(DefaultFlag[i])
         {
				DataBaseAccess::ReadValue(&Value, IdDefaultFlag[i], DbIdFlag[i]);
            if(Value == FlagForDefault[i])
            {
    		      VTFLimit[i].SetTextOnly(NameDefaultValue[i][GetLanguage()]);
            }
	         else
    	      {
			  		DataBaseAccess::ReadValue( &Value,
               	                        VTFLimit[i].GetIdParam(),
                  	                     VTFLimit[i].GetDbTarget());
					VTFLimit[i].SetValue(Value);
				}
         }
         else
         {
				DataBaseAccess::ReadValue( &Value,
                                       VTFLimit[i].GetIdParam(),
                                       VTFLimit[i].GetDbTarget());
    			VTFLimit[i].SetValue(Value);
         }
    	}
      else
		{
    		VTFLimit[i].SetTextOnly((UBYTE *)"- ");
		}

		VTFLimit[i].SetCol(1 + FRAME_WIDTH - BORDER_WIDTH
                           - VTFLimit[i].GetPixelSize());
		VTFLimit[i].Show();
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement	de l'Objet	 																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE												      								*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE									  											 		*/
/******************************************************************************/
void MonitoringObjectWithRecall::Hide()
{
	for(int i=0; i<2; i++)
	{
      VTFLimit[i].Hide();
	}

	MonitoringObject::Hide();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Blink de la limite max	 																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE												      								*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE									  											 		*/
/******************************************************************************/
void MonitoringObjectWithRecall::Blink(e_BOOL _Actif)
{
   if(GetParent()->IsVisible())
	{
      VTFLimit[GetBlinkTarget()].Blink(_Actif);
	}
}

