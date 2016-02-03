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

#define START_PIXEL 15
#define STOP_PIXEL 113
#define MID_POINT (((STOP_PIXEL-START_PIXEL)/2)+START_PIXEL)
#define LEFT_PIXELS MID_POINT-START_PIXEL
#define RIGHT_PIXELS STOP_PIXEL-MID_POINT 
#define DIFFDIV 1000
#define SENSITIVITY 1000
#define STOP_CYCLES 5000
#define SPEED .50


struct sideInfo{
	double Sum;
	int Changes;
};

int determineSensitivity(){
	return( (int)( SENSITIVITY * ( TFC_ReadPot(0) + 1 ) ) );
}

float determineSpeed(){
	return( ( SPEED * ( TFC_ReadPot(1) + 1 ) ) );
}

struct sideInfo findSideInfo( int start, int stop, int threshold ){
	struct sideInfo sideInfo;
	sideInfo.Sum = 0.0;
	sideInfo.Changes = 0;
	
	int i;
	int avg_1 = 0;
	int avg_2 = 0;
	for(i = start; i < stop; i++){
		sideInfo.Sum += LineScanImage0[i];
	    avg_1 = ( LineScanImage0[i - 2] + LineScanImage0[i - 1] + LineScanImage0[i] ) / 3;
	    avg_2 = ( LineScanImage0[i] + LineScanImage0[i + 1] + LineScanImage0[i + 2] ) / 3;
	    
	    if( (avg_2 < ( avg_1 - threshold )) || (avg_2 > ( avg_1 + threshold )) ){
	    	sideInfo.Changes++;
	    }
	}
	
	sideInfo.Sum /= (double)(stop - start);
	return(sideInfo);
}

void setTurn( struct sideInfo left, struct sideInfo right ){
	double difference = (double)abs(left.Sum - right.Sum);
	difference /= DIFFDIV;
	            
	// Default to straight ahead
	double steering_value = 0.0;

	if(left.Sum < right.Sum){
		steering_value = 0.5 * difference;
	    if(steering_value > .7)steering_value = .7;
	} else {
	    steering_value = -0.5 * difference;
	    if(steering_value < -.7)steering_value = -.7;
	}

	TFC_SetServo(0, steering_value);
}

double calcTurn( struct sideInfo left, struct sideInfo right ){
	double difference = (double)abs(left.Sum - right.Sum);
	difference /= DIFFDIV;
	            
	// Default to straight ahead
	double steering_value = 0.0;

	if(left.Sum < right.Sum){
		steering_value = 0.5 * difference;
	    if(steering_value > .7)steering_value = .7;
	} else {
	    steering_value = -0.5 * difference;
	    if(steering_value < -.7)steering_value = -.7;
	}

	return(steering_value);
}

void algo_one_debug(int mode){
	int stop = 0;
	int threshold = 0;
	float speed = 0;
	double steer = 0;
	double motor = 0;
	
	while(1) {
		struct sideInfo right;
		right.Sum = 0.0;
		right.Changes = 0;
		struct sideInfo left;
		left.Sum = 0.0;
		left.Changes = 0;
		
		TFC_Task();

		threshold = determineSensitivity();
		speed = determineSpeed();
		
		if(LineScanImageReady){
			LineScanImageReady = 0;
			left = findSideInfo( START_PIXEL, MID_POINT, threshold );
			right = findSideInfo( (int)MID_POINT, STOP_PIXEL, threshold ); 
			
			printf("%d %d\n", (int)left.Sum, (int)right.Sum);
			
			if(stop == 0)
				stop = ( right.Changes >= 1 && left.Changes >= 1 );
		}
		
		steer = calcTurn(left, right);
		
		if(stop == 0) {
		} else {
			motor = speed * ((STOP_CYCLES - stop) / STOP_CYCLES);
			stop++;
		}     
		
		if(TFC_PUSH_BUTTON_1_PRESSED) break;
		
		if(stop > STOP_CYCLES) break;
		
		if(mode == 1){
			printf("%d %d\n", left.Changes, right.Changes);
		}
		if(mode == 2){
			printf("%d %d\n", (int)left.Sum, (int)right.Sum);		
		}
		if(mode == 3){
			printf("%d %d\n", threshold, (int)(speed*1000000) );
		}
		if(mode == 4){
			printf("%d\n", (int)(motor*1000000) );
		}
		if(mode == 5){
			printf("%d\n", (int)(steer*1000000.0) );		
		}
		if(mode == 6){
			printf("%d\n", stop);
		}
		if(mode == 7){
			printf("Left Average = %d\n", (int)left.Sum);
			printf("Left Changes = %d\n", left.Changes);
			printf("Right Average = %d\n", (int)right.Sum);
			printf("Right Changes = %d\n", right.Changes);
			printf("Threshold = %d\n", threshold);
			printf("Speed * 10^6 = %d\n", (int)(speed*1000000) );
			printf("Modified Speed * 10^6 = %d\n", (int)(motor*1000000) );
			printf("Turn * 10^6 = %d\n", (int)(steer*1000000.0) );
			printf("Stop = %d\n", stop);
			delay(1000);
		}
	}
	
	//Dump Data
	
	
}


void algo_one() {
	int stop = 0;
	int threshold = 0;
	float speed = 0;
	
    while(1) {
    	struct sideInfo right;
    	right.Sum = 0.0;
    	right.Changes = 0;
    	struct sideInfo left;
    	left.Sum = 0.0;
    	left.Changes = 0;
    	
        TFC_Task();

        threshold = determineSensitivity();
        speed = determineSpeed();
        
        if(LineScanImageReady){
            LineScanImageReady = 0;
            left = findSideInfo( START_PIXEL, MID_POINT, threshold );
            right = findSideInfo( (int)MID_POINT, STOP_PIXEL, threshold ); 
            
            printf("%d %d\n", (int)left.Sum, (int)right.Sum);
            
            if(stop == 0)
            	stop = ( right.Changes >= 1 && left.Changes >= 1 );
        }
        
        setTurn(left, right);
        
        if(stop == 0) {
        	TFC_SetMotorPWM(speed, speed);
        } else {
        	double motor = speed * ((STOP_CYCLES - stop) / STOP_CYCLES);
        	TFC_SetMotorPWM(motor, motor);
        	stop++;
        }     
        
        if(TFC_PUSH_BUTTON_1_PRESSED) break;
        
        if(stop > STOP_CYCLES) break;
    }
    //Dump data
    
}

