/*
 * AlgoOne.h
 *
 *  Created on: Sep 17, 2015
 *      Author: Jared
 */

#ifndef ALGOONE_H_
#define ALGOONE_H_

#include "Common.h"

int getCommand(uint8_t*, struct Command*, int, float);
int getSensitivity();
float getSpeed();

void refineData( uint8_t*, uint8_t*, uint8_t*, int);
void clear( uint8_t*, int);

#endif /* ALGOONE_H_ */
