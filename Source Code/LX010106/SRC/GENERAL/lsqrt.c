
/*----------------------------------------------------------------------------*/


#include "typedef.h"

UWORD16 lsqrt(UWORD32 Square)
/* Routine to do a fast square root of a 16 bit integer */
{
UBYTE i;
UWORD16 root = 0; /* 16 bit answer */
UWORD32 square1 = 0; /* 32 bit storage */
UWORD32 try = 0; /* 32 bit storage */

/* 16 = #bits / 2 */
for (i=1; i <= 16; i++) 
{
	/* 30 = #bits - 2 */
	square1 = (square1 << 2) + (Square >> 30); 
	Square = (Square << 2);
	root = (root << 1);
	try = (root << 1);
	try++;
	if (try <= square1)
	{
		square1 = square1 - try;
		root = root + 1;
	}
}
return((UWORD16) root);
}
