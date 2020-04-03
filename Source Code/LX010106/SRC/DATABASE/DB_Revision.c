#pragma ORDER
/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*																			*/
/* Filename	: DB_Version.c 			   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C	Functionnal description : this function provide access to the 		  */
/*%C         version informations											  */
/*                                                            				  */
/******************************************************************************/
/*%I 	Input Parameter : 			Id			      	        	          */
/*%IO 	Input/Output Parameter : 	None 	        			              */
/*%O 	Output Parameter : 			None    				  				  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
/******************************************************************************/

/* Pragmas for code location */

#ifndef _BORLAND
   #ifndef _TASKING
	   #if defined(SUPPORTAIR_M2) || defined(LEGENDAIR_XL2) || defined(LEGENDAIR_S2) || defined(LEGENDAIR_US)
		   #pragma RENAMECLASS(HCONST=REVISION_CONST)
   	#endif
   #endif /* _TASKING */
#endif /* _BORLAND */


#include "typedef.h"
#include "enum.h"
#include "DB_Current.h"
#include "Structure.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_Revision.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


/*%C Constant declaration to locate revision and version information at the end of binary file */

const UBYTE Version_Number[19] = {'V','e','r','s','i','o','n',' ',':',' ',
								CFG_REVISION_VERSION_NUMBER_0/256,CFG_REVISION_VERSION_NUMBER_0%256,
								CFG_REVISION_VERSION_NUMBER_1/256,CFG_REVISION_VERSION_NUMBER_1%256,
								CFG_REVISION_VERSION_NUMBER_2/256,CFG_REVISION_VERSION_NUMBER_2%256,
								CFG_REVISION_VERSION_NUMBER_3/256,CFG_REVISION_VERSION_NUMBER_3%256,(UBYTE) NULL};

const UBYTE* Revision = "Revision : " CFG_REVISION_REVISION_VALUE "."
						"Date : " CFG_REVISION_BUILD_DATE_YEAR "/" 
								  CFG_REVISION_BUILD_DATE_MONTH "/"
								  CFG_REVISION_BUILD_DATE_DAY " "
								  CFG_REVISION_BUILD_DATE_HOUR ":"
								  CFG_REVISION_BUILD_DATE_MINUTE ":"
								  CFG_REVISION_BUILD_DATE_SECOND "."
						"Modified : " CFG_REVISION_MODIFIED_VALUE "."
						"Mixed : " CFG_REVISION_MIXED_VALUE
						" Working copy URL : " CFG_REVISION_WORKING_COPY_URL;


/*%C This function calculates a string lenght */
UWORD16 StrLen(UBYTE* _Text)
{
   UWORD16 Cpt = 0;
   while( (_Text[Cpt] != 0)
   	   && (Cpt < 13) )
   {
      Cpt++;
   }
   return Cpt;
}


/*%C This function reads revision informations */
UWORD16 DB_RevisionRead(e_DB_Revision Id)
{
	UBYTE* String = 0;
	UWORD16 Temp = 0;
	UWORD16 Result = 0;
	UWORD16 Rank = 1;
	UWORD16 StringLength = 0;
	SWORD16 i = 0;

/*%C Matching revision information string is stored */
	String = DB_Revision[Id];
	
/*%C String lenght is calculated */
	StringLength = StrLen(String);

/*%C String content is converted to decimal */
	for (i = StringLength-1; (i>=0) && (String[i] != ':'); i--)
	{
		Temp = String[i] - 48;
		Temp = Temp * Rank;
		Result = Result + Temp;
		Rank = Rank * 10;
	}

/*%C Decimal value is returned */
	return Result;
}

