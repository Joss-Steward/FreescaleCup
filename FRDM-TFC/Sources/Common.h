/*
 * Common.h
 *
 *  Created on: Oct 3, 2015
 *      Author: Jared
 */

#ifndef COMMON_H_
#define COMMON_H_

#define IGNORE_PIXELS 16

#define START_BUTTON TFC_PUSH_BUTTON_0_PRESSED
#define STOP_BUTTON TFC_PUSH_BUTTON_1_PRESSED

#define START_PIXEL IGNORE_PIXELS
#define STOP_PIXEL 128 - IGNORE_PIXELS
#define MID_POINT (((STOP_PIXEL-START_PIXEL)/2)+START_PIXEL)
#define LEFT_PIXELS MID_POINT-START_PIXEL
#define RIGHT_PIXELS STOP_PIXEL-MID_POINT 
#define DIFFDIV 500
#define SENSITIVITY 1000
#define SPEED .50
#define SLOW_AMOUNT .002

#define USED_PIXELS 128 - (IGNORE_PIXELS * 2)

struct Command{
	float steerValue;
	float speedL;
	float speedR;
	int stop;
};

void delay(int);

#endif /* COMMON_H_ */
