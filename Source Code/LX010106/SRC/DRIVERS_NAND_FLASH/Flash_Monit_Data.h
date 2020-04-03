/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505													  */
/*																		   	  */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Flash_Monit_Data.h											  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 							Description fonctionnelle: 					  */
/*                                                                      	  */
/*%C 								Data declaration						  */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/



/******************************************************************************
	 							Explication Config XBUS							
	 											


La flash monitoring fonctionne sur le BUSCON0

	- 1 Waitstates
	- No Read / Write Delay
	- No Waitstates on MTTCO
	- 16 bits de Multiplexed
	- Normal ALE
	- External Bus disabled
	- RDYENO : Disable
	- RDYPOLO : Low
	- CSRENO : Enable
	- CSWENO : Enable

Soit BUSCON0 = 0x00BF ;

	Les broches ALE et CMD sont commandée par le µc ;

	Les données envoyées dans le XBUS par le µc sont placée dans un tampon,
	d'ou le µc execute la suite des instructions sans avoir fini de tranférer
	l'intégralité des données ;

	Pour contrer ce temps, ajouter une tempo (_nop()) avant la retomber des
	commandes ALE et CMD.

	Cette tempo doit être de 1 _nop() supplémentaire par rapport au nombre
	de waitstate présente sur le BUSCON0.

	Ici on placera un _nop() dans toutes nos fonctions et 0 Waitstate sur
	BUSCON0



De plus:

	- Accès à un pointeur en global trop long 
	- Placer les pointeurs en local
	- Xhuge non nécessaires 
	- Pour gagner sur les temps d'accès pointeur, dans une custom optimisation
	cocher CSE

Pour une meilleure optimisation taille + vitesse de code, cocher :

	- CSE 
	- Favor code size above execution speed 
	- Code recognition to generate optimal code for expressions 
	- Optimization	of interrupt frame code for C interrupt functions 
	- Peephole optimizer 
	- Code order rearranging in flow optimization

													 
*******************************************************************************/

#ifdef DECLARATION_MONITFLASH_DATA

	#ifndef MONITFLASH_DATA_H
	#define MONITFLASH_DATA_H
	

		e_Flash_Read_Status DRV_MONIT_Read_Request = ENDED;
		e_Flash_Read_Status DRV_TREND_Read_Request = ENDED;
		t_FlashParam DRV_MONIT_Address_Write_Flash;
		t_FlashParam DRV_MONIT_Address_Write_Flash_Recording;
		t_FlashParam DRV_MONIT_Address_Start_Read_Flash_Recording;
		t_FlashParam DRV_TREND_Address_Write_Flash;
		t_FlashParam DRV_TREND_Address_Write_Flash_Recording;
		t_FlashParam DRV_TREND_Address_Start_Read_Flash_Recording;
	  

 /* Flash input buffer definition with indexes */
	  	UBYTE DRV_NAND_Monit_Buffer[MONIT_BUFFER_SIZE]
	  										[NAND_PAGE_CLUSTER_SIZE];
	  	UBYTE DRV_NAND_Trend_Buffer[TREND_BUFFER_SIZE]
	  										[NAND_PAGE_CLUSTER_SIZE];
		UWORD16 DRV_MONIT_Idx_Write_Frame = 0;
		UWORD16 DRV_MONIT_Idx_Read_Frame = 0;
		UWORD16 DRV_MONIT_Idx_Frame = 0;
		UWORD16 DRV_TREND_Idx_Write_Frame = 0;
		UWORD16 DRV_TREND_Idx_Read_Frame =	0;
		UWORD16 DRV_TREND_Idx_Frame = 0;
/* UART Output buffer definition with indexes */ 

		UBYTE DRV_MONIT_UART_Buffer_Var[MONIT_BUFFER_SIZE_READ];
		UBYTE DRV_TREND_UART_Buffer_Var[TREND_BUFFER_SIZE_READ];
		UWORD16 DRV_MONIT_Idx_Write_UART_Buffer = 0;
		UWORD16 DRV_MONIT_Idx_Read_UART_Buffer =0;		 
		UWORD16 DRV_MONIT_Idx_Frame_UART_Buffer = 0;

		UWORD16 DRV_MONIT_Received_Data = 0;

		UWORD16 DRV_TREND_Received_Data = 0;

		volatile UBYTE DRV_MONIT_New_Data = FALSE;
		volatile UBYTE DRV_TREND_New_Data = FALSE;

		UWORD16 DRV_NAND_Block_Number = 1024;
		UWORD16 DRV_NAND_First_Partition_Block_Start = 1;
		UWORD16 DRV_NAND_First_Partition_Block_End =560;
		UWORD16 DRV_NAND_Second_Partition_Block_Start = 561;
		UWORD16 DRV_NAND_Second_Partition_Block_End =1023;
		UBYTE DRV_NAND_Maximum_Bad_Block = 0;

		e_NAND_FLASH_STATE DRV_NAND_Flash_State = NAND_FREE;
		UBYTE DRV_MONIT_Step = 0;
		UBYTE DRV_TREND_Step = 0;

		UWORD16 DRV_MONIT_Partition_Full = FALSE;
		UWORD16 DRV_TREND_Partition_Full = FALSE;
		UBYTE DRV_NAND_End_Of_Read = FALSE;

//UWORD32 Nbr_Written_Data = 0;


 //	#pragma class HB=EXTERNAL_RAM
		UBYTE huge DRV_NAND_Bad_Block_Map[NAND_FLASH_BLOCK_NUMBER_LIMIT];
 //	#pragma class HB=HB		



	#endif
#else
	#ifndef MONITFLASH_DATA_H
	#define MONITFLASH_DATA_H
		extern e_Flash_Read_Status DRV_MONIT_Read_Request;
		extern e_Flash_Read_Status DRV_TREND_Read_Request;
		extern t_FlashParam DRV_MONIT_Address_Write_Flash;
		extern t_FlashParam DRV_MONIT_Address_Write_Flash_Recording;
		extern t_FlashParam DRV_MONIT_Address_Start_Read_Flash_Recording;
		extern t_FlashParam DRV_TREND_Address_Write_Flash;
		extern t_FlashParam DRV_TREND_Address_Write_Flash_Recording; 
		extern t_FlashParam DRV_TREND_Address_Start_Read_Flash_Recording;
		extern t_FlashParam DRV_TREND_Address_Read_Flash;
	 
	 /* Flash input buffer definition with indexes */
	  	extern UBYTE DRV_NAND_Monit_Buffer[MONIT_BUFFER_SIZE]
	  												 [NAND_PAGE_CLUSTER_SIZE];
	  	extern UBYTE DRV_NAND_Trend_Buffer[TREND_BUFFER_SIZE]
	  												 [NAND_PAGE_CLUSTER_SIZE];
		extern UWORD16 DRV_MONIT_Idx_Write_Frame;
		extern UWORD16 DRV_MONIT_Idx_Read_Frame;
		extern UWORD16 DRV_MONIT_Idx_Frame;
		extern UWORD16 DRV_TREND_Idx_Write_Frame;
		extern UWORD16	DRV_TREND_Idx_Read_Frame;
		extern UWORD16 DRV_TREND_Idx_Frame;

/* UART Output buffer definition with indexes */ 
		extern UBYTE DRV_MONIT_UART_Buffer_Var[MONIT_BUFFER_SIZE_READ];
		extern UBYTE DRV_TREND_UART_Buffer_Var[TREND_BUFFER_SIZE_READ];
		extern UWORD16 DRV_MONIT_Idx_Write_UART_Buffer;
		extern UWORD16 DRV_MONIT_Idx_Read_UART_Buffer;		
		extern UWORD16 DRV_MONIT_Idx_Frame_UART_Buffer;

		extern  UWORD16 DRV_MONIT_Received_Data;

		extern  UWORD16 DRV_TREND_Received_Data;

		extern volatile UBYTE DRV_MONIT_New_Data;
		extern volatile UBYTE DRV_TREND_New_Data;

		extern UWORD16 DRV_NAND_Block_Number;
		extern UWORD16 DRV_NAND_First_Partition_Block_Start;
		extern UWORD16 DRV_NAND_First_Partition_Block_End;
		extern UWORD16 DRV_NAND_Second_Partition_Block_Start;
		extern UWORD16 DRV_NAND_Second_Partition_Block_End;
		extern UBYTE DRV_NAND_Maximum_Bad_Block;

		extern UBYTE huge DRV_NAND_Bad_Block_Map[NAND_FLASH_BLOCK_NUMBER_LIMIT];
	  
	  	extern e_NAND_FLASH_STATE DRV_NAND_Flash_State;

		extern UBYTE DRV_MONIT_Step;
		extern UBYTE DRV_TREND_Step;

	    extern UWORD16 DRV_MONIT_Partition_Full;
		extern UWORD16 DRV_TREND_Partition_Full;
		extern UBYTE DRV_NAND_End_Of_Read;

	#endif
#endif


