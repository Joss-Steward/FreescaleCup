#include "derivative.h" /* include peripheral declarations */
#include "TFC\TFC.h"
#include "Algorithms.h"
#include "Common.h"
#include "InitCar.h"
#include "Camera.h"
#include "stdlib.h"

// TODO Comment all the things
int main(){
	
	init();		// Initialise program
	
	// Declares variables
	int run = 1;
	uint8_t* cameraData;
	struct Command* command;
	
	
	while(1){

		while(!TFC_PUSH_BUTTON_0_PRESSED);	// Waits till the start button is pressed
		
		while(run){
			cameraData = getCamera();	// Reads the data from the camera
			run = getCommand( cameraData, command );	// Sets the command based on the camera data and returns whether to stop or not
			
			if(TFC_GetDIP_Switch()){
				
				print(command, cameraData);
				
			} else {
				
				store(command, cameraData);
				apply(command);
				
			}

			free(cameraData);
			free(command);
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

