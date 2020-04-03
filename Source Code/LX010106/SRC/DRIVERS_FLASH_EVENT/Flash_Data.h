/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Flash_Data.h                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    Global variables of "Flash drivers"                   */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*                                                                            */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef FLASH_DATA_H
#define FLASH_DATA_H

/* Première adresse de la flash */
#define ADRESSE_DEBUT_FLASH_IC2   	0x100000		
/* Derniere adresse de la flash */
#define ADRESSE_FIN_FLASH_IC2     	0x17FFFF   	
/* Memoire de type bottom boot ex 29F400BB */
#define BOTTOM_BOOT     	   		0x22AB		
/* Memoire de type top boot ex 29F400BT */
#define TOP_BOOT        	   		0x2223 		

	#ifdef DECLARATION_FLASH_DATA
const UWORD32 adresse_secteur_bottom[12] = 
														{0
														,0x4000
														,0x6000
														,0x8000
														,0x10000
														,0x20000
														,0x30000
														,0x40000
														,0x50000
														,0x60000
														,0x70000
														,0x7FFFF}; 	
const UWORD32  adresse_secteur_top[12] = 
														{0
														,0x10000
														,0x20000
														,0x30000
														,0x40000
														,0x50000
														,0x60000
														,0x70000
														,0x78000
														,0x7A000
														,0x7C000
														,0x7FFFF};	

BIT Suspend_Erase = FALSE; 
UWORD16 xhuge *Ptr_Flash = NULL; 
UWORD16 Ptr_Evenement = 0; 
BIT Mutex_Read_Adresse = FALSE;
UBYTE Num_Sector = 0;
UWORD16 type_memoire = BOTTOM_BOOT;
UBYTE Ptr_Num_evenement_Read = 0;
UBYTE Ptr_Num_evenement_Write = 0;
BIT Buffer_Empty = FALSE;
UWORD32 End_Of_Event_Flash = 0;
BIT Mutex_Flag_Erase = FALSE;
UWORD16 xhuge *Erase_Adress = NULL;
e_DRV_EVENT_STATE Flash_State = DRV_EVENT_FREE;

	#else
extern const UWORD32 adresse_secteur_bottom[12]; 	
extern const UWORD32  adresse_secteur_top[12];

extern BIT Suspend_Erase; 
extern UWORD16 xhuge *Ptr_Flash; 
extern UWORD16 Ptr_Evenement; 
extern BIT Mutex_Read_Adresse;
extern UBYTE Num_Sector;
extern UWORD16 type_memoire;
extern UBYTE Ptr_Num_evenement_Read;
extern UBYTE Ptr_Num_evenement_Write;
extern BIT Buffer_Empty;
extern UWORD32 End_Of_Event_Flash;
extern BIT Mutex_Flag_Erase;
extern UWORD16 xhuge *Erase_Adress;
extern e_DRV_EVENT_STATE Flash_State;

	#endif

#endif
