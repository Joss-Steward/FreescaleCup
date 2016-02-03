#include "derivative.h" /* include peripheral declarations */
#include "TFC\TFC.h"
#include "Algorithms.h"
#include "Common.h"

#define DEL 50
#define START_PIXEL 10
#define STOP_PIXEL 118


void printCamera() {
    int t = 0;

    while(1){
        TFC_Task();
        if(LineScanImageReady == 1) {
            LineScanImageReady = 0;
            printf("\r\n");
            printf("L:");

            int i;
            for(i = 0; i < 128; i++)
            {
                printf("%X", LineScanImage0[i]);
                if(i == 127)
                    printf("\r\n");
                else
                    printf(",");
            }
        }
        if(TFC_PUSH_BUTTON_1_PRESSED)break;
    }
}


int main(void){
    TFC_Init();
    
    while(1){
		TFC_SetMotorPWM(0, 0);
		TFC_HBRIDGE_DISABLE;
	
		/* After power on, Wait for a button press before doing anything.
		 * This gives us time to set the DIP switches and etc 
		 */
		TFC_BAT_LED0_ON; // These lights will indicate that we're waiting
		TFC_BAT_LED1_ON;
		TFC_BAT_LED2_ON;
		TFC_BAT_LED3_ON;
		while(!TFC_PUSH_BUTTON_0_PRESSED);
	
		// Set the operating mode based on the DIP switch 
		setMode( TFC_GetDIP_Switch() );
	
		TFC_SetServo(0,0);
		TFC_SetMotorPWM(0, 0);
		TFC_BAT_LED0_OFF;
		TFC_BAT_LED1_OFF;
		TFC_BAT_LED2_OFF;
		TFC_BAT_LED3_OFF;
    }
    return 0;
}

void setMode(int mode){
	switch(mode) {
		default:
			
		case 0:
			TFC_BAT_LED0_OFF;
			TFC_BAT_LED1_OFF;
			TFC_BAT_LED2_OFF;
			TFC_BAT_LED3_OFF;
			TFC_HBRIDGE_ENABLE;
			// In this mode, we run the algorithm
			algo_one();
			TFC_HBRIDGE_DISABLE;
			break;
		case 1:
			TFC_BAT_LED0_ON;
			TFC_BAT_LED1_OFF;
			TFC_BAT_LED2_OFF;
			TFC_BAT_LED3_OFF;
			// In this mode, we run live debug
			liveDebug();
			break;
			
	}
}
