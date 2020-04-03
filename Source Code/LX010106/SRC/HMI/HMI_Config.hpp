/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Config.hpp	 								 		 			  	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_Config.cpp 				 						     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef ConfigH
#define ConfigH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

extern "C"
{
#include "typedef.h"
#include "enum.h"
}
#include "HMI_LabelOneValue.hpp"
#include "HMI_MonitoringObject.hpp"

/* Choix du produit à compiler dans le fichier header suivant */
#include "HMI_Product.hpp"
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#ifdef CONFIG_USB
	#define HMI_CONFIG_USB
#endif

#ifdef HMI_CONFIG_M2

   /* Affichage des courbes */ 
   #define HMI_CONFIG_CURVES 
   //#define HMI_CONFIG_NO_CURVES
   
   /* Affichage de menu de configuration des courbes */
   #define HMI_CONFIG_CURVE_CFG
   //#define HMI_CONFIG_NO_CURVE_CFG

   /* Format des champs "temps" */
   #define HMI_CONFIG_TIME_24H_FORMAT
   //#define HMI_CONFIG_TIME_12H_FORMAT

   /* Format des champs "date" */
   //#define HMI_CONFIG_DATE_US_FORMAT
   #define HMI_CONFIG_DATE_EUR_FORMAT

   /* Gestion du SPO2 */
   //#define HMI_CONFIG_SPO2
   #define HMI_CONFIG_NO_SPO2

   /* Gestion du 100% FiO2 */
   #define HMI_CONFIG_100_FIO2
   //#define HMI_CONFIG_NO_100_FIO2

   /* Gestion des points de progression de la fenetre USB */
   //#define HMI_CONFIG_USB_PROCESSING
   #define HMI_CONFIG_NO_USB_PROCESSING

   /* Gestion des transferts de réglages */
   //#define HMI_CONFIG_USB_SETTINGS_TRANSFER
   #define HMI_CONFIG_NO_USB_SETTINGS_TRANSFER

   /* Gestion du transfert monitoring */
   #define HMI_CONFIG_USB_MONIT_TRANSFER
   //#define HMI_CONFIG_NO_USB_MONIT_TRANSFER

   /* Gestion du transfert events */
   //#define HMI_CONFIG_USB_EVENTS_TRANSFER
   #define HMI_CONFIG_NO_EVENTS_MONIT_TRANSFER

   /* Affichage des sigma dans le rapport de ventilation */
   //#define HMI_CONFIG_TREND_SIGMA
   #define HMI_CONFIG_NO_TREND_SIGMA

   /* Affichage tronqué du I/E : on affiche 1:2.0 ald 1.0:2.0 */
   #define HMI_CONFIG_TRUNCATED_I_E
   //#define HMI_CONFIG_NO_TRUNCATED_I_E

   /* Affichage du Vte  dans le Rapport de ventilation */
   #define HMI_CONFIG_TREND_VTE
   //#define HMI_CONFIG_NO_TREND_VTE

#elif defined HMI_CONFIG_XL2

   /* Affichage des courbes */ 
   #define HMI_CONFIG_CURVES 
   //#define HMI_CONFIG_NO_CURVES
   
   /* Affichage de menu de configuration des courbes */
   //#define HMI_CONFIG_CURVE_CFG
   #define HMI_CONFIG_NO_CURVE_CFG

   /* Format des champs "temps" */
   #define HMI_CONFIG_TIME_24H_FORMAT
   //#define HMI_CONFIG_TIME_12H_FORMAT

   /* Format des champs "date" */
   //#define HMI_CONFIG_DATE_US_FORMAT
   #define HMI_CONFIG_DATE_EUR_FORMAT

   /* Gestion du SPO2 */
   //#define HMI_CONFIG_SPO2
   #define HMI_CONFIG_NO_SPO2

   /* Gestion du 100% FiO2 */
   //#define HMI_CONFIG_100_FIO2
   #define HMI_CONFIG_NO_100_FIO2

   /* Gestion des points de progression de la fenetre USB */
   //#define HMI_CONFIG_USB_PROCESSING
   #define HMI_CONFIG_NO_USB_PROCESSING

   /* Gestion des transferts de réglages */
   //#define HMI_CONFIG_USB_SETTINGS_TRANSFER
   #define HMI_CONFIG_NO_USB_SETTINGS_TRANSFER

   /* Gestion du transfert monitoring */
   #define HMI_CONFIG_USB_MONIT_TRANSFER
   //#define HMI_CONFIG_NO_USB_MONIT_TRANSFER

   /* Gestion du transfert events */
   //#define HMI_CONFIG_USB_EVENTS_TRANSFER
   #define HMI_CONFIG_NO_EVENTS_MONIT_TRANSFER

   /* Affichage des sigma dans le rapport de ventilation */
   //#define HMI_CONFIG_TREND_SIGMA
   #define HMI_CONFIG_NO_TREND_SIGMA

   /* Affichage tronqué du I/E : on affiche 1:2.0 ald 1.0:2.0 */
   #define HMI_CONFIG_TRUNCATED_I_E
   //#define HMI_CONFIG_NO_TRUNCATED_I_E

   /* Affichage du Vte  dans le Rapport de ventilation */
   #define HMI_CONFIG_TREND_VTE
   //#define HMI_CONFIG_NO_TREND_VTE

#elif defined HMI_CONFIG_S2

   /* Affichage des courbes */ 
   //#define HMI_CONFIG_CURVES 
   #define HMI_CONFIG_NO_CURVES
   
   /* Affichage de menu de configuration des courbes */
   //#define HMI_CONFIG_CURVE_CFG
   #define HMI_CONFIG_NO_CURVE_CFG

   /* Format des champs "temps" */
   #define HMI_CONFIG_TIME_24H_FORMAT
   //#define HMI_CONFIG_TIME_12H_FORMAT

   /* Format des champs "date" */
   //#define HMI_CONFIG_DATE_US_FORMAT
   #define HMI_CONFIG_DATE_EUR_FORMAT

   /* Gestion du SPO2 */
   //#define HMI_CONFIG_SPO2
   #define HMI_CONFIG_NO_SPO2

   /* Gestion du 100% FiO2 */
   //#define HMI_CONFIG_100_FIO2
   #define HMI_CONFIG_NO_100_FIO2

   /* Gestion des points de progression de la fenetre USB */
   //#define HMI_CONFIG_USB_PROCESSING
   #define HMI_CONFIG_NO_USB_PROCESSING

   /* Gestion des transferts de réglages */
   //#define HMI_CONFIG_USB_SETTINGS_TRANSFER
   #define HMI_CONFIG_NO_USB_SETTINGS_TRANSFER

   /* Gestion du transfert monitoring */
   #define HMI_CONFIG_USB_MONIT_TRANSFER
   //#define HMI_CONFIG_NO_USB_MONIT_TRANSFER

   /* Gestion du transfert events */
   //#define HMI_CONFIG_USB_EVENTS_TRANSFER
   #define HMI_CONFIG_NO_EVENTS_MONIT_TRANSFER

   /* Affichage des sigma dans le rapport de ventilation */
   //#define HMI_CONFIG_TREND_SIGMA
   #define HMI_CONFIG_NO_TREND_SIGMA

   /* Affichage tronqué du I/E : on affiche 1:2.0 ald 1.0:2.0 */
   #define HMI_CONFIG_TRUNCATED_I_E
   //#define HMI_CONFIG_NO_TRUNCATED_I_E

   /* Affichage du Vte  dans le Rapport de ventilation */
   //#define HMI_CONFIG_TREND_VTE
   #define HMI_CONFIG_NO_TREND_VTE

#else
   #error Il faut définir un produit valide dans HMI_Product.hpp !
#endif

typedef struct {
   UWORD16 Visible;
   UWORD16 Order;
} tInfoNodeForMode;

/******************************************************************************/
/*                           Configuration des Noeuds                  	   	*/
/*                               Ventil et Alarme                           	*/
/******************************************************************************/


/******************************************************************************/
/*                           Configuration de FrameVentil              	   	*/
/******************************************************************************/

#define cVENTIL_MAX_MODE  (nb_of_mode)
#define cALARM_MAX_MODE   (nb_of_mode)
#define cGRAPH_MAX_MODE   (nb_of_mode)

typedef struct {
   DisplayObject* pObject;
   tInfoNodeForMode InfoByMode[cVENTIL_MAX_MODE];
} tInfo;

typedef enum {
   OBJECT_VENTIL_LOVPIP = 0,
   OBJECT_VENTIL_LOVVTI,
   OBJECT_VENTIL_LOVVTE,
   OBJECT_VENTIL_LOVVM,
   OBJECT_VENTIL_LOVR,
   OBJECT_VENTIL_LOVFUITE,
   OBJECT_VENTIL_LOVFIO2,
   OBJECT_VENTIL_LOVSPO2,
   OBJECT_VENTIL_LTVIE,
   OBJECT_VENTIL_LTVIT,
   OBJECT_VENTIL_OBJECT_MAX,
   OBJECT_ALARM_LOVPIP = 0,
   OBJECT_ALARM_LOVVTI,
   OBJECT_ALARM_LOVMAP,
   OBJECT_ALARM_LOVPEEP,
   OBJECT_ALARM_LTVIE,
   OBJECT_ALARM_LOVIT,
   OBJECT_ALARM_LOVR,
   OBJECT_ALARM_LOVM,
   OBJECT_ALARM_OBJECT_MAX,
   OBJECT_GRAPH_MOFIO2 = 0,
   OBJECT_GRAPH_MOSPO2,
   OBJECT_GRAPH_MOPULSE,
   OBJECT_GRAPH_MOTI,
   OBJECT_GRAPH_MOTE,
   OBJECT_GRAPH_MOIE,
   OBJECT_GRAPH_MOIT,
   OBJECT_GRAPH_MOFR,
   OBJECT_GRAPH_MOVM,
   OBJECT_GRAPH_MOVTE,
   OBJECT_GRAPH_MOVTI,
   OBJECT_GRAPH_MOPE,
   OBJECT_GRAPH_MOPI,
   OBJECT_GRAPH_MOFUITE,
   OBJECT_GRAPH_OBJECT_MAX
} e_OBJECT;


extern tInfo InfoVentil[OBJECT_VENTIL_OBJECT_MAX+1];
extern const tInfo cInfoVentil[OBJECT_VENTIL_OBJECT_MAX+1];

/******************************************************************************/
/*                           Configuration de FrameAlarm               	   	*/
/******************************************************************************/

#define cALARM_MAX_MODE  (nb_of_mode)

extern tInfo InfoAlarm[OBJECT_ALARM_OBJECT_MAX+1];
extern const tInfo cInfoAlarm[OBJECT_ALARM_OBJECT_MAX+1];

/******************************************************************************/
/*                           Configuration de FrameGraph               	   	*/
/******************************************************************************/

#define cGRAPH_MAX_MODE  (nb_of_mode)

extern tInfo InfoGraph[OBJECT_GRAPH_OBJECT_MAX+1];
extern const tInfo cInfoGraph[OBJECT_GRAPH_OBJECT_MAX+1];


#endif //#ifndef ConfigH
