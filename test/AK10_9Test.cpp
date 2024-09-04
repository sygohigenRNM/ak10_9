/**
 * @file AK10_9Test.cpp
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
#include "CppUTest/TestHarness.h"
extern "C"
{
	#include "TmotorController.h"
	#include "TmotorCAN.h"
}
/*------------------------------------------------------------------------------
------
------    Defines and Types
------
------------------------------------------------------------------------------*/
typedef struct can_frame can_frame_t;
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
TEST_GROUP(AK10_9)
{

	void setup()
	{
		TMOTOR_INTERFACE(CanSpy);
		TmotorCAN_Create("can0");
		TmotorController_Create();
	}
	void teardown()
	{
		TmotorController_Destroy();
		TmotorCAN_Destroy();
	}
	void printFrame()
	{
		struct can_frame * frame;
		frame = CanSpy_GetFrame();
		printf("|\tID\t|\tdlc\t|\tpad\t|\tres\t|\tled8\t");
		for (int i = 0; i < 8; i++)
		{
			printf("|\tdata%d\t",i);
		}
		printf("|\n");
		printf("|\t%d\t",frame->can_id);
		printf("|\t%d\t",frame->can_dlc);
		printf("|\t%d\t",frame->__pad);
		printf("|\t%d\t",frame->__res0);
		printf("|\t%d\t",frame->len8_dlc);

		printf("|\t%d\t",frame->data[0]);
		printf("|\t%d\t",frame->data[1]);
		printf("|\t%d\t",frame->data[2]);
		printf("|\t%d\t",frame->data[3]);
		printf("|\t%d\t",frame->data[4]);
		printf("|\t%d\t",frame->data[5]);
		printf("|\t%d\t",frame->data[6]);
		printf("|\t%d\t",frame->data[7]);
		printf("|\n");
	}
};

/*------------------------------------------------------------------------------
------
------    Global Functions
------
------------------------------------------------------------------------------*/
TEST(AK10_9, EnableMotor)
{
	TmotorController_EnableMotor(1);
	printFrame();
}
TEST(AK10_9, OperateMotor)
{
	TmotorController_operate(RPM_MODE, 1, 1000);
	printFrame();
}