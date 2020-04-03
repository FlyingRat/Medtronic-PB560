/******************************************************************************/
/*                                                                            */
/* Project N  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_USBInterfaceCppC.cpp                               	 		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "typedef.h"
#include "HMI_Controller.hpp"

extern "C" UWORD16 HMI_USBSendCmd(UWORD16 usb_cmd_id, UWORD16 incr)
{
	Controller *Cont = Controller::GetInstance();
	UWORD16 i;
	MenuControlNode* cmd_node;
	MenuControlNode* current_node = Cont->GetCurrentNode();
	 if ((e_BOOL)(Cont->GetCurrentFrame() == FRAME_USB))
	 { 
		switch(usb_cmd_id) {
			case USB_MONITOR_TRANSFER_U16:
				cmd_node = Cont->GetNodeAt(NodeUsbTransferMonit);
			break;
			default:
				/* Command not supported */
			break;
		}
	
		/* Set current node to the cmd node and move to modif node to call the VALID handler */
		Cont->MoveCurrentNode(cmd_node);
		(Cont->*(Cont->GetCurrentNode()->GetEventNode()->OnButtonValid))();
	
		/* Increment the value by calling the ModifyUp handler as many times as requested */
		for(i=0; i<incr; i++) {
			(Cont->*(Cont->GetCurrentNode()->GetEventNode()->OnButtonUp))();
	    }
	
		/* Call the valid handler */
		(Cont->*(Cont->GetCurrentNode()->GetEventNode()->OnButtonValid))();
	
		/* At the end, set the processing node to the saved node (modif one because
		the error code handler moves back to non modif node using the timeout handler */
		cmd_node = Cont->GetNodeAt(current_node->GetEventNode()->GetIdNodeOnValid());
	
		Cont->SetUsbProcessingNode(cmd_node);

		return 0;
	}
	else
	{
		return 1;
	}
}



