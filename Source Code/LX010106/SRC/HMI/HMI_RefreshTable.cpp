/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_RefreshTable.cpp 								 						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Gestion du refresh		 													 			  	*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_RefreshTable.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/



/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
RefreshTable::RefreshTable()
{
	ResetTable();
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void RefreshTable::SetTable(DisplayObject **_Table)
{
	if(TableRefresh[0] == NULL)
   {
		TableRefresh[0] = _Table;
		InitIndice(0,_Table);
	}
	else if(TableRefresh[1] == NULL)
   {
		TableRefresh[1] = _Table;
		InitIndice(1,_Table);
	}
}

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Action de refresh permanent																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																            		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void RefreshTable::MakeRefresh()
{
   static UWORD16 CounterXAlway = XAlway;

	if(CounterXAlway == 0)
   {
		RefreshRange(IndexEndExp0+1, IndexEndXAlway0, TableRefresh[0]);
		RefreshRange(IndexEndExp1+1, IndexEndXAlway1, TableRefresh[1]);
		CounterXAlway = XAlway;
	}
	else
   {
		CounterXAlway--;
	}
	
	RefreshRange(0, IndexEndAlway0, TableRefresh[0]);
	RefreshRange(0, IndexEndAlway1, TableRefresh[1]);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Action de refresh sur inspiration														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																            		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void RefreshTable::MakeRefreshInsp()
{
	RefreshRange(IndexEndAlway0+1, IndexEndInsp0, TableRefresh[0]);
	RefreshRange(IndexEndAlway1+1, IndexEndInsp1, TableRefresh[1]);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Action de refresh sur expiration														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																            		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void RefreshTable::MakeRefreshExp()
{
	RefreshRange(IndexEndInsp0+1, IndexEndExp0, TableRefresh[0]);
	RefreshRange(IndexEndInsp1+1, IndexEndExp1, TableRefresh[1]);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de la table de refresh														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																            		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void RefreshTable::ResetTable()
{
	TableRefresh[0] = NULL;
	TableRefresh[1] = NULL;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C determine les element de refresh permanent	de refresh sur		  				*/
/*%C  inspiration et sur expiration											  				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																            		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void RefreshTable::InitIndice(UWORD16 _IdTable, DisplayObject **_TableRefresh)
{
	UWORD16 Alway, Insp, Exp, Xalway;
	if(_TableRefresh != NULL)
   {
		UWORD16 i = 0;
		while(_TableRefresh[i] != NULL)
      {
			i++;
		}
		Alway = i;
		i++;
		while(_TableRefresh[i] != NULL)
      {
			i++;
		}
		Insp = i;
		i++;
		while(_TableRefresh[i] != NULL)
      {
			i++;
		}
		Exp = i;
		i++;
		while(_TableRefresh[i] != NULL)
      {
			i++;
		}
		Xalway = i;

		if(_IdTable == 0)
      {
			IndexEndAlway0 = Alway;
			IndexEndInsp0 = Insp;
			IndexEndExp0 = Exp;
			IndexEndXAlway0 = Xalway;
		}
		else
      {
			IndexEndAlway1 = Alway;
			IndexEndInsp1 = Insp;
			IndexEndExp1 = Exp;
			IndexEndXAlway1 = Xalway;
		}
	}
	else
   {
		if(_IdTable == 0)
      {
			IndexEndAlway0 = 0;
			IndexEndInsp0 = 0;
			IndexEndExp0 = 0;
			IndexEndXAlway0 = 0;
		}
		else
      {
			IndexEndAlway1 = 0;
			IndexEndInsp1 = 0;
			IndexEndExp1 = 0;
			IndexEndXAlway1 = 0;
		}
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Permet le refresh entre 2 indice d'une table						  				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Begin	   : Indice de debut	                                    		*/
/*%I		End	   : Indice de fin			                                 	*/
/*%I	   Table    : tableau pour le refresh											  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void RefreshTable::RefreshRange( UWORD16 _Begin,
                                 UWORD16 _End,
                                 DisplayObject **_Table)
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

	if(_Table != NULL)
   {
		for(int i = _Begin; i<_End; i++)
      {
			if(_Table[i]->IsVisible() && _Table[i]->IsRefreshObject())
         {
				_Table[i]->Refresh();
			}
		}
	}
}

