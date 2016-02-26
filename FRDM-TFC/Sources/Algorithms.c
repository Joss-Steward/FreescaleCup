/*
 * AlgoOne.c
 *
 *  Created on: Sep 17, 2015
 *      Author: Jared
 */

#include "derivative.h" /* include peripheral declarations */
#include "TFC\TFC.h"
#include "Common.h"
#include "Math.h"
#include "stdlib.h"

struct sideInfo{
	float Sum;
	int Changes;
};

struct sideInfo findSideInfo( int start, int stop, int sensitivity, uint8_t* pixels ){
	struct sideInfo sideInfo;
	sideInfo.Sum = 0.0;
	sideInfo.Changes = 0;
	
	int i;
	int avg_1 = 0;
	int avg_2 = 0;
	
	for(i = start; i < stop; i++){
		sideInfo.Sum += pixels[i];
	    avg_1 = ( pixels[i - 2] + pixels[i - 1] + pixels[i] ) / 3;
	    avg_2 = ( pixels[i] + pixels[i + 1] + pixels[i + 2] ) / 3;
	    
	    if( (avg_2 < ( avg_1 - sensitivity )) || (avg_2 > ( avg_1 + sensitivity )) ){
	    	sideInfo.Changes++;
	    }
	}
	
	sideInfo.Sum /= (float)(stop - start);
	return sideInfo;
}

float calcTurn( struct sideInfo left, struct sideInfo right ){
	float difference = (float)abs(left.Sum - right.Sum);
	difference /= DIFFDIV;
	            
	// Default to straight ahead
	float steering_value = 0.0;

	if(left.Sum < right.Sum){
		steering_value = 0.5 * difference;
	    if(steering_value > .7)steering_value = .7;
	} else {
	    steering_value = -0.5 * difference;
	    if(steering_value < -.7)steering_value = -.7;
	}

	return steering_value;
}

int getCommand( uint8_t* cameraData, struct Command* command, int sensitivity, float speed ){
	
	struct sideInfo right;
	right.Sum = 0.0;
	right.Changes = 0;
	struct sideInfo left;
	left.Sum = 0.0;
	left.Changes = 0;
	
	left = findSideInfo( START_PIXEL, (int)64, sensitivity, cameraData );
	right = findSideInfo( (int)64, STOP_PIXEL, sensitivity, cameraData ); 
	
	command->steerValue = calcTurn(left, right);
	
	if(command->stop == 0) {
		command->stop = ( right.Changes >= 1 && left.Changes >= 1 );
		command->speedL = speed;
		command->speedR = speed;
	} else {
		command->speedL = fmax(0, command->speedL - (speed * SLOW_AMOUNT) );
		command->speedR = fmax(0, command->speedR - (speed * SLOW_AMOUNT) );
	}     
	
	if( command->speedL  <= 0 && command->speedR <= 0 )return 0;
	
	return 1;
}

int getSensitivity(){
	return( (int)( SENSITIVITY * ( TFC_ReadPot(0) + 1 ) ) );
}

float getSpeed(){
	return( ( SPEED * ( TFC_ReadPot(1) + 1 ) ) );
}

void refineData( uint8_t* cameraData, uint8_t* avgCamera, uint8_t* runningAvg, int period){
	int i;
	
	// If it is the end of a servo update period, calculate the average for the period and the running average 
	if(period == 0){
		for( i = 0; i < USED_PIXELS; i++){
			avgCamera[i] += cameraData[i];
			avgCamera[i] /= CAMERA_CYCLES_PER_UPDATE;
			runningAvg[i] = (runningAvg[i] + avgCamera[i])/2;
		}
	} else {
		// Adds the camera
		for( i = 0; i < USED_PIXELS; i++){
			avgCamera[i] += cameraData[i];
		}
	}
}

void clear( uint8_t* arr, int size ){
	int i;
	for( i = 0; i < size; i++){
		arr[i] = 0;
	}
}
