/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_VFrame.cpp 										 						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Fenetre					 													 			  	*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_VFrame.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/
#include "HMI_GlobalEventNode.hpp"
/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
VFrame::VFrame():DisplayObject()
{
   SetMessageOn(FALSE);
	SetMonitorOn(FALSE);
	LoupeObject = &LoupeV;
   SetImpactDisplay(FALSE);
   SetInfoTable(NULL, 0, 0, 0);
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void VFrame::SetMessageOn(e_BOOL _Flag)
{
   MessageOn = _Flag;
}
/*----------------------------------------------------------------------------*/
e_BOOL VFrame::IsMessageOn()
{
	return (e_BOOL)(MessageOn == TRUE);
}
/*----------------------------------------------------------------------------*/
void VFrame::SetMonitorOn(e_BOOL _Flag)
{
   MonitorOn = _Flag;
}
/*----------------------------------------------------------------------------*/
e_BOOL VFrame::IsMonitorOn()
{
	return (e_BOOL)(MonitorOn == TRUE);
}
/*----------------------------------------------------------------------------*/
Loupe* VFrame::GetLoupeObject()
{
   return LoupeObject;
}
/*----------------------------------------------------------------------------*/
void VFrame::SetImpactDisplay(e_BOOL _ImpactDisplay)
{
   ImpactDisplay = _ImpactDisplay;
}
/*----------------------------------------------------------------------------*/
e_BOOL VFrame::GetImpactDisplay()
{
   return(ImpactDisplay);
}
/*----------------------------------------------------------------------------*/
void VFrame::SetInfoTable(   tInfo* _InfoTablePtr,
                        UWORD16 _MaxObjects,
                        UWORD16 _SpaceHeight,
                        UWORD16 _SpaceFirstLine)
{
   InfoTablePtr = _InfoTablePtr;
   MaxObjects = _MaxObjects;
   SpaceHeight = _SpaceHeight;
   SpaceFirstLine = _SpaceFirstLine;
}
/*----------------------------------------------------------------------------*/
tInfo* VFrame::GetInfoTable()
{
   return(InfoTablePtr);
}
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne la table des Objets a rafraichir		 								  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Objets a rafraichir 																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
DisplayObject** VFrame::GetRefreshTable()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	return NULL;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet									 								  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE					 																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/

void VFrame::Show()
{
	DisplayObject::Show();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet	  							 								  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE					 																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VFrame::Hide()
{
	DisplayObject::Hide();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affiche la loupe					  							 							*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE					 																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VFrame::ShowLoupe()
{
   if(GetLoupeObject() != NULL)
   {
      GetLoupeObject()->Show();
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Efface la loupe			  							 								  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE					 																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VFrame::HideLoupe()
{
   if(GetLoupeObject() != NULL)
   {
      GetLoupeObject()->Hide();
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Changement du mode courant	  							 								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Mode : mode courant 																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VFrame::SetMode(e_MODE_TYPES _Mode)
{
	/* Pour éviter les warnings */
	_Mode = _Mode;
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Selectionne la loupe pour la fenetre alarme 								  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE					 																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VFrame::SelectLoupeAlarm()
{
   LoupeObject = &LoupeA;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de la zone de monitoring			 								  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE					 																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VFrame::ShowMonitoring()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de la zone de monitoring			 								  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE					 																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VFrame::HideMonitoring()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Contrôle la validité du contenu de la table de configuration des objets  */
/*%I Input Parameter : 																			*/
/*%I		NONE                                                                 */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si le contenu est OK, FALSE sinon  										*/
/******************************************************************************/
e_BOOL VFrame::CheckInfoTable(void)
{
   UWORD16 i,j,Order,LoopCount,countVisible ;
   tInfo* ptr;

   if(GetInfoTable() == NULL)
      return (FALSE);

   /*%C Pour chaque mode de ventilation */
   for(i=0;i<cMAX_MODE;i++)
   {
      countVisible = 0;
      j = 0;
      while(InfoTablePtr[j].pObject)
      {
         /*%C Un objet non visible doit avoir un Ordre égal à 0 */
         if((!InfoTablePtr[j].InfoByMode[i].Visible) &&
         (InfoTablePtr[j].InfoByMode[i].Order))
            return FALSE;
         if(InfoTablePtr[j].InfoByMode[i].Visible)
            countVisible++;

         j++;
      }

      /*%C Il y a forcément un objet d'ordre 0 */
      Order = 0;
      ptr = GetPtrFromOrder(Order, (e_MODE_TYPES) i);
      if (ptr == NULL)
            return (FALSE);

      /*%C Consécutivité des attributs "Order" pour chaque objet visible */
      LoopCount = 1;
      Order = 1;
      while (LoopCount != countVisible)
      {
         ptr = GetPtrFromOrder(Order, (e_MODE_TYPES) i);
         if (ptr == NULL)
            return (FALSE);
         LoopCount++;
         Order++;
      }
   }
   return (TRUE);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne un pointeur vers tInfo à partir de l'ordre d'affichage          */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_Order : Ordre d'affichage                                           */
/*%I		_Mode : Mode de Ventilation                                          */
/*%I     affichages															               */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		pointeur vers une ligne du tableau de configuration des affichages	*/
/******************************************************************************/
tInfo* VFrame::GetPtrFromOrder(UWORD16 _Order, e_MODE_TYPES _Mode)
{
	UWORD16 i = 0;
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   
   i = 0;
   while(InfoTablePtr[i].pObject)
   {
   	if ((InfoTablePtr[i].InfoByMode[_Mode].Order ==_Order)&&
     	(InfoTablePtr[i].InfoByMode[_Mode].Visible))
     	{
        	return (&InfoTablePtr[i]);
     	}
      i++;
   }
  	return (NULL);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine l'ordre d'affichage à partir d'un pointeur vers tInfo    	   */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_ptr : Pointeur vers un ligne du tableau de configuration des        */
/*%I     affichages															               */
/*%I		_Mode : Mode de Ventilation                                          */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Ordre d'affichage            														*/
/******************************************************************************/
UWORD16 VFrame::GetOrderFromPtr(tInfo* _ptr, e_MODE_TYPES _Mode)
{
	UWORD16 i = 0;
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

   i = 0;
   while(InfoTablePtr[i].pObject)
   {
     	if(&InfoTablePtr[i] == _ptr)
     	{
        	return (InfoTablePtr[i].InfoByMode[_Mode].Order);
     	}
      i++;
   }
  	return (0);
}
/************************************************************************/
/*%C Description   : Permute les configuration d'affichage de deux      */
/*%C objets pour un mode donné                                          */
/*%C Parametres en entree : 		                                       */
/*    - _First, _Second : Objets dont les configuration doivent être    */
/*                       permutées                                      */
/*		- _Mode : mode pour lequel la configuration doit être permutée    */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void VFrame::SwitchDisplayConfigForOneMode(  e_OBJECT _First,
                                             e_OBJECT _Second,
                                             e_MODE_TYPES _Mode)
{

   tInfoNodeForMode InfoBackUp;
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

   if((_First < MaxObjects) &&
      (_Second < MaxObjects) &&
      (_Mode < cVENTIL_MAX_MODE))
   {
      /*%C Sauvegarde de _First */
      InfoBackUp.Visible = InfoTablePtr[_First].InfoByMode[_Mode].Visible;
      InfoBackUp.Order = InfoTablePtr[_First].InfoByMode[_Mode].Order;

      /*%C Le _Second dans le _First */
      InfoTablePtr[_First].InfoByMode[_Mode].Visible = InfoTablePtr[_Second].InfoByMode[_Mode].Visible;
      InfoTablePtr[_First].InfoByMode[_Mode].Order = InfoTablePtr[_Second].InfoByMode[_Mode].Order;

      /*%C Le _First dans le _Second (via le BackUp)*/
      InfoTablePtr[_Second].InfoByMode[_Mode].Visible = InfoBackUp.Visible;
      InfoTablePtr[_Second].InfoByMode[_Mode].Order = InfoBackUp.Order;
   }
}
/************************************************************************/
/*%C Description   : Permute les configurations d'affichage de deux     */
/*%C objets pour tous les modes                                         */
/*%C Parametres en entree : 		                                       */
/*    - _First, _Second : Objets dont les configurations doivent être   */
/*                       permutées                                      */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void VFrame::SwitchDisplayConfigForAllModes(    e_OBJECT _First,
                                                e_OBJECT _Second)
{
   UWORD16 i;

   if((_First <MaxObjects) &&
      (_Second <MaxObjects))
   {
      for(i=0; i<cVENTIL_MAX_MODE; i++)
      {
         SwitchDisplayConfigForOneMode(_First,_Second, (e_MODE_TYPES)i);
      }
   }
}
/************************************************************************/
/*%C Description   : Reconstruit l'arbre des noeuds pour un mode donné  */
/*%C Parametres en entree : 		                                       */
/*		- Mode : mode pour lequel l'arbre doit être reconstruit           */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void VFrame::RebuildFrameTree(e_MODE_TYPES Mode)
{
   UWORD16 Cnt, Order, Spacing;
   e_BOOL IsVisible;
   tInfo* ptrInfo = InfoTablePtr;

   /* Première boucle pour connaître le nombre d'objets */
   Cnt = 0;
   ptrInfo = GetPtrFromOrder(0,Mode);
   do
   {
      Order = GetOrderFromPtr(ptrInfo, Mode);
      Cnt++;
      /*%C On passe au noeud suivant dans l'ordre*/
      ptrInfo = GetPtrFromOrder(++Order,Mode);

   } while (ptrInfo != NULL);

   /* Calcul de l'espacement entre les lignes */
   Spacing = (SpaceHeight / (Cnt+1));

   /* Deuxième parcours pour mise à jour des lignes */
   Cnt = 0;
   ptrInfo = GetPtrFromOrder(0,Mode);
   do
   {
      Order = GetOrderFromPtr(ptrInfo, Mode);

      /*%C On rend l'objet invisible pour éviter que SetLine() ne fasse appel
        à Show() */
      IsVisible = ptrInfo->pObject->IsVisible();
      ptrInfo->pObject->SetVisible(FALSE);

      /*%C Mise à jour de la ligne d'affichage */
      ptrInfo->pObject->SetLine(SpaceFirstLine + (Cnt+1)*Spacing);

      Cnt++;

      /*%C On restaure la visibilité pour cet objet */
      ptrInfo->pObject->SetVisible(IsVisible);

      /*%C On passe au noeud suivant dans l'ordre*/
      ptrInfo = GetPtrFromOrder(++Order,Mode);

   } while (ptrInfo != NULL);

}
/************************************************************************/
/* Description   : Cache les objets qui sont visibles dans ce mode      */
/* Parametres en entree :                                               */
/*		- Mode : mode pour lequel on doit faire l'opération               */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void VFrame::ObjectsHide(e_MODE_TYPES _Mode)
{
   UWORD16 i;

   if(GetImpactDisplay() && GetEndOfInit())
   {
      i = 0;
      while(InfoTablePtr[i].pObject)
      {
         if((InfoTablePtr[i].pObject != NULL)&&
            (InfoTablePtr[i].InfoByMode[_Mode].Visible))
            InfoTablePtr[i].pObject->Hide();

         i++;
      }
   }
}
/************************************************************************/
/* Description   : Affiche les objets qui sont visibles dans ce mode    */
/* Parametres en entree :                                               */
/*		- Mode : mode pour lequel on doit faire l'opération               */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void VFrame::ObjectsShow(e_MODE_TYPES _Mode)
{
   UWORD16 i;
   if(GetImpactDisplay() && GetEndOfInit())
   {
      i = 0;
      while(InfoTablePtr[i].pObject)
      {
         if((InfoTablePtr[i].pObject != NULL)&&
            (InfoTablePtr[i].InfoByMode[_Mode].Visible))
            InfoTablePtr[i].pObject->Show();
         i++;
      }
   }
}
/************************************************************************/
/* Description   : Cache l'objet s'il est visible dans ce mode          */
/* Parametres en entree :                                               */
/*		- _Mode : mode pour lequel on doit faire l'opération              */
/*		- _ObjectId : Objet à cacher                                      */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void VFrame::ObjectsHide(e_MODE_TYPES _Mode, e_OBJECT _ObjectId)
{
   if(GetImpactDisplay())
   {
      if(_ObjectId < MaxObjects)
      {
         if((InfoTablePtr[_ObjectId].pObject != NULL)&&
            (InfoTablePtr[_ObjectId].InfoByMode[_Mode].Visible))
            InfoTablePtr[_ObjectId].pObject->Hide();

      }
   }
}
/************************************************************************/
/* Description   : Affiche l'objet s'il est visible  dans ce mode       */
/* Parametres en entree :                                               */
/*		- Mode : mode pour lequel on doit faire l'opération               */
/*		- _ObjectId : Objet à afficher                                    */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void VFrame::ObjectsShow(e_MODE_TYPES _Mode, e_OBJECT _ObjectId)
{
   if(GetImpactDisplay())
   {
      if(_ObjectId < MaxObjects)
      {
         if((InfoTablePtr[_ObjectId].pObject != NULL)&&
            (InfoTablePtr[_ObjectId].InfoByMode[_Mode].Visible))
            InfoTablePtr[_ObjectId].pObject->Show();
      }
   }
}
/************************************************************************/
/* Description   : Enable/Disable le refresh des objets                 */
/* Parametres en entree :                                               */
/*		- _Enable : Flag d'enable/disable                                 */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void VFrame::ObjectsRefreshEnable(e_BOOL _Enable)
{
   UWORD16 i;
   if(GetImpactDisplay())
   {
      i = 0;
      while(InfoTablePtr[i].pObject)
      {
         if(InfoTablePtr[i].pObject != NULL)
            InfoTablePtr[i].pObject->RefreshEnable(_Enable);
         i++;
      }
   }
}

/************************************************************************/
/* Description   : Refresh du langage des objets                        */
/* Parametres en entree :                                               */
/*		- Mode : mode pour lequel on doit faire l'opération               */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void VFrame::ObjectsRefreshLanguage(e_MODE_TYPES _Mode)
{
   UWORD16 i;
   _Mode = _Mode;
   if(GetImpactDisplay())
   {
      i = 0;
      while(InfoTablePtr[i].pObject)
      {
         if(InfoTablePtr[i].pObject != NULL)
            InfoTablePtr[i].pObject->RefreshLanguage();
         i++;
      }
   }
}
/************************************************************************/
/* Description   : Stoppe le monitoring des objets                      */
/* Parametres en entree : Néant                                         */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void VFrame::ObjectsStopMonitoringMode(void)
{
   UWORD16 i;
   if(GetImpactDisplay())
   {
      i = 0;
      while(InfoTablePtr[i].pObject)
      {
         if(InfoTablePtr[i].pObject != NULL)
            InfoTablePtr[i].pObject->StopMonitoringMode();
         i++;
      }
   }
}
/************************************************************************/
/* Description   : Démarre le monitoring des objets                     */
/* Parametres en entree : Néant                                         */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void VFrame::ObjectsStartMonitoringMode(void)
{
   UWORD16 i;
   if(GetImpactDisplay())
   {
      i = 0;
      while(InfoTablePtr[i].pObject)
      {
         if(InfoTablePtr[i].pObject != NULL)
         {
            InfoVentil[i].pObject->StartMonitoringMode();
         }
         i++;
      }
}  }

