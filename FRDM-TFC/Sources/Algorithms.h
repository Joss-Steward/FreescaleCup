/*
 * AlgoOne.h
 *
 *  Created on: Sep 17, 2015
 *      Author: Jared
 */

#ifndef ALGOONE_H_
#define ALGOONE_H_

#include "Common.h"

int getCommand(uint16_t*, struct Command*, int, float);
int getSensitivity();
float getSpeed();


void algo_one();
void algo_one_debug(int);

#endif /* ALGOONE_H_ */
