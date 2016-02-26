/*
 * Camera.c
 *
 *  Created on: Feb 3, 2016
 *      Author: Jared
 */

#include "TFC\TFC.h"
#include "Common.h"
#include "stdlib.h"



void getCamera(uint8_t* cameraData){
	while(!LineScanImageReady);
	int i;
	for( i = 0; i < 128; i++){
		cameraData[i] = (uint8_t)(LineScanImage0[ i ]>>4);
	}
	LineScanImageReady = 0;
}

