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

void algo_one(){
    int i;

    //Variables for calculating average light levels
    long int sum = 0;
    int avg;

    //Array recording if pixel light level is below average
    int belowAvg[ STOP_PIXEL - START_PIXEL + 1 ];

    //Variables for calculating center of the pixels below average and difference from center of all pixels
    int sumBelowAvg = 0;
    int totBelowAvg = 0;
    int centerBelowAvg;
    int center = ( STOP_PIXEL - START_PIXEL + 1) / 2;
    int diffCenter;
    float diff;

    if( LineScanImageReady == 1 ){
        LineScanImageReady = 0;

        //Adds each pixels light value to the total
        for( i = START_PIXEL; i < STOP_PIXEL; i++ ){
            sum += LineScanImage0[i];
        }

        //Calculates average light value
        avg = sum / ( STOP_PIXEL - START_PIXEL );

        //Calculates which pixels are below average and fills the array accordingly
        for( i = START_PIXEL; i < STOP_PIXEL; i++ ){

            //If pixel is below average sets corresponding array element to 1
            if( LineScanImage0[i] < avg ){
                belowAvg[ i - START_PIXEL ] = 1;
            }

            //If pixel is above average sets corresponding array element to 0
            else {
                belowAvg[ i - START_PIXEL ] = 0;
            }
        }

        //Outputs the array over serial
        for( i = START_PIXEL; i < STOP_PIXEL; i++ ){
            printf( "%d", belowAvg[ i - START_PIXEL ] );
        }
        printf( "\r\n" );
    }

    //Adds all the pixels below average
    for( i = 0; i < STOP_PIXEL - START_PIXEL + 1; i++){
        if( belowAvg[i] ){
            totBelowAvg++;
            sumBelowAvg += i;
        }
    }

    centerBelowAvg = sumBelowAvg / totBelowAvg; //calculates the center of the below average pixels
    diffCenter = center - centerBelowAvg;  //Clalculates the difference of the center of the below average pixels and all the pixels
    diff = (float)( center - diffCenter ) / (float)center; //Calculates "percent" difference. Ranges from 0 - 2
    TFC_SetServo(0,diff - 1); //Adjusts servo accordingly
    delay(2); //Allows servo time to move
}

void algo_two(){
    float mid_point = ( STOP_PIXEL - START_PIXEL ) / 2 + START_PIXEL;

    if( LineScanImageReady == 1 ){
        LineScanImageReady = 0;
        
        int i;
        double sum = 0.0f;
        for( i = START_PIXEL; i < STOP_PIXEL; i++ ){
            int offset = mid_point - i;

            if(offset == 0) offset = 1;
            double scale = mid_point / offset;

            if(LineScanImage0[i] == 0) {
                sum += scale * 1;
            } else {
                sum += scale * ((1.0f / (float)LineScanImage0[i]));
            }
        }
    
        sum = (double)sum;
        TFC_SetServo( 0, sum);
    }
}

void algo_three() {
	double avg_left = 0, avg_right = 0;
	unsigned int numberOfTries = 0;
	
    while(1) {
        TFC_Task();

        if(LineScanImageReady){
        	numberOfTries++;
            float mid_point = (STOP_PIXEL - START_PIXEL) / 2 + START_PIXEL;
            LineScanImageReady = 0;
            
            double left_sum = 0;
            double right_sum = 0;

            int i = 0;

            for(i = START_PIXEL; i < mid_point; i++){
                left_sum += LineScanImage0[i];
            }

            for(i = (int)mid_point; i < STOP_PIXEL; i++){
                right_sum += LineScanImage0[i];
            }
            
            left_sum /= mid_point - START_PIXEL;
            right_sum /= STOP_PIXEL - mid_point;
            double diff = (double)abs(left_sum - right_sum);

            diff /= 400;
            
            printf( "%d, %d, %d\n", (int)left_sum, (int)right_sum, (int)diff );
            
            // Default to straight ahead
            double steering_value = 0.0;

    		if(left_sum < right_sum){
    			steering_value = 0.5 * diff;
    		} else {
    			steering_value = -0.5 * diff;
    		}

            TFC_SetServo(0, steering_value);
            
            if(left_sum < (0.90 * avg_left) && right_sum < (0.90 * avg_right)) {
            	break;            	
            } else {
            	avg_left += left_sum;
            	avg_left /= numberOfTries;
            	
            	avg_right += right_sum;
            	avg_right /= numberOfTries;
            }
        }
        
        TFC_SetMotorPWM(0.35, 0.35);
        if(TFC_PUSH_BUTTON_1_PRESSED) break;
    }
}

int stop_car(){
	
	while(!LineScanImageReady);
	LineScanImageReady = 0;
	
	int i;
	int black_spots = 0;
	
	for( i = START_PIXEL; i < STOP_PIXEL - 5; i++ ){
		if( ( LineScanImage0[i] < ( LineScanImage0[i-1] - 500 ) ) || ( LineScanImage0[i] < ( LineScanImage0[i-2] - 1000 ) ) ){ 
			black_spots++;
		}
	}
	if(black_spots > 3){
		return 1;
	}
	else return 0;
}
