/**
 * @file CanTest.cpp
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
	#include <stdio.h>
	#include "canSpy.h"
}

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
------    Global variables(external)
------
------------------------------------------------------------------------------*/
TEST_GROUP(CAN)
{
	void setup()
	{
		CanSpy_Create("vcan0");
	}
	void teardown()
	{
		CanSpy_Destroy();
	}
	void validName()
	{
		STRCMP_EQUAL("vcan0", CanSpy_GetName());
	}
	void validId(uint32_t id)
	{
		LONGS_EQUAL(id, CanSpy_GetId());
	}
	void validFrame(uint8_t * validData)
	{
		for (int i = 0; i < 8; i++)
		{
			LONGS_EQUAL(validData[i], CanSpy_GetFrame()->data[i]);
		}
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

// /*------------------------------------------------------------------------------
// ------
// ------    Global Functions
// ------
// ------------------------------------------------------------------------------*/
TEST(CAN, GetName)
{
	validName();
}
TEST(CAN, GetId)
{
	uint8_t data[8];
	data[0] = 1;
	data[1] = 2;
	data[2] = 3;
	data[3] = 4;
	data[4] = 5;
	data[5] = 6;
	data[6] = 7;
	data[7] = 8;
	CanSpy_SendFrame(0, 8, data);
	validId(0);
}
TEST(CAN, SendSocketFrame)
{
	uint8_t data[8];
	data[0] = 1;
	data[1] = 2;
	data[2] = 3;
	data[3] = 4;
	data[4] = 5;
	data[5] = 6;
	data[6] = 7;
	data[7] = 8;
	CanSpy_SendFrame(0, 8, data);
	validFrame(data);
}
TEST(CAN, PrintFrame)
{
	uint8_t data[8];
	data[0] = 1;
	data[1] = 2;
	data[2] = 3;
	data[3] = 4;
	data[4] = 5;
	data[5] = 6;
	data[6] = 7;
	data[7] = 8;
	CanSpy_SendFrame(1, 8, data);
	validFrame(data);
	// printFrame();
}
TEST(CAN, OtherLensFrame)
{
	uint8_t data[4];
	data[0] = 11;
	data[1] = 21;
	data[2] = 31;
	data[3] = 41;
	CanSpy_SendFrame(1, 8, data);
	validFrame(data);
	// printFrame();
}