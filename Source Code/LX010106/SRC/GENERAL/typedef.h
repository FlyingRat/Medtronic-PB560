/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: typedef.h	   				   					               		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description : 	Type redéfinition      								*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None		       			                  	*/
/*%IO Input/Output Parameter :   None                                		  	*/
/*%O 	Output Parameter : 			None     	                				  		*/
/******************************************************************************/
#ifndef TYPEDEF_H
#define TYPEDEF_H
/******************************************************************************/

#ifndef  _BORLAND
#if 0
typedef enum {
        FALSE = 0,
        TRUE
        } e_BOOL;
#else
typedef int e_BOOL;
#define FALSE 0
#define TRUE 1
#endif // #if 0
#else
#define FALSE 0
#define TRUE 1
#define huge
#define xhuge
typedef int  e_BOOL;
#endif


// RAM interne
#ifndef  _BORLAND 
typedef unsigned int         	BIT;
typedef unsigned char idata 	UBYTE_I;
typedef unsigned int  idata 	UWORD16_I;
typedef unsigned long idata  	UWORD32_I;
typedef   signed char idata 	SBYTE_I;
typedef   signed int  idata	    SWORD16_I;
typedef   signed long idata 	SWORD32_I;
typedef   		 float idata	FLOAT32_I;	   
#else
typedef char                	BIT;
#define idata
#endif

#ifndef  _BORLAND
// RAM extension
typedef unsigned char  	UBYTE;
typedef unsigned int		UWORD16;
typedef unsigned long  	UWORD32;
typedef   signed char  	SBYTE;
typedef   signed int 	SWORD16;
typedef   signed long  	SWORD32;
typedef   		 float 	FLOAT32;
#else
typedef unsigned char  	UBYTE;
typedef unsigned short  UWORD16;
typedef unsigned long  	UWORD32;
typedef   signed char  	SBYTE;
typedef   signed short 	SWORD16;
typedef   signed long  	SWORD32;
typedef   		 float 	FLOAT32;

#define sdata
#define xnear
#define near
#define shuge
#define xhuge
#endif


#ifndef  _BORLAND
	#ifndef _TASKING
		#ifndef NULL
	 		#ifdef __cplusplus              // EC++
	   		#define NULL   0
	 		#else
	   		#define NULL ((void *) 0)
	 		#endif
		#endif	
	#else
		#ifndef NULL
			#ifdef	__cplusplus
				#define NULL	(0)
			#else	/* !defined(__cplusplus) */
				#define	NULL	( 0)
			#endif	/* defined(__cplusplus) */
		#endif
	#endif
#else
	#ifndef NULL
 		#ifdef __cplusplus              // EC++
   		#define NULL   0
 		#else
   		#define NULL ((void *) 0)
 		#endif
	#endif	
#endif

#endif
/******************************************************************************/

