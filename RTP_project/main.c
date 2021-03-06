//*****************************************************************************
//
// music1.c - Example program for ENCE361 - intro to interrupts.
//          - Also used in preparation for ENCE463 Project #1 2013.
//
//  P.J. Bones	UCECE
//  Last modified:  26.6.2013
//*****************************************************************************

//*****************************************************************************
//
//! Simple interrupt driven program:
//!   samples with ADC0 (Pin 62 on board header)
//!   reference high voltage on PF7 (Pin 29)
//!  Based on 'convertV1.c'
//!
//*****************************************************************************


// API Peripheral Modules
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"

// C Modules
#include <stdio.h>

// Program specific modules
#include "vbutton.h"
#include "mdisplay.h"
#include "yaw.h"
#include "PID.h"
#include "mPWM.h"
#include "height.h"
#include "mRTC.h"





//*****************************************************************************
// Constants
//*****************************************************************************

#define RTC_RATE_HZ 1000

#define BUTTON_POLE_RATE_HZ 1000

#define HEIGHT_SAMPLE_RATE_HZ 1000

#define PID_RATE_HZ 1000

//*****************************************************************************
// Main module prototypes
//*****************************************************************************

void updateSetpoints(short* yawSetpoint, short* heightSetpoint)
{
	// Yaw
	if (ButtonCheck(LEFT))
	{
		*yawSetpoint -= 15;
	}
	else if (ButtonCheck(RIGHT))
	{
		*yawSetpoint += 15;
	}

	if (*yawSetpoint > 300)
	{
		*yawSetpoint = 300;
	}
	else if (*yawSetpoint < -300)
	{
		*yawSetpoint = -300;
	}


	// Height
	if (ButtonCheck(DOWN) )//&& *heightSetpoint > 0)
	{
		*heightSetpoint -= 10;
	}
	else if (ButtonCheck(UP))
	{
		*heightSetpoint += 10;
	}

	if (*heightSetpoint > 100)
	{
		*heightSetpoint = 100;
	}
	else if (*heightSetpoint < 0)
	{
		*heightSetpoint = 0;
	}
	return;
}

// Spins the main rotor down to landing speed while controlling yaw with PID
/*void spinDown(short heightPIDOffset, pid_t yawPID)
{
	short time;
	short yawError;

	mDisplayLine("     spin down...    ", 0, 5, 15);

	short yawSetPoint = yawGetAngle();

	short heightPIDOffsetRegulator = 0;
	while(heightPIDOffset > heightPIDOffsetRegulator)
	{
		time = mRTCGetMilliSeconds();

		// Spinup time 5 seconds
		if((time % 100 ) == 0)
		{
			heightPIDOffsetRegulator++;
			mPWMSet(PWM1, heightPIDOffset - heightPIDOffsetRegulator);
		}

		//PID control for YAW

		if ((time % (RTC_RATE_HZ/PID_RATE_HZ)) == 0)
		{
			yawError = yawSetPoint - yawGetAngle();;

			mPWMSet(PWM4, (unsigned short)PIDUpdate(&yawPID, yawError, 1.0 / (float) PID_RATE_HZ));
		}
	}
	return;
}*/

// Spins the main rotor up to takeoff speed while controlling yaw with PID
void spinUp(short heightPIDOffset, pid_t yawPID)
{
	short time;

	mDisplayLine("     spin up...    ", 0, 5, 15);

	short mainSpeed = 0;
	short tailSpeed = 10;

	while(mainSpeed < heightPIDOffset)
	{
		time = mRTCGetMilliSeconds();

		// Spinup time 2 seconds
		// update 5 times per second

		if((time % 200 ) == 0)
		{
			mainSpeed+= heightPIDOffset / 10;
			tailSpeed += 5;
			mPWMSet(PWM1, mainSpeed);
			mPWMSet(PWM4, tailSpeed);
		}
	}
	return;
}




///////////////////////////////////////////////////////////////////////////////
////////////////////////////////    MAIN    ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int main(void)
{
	IntMasterDisable();

	//=====SYSTEM PERIPHERAL INITIALIZATION=====

	// Initialize real time clock
	mRTCInit(RTC_RATE_HZ);

	// Millisecond timekeeping variable
	int time;

	//Add periodic tasks to be executed by systick
	mRTCAddTask(heightSample, HEIGHT_SAMPLE_RATE_HZ);

	// Set up display
    mDisplayInit(1000000);
    mDisplayLine("     Waiting...    ", 0, 5, 15);

	// Set up buttons
    ButtonInit();

	// Set up PWM
	mPWMInit();
	mPWMEnable(PWM4, false); // tail rotor, yaw control.
	mPWMEnable(PWM1, false); // main rotor, height control.

	//=========CONTROL INITIALIZATION========


	//-----altitude PID control------

    // Initialize altitude module
	heightInit();

	// =========PID parameters========================

	//Phils
	float H_kp = 1;float H_ki = 1.5;float H_kd = -0.5;

	short heightPIDOffset = 40;

	float Y_kp = 0.6;float Y_ki = 0;float Y_kd = 0;

	short YawPIDOffset = 0;//50;


	// Windup regulator
	float H_windup_limit = 10;
	if (H_ki)
		H_windup_limit /= H_ki;

	// height PID controller
	pid_t heightPID;
	PIDInit(&heightPID);
	PIDSet(&heightPID, H_kp, H_ki, H_kd, H_windup_limit); // set PID constants

	// height PID control variables
	//35; // PID out offset such that the rotor is at near-takoff speed
	short height = 0;
    short heightSetpoint = 0; // in degrees
    short heightError = 0;
    short heightPIDOut = 0;


	//-----yaw PID control-------

	// Initialise Yaw decoder module
	yawInit(); // yaw monitor



	float Y_windup_limit = 20; // Maximum integral contribution to PID output value
	if (Y_ki)
		Y_windup_limit /= Y_ki;	// devide by Y_ki to find maximum value in terms of error

	// Yaw PID controller
	pid_t yawPID;
	PIDInit(&yawPID);
	PIDSet(&yawPID, Y_kp, Y_ki, Y_kd, Y_windup_limit); // set PID constants

	// yaw PID control variables
	short yaw = 0;
	short yawSetpoint = 0;
    short yawError = 0;
    short yawPIDOut = 0;


    //
    // Enable interrupts to the processor.
    IntMasterEnable();


    short takeOffFlag = false;
	while (!takeOffFlag)
	{
		if (ButtonCheck(SELECT))
		//if (GPIOPinRead(GPIO_PORTG_BASE, 0x80))
		{
			takeOffFlag = true;
		}
	}

	// Reset setpoints to current position
	heightSetpoint = heightGet();
	yawSetpoint = yawGetAngle();



	mPWMEnable(PWM4, true); // tail rotor, yaw control.
	mPWMEnable(PWM1, true); // main rotor, height control.


	//spin up routine
	//spinUp(heightPIDOffset, yawPID);

	// Reset clock to zero for effective helicopter launch time
	mRTCSet(0);

	while (1)
	{
		//mDisplayClear();

		time = mRTCGetMilliSeconds();

		// Update Setpoints
		updateSetpoints(&yawSetpoint, &heightSetpoint);

		// ==================PID Control=================
		if ((time % (RTC_RATE_HZ/PID_RATE_HZ)) /*1000/(float)PID_RATE_HZ*/ == 0)
		{
			//
			// ~~~~~~~~~~~~~~~~~ HEIGHT PID ~~~~~~~~~~~~~~~~

			height = heightGet();

			heightError = heightSetpoint - height;

			heightPIDOut = PIDUpdate(&heightPID, heightError, 1.00 / (float)PID_RATE_HZ) + heightPIDOffset;

			if (heightPIDOut > 79)
				//heightPIDOut = 79;
			if (heightPIDOut < 2)
				heightPIDOut = 2;

			mPWMSet(PWM1, (unsigned short)heightPIDOut);


			//
			// ~~~~~~~~~~~~~~~~~~ YAW PID ~~~~~~~~~~~~~~~~~~~
			yaw = yawGetAngle();

			yawError = yaw - yawSetpoint;

			yawPIDOut = PIDUpdate(&yawPID, yawError, 1.00 / (float)PID_RATE_HZ) + YawPIDOffset;

			if (yawPIDOut > 79)
				yawPIDOut = 79;
			if (yawPIDOut < 2)
				yawPIDOut = 2;

			mPWMSet(PWM4, (unsigned short)yawPIDOut);

			// ===============================================
		}

		// RTC_RATE_HZ - PID_RATE_HZ
		if (( (time) % 10) == 0)
		{
			mDisplayLine("time:%.6d mS", time, 0, 7);
			mDisplayLine("Yaw  = %.4d'    ", (int)yaw, 1, 15);
			mDisplayLine("YSet = %.4d'    ", (int)yawSetpoint, 2, 15);
			mDisplayLine("YErr = %.4d'    ", (int)yawError, 3, 15);
			mDisplayLine("YOut = %.4d'    ", (int)yawPIDOut, 4, 15);
			mDisplayLine("height = ~%.3d ", (int)height, 5, 15);
			mDisplayLine("Hset   = %.4d   ", (int)heightSetpoint, 6, 15);
			mDisplayLine("Herr   = %.4d   ", (int)heightError, 7, 15);
			mDisplayLine("Hout   = %.4d   ", (int)heightPIDOut, 8, 15);
		}

		// should put this as part of the main while loop condition
		//if (ButtonCheck(SELECT))
		//{
		//	spinDown();
		//}

	}
}



