/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Main_Carte_Alim.h            					              			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        			  										      		  					*/
/*%C          																  						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef MAIN_CARTE_ALIM_H
#define MAIN_CARTE_ALIM_H


/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/
/******************************************************************************/

extern void INIT_CPU(void);
extern void PUST_Checks(UBYTE _ForceFail);
extern void INIT_DataBase(void);
extern void INIT_Sample(void);
extern void INIT_Timer(void);
extern void INIT_Charger(void);
extern void INIT_RS232_Driver(void);
extern void INIT_Interrupt_T0(void);
extern void INIT_SPI_ST10_Driver(void);
extern void INIT_EEPROM_BAT_Driver(void);
extern void INIT_Leds(void);

extern void SCHED_Launch(void);

#endif
