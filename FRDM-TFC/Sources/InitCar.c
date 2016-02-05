/*
 * InitCar.c
 *
 *  Created on: Feb 3, 2016
 *      Author: Jared
 */

#include "TFC\TFC.h"
#include "Common.h"

void lightInitSequence(){
	
	// Delay time between lights
	int delayT = 10;
	
	// All lights off
	TFC_BAT_LED0_OFF;
	TFC_BAT_LED1_OFF;
	TFC_BAT_LED2_OFF;
	TFC_BAT_LED3_OFF;
	delay(delayT);
	
	// Turns light 1 on
	TFC_BAT_LED0_ON;
	TFC_BAT_LED1_OFF;
	TFC_BAT_LED2_OFF;
	TFC_BAT_LED3_OFF;
	delay(delayT);
	
	// Turns light 2 on and 1 off
	TFC_BAT_LED0_OFF;
	TFC_BAT_LED1_ON;
	TFC_BAT_LED2_OFF;
	TFC_BAT_LED3_OFF;
	delay(delayT);
	
	// Turns light 3 on and 2 off
	TFC_BAT_LED0_OFF;
	TFC_BAT_LED1_OFF;
	TFC_BAT_LED2_ON;
	TFC_BAT_LED3_OFF;
	delay(delayT);
	
	// Turns light 4 on and 3 off
	TFC_BAT_LED0_OFF;
	TFC_BAT_LED1_OFF;
	TFC_BAT_LED2_OFF;
	TFC_BAT_LED3_ON;
	delay(delayT);
	
	// All lights on
	TFC_BAT_LED0_ON;
	TFC_BAT_LED1_ON;
	TFC_BAT_LED2_ON;
	TFC_BAT_LED3_ON;
	
}

void init(){
	
	// TFC initialisation function
	TFC_Init();
	
	// Sets the motors to off
	TFC_SetMotorPWM(0, 0); 	
	
	// Sets the servo to straight
	TFC_SetServo(0, 0);		
	
	// Runs light initialisation sequence
	lightInitSequence();	
}
