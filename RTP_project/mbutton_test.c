
//*****************************************************************************
//
// mbutton_test.c - Test program for button module
//
// Author:  Martin C. Steinke
// Last modified:	2014-04-19
//*****************************************************************************

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/pwm.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "utils/uartstdio.h"
#include "driverlib/debug.h"
#include "drivers/rit128x96x4.h"
#include "stdio.h"
#include "driverlib/interrupt.h"
//#include "buttonSet.h"
#include "mbutton.h"
#include "mdisplay.h"



int
main(void)
{
	IntMasterDisable();

	//initClock();


	mButtonInit(UP);
	mButtonInit(DOWN);
	mButtonInit(LEFT);
	mButtonInit(RIGHT);
	mButtonInit(SELECT);

	mDisplayInit(10000000);

	unsigned long ulCount[5] = {0,0,0,0,0};
	unsigned char but = 0;

	//
	// Enable interrupts to the processor.
	IntMasterEnable();

	while (1)
	{
		// Background task: Check for button pushes and
		//  display latest button pushed
		for (but = 0; but <= SELECT; but++)
		{
			if (mButtonCheck(but))
			{
				//displayBut(state, g_ulCount);
				ulCount[but] += 1;
			}
		}
		mDisplayLine("Up =     %.3u", ulCount[UP], 1, 15);
		mDisplayLine("Down =   %.3u", ulCount[DOWN], 2, 15);
		mDisplayLine("Left =   %.3u", ulCount[LEFT], 3, 15);
		mDisplayLine("Right =  %.3u", ulCount[RIGHT], 4, 15);
		mDisplayLine("Select = %.3u", ulCount[SELECT], 5, 15);

		mDisplayLine("Port G = %.3u",
				GPIOPinRead(GPIO_PORTG_BASE, 248), 8, 6);
	}
}


















