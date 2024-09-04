/**
 * @file TmotorCAN.c
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2024-09-04
 *
 * @copyright Copyright (c) 2024
 *
 */
/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include "TmotorCAN.h"
#include "socketCAN.h"
#include "common.h"
/*------------------------------------------------------------------------------
------
------    Defines and Types
------
------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
------
------    Macro
------
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
------
------    variables(external)
------
------------------------------------------------------------------------------*/
TmotorCAN_interface TmotorInterface = {
	.Create = SocketCAN_Create,
	.Destroy = SocketCAN_Destroy,
	.SendFrame = SocketCAN_SendFrame,
	.ReceiveFrame = SocketCAN_ReceiveFrame
};

/*------------------------------------------------------------------------------
------
------    Functions
------
------------------------------------------------------------------------------*/
void TmotorCAN_Create(const char * name)
{
	TmotorInterface.Create(name);
}
void TmotorCAN_Destroy()
{
	TmotorInterface.Destroy();

	TmotorInterface.Create = NULL;
	TmotorInterface.Destroy = NULL;
	TmotorInterface.SendFrame = NULL;
}
BOOL TmotorCAN_SendFrame(uint32_t id, uint8_t dlc, const uint8_t * CANMsg)
{
	if(FALSE != TmotorInterface.SendFrame(id, dlc, CANMsg))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
BOOL TmotorCAN_ReceiveFrame(uint8_t * CANMsg)
{
	if(FALSE != TmotorInterface.ReceiveFrame(CANMsg))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}