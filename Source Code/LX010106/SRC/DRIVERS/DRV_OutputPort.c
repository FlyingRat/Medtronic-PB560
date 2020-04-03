/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_OutputPort.c  						                        	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     																		*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : # Port, Value                                          */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "io_declare.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_OutputPort(e_OUTPUT_NAME _Port, UWORD16 _Value)
{
	UWORD16 *PtrPortWord = (UWORD16 xhuge *)0x800000;
	UWORD16 Tampon1 = 0x0000;
	UWORD16 Tampon2 = 0x0000;
	static UWORD16 OutputPortValue = 0x1FE8;

 	if (_Value == 0)
 	{
		/*%C If a CE SPI is set - RAZ all the other CE SPI except CE SPI USB */
		if ((_Port >= CE_EEP) && (_Port <= CE_FLOW_EXP_SENS) && (_Port != CE_SPI_USB))
		{
			Tampon1 = ~(0x0001 << _Port);
 			Tampon2 = OutputPortValue & RAZ_CEb_SPI;
 			Tampon2 = Tampon2 | RAZ_CE_SPI;
 			OutputPortValue = Tampon2 & Tampon1;
		}
		else
		{
			Tampon1 = ~(0x0001 << _Port);
 			OutputPortValue = OutputPortValue & Tampon1;
		}
	}
	else
	{
		/*%C If a CE SPI is set - Set only this one, RAZ the other except CE SPI USB */
		if ((_Port >= CE_EEP) && (_Port <= CE_FLOW_EXP_SENS) && (_Port != CE_SPI_USB))
		{
			Tampon1 = (0x0001 << _Port);
 			Tampon2 = OutputPortValue & RAZ_CEb_SPI;
 			Tampon2 = Tampon2 | RAZ_CE_SPI;
 			OutputPortValue = Tampon2 | Tampon1;
		}
		else
		{
			Tampon1 = (0x0001 << _Port);
 			OutputPortValue = OutputPortValue | Tampon1;
		}
	}
 	
	/*activation des sorties de IC14*/                           
	*PtrPortWord =	OutputPortValue;

}
