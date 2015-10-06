#include "derivative.h" /* include peripheral declarations */
#include "TFC\TFC.h"
#include "Algorithms.h"
#include "Common.h"

#define DEL 50
#define START_PIXEL 10
#define STOP_PIXEL 118


void forwardFull(){
    TFC_HBRIDGE_ENABLE;
    TFC_SetServo(0,-.15);
    TFC_SetMotorPWM(1,1);
    delay(30);
    TFC_SetMotorPWM(0,0);
    TFC_HBRIDGE_DISABLE;
}

void printCamera() {
    int t = 0;

    while(1){
        TFC_Task();
        if(LineScanImageReady == 1) {
            LineScanImageReady = 0;
            printf("\r\n");
            printf("L:");
            if(t == 0)
                t = 3;
            else
                t--;

            TFC_SetBatteryLED_Level(t);

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
    }
}


void runToLine(){

    long int sum;
    int avg = 0;
    int i;



    while(1){
        TFC_Task();
        sum = 0;
        TFC_SetServo(0,-.15);
        if( LineScanImageReady == 1 ){
            LineScanImageReady = 0;

            //Adds each pixels light value to the total
            for( i = START_PIXEL; i < STOP_PIXEL; i++ ){
                sum += LineScanImage0[i];
            }

            //Calculates average light value
            avg = sum / ( STOP_PIXEL - START_PIXEL );
        }
        printf("\n%X", avg);
        if(avg>>11&&0x01){
            TFC_SetMotorPWM(.3, .3);
        }
        else{
            TFC_SetMotorPWM(0, 0);
            TFC_HBRIDGE_DISABLE;
            while(1);
        }
    }
}

int main(void){
    TFC_Init();
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
    switch(TFC_GetDIP_Switch()&0x07) {
        default:
        case 0:
        	TFC_BAT_LED0_OFF;
            TFC_BAT_LED1_OFF;
            TFC_BAT_LED2_OFF;
            TFC_BAT_LED3_OFF;
            // In the default mode, simply read out the camera forever
            printCamera();
            break;
        case 1:
            TFC_BAT_LED0_ON;
            TFC_BAT_LED1_OFF;
            TFC_BAT_LED2_OFF;
            TFC_BAT_LED3_OFF;
            TFC_HBRIDGE_ENABLE;
            // In this mode, we will actually run the analysis and drive.
            while(1) {
                TFC_Task();
                algo_one();
                TFC_SetMotorPWM(.3, .3);
                if(TFC_PUSH_BUTTON_1_PRESSED)break;
                if(stop_car()){
                	delay(5);
                    break;
                }
            }
            break;
        case 2:
            // In this mode, we drive forward a little bit.
        	TFC_BAT_LED0_OFF;
        	TFC_BAT_LED1_ON;
            TFC_BAT_LED2_OFF;
            TFC_BAT_LED3_OFF;
            delay(300);
            forwardFull();
            break;
        case 3:
            // In this mode, we drive forward until the input is below a threshold
            TFC_BAT_LED0_ON;
            TFC_BAT_LED1_ON;
            TFC_BAT_LED2_OFF;
            TFC_BAT_LED3_OFF;
            TFC_HBRIDGE_ENABLE;
            runToLine();
            break;
        case 4:
            TFC_BAT_LED0_OFF;
            TFC_BAT_LED1_OFF;
            TFC_BAT_LED2_ON;
            TFC_BAT_LED3_OFF;
            TFC_HBRIDGE_ENABLE;
            while(1) {
                TFC_Task();
                algo_two();
                TFC_SetMotorPWM(.3, .3);
                if(TFC_PUSH_BUTTON_1_PRESSED)break;
                if(stop_car()){
                	delay(5);
                    break;
                }
            }

            break;
        case 5:
            TFC_BAT_LED0_ON;
            TFC_BAT_LED1_OFF;
            TFC_BAT_LED2_ON;
            TFC_BAT_LED3_OFF;
            TFC_HBRIDGE_ENABLE;
            while(1) {
                TFC_Task();
                algo_three();
                TFC_SetMotorPWM(0.25, 0.25);
                if(TFC_PUSH_BUTTON_1_PRESSED) break;
                if(stop_car()){
                	delay(5);
                	break;
                }
            }

            break;
    }

    TFC_SetServo(0,0);
    TFC_SetMotorPWM(0, 0);
    TFC_BAT_LED0_OFF;
    TFC_BAT_LED1_OFF;
    TFC_BAT_LED2_OFF;
    TFC_BAT_LED3_OFF;
    TFC_HBRIDGE_DISABLE;
    return 0;
}
