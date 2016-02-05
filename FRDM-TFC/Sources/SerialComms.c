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


void print(struct Command command, uint8_t* cameraData){
	
	printf("{\"rightMotor\":%f,", command.speedR );
	printf("\"leftMotor\":%f,", command.speedL );
	printf("\"steering\":%f,", command.steerValue );
	printf("\"stop\":%d,", command.stop );
	printf("\"camera\":[");
	
	int i;
	for( i = 0; i < USED_PIXELS - 1; i++){
		printf("%d,", cameraData[i] );
	}
	
	printf("%d]}", cameraData[USED_PIXELS]);
	
	// TODO TFC_TASK() ?
		
}

