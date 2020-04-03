/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Config.cpp											 						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Classe de configuration de l'IHM     								 			  	*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_Config.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/

/* Contrôle du produit compilé */
#ifdef HMI_CONFIG_M2
#elif defined HMI_CONFIG_XL2
#elif defined HMI_CONFIG_S2
#else
   #error Il faut définir un produit valide dans HMI_Config.hpp
#endif

/******************************************************************************/
/*                           Configuration des Noeuds                	   	*/
/******************************************************************************/

/* IMPORTANT : la configuration des noeuds (Ventil et Alarme) se trouve dans le
   fichier HMI_GlobalEventNode.cpp et est contrôlée par les mêmes directives
   que ci-dessus. */

/******************************************************************************/
/*                           Configuration de FrameVentil             	   	*/
/******************************************************************************/
tInfo InfoVentil[OBJECT_VENTIL_OBJECT_MAX+1];
tInfo InfoAlarm[OBJECT_ALARM_OBJECT_MAX+1];
tInfo InfoGraph[OBJECT_GRAPH_OBJECT_MAX+1];

#ifdef HMI_CONFIG_M2

const tInfo cInfoVentil[OBJECT_VENTIL_OBJECT_MAX+1] =
{
			  /*C% les modes :  V(A)C, VP(A)C, PSV, VSIMV,PSIMV, CPAP */
						   /* adresse, {Visible, Order} x (nb_mode - 1) */
						   {NULL,{{1,0},{0,0},{0,0},{1,0},{0,0},{0,0}}},   //LOVPip
						   {NULL,{{0,0},{1,0},{1,0},{0,0},{1,0},{1,0}}},   //LOVVti
						   {NULL,{{1,1},{1,1},{1,1},{1,1},{1,1},{1,1}}},   //LOVVte
						   {NULL,{{1,5},{1,2},{1,2},{1,5},{1,2},{1,2}}},   //LOVVm
						   {NULL,{{1,2},{1,3},{1,3},{1,2},{1,3},{1,3}}},   //LOVR
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVFuite
						   {NULL,{{1,4},{1,5},{1,5},{1,4},{1,5},{1,5}}},   //LOVFIO2
		 #ifdef HMI_CONFIG_SPO2
						   {NULL,{{1,6},{1,6},{1,6},{1,6},{1,6},{1,6}}},   //LOVSPO2
		 #else
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVSPO2
		 #endif
						   {NULL,{{1,3},{1,4},{1,4},{1,3},{1,4},{1,4}}},   //LTVIE
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVIT
/* Toujours terminer -> */ {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}}
/* par cette ligne et renseigner InitInfoVentilTable en accord !*/
};

#elif defined HMI_CONFIG_XL2

const tInfo cInfoVentil[OBJECT_VENTIL_OBJECT_MAX+1] =
{
			  /*C% les modes :  V(A)C, VP(A)C, PSV, VSIMV,PSIMV, CPAP */
						   /* adresse, {Visible, Order} x (nb_mode - 1) */
						   {NULL,{{1,0},{0,0},{0,0},{1,0},{0,0},{0,0}}},   //LOVPip
						   {NULL,{{0,0},{1,0},{1,0},{0,0},{1,0},{1,0}}},   //LOVVti
						   {NULL,{{1,1},{1,1},{1,1},{1,1},{1,1},{1,1}}},   //LOVVte
						   {NULL,{{1,5},{1,2},{1,2},{1,5},{1,2},{1,2}}},   //LOVVm
						   {NULL,{{1,2},{1,3},{1,3},{1,2},{1,3},{1,3}}},   //LOVR
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVFuite
						   {NULL,{{1,4},{1,5},{1,5},{1,4},{1,5},{1,5}}},   //LOVFIO2
		 #ifdef HMI_CONFIG_SPO2
						   {NULL,{{1,6},{1,6},{1,6},{1,6},{1,6},{1,6}}},   //LOVSPO2
		 #else
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVSPO2
		 #endif
						   {NULL,{{1,3},{1,4},{1,4},{1,3},{1,4},{1,4}}},   //LTVIE
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVIT
/* Toujours terminer -> */ {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}}
/* par cette ligne et renseigner InitInfoVentilTable en accord !*/
};

#elif defined HMI_CONFIG_S2

const tInfo cInfoVentil[OBJECT_VENTIL_OBJECT_MAX+1] =
{
			  /*C% les modes :  V(A)C, VP(A)C, PSV, VSIMV,PSIMV, CPAP */
						   /* adresse, {Visible, Order} x (nb_mode - 1) */
						   {NULL,{{1,0},{0,0},{0,0},{1,0},{0,0},{0,0}}},   //LOVPip
						   {NULL,{{0,0},{1,0},{1,0},{0,0},{1,0},{1,0}}},   //LOVVti
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVVte
						   {NULL,{{0,0},{1,2},{1,2},{0,0},{1,2},{1,2}}},   //LOVVm
						   {NULL,{{1,2},{1,3},{1,3},{1,2},{1,3},{1,3}}},   //LOVR
						   {NULL,{{1,1},{1,1},{1,1},{1,1},{1,1},{1,1}}},   //LOVFuite
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVFIO2
		 #ifdef HMI_CONFIG_SPO2
						   {NULL,{{1,4},{1,5},{1,5},{1,4},{1,5},{1,5}}},   //LOVSPO2
		 #else
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVSPO2
		 #endif
						   {NULL,{{1,3},{1,4},{1,4},{1,3},{1,4},{1,4}}},   //LTVIE
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVIT
/* Toujours terminer -> */ {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}}
/* par cette ligne et renseigner InitInfoVentilTable en accord !*/
};
#endif

/******************************************************************************/
/*                           Configuration de FrameAlarm               	   	*/
/******************************************************************************/
#ifdef HMI_CONFIG_M2

const tInfo cInfoAlarm[OBJECT_ALARM_OBJECT_MAX+1] =
{
			  /*C% les modes :  V(A)C, VP(A)C, PSV, VSIMV, PSIMV, CPAP */
						   /* adresse, {Visible, Order} x (nb_mode - 1) */
						   {NULL,{{0,0},{1,0},{1,0},{0,0},{1,0},{0,0}}},   //LOVPip
						   {NULL,{{1,0},{0,0},{0,0},{1,0},{0,0},{0,0}}},   //LOVVti
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVMap
						   {NULL,{{1,1},{1,1},{1,1},{1,1},{1,1},{1,0}}},   //LOVPeep
						   {NULL,{{1,3},{1,3},{1,3},{1,3},{1,3},{1,2}}},   //LTVIE
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVIT
		 #ifdef HMI_CONFIG_SPO2
						   {NULL,{{1,4},{1,4},{1,4},{1,4},{1,4},{1,3}}},   //LOVR
		 #else
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVR
		 #endif
						   {NULL,{{1,2},{1,2},{1,2},{1,2},{1,2},{1,1}}},   //LOVM
/* Toujours terminer -> */ {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}}
/* par cette ligne et renseigner InitInfoAlarmTable en accord !*/
};

#elif defined HMI_CONFIG_XL2

const tInfo cInfoAlarm[OBJECT_ALARM_OBJECT_MAX+1] =
{
			  /*C% les modes :  V(A)C, VP(A)C, PSV, VSIMV, PSIMV, CPAP */
						   /* adresse, {Visible, Order} x (nb_mode - 1) */
						   {NULL,{{0,0},{1,0},{1,0},{0,0},{1,0},{0,0}}},   //LOVPip
						   {NULL,{{1,0},{0,0},{0,0},{1,0},{0,0},{0,0}}},   //LOVVti
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVMap
						   {NULL,{{1,1},{1,1},{1,1},{1,1},{1,1},{1,0}}},   //LOVPeep
						   {NULL,{{1,3},{1,3},{1,3},{1,3},{1,3},{1,2}}},   //LTVIE
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVIT
		 #ifdef HMI_CONFIG_SPO2
						   {NULL,{{1,4},{1,4},{1,4},{1,4},{1,4},{1,3}}},   //LOVR
		 #else
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVR
		 #endif
						   {NULL,{{1,2},{1,2},{1,2},{1,2},{1,2},{1,1}}},   //LOVM
/* Toujours terminer -> */ {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}}
/* par cette ligne et renseigner InitInfoAlarmTable en accord !*/
};

#elif defined HMI_CONFIG_S2

const tInfo cInfoAlarm[OBJECT_ALARM_OBJECT_MAX+1] =
{
			  /*C% les modes :  V(A)C, VP(A)C, PSV, VSIMV, PSIMV, CPAP */
						   /* adresse, {Visible, Order} x (nb_mode - 1) */
						   {NULL,{{0,0},{1,0},{1,0},{0,0},{1,0},{0,0}}},   //LOVPip
						   {NULL,{{1,0},{0,0},{0,0},{1,0},{0,0},{0,0}}},   //LOVVti
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVMap
						   {NULL,{{1,1},{1,1},{1,1},{1,1},{1,1},{1,0}}},   //LOVPeep
						   {NULL,{{1,3},{1,3},{1,3},{1,3},{1,3},{1,2}}},   //LTVIE
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVIT
		 #ifdef HMI_CONFIG_SPO2
						   {NULL,{{1,4},{1,4},{1,4},{1,4},{1,4},{1,3}}},   //LOVR
		 #else
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //LOVR
		 #endif
						   {NULL,{{1,2},{1,2},{1,2},{1,2},{1,2},{1,1}}},   //LOVM
/* Toujours terminer -> */ {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}}
/* par cette ligne et renseigner InitInfoAlarmTable en accord !*/
};

#endif

/******************************************************************************/
/*                           Configuration de FrameGraph               	   	*/
/******************************************************************************/
#ifdef HMI_CONFIG_M2

const tInfo cInfoGraph[OBJECT_GRAPH_OBJECT_MAX+1] =
{
			  /*C% les modes :  V(A)C, VP(A)C, PSV, VSIMV, PSIMV, CPAP */
						   /* adresse, {Visible, Order} x (nb_mode - 1) */
						   {NULL,{{1,0},{1,0},{1,0},{1,0},{1,0},{1,0}}},   //MoFiO2
		 #ifdef HMI_CONFIG_SPO2
						   {NULL,{{1,1},{1,1},{1,1},{1,1},{1,1},{1,1}}},   //MoSpO2
						   {NULL,{{1,2},{1,2},{1,2},{1,2},{1,2},{1,2}}},   //MoPulse
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoTi
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoTe
						   {NULL,{{1,3},{1,3},{1,3},{1,3},{1,3},{1,3}}},   //MoIE
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoIT
						   {NULL,{{1,4},{1,4},{1,4},{1,4},{1,4},{1,4}}},   //MoFR
						   {NULL,{{1,5},{1,5},{1,5},{1,5},{1,5},{1,5}}},   //MoVmi
						   {NULL,{{1,6},{1,6},{1,6},{1,6},{1,6},{1,6}}},   //MoVTE
						   {NULL,{{1,7},{1,7},{1,7},{1,7},{1,7},{1,7}}},   //MoVTI
						   {NULL,{{1,8},{1,8},{1,8},{1,8},{1,8},{1,8}}},   //MoPE
						   {NULL,{{1,9},{1,9},{1,9},{1,9},{1,9},{0,0}}},   //MoPI
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoFuite
		 #else
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoSpO2
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoPulse
						   {NULL,{{1,1},{1,1},{1,1},{1,1},{1,1},{1,1}}},   //MoTi
						   {NULL,{{1,2},{1,2},{1,2},{1,2},{1,2},{1,2}}},   //MoTe
						   {NULL,{{1,3},{1,3},{1,3},{1,3},{1,3},{1,3}}},   //MoIE
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoIT
						   {NULL,{{1,4},{1,4},{1,4},{1,4},{1,4},{1,4}}},   //MoFR
						   {NULL,{{1,7},{1,7},{1,7},{1,7},{1,7},{1,7}}},   //MoVmi
						   {NULL,{{1,5},{1,5},{1,5},{1,5},{1,5},{1,5}}},   //MoVTE
						   {NULL,{{1,6},{1,6},{1,6},{1,6},{1,6},{1,6}}},   //MoVTI
						   {NULL,{{1,8},{1,8},{1,8},{1,8},{1,8},{1,8}}},   //MoPE
						   {NULL,{{1,9},{1,9},{1,9},{1,9},{1,9},{0,0}}},   //MoPI
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoFuite
		 #endif
/* Toujours terminer -> */ {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}}
/* par cette ligne et renseigner InitInfoGraphTable en accord !*/
};

#elif defined HMI_CONFIG_XL2

const tInfo cInfoGraph[OBJECT_GRAPH_OBJECT_MAX+1] =
{
			  /*C% les modes :  V(A)C, VP(A)C, PSV, VSIMV, CPAP */
						   /* adresse, {Visible, Order} x (nb_mode - 1) */
						   {NULL,{{1,0},{1,0},{1,0},{1,0},{1,0},{1,0}}},   //MoFiO2
		 #ifdef HMI_CONFIG_SPO2
						   {NULL,{{1,1},{1,1},{1,1},{1,1},{1,1},{1,1}}},   //MoSpO2
						   {NULL,{{1,2},{1,2},{1,2},{1,2},{1,2},{1,2}}},   //MoPulse
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoTi
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoTe
						   {NULL,{{1,3},{1,3},{1,3},{1,3},{1,3},{1,3}}},   //MoIE
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoIT
						   {NULL,{{1,4},{1,4},{1,4},{1,4},{1,4},{1,4}}},   //MoFR
						   {NULL,{{1,5},{1,5},{1,5},{1,5},{1,5},{1,5}}},   //MoVmi
						   {NULL,{{1,6},{1,6},{1,6},{1,6},{1,6},{1,6}}},   //MoVTE
						   {NULL,{{1,7},{1,7},{1,7},{1,7},{1,7},{1,7}}},   //MoVTI
						   {NULL,{{1,8},{1,8},{1,8},{1,8},{1,8},{1,8}}},   //MoPE
						   {NULL,{{1,9},{1,9},{1,9},{1,9},{0,0},{0,0}}},   //MoPI
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoFuite
		 #else
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoSpO2
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoPulse
						   {NULL,{{1,1},{1,1},{1,1},{1,1},{1,1},{1,1}}},   //MoTi
						   {NULL,{{1,2},{1,2},{1,2},{1,2},{1,2},{1,2}}},   //MoTe
						   {NULL,{{1,3},{1,3},{1,3},{1,3},{1,3},{1,3}}},   //MoIE
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoIT
						   {NULL,{{1,4},{1,4},{1,4},{1,4},{1,4},{1,4}}},   //MoFR
						   {NULL,{{1,7},{1,7},{1,7},{1,7},{1,7},{1,7}}},   //MoVmi
						   {NULL,{{1,5},{1,5},{1,5},{1,5},{1,5},{1,5}}},   //MoVTE
						   {NULL,{{1,6},{1,6},{1,6},{1,6},{1,6},{1,6}}},   //MoVTI
						   {NULL,{{1,8},{1,8},{1,8},{1,8},{1,8},{1,8}}},   //MoPE
						   {NULL,{{1,9},{1,9},{1,9},{1,9},{1,9},{0,0}}},   //MoPI
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoFuite
		 #endif
/* Toujours terminer -> */ {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}}
/* par cette ligne et renseigner InitInfoGraphTable en accord !*/
};


#elif defined HMI_CONFIG_S2

const tInfo cInfoGraph[OBJECT_GRAPH_OBJECT_MAX+1] =
{
			  /*C% les modes :  V(A)C, VP(A)C, PSV, VSIMV, CPAP */
						   /* adresse, {Visible, Order} x (nb_mode - 1) */
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoFiO2
		 #ifdef HMI_CONFIG_SPO2
						   {NULL,{{1,0},{1,0},{1,0},{1,0},{1,0},{1,0}}},   //MoSpO2
						   {NULL,{{1,1},{1,1},{1,1},{1,1},{1,1},{1,1}}},   //MoPulse
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoTi
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoTe
						   {NULL,{{1,2},{1,2},{1,2},{1,2},{1,2},{1,2}}},   //MoIE
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoIT
						   {NULL,{{1,3},{1,3},{1,3},{1,3},{1,3},{1,3}}},   //MoFR
						   {NULL,{{1,4},{1,4},{1,4},{1,4},{1,4},{1,4}}},   //MoVmi
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoVTE
						   {NULL,{{1,6},{1,6},{1,6},{1,6},{1,6},{1,6}}},   //MoVTI
						   {NULL,{{1,7},{1,7},{1,7},{1,7},{1,7},{1,7}}},   //MoPE
						   {NULL,{{1,8},{1,8},{1,8},{1,8},{1,8},{0,0}}},   //MoPI
						   {NULL,{{1,5},{1,5},{1,5},{1,5},{1,5},{1,5}}},   //MoFuite
		 #else
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoSpO2
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoPulse
						   {NULL,{{1,0},{1,0},{1,0},{1,0},{1,0},{1,0}}},   //MoTi
						   {NULL,{{1,1},{1,1},{1,1},{1,1},{1,1},{1,1}}},   //MoTe
						   {NULL,{{1,2},{1,2},{1,2},{1,2},{1,2},{1,2}}},   //MoIE
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoIT
						   {NULL,{{1,3},{1,3},{1,3},{1,3},{1,3},{1,3}}},   //MoFR
						   {NULL,{{1,4},{1,4},{1,4},{1,4},{1,4},{1,4}}},   //MoVmi
						   {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}},   //MoVTE
						   {NULL,{{1,6},{1,6},{1,6},{1,6},{1,6},{1,6}}},   //MoVTI
						   {NULL,{{1,7},{1,7},{1,7},{1,7},{1,7},{1,7}}},   //MoPE
						   {NULL,{{1,8},{1,8},{1,8},{1,8},{1,8},{0,0}}},   //MoPI
						   {NULL,{{1,5},{1,5},{1,5},{1,5},{1,5},{1,5}}},   //MoFuite
		 #endif
/* Toujours terminer -> */ {NULL,{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}}
/* par cette ligne et renseigner InitInfoGraphTable en accord !*/
};


#endif

