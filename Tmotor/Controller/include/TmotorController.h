/**
 * @file Controller.h
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2024-08-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include <stdint.h>
/*------------------------------------------------------------------------------
------
------    Defines and Types
------
------------------------------------------------------------------------------*/
#define P_MIN	-12.5f
#define P_MAX	12.5f
#define V_MIN	-30.f
#define V_MAX	30.f
#define T_MIN	-18.0f
#define	T_MAX	18.0f
#define KP_MIN	0
#define KP_MAX	500.0f
#define KD_MIN	0
#define KD_MAX	5.0f

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

/*------------------------------------------------------------------------------
------
------    Global Functions
------
------------------------------------------------------------------------------*/
void TmotorController_Create();
void TmotorController_Destroy();
void TmotorController_operate(uint8_t index, uint8_t id, float data);
void TmotorController_EnableMotor(uint32_t id);
#endif // CONTROLLER_H