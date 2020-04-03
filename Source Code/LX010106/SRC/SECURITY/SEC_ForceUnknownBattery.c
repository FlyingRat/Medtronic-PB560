/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_ForceUnknownBattery.c                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Management of forcing the alarm unknown battery            */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : Unknow battery alarm has to be (or not) forced        */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES                               */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_PowerSupply.h"
#include "SEC_ForceUnknownBattery.h"      

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
__inline e_BOOL SEC_ForceUnknownBattery(void)
{
	e_BOOL force = FALSE;
	
#ifdef CONFIG_SMALL_BATTERIES

/*%C Theoretical Capacity recovery from base                                  */
    UWORD16 TheoreticalCapacity = DB_PowerSupplyRead(CAPACITY_THEORICAL_U16);

/*%C If CAPACITY_THEORICAL_U16 >= CONFIG_SMALL_BATTERIES_THRESHOLD            */
/*%C then                                                                     */
	if (TheoreticalCapacity >= CONFIG_SMALL_BATTERIES_THRESHOLD)
	{
        /*%C Set force flag to TRUE                                           */
		force = TRUE;
	}
/*%C End if	                                                                  */

#endif /* CONFIG_SMALL_BATTERIES */
                    
	/* return flag */
    return(force);
}