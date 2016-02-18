/*
 * Camera.c
 *
 *  Created on: Feb 3, 2016
 *      Author: Jared
 */

#include "TFC\TFC.h"
#include "Common.h"
#include "stdlib.h"



uint16_t* getCamera(){
	uint16_t* cameraData = (uint16_t*) malloc( sizeof(uint16_t) * 128 );
	while(!LineScanImageReady);
	int i;
	for( i = 0; i < 128; i++){
		cameraData[i] = (uint16_t)LineScanImage0[ i ];
	}
	LineScanImageReady = 0;
	return cameraData;
}

