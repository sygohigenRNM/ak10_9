/**
 * @file Controller.c
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2024-08-30
 *
 * @copyright Copyright (c) 2024
 *
 */
/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include "TmotorController.h"
#include "TmotorCAN.h"
#include <string.h>
#include <unistd.h>
/*------------------------------------------------------------------------------
------
------    Defines and Types
------
------------------------------------------------------------------------------*/
typedef void (*OpMode)(uint8_t, float );
/*------------------------------------------------------------------------------
------
------    Macro
------
------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
------
------    Global variables(external)
------
------------------------------------------------------------------------------*/
const uint8_t motorEnableMsg[8] = {0xFF, 0xFF, 0xFF, 0xFF,
                                         0xFF, 0xFF, 0xFF, 0xFC};

const uint8_t motorDisableMsg[8] = {0xFF, 0xFF, 0xFF, 0xFF,
                                          0xFF, 0xFF, 0xFF, 0xFD};

const uint8_t motorSetZeroPositionMsg[8] = {0xFF, 0xFF, 0xFF, 0xFF,
                                                  0xFF, 0xFF, 0xFF, 0xFE};

unsigned int motorReplyWaitTime = 50;

OpMode opmode[7];

uint8_t CANTxMsg[8];
uint8_t CANRxMsg[8];
/*------------------------------------------------------------------------------
------
------    Global Functions
------
------------------------------------------------------------------------------*/
static void comm_can_set_duty(uint8_t controller_id, float duty);
static void comm_can_set_current(uint8_t controller_id, float current);
static void comm_can_set_current_brake(uint8_t controller_id, float current);
static void comm_can_set_rpm(uint8_t controller_id, float rpm);
static void comm_can_set_pos(uint8_t controller_id, float pos);

void TmotorController_Create()
{
	OpMode tmp[7] = {
		comm_can_set_duty,
		comm_can_set_current,
		comm_can_set_current_brake,
		comm_can_set_rpm,
		comm_can_set_pos,
		NULL,
		NULL
	};
	memcpy(opmode, tmp, sizeof(opmode));
}
void TmotorController_Destroy()
{
	OpMode tmp[7] = {
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL
	};
	memcpy(opmode, tmp, sizeof(opmode));
}
void TmotorController_operate(uint8_t index, uint8_t id, float data)
{
	opmode[index](id, data);
}

void TmotorController_EnableMotor(uint32_t id)
{
	TmotorCAN_SendFrame(id, sizeof(motorEnableMsg), motorEnableMsg);
	usleep(motorReplyWaitTime);
	TmotorCAN_ReceiveFrame(CANRxMsg);
}

static void buffer_append_int32(uint8_t* buffer, int32_t number, int32_t *index) {
	buffer[(*index)++] = number >> 24;
	buffer[(*index)++] = number >> 16;
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number;
}

// static void buffer_append_int16(uint8_t* buffer, int16_t number, int16_t *index) {
// 	buffer[(*index)++] = number >> 8;
// 	buffer[(*index)++] = number;
// }

static void comm_can_set_duty(uint8_t controller_id, float duty) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(duty * 100000.0), &send_index);
	TmotorCAN_SendFrame(controller_id |
			((uint32_t)CAN_PACKET_SET_DUTY << 8), send_index, buffer);
}

static void comm_can_set_current(uint8_t controller_id, float current) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(current * 1000.0), &send_index);
	TmotorCAN_SendFrame(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT << 8), send_index, buffer);
}

static void comm_can_set_current_brake(uint8_t controller_id, float current) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(current * 1000.0), &send_index);
	TmotorCAN_SendFrame(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_BRAKE << 8), send_index, buffer);
}

static void comm_can_set_rpm(uint8_t controller_id, float rpm) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)rpm, &send_index);
	TmotorCAN_SendFrame(controller_id |
			((uint32_t)CAN_PACKET_SET_RPM << 8), send_index, buffer);
}

static void comm_can_set_pos(uint8_t controller_id, float pos) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(pos * 1000000.0), &send_index);
	TmotorCAN_SendFrame(controller_id |
			((uint32_t)CAN_PACKET_SET_POS << 8), send_index, buffer);
}