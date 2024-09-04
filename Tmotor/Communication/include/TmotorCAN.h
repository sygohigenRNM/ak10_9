/**
 * @file TmotorCAN.h
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2024-09-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef TMOTOR_CAN_H
#define TMOTOR_CAN_H

/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include <stdint.h>
#include "common.h"
/*------------------------------------------------------------------------------
------
------    Defines and Types
------
------------------------------------------------------------------------------*/
/* special address description flags for the CAN_ID */
#define CAN_EFF_FLAG 0x80000000U /* EFF/SFF is set in the MSB */
#define CAN_RTR_FLAG 0x40000000U /* remote transmission request */
#define CAN_ERR_FLAG 0x20000000U /* error message frame */

/* valid bits in CAN ID for frame formats */
#define CAN_SFF_MASK 0x000007FFU /* standard frame format (SFF) */
#define CAN_EFF_MASK 0x1FFFFFFFU /* extended frame format (EFF) */
#define CAN_ERR_MASK 0x1FFFFFFFU /* omit EFF, RTR, ERR flags */

typedef enum {
	CAN_PACKET_SET_DUTY = 0, // Duty Cycle Mode
	CAN_PACKET_SET_CURRENT, // Current Loop Mode
	CAN_PACKET_SET_CURRENT_BRAKE, // Current Brake Mode
	CAN_PACKET_SET_RPM, // Speed Mode
	CAN_PACKET_SET_POS, // Position Mode
	CAN_PACKET_SET_ORIGIN_HERE, // Set Origin Mode
	CAN_PACKET_SET_POS_SPD, // Position-Speed Loop Mode
}CAN_PACKET_ID;

typedef struct{
	void (*Create)(const char * socket_name);
	void (*Destroy)();
	BOOL (*SendFrame)(uint32_t id, uint8_t dlc, const uint8_t * CANMsg);
	BOOL (*ReceiveFrame)(uint8_t * CANMsg);

}TmotorCAN_interface;
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
void TmotorCAN_Create(const char * name);
void TmotorCAN_Destroy();
BOOL TmotorCAN_SendFrame(uint32_t id, uint8_t dlc, const uint8_t * CANMsg);
BOOL TmotorCAN_ReceiveFrame(uint8_t * CANMsg);
#endif // TMOTOR_CAN_H