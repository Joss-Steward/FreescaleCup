#include "derivative.h" /* include peripheral declarations */
#include "TFC\TFC.h"

#define DEL 50

void delay(int x){
	int i;
	for(i = 0; i < 100000*x; i++);
}

void forwardFull(){
	TFC_HBRIDGE_ENABLE;
	TFC_SetServo(0,-.1);
	TFC_SetMotorPWM(1,1);
	delay(30);
	TFC_SetMotorPWM(0,0);
	TFC_HBRIDGE_DISABLE;
}

int main(void){
	
	
	
	int x = 0;
	TFC_Init();
	
	//TFC_SetMotorPWM(0,0);

	
//	TFC_BAT_LED0_ON;
//	TFC_Task();
//	delay(DEL);
//	delay(DEL);
//	TFC_BAT_LED0_ON;
//	delay(DEL);
//	delay(DEL);
//	TFC_BAT_LED1_ON;
//	delay(DEL);
//	delay(DEL);
//	TFC_BAT_LED2_ON;
//	delay(DEL);
//	delay(DEL);
//	TFC_BAT_LED3_ON;
//	delay(DEL);
//	delay(DEL);
//	forwardFull();
	for(;;){
		TFC_Task();
		if(LineScanImageReady==1){
			LineScanImageReady=0;
			printf("\r\n");
			printf("L:");
			int i;
			for(i=0;i<128;i++){
				 printf("%X,",LineScanImage0[i]);
			}					
			for(i=0;i<128;i++){
				printf("%X",LineScanImage1[i]);
				if(i==127)printf("\r\n");//,LineScanImage1[i]);
				else printf(",");//,LineScanImage1[i]);
			}																	
		}
		if((TFC_GetDIP_Switch()&0x01)&&x==0){
			x = 1;
			TFC_Task();
			delay(DEL);
			TFC_BAT_LED0_ON;
			delay(DEL);
			TFC_BAT_LED1_ON;
			delay(DEL);
			TFC_BAT_LED2_ON;
			delay(DEL);
			TFC_BAT_LED3_ON;
			delay(DEL);
			forwardFull();
		}
		
	}
	
//	TFC_SetServo(0,-.5);
	
//	TFC_HBRIDGE_ENABLE;
	//TFC_SetMotorPWM(.05,.05);
//	TFC_BAT_LED1_ON;
//	delay();
//	for(i = 0.0; i < 100; i++){
//		TFC_SetMotorPWM(i/100.0,i/100.0);
//		delay();
//	}
//	TFC_SetMotorPWM(0,0);
//	TFC_SetServo(0,0);
//	TFC_HBRIDGE_DISABLE;
//	TFC_BAT_LED2_ON;
//	delay();
//	TFC_BAT_LED0_ON;
//	TFC_SetServo(0,-1.0);
//	delay();
//	TFC_SetServo(0,1.0);
//	delay();
//	TFC_SetServo(0,-1.0);
//	delay();
//	TFC_SetServo(0,1.0);
//	delay();
//	TFC_SetServo(0,0.1);
//	delay();
//	TFC_BAT_LED1_ON;
//	while(1){}
//	while(1){
//	if(LineScanImageReady==1){
//		
//		LineScanImageReady=0;
//			printf("\r\n");
//			printf("L:");
//						 
//						 	//if(t==0)
//						 	//	t=3;
//						 	//else
//						 	//	t--;
//						 	
//							// TFC_SetBatteryLED_Level(t);
//			int i;
//							
//							 for(i=0;i<128;i++)
//							 {
//									 printf("%X,",LineScanImage0[i]);
//							 }
//							
//							 for(i=0;i<128;i++)
//							 {
//									 printf("%X",LineScanImage1[i]);
//									 if(i==127)
//										 printf("\r\n");//,LineScanImage1[i]);
//									 else
//										 printf(",");//,LineScanImage1[i]);
//							}										
//								
//						}
//	}
	return (0);
}



/*
int main(void)
{
	uint32_t t,i=0;
	
	TFC_Init();
	
	for(;;)
	{	   
		//TFC_Task must be called in your main loop.  This keeps certain processing happy (I.E. Serial port queue check)
			TFC_Task();

			//This Demo program will look at the middle 2 switch to select one of 4 demo modes.
			//Let's look at the middle 2 switches
			switch((TFC_GetDIP_Switch()>>1)&0x03)
			{
			default:
			case 0 :
				//Demo mode 0 just tests the switches and LED's
				if(TFC_PUSH_BUTTON_0_PRESSED)
					TFC_BAT_LED0_ON;
				else
					TFC_BAT_LED0_OFF;
				
				if(TFC_PUSH_BUTTON_1_PRESSED)
					TFC_BAT_LED3_ON;
				else
					TFC_BAT_LED3_OFF;
				
				
				if(TFC_GetDIP_Switch()&0x01)
					TFC_BAT_LED1_ON;
				else
					TFC_BAT_LED1_OFF;
				
				if(TFC_GetDIP_Switch()&0x08)
					TFC_BAT_LED2_ON;
				else
					TFC_BAT_LED2_OFF;
				
				break;
					
			case 1:
				
				//Demo mode 1 will just move the servos with the on-board potentiometers
				if(TFC_Ticker[0]>=20)
				{
					TFC_Ticker[0] = 0; //reset the Ticker
					//Every 20 mSeconds, update the Servos
					TFC_SetServo(0,TFC_ReadPot(0));
					TFC_SetServo(1,TFC_ReadPot(1));
				}
				//Let's put a pattern on the LEDs
				if(TFC_Ticker[1] >= 125)
				{
					TFC_Ticker[1] = 0;
					t++;
					if(t>4)
					{
						t=0;
					}			
					TFC_SetBatteryLED_Level(t);
				}
				
				TFC_SetMotorPWM(0,0); //Make sure motors are off
				TFC_HBRIDGE_DISABLE;
			

				break;
				
			case 2 :
				
				//Demo Mode 2 will use the Pots to make the motors move
				TFC_HBRIDGE_ENABLE;
				TFC_SetMotorPWM(TFC_ReadPot(0),TFC_ReadPot(1));
						
				//Let's put a pattern on the LEDs
				if(TFC_Ticker[1] >= 125)
					{
						TFC_Ticker[1] = 0;
							t++;
							if(t>4)
							{
								t=0;
							}			
						TFC_SetBatteryLED_Level(t);
					}
				break;
			
			case 3 :
			
				//Demo Mode 3 will be in Freescale Garage Mode.  It will beam data from the Camera to the 
				//Labview Application
				
		
				if(TFC_Ticker[0]>100 && LineScanImageReady==1)
					{
					 TFC_Ticker[0] = 0;
					 LineScanImageReady=0;
					 TERMINAL_PRINTF("\r\n");
					 TERMINAL_PRINTF("L:");
					 
					 	if(t==0)
					 		t=3;
					 	else
					 		t--;
					 	
						 TFC_SetBatteryLED_Level(t);
						
						 for(i=0;i<128;i++)
						 {
								 TERMINAL_PRINTF("%X,",LineScanImage0[i]);
						 }
						
						 for(i=0;i<128;i++)
						 {
								 TERMINAL_PRINTF("%X",LineScanImage1[i]);
								 if(i==127)
									 TERMINAL_PRINTF("\r\n",LineScanImage1[i]);
								 else
									 TERMINAL_PRINTF(",",LineScanImage1[i]);
						}										
							
					}
					


				break;
			}
	}
	
	return 0;
}
*/
