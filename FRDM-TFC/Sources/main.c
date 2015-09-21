#include "derivative.h" /* include peripheral declarations */
#include "TFC\TFC.h"
#include "AlgoOne.h"

#define DEL 50

void forwardFull(){
   TFC_HBRIDGE_ENABLE;
   TFC_SetServo(0,-.1);
   TFC_SetMotorPWM(1,1);
   delay(30);
   TFC_SetMotorPWM(0,0);
   TFC_HBRIDGE_DISABLE;
}

void printCamera() {
   int t = 0;

   while(1) {
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
            printf("%X,", LineScanImage0[i]);
            if(i == 127)
               printf("\r\n");
            else
               printf(",");
         }
      }
   }
}

int main(void){
   TFC_Init();
   TFC_SetMotorPWN(0, 0);
   TFC_HBRIDGE_DISABLE;

   /* After power on, Wait for a button press before doing anything.
    * This gives us time to set the DIP switches and etc */
   TFC_BAT_LED0_ON; // This light will indicate that we're waiting
   while(!TFC_PUSH_BUTTON_0_PRESSED);

   /* Then set the operating mode based on the DIP switch */
   switch(TFC_GetDIP_Switch()&0x03) {
      default:
      case 0:
    	 TFC_BAT_LED1_ON;
         // In the default mode, simply read out the camera forever
         printCamera();
         break;
      case 1:
    	 TFC_BAT_LED2_ON;
         TFC_HBRIDGE_ENABLE;
         // In this mode, we will actually run the analysis and drive.
         while(1) {
            TFC_Task();
            run();
         }
         break;
      case 2:
    	 // In this mode, we drive forward a little bit.
    	 TFC_BAT_LED3_ON;	
    	 delay(300);
    	 forwardFull();
    	 break;
   }

   TFC_SetMotorPWM(0, 0);
   TFC_HBRIDGE_DISABLE;
   return 0;
}
