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

#define START_PIXEL 10
#define STOP_PIXEL 118


int stop_car(){
	
	while(!LineScanImageReady);
	LineScanImageReady = 0;
	
	int i;
	int width = 0;
	int start = START_PIXEL;
	int stop = 0;
	
	for( i = START_PIXEL; i < STOP_PIXEL; i++ ){
		if( LineScanImage0[i] < ( LineScanImage0[i-1] - 500 ) ){ 
			start = i;
		}
		if( LineScanImage0[i] > ( LineScanImage0[i-1] + 500 ) ){
			stop = i;
		}
		width = stop - start;
		if( width > 20 ){
			return 1;
		}
	}
	return 0;
}

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
	//double avg_left = 0, avg_right = 0;
	unsigned int numberOfTries = 0;
	int stop_algo = 0;
	
    while(1) {
        TFC_Task();

        if(LineScanImageReady){
        	numberOfTries++;
            float mid_point = (STOP_PIXEL - START_PIXEL) / 2 + START_PIXEL;
            LineScanImageReady = 0;
            
            double left_sum = 0;
            double right_sum = 0;

            int i = 0;
            
            int avg_1 = 0;
            int avg_2 = 0;
            

            int num_changes_left = 0;
            int num_changes_right = 0;
            float sensitivity = TFC_ReadPot(0);
            int threshold = (int)(1000 * sensitivity);
            
            for(i = START_PIXEL; i < mid_point; i++){
                left_sum += LineScanImage0[i];
                avg_1 = ( LineScanImage0[i - 2] + LineScanImage0[i - 1] + LineScanImage0[i] ) / 3;
                avg_2 = ( LineScanImage0[i] + LineScanImage0[i + 1] + LineScanImage0[i + 2] ) / 3;
                if( avg_2 < ( avg_1 - threshold ) ){
                	num_changes_left++;
                }
                if( avg_2 > ( avg_1 + threshold ) ){
                	num_changes_left++;
                }
            }

            for(i = (int)mid_point; i < STOP_PIXEL; i++){
                right_sum += LineScanImage0[i];
                avg_1 = ( LineScanImage0[i - 2] + LineScanImage0[i - 1] + LineScanImage0[i] ) / 3;
                avg_2 = ( LineScanImage0[i] + LineScanImage0[i + 1] + LineScanImage0[i + 2] ) / 3;
                if( avg_2 < ( avg_1 - threshold ) ){
                	num_changes_right++;
                }
                if( avg_2 > ( avg_1 + threshold ) ){
                    num_changes_right++;
                }
            }
            
            if( num_changes_right >= 1 && num_changes_left >= 1 ){
            	stop_algo = 1;
            }
            
            left_sum /= mid_point - START_PIXEL;
            right_sum /= STOP_PIXEL - mid_point;
            double diff = (double)abs(left_sum - right_sum);

            diff /= 400;
            
            printf( "%d, %d, %d, %d, %d:%d\n", (int)left_sum, (int)right_sum, (int)diff, threshold, num_changes_left, num_changes_right );
            
            // Default to straight ahead
            double steering_value = 0.0;

    		if(left_sum < right_sum){
    			steering_value = 0.5 * diff;
    			if(steering_value > .7)steering_value = .7;
    		} else {
    			steering_value = -0.5 * diff;
    			if(steering_value < -.7)steering_value = -.7;
    		}

            TFC_SetServo(0, steering_value);
        }
        
        if(stop_algo == 0) {
        	TFC_SetMotorPWM(0.30, 0.30);
        } else {
        	double motor = (5000 - stop_algo) / 5000;
        	TFC_SetMotorPWM(motor, motor);
        	stop_algo++;
        }
        if(TFC_PUSH_BUTTON_1_PRESSED) break;
        
        if(stop_algo > 5000) break;
    }
}

