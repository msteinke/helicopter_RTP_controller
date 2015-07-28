// *******************************************************
//
// mPWM.c
//
// Functions to set-up PWM
//  Stellaris LM3S1968 EVK
//
// *******************************************************

#include "mPWM.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"


// From Phil Bones:
//*****************************************************************************
// Generates PWM signal: 100 usec pulses @ 660 Hz on PD1/PWM1: Pin 53
//    (6.6 % duty cycle) 100 usec = 1 / PWM1_100USEC
// Generates PWM signal: 200 usec @ 333 Hz on PF3/PWM5:  Pin 23
//    (6.67 % duty cycle) 200 usec = 1 / PWM5_200USEC
// Note that PWM Generator 0 drives output 'PWM1' and PWM Generator 2
// drives output 'PWM5' (Ref LMS1968 datasheet)
//
//*****************************************************************************

//static unsigned short g_PWMPeriod;

// *******************************************************
// returns the period with respect to the set PWM rate and
// PWM clock speed.
unsigned long mPWMGetPeriod(void)
{
	return SysCtlClockGet () / PWM_RATE_HZ;
}



// *******************************************************
// Enable the GPIO ports and PWM peripherals.
void initPorts(void)
{
	//
	// Initialise and enable the GPIO (Ports D and F)
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOF);

    //
    // Set GPIO D1 and GPIO F2, F3 as PWM pins.
    GPIOPinTypePWM (GPIO_PORTD_BASE, GPIO_PIN_1);
    GPIOPinTypePWM (GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3);

    //
    // Initialise the PWM generators (PWM1 and PWM5)
    SysCtlPeripheralEnable (SYSCTL_PERIPH_PWM);
}

// *******************************************************
// configure all PWM ports to use the set PWM frequency.
void configurePWMs (void)
{

	unsigned long PWMPeriod = mPWMGetPeriod();
	//
	// Compute the PWM period based on the system clock.

	//  PWM1, Gen0
	PWMGenConfigure (PWM_BASE, PWM_GEN_0,
	                 PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenPeriodSet (PWM_BASE, PWM_GEN_0, PWMPeriod);
	//PWMPulseWidthSet (PWM_BASE, PWM_OUT_1, SysCtlClockGet () / PWM1_100USEC);

	//
	//  PWM5, Gen2
	PWMGenConfigure (PWM_BASE, PWM_GEN_2,
	                 PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenPeriodSet (PWM_BASE, PWM_GEN_2, PWMPeriod);
	//PWMPulseWidthSet (PWM_BASE, PWM_OUT_5, SysCtlClockGet () / PWM5_200USEC);


	//
	// Enable the PWM generators.
	PWMGenEnable (PWM_BASE, PWM_GEN_0);
	PWMGenEnable (PWM_BASE, PWM_GEN_2);

	//
	// Enable the PWM output signals.
	PWMOutputState (PWM_BASE, PWM_OUT_1_BIT, true);
	PWMOutputState (PWM_BASE, PWM_OUT_5_BIT, true);

	//
	// Half the clock rate so that we meet the specs of 333/2 = 150Hz
	SysCtlPWMClockSet(SYSCTL_PWMDIV_2);
}



// *******************************************************
// Initialize the PWMs. Use this in your main function.
void mPWMInit(void)
{
	//g_PWMPeriod = mPWMGetPeriod(); // I don't actually need a function global...
	initPorts();
	configurePWMs();
}


// *******************************************************
// Set the duty cycle of a particular PWM pin.
void mPWMSet(unsigned short pwmPin, unsigned short dutyCycle)
{
	if (dutyCycle > 100)
	{
		dutyCycle = 100;
	}

	unsigned long PWMPeriod = mPWMGetPeriod()*dutyCycle/100;

	if (pwmPin == PWM1)
	{
		PWMPulseWidthSet (PWM_BASE, PWM_OUT_1, PWMPeriod);
	}
	else if (pwmPin == PWM4)
	{
		PWMPulseWidthSet (PWM_BASE, PWM_OUT_4, PWMPeriod);
	}
	else if (pwmPin == PWM5)
	{
		PWMPulseWidthSet (PWM_BASE, PWM_OUT_5, PWMPeriod);
	}

}
// *******************************************************
// Enables three PWM pins, PWM1, PWM4 and PWM 5.
// @param pwmPin is the specific pwm pin you want.
// @param state is to enable (1) or to disable (0) the pin.
void mPWMEnable(unsigned short pwmPin, unsigned short state)
{
	if (pwmPin == PWM1)
	{
		PWMOutputState (PWM_BASE, PWM_OUT_1_BIT, state);
	}
	else if (pwmPin == PWM4)
	{
		PWMOutputState (PWM_BASE, PWM_OUT_4_BIT, state);
	}
	else if (pwmPin == PWM5)
	{
		PWMOutputState (PWM_BASE, PWM_OUT_5_BIT, state);
	}
}














