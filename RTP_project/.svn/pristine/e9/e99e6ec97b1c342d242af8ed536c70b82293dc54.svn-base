// *******************************************************
//
// PID.c
//
// Functions to set-up PID for a helicopter
//  Stellaris LM3S1968 EVK
//
// using code from Michael Hayes
// *******************************************************

#include "PID.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
//#include "driverlib/gpio.h"
//#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "mPWM.h" // so that i can have PWM_MAX and PWM_MIN defs




// *******************************************************
// Initalize a PID type for use in the main loop.
void PIDInit(pid_t* state)
{
	state->error_integrated = 0.0;
	state->error_previous = 0.0;
	state->K_P = 0.0;
	state->K_I = 0.0;
	state->K_D = 0.0;
	state->enabled = true;
	state->windup_limit = 0;
	state->control_previous = 0.0;
}



// *******************************************************
// Returns the PID control value given the error, time and
// PID constants.
float PIDUpdate(pid_t* state, float error, float delta_t)
{
	float control = 0;

	//
	// only do the calculation if the PID is enabled
	if (state->enabled /*&& state->windup == false*/)
	{
		control = PIDCaclulate(state, error, delta_t);
	}
	else
	{
		control = state->control_previous;
	}

	return control;
}

// *******************************************************
// calculates the PID control value given the error, time
// and PID constants.
float PIDCaclulate(pid_t* state, float error, float delta_t)
{
	float error_derivative;
	float control;


	// put our PID constants into useful variables
	float proportional_gain = state->K_P;
	float integral_gain = state->K_I;
	float derivative_gain = state->K_D;

	state->error_integrated += error * delta_t;

	if (state->error_integrated > state->windup_limit)
		state->error_integrated = state->windup_limit;
	if (state->error_integrated < -1*state->windup_limit) // ie |integrated error| < max value
		state->error_integrated	= -1*state->windup_limit;

	;
	error_derivative = (error - state->error_previous) / delta_t;


	control = (error*proportional_gain) + ((state->error_integrated)*integral_gain) + (error_derivative*derivative_gain);

	state->error_previous = error;
	state->control_previous = control;

	/*if (control >= YAW_MAX)
	{
		control = YAW_MAX;
	}
	else if (control <= YAW_MIN)
	{
		control = YAW_MIN;
	}*/

	return control;
}



// *******************************************************
// Set the proportional, integral, derivative constants for
// a specified PID type.
void PIDSet(pid_t* state, float K_P, float K_I, float K_D, float windup_limit)
{
	state->K_P = K_P;
	state->K_I = K_I;
	state->K_D = K_D;
	state->windup_limit = windup_limit;
}



// *******************************************************
// Enables a PID type.
void PIDEnable(pid_t* state)
{
	state->enabled = true;
}


// *******************************************************
// Disables a PID type.
void PIDDisable(pid_t* state)
{
	state->enabled = false;
}


