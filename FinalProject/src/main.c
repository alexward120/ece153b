/*
 * ECE 153B - Winter 2023
 *
 * Name(s):
 * Section:
 * Lab: 6A
 */

#include "stm32l476xx.h"
#include "motor.h"
#include "LCD.h"

void GPIO_Init(void){	
	// Activate gpio, set mode to output, set speed to very fast, set type to push pull and turn off pupd
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	GPIOC->MODER = 0;
	GPIOC->MODER |= GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0 | GPIO_MODER_MODE8_0 | GPIO_MODER_MODE9_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED5 | GPIO_OSPEEDR_OSPEED6 |GPIO_OSPEEDR_OSPEED8 | GPIO_OSPEEDR_OSPEED9;
	GPIOC->OTYPER = 0;
	GPIOC->PUPDR = 0;
}

int main(void){
	GPIO_Init();
	
	// Rotate 360 degrees either clockwise or counter-clockwise
	Full_Stepping_CounterClockwise();
	Depower_Horizontal();
	Depower_Vertical();
}
