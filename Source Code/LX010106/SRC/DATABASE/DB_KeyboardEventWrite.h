/******************************************************************************/
/*									                                       	  */
/* N° du Projet	: 	RB0505     			     		                       	  */
/*                                                                			  */
/* Societe		: AIROX	                                        			  */
/* Adresse societe	: BP 833 - 64000 PAU	   		                          */
/* Telephone		: 05.59.14.02.02                         		      	  */
/* Email			: be@airox.fr    						                  */
/*----------------------------------------------------------------------------*/
/*                                                                 			  */
/* Nom du Fichier	: DB_KeyboardEvent.h   					                  */
/* Type			: Module	                                 		   	      */
/* Langage utilise	: Langage C pour micro controleur ST10 THOMSON       	  */
/*                                                           				  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/* 			Description fonctionnelle:		 	                        	  */
/*                                                                      	  */
/* Ecriture dans la base "KeyboardEvent"                                      */
/*          	                                                              */
/*                                                            				  */
/******************************************************************************/
/* Parametres en entree : aucun                 			                  */
/*                                                                    		  */
/* Parametres en sortie : aucun                              				  */
/******************************************************************************/


#ifndef DB_KEYBOARD_EVENT_WRITE_H
#define DB_KEYBOARD_EVENT_WRITE_H


void DB_KeyboardEventWrite(e_DB_KEYBOARD_EVENT_ID Id,
									UWORD16 Value);


#endif