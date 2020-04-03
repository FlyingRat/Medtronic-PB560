/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: saturation.c                                 	        		   */
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function limits	the value to    	*/
/*%C        its min or max value if necessary                          	  		*/
/*                                                            				  		*/
/*%C If Value > max => Function_Result = Max               							*/
/*%C If Value < min => Function_Result = Min               							*/
/*%C In the other cases, Function_Result = Value                          		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				Value                                 		  	*/
/*%I 	Input Parameter :				Min                                 		  	*/
/*%I 	Input Parameter :				Max                                 		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
/*%O 	Output Parameter : 			Function_Result              				  		*/
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
SWORD32 saturation(SWORD32 Value,
                   SWORD32 Min,
                   SWORD32 Max) 
{

/* Function result declaration */
   SWORD32 Function_Result = 0;
      
   if (Value > Max)
	{
	   Function_Result = Max;   
	}
   else if (Value < Min)
	{
	   Function_Result = Min;   
	}
   else
	{
	   Function_Result = Value;
	}

   return(Function_Result);
}