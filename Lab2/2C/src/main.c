/*
 * ECE 153B - Winter 2023
 *
 * Name(s): Alexander Ward, Diego Jerez
 * Section: W 7pm
 * Lab: 2C
 */
 
#include "stm32l476xx.h"

#include "LED.h"
#include "RTC.h"
#include "SysClock.h"

char strTime[12] = {0};
char strDate[12] = {0};

void RTC_Set_Alarm(void) {
	// [TODO]
}

void RTC_Alarm_Enable(void) {
	// [TODO]
}

void RTC_Alarm_IRQHandler(void) {
	// [TODO]
}

int main(void) {	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	
	LED_Init();
	
	RTC_Init();
	RTC_Alarm_Enable();
	RTC_Set_Alarm();
	
	while(1) {
		// [TODO]
	}
}
