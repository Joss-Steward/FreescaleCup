/*
 * Common.h
 *
 *  Created on: Oct 3, 2015
 *      Author: Jared
 */

#ifndef COMMON_H_
#define COMMON_H_

#define IGNORE_PIXELS 8
#define USED_PIXELS 128 - ( IGNORE_PIXELS * 2 )

struct Command{
	float steerValue;
	float speedL;
	float speedR;
};

void delay(int);

#endif /* COMMON_H_ */
