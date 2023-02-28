/*
 * ECE 153B - Winter 2023
 *
 * Name(s):
 * Section:
 * Lab: 5B
 */


#include "ADC.h"
#include "DAC.h"
#include "EXTI.h"
#include "PWM.h"
#include "SysClock.h"
#include "stm32l476xx.h"
#include <stdio.h>

int adc_data;
volatile float v_in;

int main(void) {
    // Initialization
    System_Clock_Init(); // Switch System Clock = 8 MHz

    ADC_Init();
    DAC_Init();
    EXTI_Init();
	PWM_Init();
	adc_data = 0;
	v_in = 0;

    while (1) {
        ADC1->CR |= ADC_CR_ADSTART;
		while ((ADC1->ISR & ADC_ISR_EOC) == 0);
		
		adc_data = ADC1->DR & ADC_DR_RDATA;
		v_in = 3.3*((4096-((float)adc_data))/4096);
		
		TIM2->CCR1 &= ~TIM_CCR1_CCR1;
		TIM2->CCR1 |= adc_data;

        // [TODO] LED behavior based on ADC result
		for (int i=0; i < 1000; ++i); //Some Delay
    }
}
