/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_TreeNode.hpp 	  							 		 			  	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration 							  		 							     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef TreeNodeH
#define TreeNodeH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_EventNode.h"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

const EventNode EventNode4000(1,
										&Controller::MoveUp,
										&Controller::MoveDown,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1);

const EventNode EventNode4010(1,
										&Controller::MoveUp,
										&Controller::MoveDown,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1);

const EventNode EventNode4020(1,
										&Controller::MoveUp,
										&Controller::MoveDown,
	                           &Controller::Action1,
	                           &Controller::Action1,
   	                        &Controller::Action1,
   	                        &Controller::Action1);

const EventNode EventNode4030(1,
										&Controller::MoveUp,
										&Controller::MoveDown,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1);

const EventNode EventNode4040(1,
										&Controller::MoveUp,
										&Controller::MoveDown,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1);

const EventNode EventNode4050(1,
										&Controller::MoveUp,
										&Controller::MoveDown,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1);

const EventNode EventNode4060(1,
										&Controller::MoveUp,
										&Controller::MoveDown,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1);

const EventNode EventNode4070(1,
										&Controller::MoveUp,
										&Controller::MoveDown,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1);

const EventNode EventNode4080(1,
										&Controller::MoveUp,
										&Controller::MoveDown,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1);

const EventNode EventNode4090(1,
										&Controller::MoveUp,
										&Controller::MoveDown,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1,
                            	&Controller::Action1);

#endif
