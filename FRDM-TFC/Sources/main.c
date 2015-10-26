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
		 * This gives us time to set the DIP switches and etc */
		TFC_BAT_LED0_ON; // These lights will indicate that we're waiting
		TFC_BAT_LED1_ON;
		TFC_BAT_LED2_ON;
		TFC_BAT_LED3_ON;
		while(!TFC_PUSH_BUTTON_0_PRESSED);
	
		/* Then set the operating mode based on the DIP switch */
		switch(TFC_GetDIP_Switch()) {
			default:
			case 0:
				TFC_BAT_LED0_OFF;
				TFC_BAT_LED1_OFF;
				TFC_BAT_LED2_OFF;
				TFC_BAT_LED3_OFF;
				TFC_HBRIDGE_ENABLE;
				// In this mode, we run the algorithm
				algo_one();
				break;
			case 1:
				TFC_BAT_LED0_ON;
				TFC_BAT_LED1_OFF;
				TFC_BAT_LED2_OFF;
				TFC_BAT_LED3_OFF;
				// In this mode, we print the number of changes on each side
				algo_one_debug(1);
				break;
			case 2:
				// In this mode, we drive forward a little bit.
				TFC_BAT_LED0_OFF;
				TFC_BAT_LED1_ON;
				TFC_BAT_LED2_OFF;
				TFC_BAT_LED3_OFF;
				algo_one_debug(2);
				break;
			case 3:
				// In this mode, we drive forward until the input is below a threshold
				TFC_BAT_LED0_ON;
				TFC_BAT_LED1_ON;
				TFC_BAT_LED2_OFF;
				TFC_BAT_LED3_OFF;
				algo_one_debug(3);
				break;
			case 4:
				TFC_BAT_LED0_OFF;
				TFC_BAT_LED1_OFF;
				TFC_BAT_LED2_ON;
				TFC_BAT_LED3_OFF;
				algo_one_debug(4);
				break;
			case 5:
				TFC_BAT_LED0_ON;
				TFC_BAT_LED1_OFF;
				TFC_BAT_LED2_ON;
				TFC_BAT_LED3_OFF;
				algo_one_debug(5);
				break;
			case 6:
				TFC_BAT_LED0_OFF;
				TFC_BAT_LED1_ON;
				TFC_BAT_LED2_ON;
				TFC_BAT_LED3_OFF;
				algo_one_debug(6);
				break;
			case 7:
				TFC_BAT_LED0_ON;
				TFC_BAT_LED1_ON;
				TFC_BAT_LED2_ON;
				TFC_BAT_LED3_OFF;
				algo_one_debug(7);
				break;
			case 14:
				TFC_BAT_LED0_OFF;
				TFC_BAT_LED1_ON;
				TFC_BAT_LED2_ON;
				TFC_BAT_LED3_ON;
				break;
			case 15:
				TFC_BAT_LED0_ON;
				TFC_BAT_LED1_ON;
				TFC_BAT_LED2_ON;
				TFC_BAT_LED3_ON;
				// In this mode, we simply read out the camera forever
				printCamera();
				break;
		}
	
		TFC_SetServo(0,0);
		TFC_SetMotorPWM(0, 0);
		TFC_BAT_LED0_OFF;
		TFC_BAT_LED1_OFF;
		TFC_BAT_LED2_OFF;
		TFC_BAT_LED3_OFF;
		TFC_HBRIDGE_DISABLE;
    }
    return 0;
}
