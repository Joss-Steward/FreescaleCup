/*
 * Common.h
 *
 *  Created on: Oct 3, 2015
 *      Author: Jared
 */

#ifndef COMMON_H_
#define COMMON_H_

#define IGNORE_PIXELS 8
#define USED_PIXELS (128 - ( IGNORE_PIXELS * 2 ))

#define START_BUTTON TFC_PUSH_BUTTON_0_PRESSED
#define STOP_BUTTON TFC_PUSH_BUTTON_1_PRESSED

struct Command{
	float steerValue;
	float speedL;
	float speedR;
	int stop;
};

void delay(int);

#endif /* COMMON_H_ */
