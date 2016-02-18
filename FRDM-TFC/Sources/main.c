#include "derivative.h" /* include peripheral declarations */
#include "TFC\TFC.h"
#include "Algorithms.h"
#include "Common.h"
#include "InitCar.h"
#include "Camera.h"
#include "stdlib.h"
#include "Control.h"
#include "SerialComms.h"


// TODO Comment all the things
int main(){
	
	// Initialise program
	init();		
	
	// Used to indicate stopping
	int run = 1;
	
	int first = 1;
	int sensitivity;
	float speed;
	
	// Pointers for referencing data
	uint16_t* cameraData;
	struct Command command;
	command.speedL = 0.0;
	command.speedR = 0.0;
	command.steerValue = 0.0;
	command.stop = 0;
	
	int i;
	TFC_SetLineScanExposureTime(25000);
	
	
	while(1){
		while(1){
			while(!LineScanImageReady);
			LineScanImageReady = 0;
			printf("|");
			for( i = 16; i < 112; i++){
				char out = LineScanImage0[i] >> 10;
				
				if(out == 0) {
					printf(" ");								
				} else if(out == 1) {
					printf("%c", 176);								
				} else if(out == 2) {
					printf("%c", 177);
				} else {
					printf("%c", 178);
				}
			}
			printf("|\r\n");
			//delay(50);
			
			// Waits till the start button is pressed
			if(START_BUTTON) break;		
		}
	
		// Waits till the start button is pressed
		while(!START_BUTTON);	
		
		sensitivity = getSensitivity();
		speed = getSpeed();
		TFC_HBRIDGE_ENABLE;
		
		printf("{\"version\":0,\"sensitivity\":%d,\"speed\":%d,\"data\":[", sensitivity, (int)(speed*100));
		
		while(run){
			
			if(first){	
				first = 0;
			} else {
				printf(",");
			}
			
			// Reads the data from the camera
			cameraData = getCamera();	
			
			// Sets the command based on the camera data and returns whether to stop or not
			run = getCommand( cameraData, &command, sensitivity, speed );	
			
			// Debug mode
			if(0){	
				
				// Sends the command and camera data over serial
				print(command, cameraData);
				
				// Run mode	
			} else {	
				
				// Sends the command and camera data over serial to be stored
				print(command, cameraData);
				
				// Applies the command to the car
				apply(command);
				
			}

			// Frees the malloc'd memory for cameraData and command
			free(cameraData);
			
			// Exits the loop if the stop button is pressed
			if(STOP_BUTTON) break;
		}
		
		TFC_HBRIDGE_DISABLE;
		
		printf("]}");
		
	}
	
	return 0;
}
