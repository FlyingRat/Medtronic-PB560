/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : locate_Security_code.h                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/



#include "product.h"

#ifndef LOCATE_SECURITY_CODE_H
#define LOCATE_SECURITY_CODE_H

/* Pragmas for code location */

#ifndef _BORLAND
   #ifdef _TASKING
   	   #pragma class PR=SECURITY_CODE

   #else
	   #if defined(SUPPORTAIR_M2) || defined(LEGENDAIR_XL2) || defined(LEGENDAIR_S2)
		   #pragma RENAMECLASS (FCODE=SECURITY_CODE)
   	#endif
   #endif /* _TASKING */
#endif /* _BORLAND */


#endif // LOCATE_SECURITY_CODE_H



