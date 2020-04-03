/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTwoValueTrig.cpp 		   	      	 	  					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	de 2 valeurs avec trigger					 					*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelTwoValueTrig.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/
#include "HMI_Config.hpp"
#include "HMI_DataBaseAccess.hpp"
#include "define.h"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelTwoValueTrig::LabelTwoValueTrig():LabelTwoValueLock()    
{
   FTrig.SetParent(this);
   FTrig.SetSymbol(TRIGGER);
	FTrig.SetCol(136);
	HideTrigger();
	Float = FALSE;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelTwoValueTrig::SetColTrigger(UWORD16 _Col)
{
   FTrig.SetCol(_Col);
}
/*----------------------------------------------------------------------------*/
void LabelTwoValueTrig::SetTrigger(e_BOOL _Flag)
{
	Trigger = _Flag;
}
/*----------------------------------------------------------------------------*/
void LabelTwoValueTrig::SetFloatValues(e_BOOL _FloatValues)
{
	LabelOneValue::SetFloatValue1(_FloatValues);
	LabelTwoValue::SetFloatValue2(_FloatValues);
	SetFloat(_FloatValues);
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTwoValueTrig::IsTrigger()
{
    return(e_BOOL)(Trigger == TRUE);
}
/*----------------------------------------------------------------------------*/
void LabelTwoValueTrig::SetFloat(e_BOOL _Float)
{
	Float = _Float;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTwoValueTrig::GetFloat()
{
	return Float;
}

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de l'affichage																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValueTrig::Refresh()
{
    if (!IsStopMonitoring())
   {
		/*%C Check the Value #1 */
        if (GetIdParam() != NO_ID)
		{
			UWORD16 Value1;
			/*%C Read the Value #1 */
			DataBaseAccess::ReadValue(	&Value1,
												GetIdParam(),
												GetDbTarget());
			/*%C Apply the divisor */
			Value1 = Value1 / GetDivider();

#ifdef HMI_CONFIG_TRUNCATED_I_E
			/*%C If decimal is asked */
            if (Float)
			{
                //   if value >= 100 or value == 1.0
                //   then the value is set whith Integer attribute
                //   to force three significant digits
                if ((Value1 >= 1000) || (Value1 == 10))
				{
					SetFloatValue1(FALSE);
					Value1 = Value1 / 10;
				}
				/*%C else Value stay decimal */
				else
				{
					SetFloatValue1(TRUE);
				}
			}
#endif
			/*%C Check the righ colum */
			RefreshValueColumn();
			/*%C Apply the modification */
			SetValue1(Value1);
		}

		/*%C Check the Value #2 */
        if (GetIdParam2() != NO_ID)
		{
			UWORD16 Value2;
			/*%C Read the Value #2 */
			DataBaseAccess::ReadValue(	&Value2,
												GetIdParam2(),
												GetDbTarget2());
			/*%C Apply the divisor */
			Value2 = Value2 / GetDivider();

#ifdef HMI_CONFIG_TRUNCATED_I_E
			/*%C If decimal is asked */
            if (Float)
			{
                //   if value >= 100 or value == 1.0
                //   then the value is set whith Integer attribute
                //   to force three significant digits
                if ((Value2 >= 1000) || (Value2 == 10))
				{
					SetFloatValue2(FALSE);
					Value2 = Value2 / 10;
				}
				/*%C else Value stay decimal */
				else
				{
					SetFloatValue2(TRUE);
				}
			}
#endif
			/*%C Apply the modification */
			SetValue2(Value2);
		}
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Rafraichit les abscisses des 2 valeurs												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValueTrig::RefreshValueColumn()
{

    if (GetFloatValue1())
	{
		SetColValue2(GetColValue1() + 33);
	}
	else
	{
		SetColValue2(GetColValue1() + 18);
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affiche le trigger																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValueTrig::ShowTrigger()
{
   SetTrigger(TRUE);
	FTrig.Show();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Efface le trigger																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValueTrig::HideTrigger()
{
   SetTrigger(FALSE);
   FTrig.Hide();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Passage en invertion video																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		InvertVideo   : invertion si TRUE												*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValueTrig::SetInvertVideo(e_BOOL _InvertVideo)
{
   LabelTwoValueLock::SetInvertVideo(_InvertVideo);
   FTrig.SetReverseVideo(_InvertVideo);

    if (_InvertVideo)
   {
      FTrig.SetSymbol(TRIGGERINV);
   }
   else
   {
      FTrig.SetSymbol(TRIGGER);
   }
}

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
void LabelTwoValueTrig::Show()
{
	LabelTwoValueLock::Show();
    if (IsTrigger())
   {
      ShowTrigger();
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
void LabelTwoValueTrig::Hide()
{
   HideTrigger();
   LabelTwoValueLock::Hide();   
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement total de l'Objet (vide pour cette classe)                     */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValueTrig::HideAll()
{
   NO_THIS;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret du monitorage pour l'Objet														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValueTrig::StopMonitoringMode()
{
   LabelOneValue::StopMonitoringMode();
	SetTextValue2((UBYTE *)"");
}

