/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : VEN_RiseCompute.c                                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C This function realizes an interpolation with the function parameters     */
/*                                                                            */
/*%C Function  y = ax + b (with saturation)                                   */
/*                                                                            */
/*   y2 |       /                                                             */
/*      |     /                                                               */
/*   y1 |   /                                                                 */
/*      | /                                                                   */
/*     ------------                                                           */
/*       x1    x2                                                             */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : x                                                      */
/*%I Input Parameter : x1                                                     */
/*%I Input Parameter : y1                                                     */
/*%I Input Parameter : x2                                                     */
/*%I Input Parameter : y2                                                     */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "VEN_RiseCompute.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


SWORD32 VEN_RiseCompute(SWORD32 x,
                        SWORD32 x1,
                        SWORD32 y1,
                        SWORD32 x2,
                        SWORD32 y2)
{

   SWORD32 Compute = 0;

/*%C y = (x - x1) * (y2 -y1) / (x2-x1) + y1     */
/*%C Rise compute       */
   Compute = (x - x1) * (y2 - y1);
   Compute = Compute  / (x2 - x1);
   Compute = Compute + y1;

/*%C Saturation       */
   if (y2 < y1)
   {
      Compute = saturation(Compute,
                           y2,
                           y1);
   }
   else
   {
      Compute = saturation(Compute,
                           y1,
                           y2);
   }

   return(Compute);
}
