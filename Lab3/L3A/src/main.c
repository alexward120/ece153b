/*
 * ECE 153B - Winter 2023
 *
 * Name(s): Alexander Ward, Diego Jerez
 * Section: W 7pm
 * Lab: 3A
 */

#include "stm32l476xx.h"
 
void PWM_Init() {
	// Enable GPIO Port A Clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	
	// Enable TIM2 Clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	
	// Configure PA5
	GPIOA->MODER &= ~GPIO_MODER_MODE5;
	GPIOA->MODER |= GPIO_MODER_MODE5_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL5;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_0;

	// Configure PWM Output for TIM2 CH 1
	TIM2->CR1 &= ~TIM_CR1_DIR;
	TIM2->PSC &= ~TIM_PSC_PSC;
	TIM2->ARR &= ~TIM_ARR_ARR;
	TIM2->ARR |= (uint_32_t)1000;

	TIM2->CCMR1 &= ~TIM_CCMR1_OC1M;
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_1;
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_2;
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE;

	TIM2->CCER |= TIM_CCER_CC1P;
	TIM2->CCER |= TIM_CCER_CC1E;
	TIM2->CCR1 &= ~TIM_CCR1_CCR1;
	TIM2->CCR1 |= (uint_32_t)500;
	TIM2->CR1 |= TIM_CR1_CEN;

int main() {
	// Initialization - We will use the default 4 MHz clock
	PWM_Init();
	
	// Periodic Dimming
	int i;
	uint32_t arr = 1000;
	uint32_t ccr = 1000;
	while(1) {
		TIM1 -> CCR1 = ccr % arr;
		ccr--;
		if (ccr == 0) {
			ccr = 1000;
		}
		for(i=0; i<1000; ++i); // Some Delay
	}
	
	return 0;
}
