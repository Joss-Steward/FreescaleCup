/*
 * Control.c
 *
 *  Created on: Feb 4, 2016
 *      Author: Jared
 */
#include "Common.h"
#include "TFC\TFC.h"

void apply(struct Command command){
	
	// Sets the motors to the calculated values
	TFC_SetMotorPWM(command.speedL, command.speedR);
	
	// Sets the steering to the calculated value
	TFC_SetServo(0, command.steerValue);
}
