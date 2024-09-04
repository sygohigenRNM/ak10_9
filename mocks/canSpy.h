/**
 * @file canSpy.h
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2024-09-04
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef CAN_SPY_H
#define CAN_SPY_H

/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include "socketCAN.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
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

/*------------------------------------------------------------------------------
------
------    Functions
------
------------------------------------------------------------------------------*/
void CanSpy_Create(const char *);
void CanSpy_Destroy();
void CanSpy_SendFrame(uint32_t id, uint8_t dlc, const uint8_t * CANMsg);
void CanSpy_ReceiveFrame(uint8_t * CANMsg);

char * CanSpy_GetName();
uint32_t CanSpy_GetId();
struct can_frame * CanSpy_GetFrame();
#endif // CAN_SPY_H