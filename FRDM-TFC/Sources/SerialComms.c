/*
 * SerialComms.c
 *
 *  Created on: Feb 4, 2016
 *      Author: Jared
 */
#include "TFC\TFC.h"
#include "stdlib.h"
#include "Common.h"
#include "string.h"


void print(struct Command command, uint16_t* cameraData){
	
	// Prints the command data for json and starts the camera data json
	printf("{\"rightMotor\":%d,", (int)( command.speedR * 100.0 ) );
	printf("\"leftMotor\":%d,", (int)( command.speedL * 100.0 ) );
	printf("\"steering\":%d,", (int)( command.steerValue * 100.0 ) );
	printf("\"stop\":%d,", command.stop );
	printf("\"camera\":[");
	
	// Prints the camera data
	int i;
	for( i = 0; i < USED_PIXELS - 1; i++){
		printf("%d,", cameraData[i] );
	}
	
	// Adds the last camera pixel we are looking at with the closing square bracket
	printf("%d]}", cameraData[USED_PIXELS]);
	
}

