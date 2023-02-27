/*
 * ECE 153B - Winter 2023
 *
 * Name(s):
 * Section:
 * Lab: 5A
 */


#include "ADC.h"
#include "PWM.h"
#include "SysClock.h"
#include "stm32l476xx.h"
#include <stdio.h>

int main(void) {
    // Initialization
    System_Clock_Init(); // Switch System Clock = 8 MHz

    ADC_Init();

    // [TODO] Initialize PWM

    while (1) {
        // [TODO] Trigger ADC and get result
		ADC1->CR |= ADC_CR_ADSTART;
		while ((ADC1->ISR & ADC_ISR_EOC) == 0);
		uint16_t adc_data = (uint16_t)ADC1->DR & ADC_DR_RDATA;
		

        // [TODO] LED behavior based on ADC result
    }
}
