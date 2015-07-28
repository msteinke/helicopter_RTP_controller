// *******************************************************
//
// yaw.h
//
//  Functions to keep track of the yaw of a helicopter
//  Stellaris LM3S1968 EVK
//
// *******************************************************

#ifndef YAW_H_
#define YAW_H_

// CONSTANTS
#define YAW_CW 1
#define YAW_CCW 0
#define YAW_NUM_SLOTS 112

// PROTOTYPES
// *******************************************************
// Initializes the GPIO pins and their interrupt handlers.
void yawInit(void);

// *******************************************************
// Returns the value of g_clicks. This is the location of
// the helicopter on the yaw axis.
int yawGetClicks(void);

// *******************************************************
// Returns the angle of yaw. This is the location of
// the helicopter on the yaw axis.
int yawGetAngle(void);

// *******************************************************
// Returns the last known direction of rotation of the wheel.
int yawGetDirection(void);

// *******************************************************
// Returns the last known direction of rotation of the wheel.
int yawIsCW(void);

// *******************************************************
// Sets the yaw counter to a desired value.
void yawSetClicks(int value);

#endif /*YAW_H_*/
