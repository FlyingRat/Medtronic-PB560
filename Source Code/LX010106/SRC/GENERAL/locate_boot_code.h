/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : locate_boot_code.h                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/



#include "product.h"

#ifndef LOCATE_BOOT_CODE_H
#define LOCATE_BOOT_CODE_H

/* Pragmas for code location */

#ifndef _BORLAND
   #ifdef _TASKING
   	   #pragma class PR=BOOT_CODE
   #else
	   #if defined(SUPPORTAIR_M2) || defined(LEGENDAIR_XL2) || defined(LEGENDAIR_S2) || defined(LEGENDAIR_US)
		   #pragma RENAMECLASS (FCODE=BOOT_CODE)
   	#endif
   #endif /* _TASKING */
#endif /* _BORLAND */


#endif // LOCATE_BOOT_CODE_H