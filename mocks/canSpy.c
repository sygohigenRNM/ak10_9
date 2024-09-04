/**
 * @file canSpy.c
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
#include "canSpy.h"
#include <stdio.h>
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
static char name[10];
static uint8_t bus[100] = {0,};
/*------------------------------------------------------------------------------
------
------    Functions
------
------------------------------------------------------------------------------*/
void CanSpy_Create(const char * can_name)
{
	memcpy(name, can_name, sizeof(name));
}
void CanSpy_Destroy()
{
	for (uint32_t i = 0; i < sizeof(name); i++)
	{
		name[i] = '\0';
	}

}
void CanSpy_SendFrame(uint32_t id, uint8_t dlc, const uint8_t * CANMsg)
{
	struct can_frame tx_frame = {0,};

    tx_frame.can_id = id;
    tx_frame.can_dlc = dlc;
    memcpy(tx_frame.data, CANMsg, tx_frame.can_dlc);
	memcpy(bus, &tx_frame, sizeof(struct can_frame));
}
void CanSpy_ReceiveFrame(uint8_t * CANMsg)
{
	struct can_frame rx_frame = {0,};

	memcpy(&rx_frame, bus, sizeof(struct can_frame));
	memcpy(CANMsg, &rx_frame.data, rx_frame.can_dlc);
}

char * CanSpy_GetName()
{
	return name;
}

uint32_t CanSpy_GetId()
{
	struct can_frame frame = {0,};
	memcpy(&frame, bus, sizeof(struct can_frame));
	return frame.can_id;
}

struct can_frame * CanSpy_GetFrame()
{
	return (struct can_frame*)bus;
}