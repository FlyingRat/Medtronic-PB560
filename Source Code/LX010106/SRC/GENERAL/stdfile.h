/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: stdfile.h   				   					               		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description : 	       													*/
/*%C		declaration of external standard function					*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None		       			                  	*/
/*%IO Input/Output Parameter :   None                                		  	*/
/*%O 	Output Parameter : 			None     	                				  		*/
/******************************************************************************/
#ifndef STDFILE_H
#define STDFILE_H
/******************************************************************************/

#ifndef _TASKING
extern int  sprintf   (char *buf, const char *fmt, ...);
extern int    abs  (int   val);
#else
extern	_USMLIB int    sprintf  ( char *, const char *, ... );
extern	_USMLIB	int                     abs      ( int );
#endif
#endif

