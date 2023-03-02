/*
 * ECE 153B - Winter 2023
 *
 * Name(s):
 * Section:
 * Lab: 6A
 */

#include "stm32l476xx.h"

void GPIO_Init(void){	
	// Activate gpio, set mode to output, set speed to very fast, set type to push pull and turn off pupd
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	GPIOC->MODER = 0;
	GPIOC->MODER |= GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0 | GPIO_MODER_MODE8_0 | GPIO_MODER_MODE9_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED5 | GPIO_OSPEEDR_OSPEED6 |GPIO_OSPEEDR_OSPEED8 | GPIO_OSPEEDR_OSPEED9;
	GPIOC->OTYPER = 0;
	GPIOC->PUPDR = 0;
}


#define DELAY 225	// delay between steps of the sequences

void delay(void) {
	for (int i=0; i<DELAY; i++);
}

void Power_North(void) {
	//activate P5, deactivate P6
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR |= GPIO_ODR_OD6;
}

void Power_South(void) {
	//activate P6, deactivate P5
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR |= GPIO_ODR_OD5;

}

void Power_East(void) {
	//activate P8, deactivate P9
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	GPIOC->ODR |= GPIO_ODR_OD8;
}

void Power_West(void) {
	//activate P9, deactivate P8
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR |= GPIO_ODR_OD9;
}

void Depower_Horizontal(void) {
	// deactivate p8 and P9
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
}

void Depower_Vertical(void) {
	// deactivate p5 and P6
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR &= ~GPIO_ODR_OD6;

}

void Full_Stepping_Clockwise(void){
	for (int i=0; i<512; i++) {
		Depower_Horizontal();
		Power_North();
		delay();
		
		Depower_Vertical();
		Power_East();
		delay();
		
		Depower_Horizontal();
		Power_South();
		delay();
		
		Depower_Vertical();
		Power_West();
		delay();
	}
}

void Full_Stepping_CounterClockwise(void){
	for (int i=0; i<512; i++) {
		Depower_Horizontal();
		Power_North();
		delay();
		
		Depower_Vertical();
		Power_West();
		delay();
		
		Depower_Horizontal();
		Power_South();
		delay();
		
		Depower_Vertical();
		Power_East();
		delay();
	}
}

void Half_Stepping_Clockwise(void){
	Depower_Horizontal();
	Power_North();
	for (int i=0; i<512; i++) {
		Power_North();
		delay();
		
		Depower_Horizontal();
		delay();
		
		Power_East();
		delay();
		
		Depower_Vertical();
		delay();
		
		Power_South();
		delay();
		
		Depower_Horizontal();
		delay();
		
		Power_West();
		delay();
		
		Depower_Vertical();
		delay();
	}
}

void Half_Stepping_CounterClockwise(void){
		Depower_Horizontal();
	Power_North();
	for (int i=0; i<512; i++) {
		Power_North();
		delay();
		
		Depower_Horizontal();
		delay();
		
		Power_West();
		delay();
		
		Depower_Vertical();
		delay();
		
		Power_South();
		delay();
		
		Depower_Horizontal();
		delay();
		
		Power_East();
		delay();
		
		Depower_Vertical();
		delay();
	}

}



int main(void){
	GPIO_Init();
	
	// Rotate 360 degrees either clockwise or counter-clockwise
	Half_Stepping_CounterClockwise();
	Depower_Horizontal();
	Depower_Vertical();
}
