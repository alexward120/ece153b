/*
 * ECE 153B - Winter 2021
 *
 * Name(s): Alexander Ward, Diego Jerez
 * Section: W 7pm
 * Lab: 2B
 */

#include "LED.h"

void LED_Init(void) {
	// Enable GPIO Clocks
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	
	
	// Initialize Green LED
	GPIOA->MODER &= ~GPIO_MODER_MODE5;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT_5;
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;
}

void Green_LED_Off(void) {
	// [TODO]
}

void Green_LED_On(void) {
	// [TODO]
}

void Green_LED_Toggle(void){
	GPIOA->ODR ^= GPIO_ODR_OD5;
}
