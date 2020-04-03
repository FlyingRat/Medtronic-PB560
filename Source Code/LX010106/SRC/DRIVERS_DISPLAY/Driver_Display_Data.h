/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Driver_Display_data.h 		                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Description fonctionnelle:		 	                        	      */
/*                                                                      	   */
/*%C    Data declaration for display driver functions                        */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#define grESC					0x1B
#define grNULL					0
#define DUMMY 					0x55
#define REQUEST_ON 			0x400004
#define REQUEST_OFF			0x400000
#define RAM_ACCES 			0x400007


#define ON					0xFF
#define OFF					0x00
#define INV					0x80
#define ARIAL8				0
#define ARIAL9				1
#define ARIALBLACK11		2
#define ARIALBOLD29			3
//#define ARIALFREE			4 non utilisé
#define ARIAL9_JAPANESE		4
#define ARIAL9_KOREAN_GREEK	5
#define ARIAL9_CHINESE		6

#define BLACK				0xFF
#define WHITE				0x00
#define PAGEOFF 			0
#define PAGEON 			4
#define SLOWBLINK			8
#define FASTBLINK			12
#define PAGE1				1
#define PAGE2				2
#define PAGE3				3
#define DECIMAL			1
#define INTEGER			0


#ifdef DISPLAY_DRIVER_DATA_DECLARATION

	#ifndef DRIVER_DISPLAY_DATA_H
	#define DRIVER_DISPLAY_DATA_H


	#endif
#else

#endif
