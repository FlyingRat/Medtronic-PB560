/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : KEY_Touch_Detection.h                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Key press detection                                            */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : Touch                                                  */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : Result                                                */
/******************************************************************************/


/******************************************************************************/
/*                              INCLUDE FILES		                          */
/******************************************************************************/


#ifndef KEY_TOUCH_DETECTION_H
#define KEY_TOUCH_DETECTION_H

/******************************************************************************/
/*                          STRUCTURE DECLARATION     	             	      */
/******************************************************************************/
// Structure de la matrice
typedef struct
{
	UWORD16 Colum;
	UWORD16 Line;
} t_SYS_Matrice;


#ifdef DECLARATION_KEY_TOUCH_DETECTION

/******************************************************************************/
/*                      EXTERNAL CONSTANT DECLARATION                     	  */
/******************************************************************************/

/*%C Clavier Seritech */
//const t_SYS_Matrice SYS_KeyboardMatrice[Number_of_key - Mark_Begin_Simple_Touch - 1]
//= {
//   /* respect the order of the enum "e_SYS_KeyboardInput" */
//   
//   /* KEY_CODE_UP */
//   {COM2, 	TOUCHE_1}, 	 	
//   
//   /* KEY_CODE_DOWN */
//   {COM3, 	TOUCHE_1}, 	 	
//   
//   /* KEY_CODE_VALID  */
//   {COM1, 	TOUCHE_2}, 
//   
//   /* KEY_CODE_MONIT (un-matrixes key -> 0xFFFF sur COMx  )	 	*/
//   {0xFFFF,	TOUCHE_INHIB},	
//   
//   /* KEY_CODE_STARTSTOPVENTIL */
//   {COM2, 	TOUCHE_2},
//   
//   /* KEY_CODE_100_02 */
//   {COM3,	TOUCHE_2}, 	 	
//   
//   /* KEY_CODE_NAVIG */
//   {COM1, 	TOUCHE_1}
//    }; 


/*%C Clavier Graphic Art */ 
const t_SYS_Matrice SYS_KeyboardMatrice[Number_of_key - Mark_Begin_Simple_Touch - 1]
= {
   /* respect the order of the enum "e_SYS_KeyboardInput" */

   /* KEY_CODE_UP */
   {COM3, TOUCHE_2}, 	 	

   /* KEY_CODE_DOWN */
   {COM1, TOUCHE_1}, 	 	
   
   /* KEY_CODE_VALID */
   {COM2, TOUCHE_1}, 

   /* KEY_CODE_MONIT (un-matrixes key -> 0xFFFF sur COMx  )	*/ 	
   {0xFFFF,	TOUCHE_INHIB},

   /* KEY_CODE_STARTSTOPVENTIL */
   {COM2, TOUCHE_2},

	/*KEY_CODE_100_02 */
	{COM1, TOUCHE_2},
   
   /* KEY_CODE_NAVIG */
   {COM3, TOUCHE_1}
    }; 
#else

/******************************************************************************/
/*                      EXTERNAL CONSTANT DECLARATION                     	  */
/******************************************************************************/
extern const t_SYS_Matrice SYS_KeyboardMatrice[]; 


#endif
#endif
