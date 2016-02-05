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
	uint8_t* cameraData;
	struct Command command;
	command.speedL = 0.0;
	command.speedR = 0.0;
	command.steerValue = 0.0;
	command.stop = 0;
	
	while(1){

		// Waits till the start button is pressed
		while(!START_BUTTON);	
		
		sensitivity = getSensitivity();
		speed = getSpeed();
		TFC_HBRIDGE_ENABLE;
		
		printf("{\"version\":0,\"sensitivity\":%d,\"speed\":%f,\"data\":[", sensitivity, speed);
		
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
			if(TFC_GetDIP_Switch()){	
				
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
