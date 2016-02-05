#include "derivative.h" /* include peripheral declarations */
#include "TFC\TFC.h"
#include "Algorithms.h"
#include "Common.h"
#include "InitCar.h"
#include "Camera.h"
#include "stdlib.h"

#define START_BUTTON TFC_PUSH_BUTTON_0_PRESSED
#define STOP_BUTTON TFC_PUSH_BUTTON_1_PRESSED

// TODO Comment all the things
int main(){
	
	init();		// Initialise program
	
	int run = 1;	// Used to indicate stopping
	
	// Pointers for referencing data
	uint8_t* cameraData;
	struct Command* command;
	
	
	while(1){

		// Waits till the start button is pressed
		while(!START_BUTTON);	
		
		while(run){
			
			// Reads the data from the camera
			cameraData = getCamera();	
			
			// Sets the command based on the camera data and returns whether to stop or not
			run = getCommand( cameraData, command );	
			
			// Debug mode
			if(TFC_GetDIP_Switch()){	
				
				// Sends the formated command and camera data over serial
				print(command, cameraData);
				
				// Run mode	
			} else {	
				
				// Sends the unformatted command and camera data over serial to be stored
				save(command, cameraData);
				
				// Applies the command to the car
				apply(command);
				
			}

			// Frees the malloc'd memory for cameraData and command
			free(cameraData);
			free(command);
			
			// Exits the loop if the stop button is pressed
			if(STOP_BUTTON) break;
		}
		
	}
	
	return 0;
}





//
//
//
//void printCamera() {
//    int t = 0;
//
//    while(1){
//        TFC_Task();
//        if(LineScanImageReady == 1) {
//            LineScanImageReady = 0;
//            printf("\r\n");
//            printf("L:");
//
//            int i;
//            for(i = 0; i < 128; i++)
//            {
//                printf("%X", LineScanImage0[i]);
//                if(i == 127)
//                    printf("\r\n");
//                else
//                    printf(",");
//            }
//        }
//        if(TFC_PUSH_BUTTON_1_PRESSED)break;
//    }
//}
//

