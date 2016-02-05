/*
 * Control.c
 *
 *  Created on: Feb 4, 2016
 *      Author: Jared
 */
#include "Common.h"
#include "TFC\TFC.h"

void apply(struct Command command){
	TFC_SetMotorPWM(command.speedL, command.speedR);
	TFC_SetServo(0, command.steerValue);
}
