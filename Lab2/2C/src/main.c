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
	RTC->CR &= ~RTC_CR_ALRBIE;
	RTC->CR &= ~RTC_CR_ALRAIE;
	RTC->CR &= ~RTC_CR_ALRAE;
	RTC->CR &= ~RTC_CR_ALRBE;
	RTC_Disable_Write_Protection();
	while(!((RTC -> ISR) & RTC_ISR_ALRAWF) || !((RTC -> ISR) & RTC_ISR_ALRBWF));
	RTC -> ALRMAR |= RTC_ALRMAR_MSK4;
	RTC -> ALRMAR |= RTC_ALRMAR_MSK3;
	RTC -> ALRMAR |= RTC_ALRMAR_MSK2;
	RTC -> ALRMAR &= ~RTC_ALRMAR_MSK1;

	RTC -> ALRMAR |= RTC_ALRMAR_ST_0; //trigger when seconds is 30
	RTC -> ALRMAR |= RTC_ALRMAR_ST_1;

	RTC -> ALRMBR |= RTC_ALRMBR_MSK4; //dont look at any registers as we just look at clock
	RTC -> ALRMBR |= RTC_ALRMBR_MSK3;
	RTC -> ALRMBR |= RTC_ALRMBR_MSK2;
	RTC -> ALRMBR |= RTC_ALRMBR_MSK1;

	RTC->CR |= RTC_CR_ALRBIE;
	RTC->CR |= RTC_CR_ALRAIE;
	RTC->CR |= RTC_CR_ALRAE;
	RTC->CR |= RTC_CR_ALRBE;

	RTC_Enable_Write_Protection();
}

void RTC_Alarm_Enable(void) {
	EXTI->RTSR1 |= EXTI_RTSR1_RT18; //Configure interupt trigger on rising edge
	EXTI->IMR1 |= EXTI_IMR1_IM18;
	EXTI->EMR1 |= EXTI_EMR1_EM18;
	EXTI->PR1 |= EXTI_PR1_PIF18;
	NVIC_EnableIRQ(RTC_Alarm_IRQn);
	NVIC_SetPriority(RTC_Alarm_IRQn, 0);
}

void RTC_Alarm_IRQHandler(void) {
	if (RTC->ISR & RTC_ISR_ALRAF) {
		Green_LED_Toggle();
	}
	if (RTC->ISR & RTC_ISR_ALRBF) {
		Green_LED_Toggle();
	}
	RTC->ISR &= ~RTC_ISR_ALRAF;
	RTC -> ISR &= ~RTC_ISR_ALRBF;
	EXTI->PR1 |= EXTI_PR1_PIF18;
}

int main(void) {	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	
	LED_Init();
	
	RTC_Init();
	RTC_Alarm_Enable();
	RTC_Set_Alarm();
	
	while(1) {
		Get_RTC_Calendar(strTime, strDate);
	}
}
