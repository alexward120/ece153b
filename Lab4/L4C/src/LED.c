/*
 * ECE 153B - Winter 2021
 *
 * Name(s):
 * Section:
 * Lab: 4C
 */

#include "LED.h"

void LED_Init(void) {
	// Enable GPIO Clocks
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	
	// Initialize Green LED
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	GPIOA->MODER &= ~(GPIO_MODER_MODE5);  
	GPIOA->MODER |=   GPIO_MODER_MODE5_0;      // Output(01)
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED5); // Low speed (00)
	
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5);      // Push-pull
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIOA->PUPDR  &= ~(GPIO_PUPDR_PUPDR5);  // No pull-up, no pull-down
}

void LED_Off(void) {
	GPIOA->ODR &= ~(GPIO_ODR_OD5);
}

void LED_On(void) {
	GPIOA->ODR |= GPIO_ODR_OD5;
}

void LED_Toggle(void) {
	GPIOA->ODR ^= GPIO_ODR_OD5;
}
