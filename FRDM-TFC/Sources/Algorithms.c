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

#define START_PIXEL 10
#define STOP_PIXEL 118



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
   //TFC_SetServo(0,diff - 1); //Adjusts servo accordingly
   delay(2); //Allows servo time to move
}

void algo_two(){
	int i;
	
	double sum = 0;
	float mid_point = ( STOP_PIXEL - START_PIXEL ) / 2 + START_PIXEL;
	
	 if( LineScanImageReady == 1 ){
	    LineScanImageReady = 0;
		for( i = START_PIXEL; i < STOP_PIXEL; i++ ){
			int offset = mid_point - i;
			
			if(offset == 0) offset = 1;
			double scale = mid_point / offset;
			
			if(LineScanImage0[i] == 0) {
				sum += scale * 1;
			} else {
				sum += scale * ((4096.0f / (float)LineScanImage0[i]) / 4096.0f);
			}
			
		//	printf("%d,", sum);
			//sum += ((float)LineScanImage0[i] / 4096) / (float)( i - mid_point);
		//	if(sum>2000000000){
		//		printf("Stop");
		//		break;
		//	}
		//	printf("%d,", (int)i );
		//	printf("%d\n",(int)sum );
		}
	 }
	 sum = sum / 64;
	 TFC_SetServo( 0, sum * 500 );
	 //printf( "\nLong Sum: %d\n", (int)sum );
	 //if(sum>0){
	//	 printf("HEY\n");
	 //}
	// else{
	//	 printf("HELLO\n");
	// }
	// printf( "Sum: %d\n", (int)(sum/50000000000000) );
	 delay(5);
	 
}
