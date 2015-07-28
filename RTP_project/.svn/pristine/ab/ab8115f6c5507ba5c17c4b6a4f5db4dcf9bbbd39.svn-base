// *******************************************************
//
// mRTC.h
//
//  Functions to set-up a real time clock using SysTick.
//  Stellaris LM3S1968 EVK
//
// *******************************************************

#ifndef MRTC_H_
#define MRTC_H_

// INCLUDES

#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"

// GLOBAL CONSTANTS
#define SYSTICK_TASK_LIST_SIZE 5

// type defs

typedef void (*myFuncDef)(void);



// PROTOTYPES
void mRTCInit(unsigned short rtc_rate_hz);
void mRTCSet(unsigned long long ullTime);

unsigned long long mRTCGetSeconds(void);
unsigned long long mRTCGetMilliSeconds(void);
unsigned long long mRTCGetMicroSeconds(void);
//unsigned long long mRTCGetRaw(void);

short mRTCAddTask(myFuncDef func, unsigned short rate);
short mRTCRemoveTask();

#endif /*MRTC_H_*/
