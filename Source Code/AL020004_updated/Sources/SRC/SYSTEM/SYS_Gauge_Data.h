/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Gauge_Data.h                                               */
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     Gauge Global Data declaration                        */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                             	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SYS_GAUGEDATAS_H
#define SYS_GAUGEDATAS_H

/******************************************************************************/
/*                         		DEFINE 			   	                	      */
/******************************************************************************/


/* Nonbre de points des courbes de capacité théorique= f(Tension à vide) 	   */
#define NB_CURVES                      3
/* Nonbre de points capacité théorique= f(Tension à vide) par courbe    	   */
#define NB_POINTS                      13
/* Valeur des ageings de chaque courbe														*/
#define AGE1                           100 //%
#define AGE2                           91	//%
#define AGE3                           81	//%

/* Courbes théoriques de capacité = f(Tension à vide)                         */ 			
/* Index des capacités en Y 																	*/
#define IDX_CAPACITY 						2	
/* Index de l'emplacement en Y									        				   */
#define IDX_AGE  	         				13 


/* Courbes de capacité= f(Tension à vide,Ageing)                              */ 
/* Index du tableau correspondant aux valeurs en X 	                        */
#define IDX_VOLTAGE_CURRENT            0   	
/* Index du tableau correspondant aux valeurs en Y 									*/
#define IDX_CAPACITY_CURENT 				1
	

/*Tableau de calcul du Batageing
/*Index des courbes en  X                                                 	   */
#define IDX_CAPACITY_CURVE1            0
#define IDX_CAPACITY_CURVE2            1
#define IDX_CAPACITY_CURVE3            2

/*Index des parametres en  Y                                                 	*/
#define IDX_T1                         0
#define IDX_T2                         1
#define IDX_DELTA_CAPACITY             2

/*Capacités Theéorique des batteries														*/
#define IDX_T1                         0
#define IDX_T2                         1  
/******************************************************************************/
/*                         CONSTANT DECLARATION                     	     	 	*/
/******************************************************************************/

#ifdef DECLARATION_GAUGE_DATA
	#ifndef SYS_GAUGE_H
	#define SYS_GAUGE_H

	/* Capacité en fonction de la tension à vide de battery SAFT en fonction de l'ageing*/
	/* Le dernier point correspond au viellissement de référence pour la courbe */
	rom const UWORD16 cCapacityBasedVoltage[NB_POINTS+1][NB_CURVES+1]={	
																		{2240,2240,2240,0},
																		{2470,2355,2280,2},
																		{2553,2450,2335,5},
																		{2572,2530,2424,10},
																		{2611,2590,2525,20},
																		{2632,2620,2575,30},	
																		{2653,2630,2602,40},	
																		{2677,2650,2625,50},	
																		{2716,2700,2665,60},	
																		{2758,2750,2709,70},	
																		{2801,2790,2760,80},	
																		{2861,2861,2821,90},	
																		{2920,2920,2920,100},
																		{AGE1,AGE2,AGE3,0}
																   	};

	/* courbe de la capacité en fonction de la tension à vide calculée par rapport au viellisement */															 	
	SWORD16 CapacityBasedVoltageComputed[NB_POINTS][2]={	
																	   {0,0},
																	   {0,2},
																		{0,5},
																		{0,10},
																		{0,20},
																		{0,30},	
																		{0,40},	
																		{0,50},	
																		{0,60},	
																		{0,70},	
																		{0,80},	
																		{0,90},	
																		{0,100}
															         };
																					
   /* courbe de la capacité en fonction de la tension à vide calculée par rapport au viellisement */															 	
	UWORD16 AgeingCompute[3][NB_CURVES]={	
																	   {0,0},
																		{0,0},
																	 	{0,0},
																		};
	/*%C Variable for	capacity ercent compute											*/
	UWORD16 TYPICAL_BAT_CAPACITY;
	
	/*%C Variable for BAT_AGEING compute 												*/
	UWORD16 DELTA_BAT_VOLTAGE;
	UWORD32 DELTA_CAPACITY ;
	UWORD16 CAPACITY_AT_T1;
	UWORD16 VOLTAGE_AT_T1;
	UWORD16 SAMPLES_AGEING_NUMBER;

	/*%C Variables for the BAT_FEM compute												*/
	UWORD32 SUM_BAT_FEM;
	UWORD16 SAMPLE_BAT_FEM;
	
	/*%C Flags to compute battery capacity												*/
	UWORD16 BatteryChangingDetectedFlagToImpedanceCompute;
	UWORD16 BatteryChangingDetectedFlagToCycleCompute;
	UWORD16 BatteryChangingDetectedFlagToAgeingCompute;

	#endif

#else

	#ifndef SYS_GAUGE_H
	#define SYS_GAUGE_H

	extern rom const UWORD16 cCapacityBasedVoltage[NB_POINTS+1][NB_CURVES+1];
	extern UWORD16 CapacityBasedVoltageComputed[NB_POINTS][2];
	extern UWORD16 AgeingCompute[3][NB_CURVES];
	extern UWORD16 TYPICAL_BAT_CAPACITY;

	/*%C Variable for BAT_AGEING initialization 										*/
	extern UWORD16 DELTA_BAT_VOLTAGE;
	extern UWORD32 DELTA_CAPACITY ;
	extern UWORD16 CAPACITY_AGE1_AT_T1;
	extern UWORD16 CAPACITY_AGE2_AT_T1;
	extern UWORD16 VOLTAGE_AT_T1;
	extern UWORD16 SAMPLES_AGEING_NUMBER;

	/*%C Variables for the BAT_FEM compute												*/
	extern UWORD32 SUM_BAT_FEM;
	extern UWORD16 SAMPLE_BAT_FEM;

	/*%C Flags to compute battery capacity												*/
	extern UWORD16 BatteryChangingDetectedFlagToImpedanceCompute;
	extern UWORD16 BatteryChangingDetectedFlagToCycleCompute;
	extern UWORD16 BatteryChangingDetectedFlagToAgeingCompute;

	#endif
#endif
#endif								 							 		


