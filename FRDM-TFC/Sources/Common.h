/*
 * Common.h
 *
 *  Created on: Oct 3, 2015
 *      Author: Jared
 */

#ifndef COMMON_H_
#define COMMON_H_

// How many pixels are ignored on each end and total used
#define IGNORE_PIXELS 16
#define USED_PIXELS 128 - (IGNORE_PIXELS * 2)

// Indexes of the first, middle and end pixels
#define START_PIXEL IGNORE_PIXELS
#define STOP_PIXEL 128 - IGNORE_PIXELS
#define MID_POINT (((STOP_PIXEL-START_PIXEL)/2)+START_PIXEL)

// Number of pixels on each side
#define LEFT_PIXELS MID_POINT-START_PIXEL
#define RIGHT_PIXELS STOP_PIXEL-MID_POINT 

// Defines which button is start and which is stop
#define START_BUTTON TFC_PUSH_BUTTON_0_PRESSED
#define STOP_BUTTON TFC_PUSH_BUTTON_1_PRESSED

// Calculation constants
#define DIFFDIV 500
#define SENSITIVITY 1000
#define SPEED .50
#define SLOW_AMOUNT .002

// Camera constants
#define CAMERA_FREQ 50
#define CAMERA_CYCLES_PER_UPDATE CAMERA_FREQ/50
#define CAMERA_PERIOD 1000000/CAMERA_FREQ



struct Command{
	float steerValue;
	float speedL;
	float speedR;
	int stop;
};

void delay(int);

#endif /* COMMON_H_ */
