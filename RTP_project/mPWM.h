// *******************************************************
//
// mPWM.h
//
//  Functions to set-up PWM
//  Stellaris LM3S1968 EVK
//
// *******************************************************

#ifndef MPWM_H_
#define MPWM_H_


// GLOBAL CONSTANTS
//#define PWM1_RATE_HZ 660
#define PWM_RATE_HZ 300
#define PWM1_100USEC 50000
//#define PWM5_RATE_HZ 333
#define PWM5_200USEC 25000
#define PWM_MAX 98
#define PWM_MIN 2

#define PWM1 0
#define PWM4 1
#define PWM5 2

// PROTOTYPES
void mPWMInit(void);
void mPWMEnable(unsigned short pwmPin, unsigned short state);
unsigned long mPWMGetPeriod(void);
void mPWMSet(unsigned short pwmPin, unsigned short dutyCycle);

#endif /*MPWM_H_*/
