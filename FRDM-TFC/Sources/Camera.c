/*
 * Camera.c
 *
 *  Created on: Feb 3, 2016
 *      Author: Jared
 */

#include "TFC\TFC.h"
#include "Common.h"
#include "stdlib.h"



uint8_t* getCamera(){
	uint8_t* cameraData = (uint8_t*) malloc( 8 * USED_PIXELS );
	while(!LineScanImageReady);
	int i;
	for( i = 0; i < USED_PIXELS; i++){
		cameraData[i] = LineScanImage0[ i + IGNORE_PIXELS ];
	}
	return cameraData;
}

