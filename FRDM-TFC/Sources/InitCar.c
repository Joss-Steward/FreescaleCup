/*
 * InitCar.c
 *
 *  Created on: Feb 3, 2016
 *      Author: Jared
 */

#include "TFC\TFC.h"
#include "Common.h"

void lightInitSequence(){
	int delayT = 200;
	
	TFC_BAT_LED0_OFF;
	TFC_BAT_LED1_OFF;
	TFC_BAT_LED2_OFF;
	TFC_BAT_LED3_OFF;
	delay(delayT);
	
	TFC_BAT_LED0_ON;
	TFC_BAT_LED1_OFF;
	TFC_BAT_LED2_OFF;
	TFC_BAT_LED3_OFF;
	delay(delayT);
	
	TFC_BAT_LED0_OFF;
	TFC_BAT_LED1_ON;
	TFC_BAT_LED2_OFF;
	TFC_BAT_LED3_OFF;
	delay(delayT);
	
	TFC_BAT_LED0_OFF;
	TFC_BAT_LED1_OFF;
	TFC_BAT_LED2_ON;
	TFC_BAT_LED3_OFF;
	delay(delayT);
	
	TFC_BAT_LED0_OFF;
	TFC_BAT_LED1_OFF;
	TFC_BAT_LED2_OFF;
	TFC_BAT_LED3_ON;
	delay(delayT);
	
	TFC_BAT_LED0_ON;
	TFC_BAT_LED1_ON;
	TFC_BAT_LED2_ON;
	TFC_BAT_LED3_ON;
}

void init(){
	TFC_Init();
	lightInitSequence();
}
