/*
 * ECE 153B - Winter 2023
 *
 * Name(s): Alexander Ward, Diego Jerez
 * Section: W 7pm
 * Lab: 3B
 */
 
#include <stdio.h> 
 
#include "stm32l476xx.h"

uint32_t volatile currentValue = 0;
uint32_t volatile lastValue = 0;
uint32_t volatile overflowCount = 0;
uint32_t volatile timeInterval = 0;

void Input_Capture_Setup() {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN // Enable GPIO Clock for PB6
	GPIOB->MODER &= ~GPIO_MODER_MODE6; // Set PE9 to alternative function mode and select alternate function 1 (TIM1_CH2).
	GPIOB->MODER |= GPIO_MODER_MODE6_1; //Setting moder to 10 for alternative function
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL6; //Selecting channel 2 for afr pin 6
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL6_1;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD6; //setting to 0 for no pull up/pull down

	RCC->ABP1ENR1 |= RCC_ABP1ENR1_TIM4EN; //enable time 4 channel 1

	TIM4->PSC &= ~TIM_PSC_PSC;
	TIM4->PSC &= (uint32_t)15;
	TIM4->CR1 |= TIM_CR1_ARPE; //enable auto reload 
	TIM4->ARR |= TIM_ARR_ARR; //setting arr to max value

	TIM4->CCMR1 |= TIM_CCMR1_CC1S_0; //set the input capture mode bits such that the input capture is mapped to timer input 1
	TIM4->CCMR1 &= ~TIM_CCMR1_CC1S_1;

	TIM4->CCER |= TIM_CCER_CC1P; // In the capture/compare enable register, set bits to capture both rising/falling
	TIM4->CCER |= TIM_CCER_CC1NP; // edges and enable capturing.
	TIM4->CCER |= TIM_CCER_CC1E;

	// In the DMA/Interrupt enable register, enable both interrupt and DMA requests. In
	// addition, enable the update interrupt.
	TIM4->DIER |= TIM_DIER_CC1IE;
	TIM4->DIER |= TIM_DIER_CC1DE;
	TIM4->DIER |= TIM_DIER_UIE;

	TIM4->EGR |= TIM_EGR_UG; // Enable update generation in the event generation register.

	TIM4->SR &= ~TIM_SR_UIF; // Clear the update interrupt flag.

	TIM4 -> CR1 &= ~TIM_CR1_DIR;
	TIM4 -> CR1 |= TIM_CR1_CEN; // Set the direction of the counter and enable the counter in the control register

	NVIC_EnableIRQ(TIM4_IRQn);
	NVIC_SetPriority(TIM4_IRQn, 2);
}

void TIM4_IRQHandler(void) {
	if((TIM4->SR) & TIM_SR_CC1IF) {
		if((GPIOB->IDR) & GPIO_IDR_ID6) {
			lastValue = (TIM4->CCR1) & TIM_CCR1_CCR1;
		}
		else {
			currentValue = (TIM4->CCR1) & TIM_CCR1_CCR1;
			timeInterval = currentValue + (65536 * overflowCount) - lastValue;
			overflowCount = 0;
		}
	}
	else if((TIM4->SR) & TIM_SR_UIF) {
		overflowCount++;
	}
	TIM4->SR &= ~TIM_SR_UIF;
}

void Trigger_Setup() {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN // Enable GPIO Clock for PA9
	GPIOA->MODER &= ~GPIO_MODER_MODE9; // Set PE9 to alternative function mode and select alternate function 1 (TIM1_CH2).
	GPIOA->MODER |= GPIO_MODER_MODE9_1; //Setting moder to 10 for alternative function
	GPIOA->AFR[1] &= ~GPIO_AFRH_AFSEL9; //Selecting channel 1 for afr pin 9
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL9_0;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD9; //setting to 0 for no pull up/pull down
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT9; //setting to 0 for push-pull
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED9; //set pa9 to very high speed	
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; //enable timer 1 in reg

	TIM1->PSC  &= ~TIM_PSC_PSC;
	TIM1->PSC |= (uint32_t)15; //setting prescalar value to 15

	TIM1->CR1 |= TIM_CR1_ARPE; //enable auto reload 
	TIM1->ARR |= TIM_ARR_ARR; //setting arr to max value

	TIM1->CCR2 &= ~TIM_CCR2_CCR2; //setting the ccr value
	TIM1->CCR2 |= (uint32_t)10; //setting ccr value to arr-10 value so pulse is 

	TIM1->CCMR1 &= ~TIM_CCMR1_OC2M; //configure channeel to use in output compare mode
	TIM1->CCMR1 |= TIM_CCMR1_OC2M_1; //mode pwm 1 (0110)
	TIM1->CCMR1 |= TIM_CCMR1_OC2M_2;
	TIM1->CCMR1 |= TIM_CCMR1_OC2PE;

	TIM1->CCER |= TIM_CCER_CC2E; //enable capture/compare enable register

	TIM1->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSR; //In the break and dead-time register, set the bits for main output enable and off-state selection for run mode.

	TIM1->EGR |= TIM_EGR_UG; // Enable update generation in the event generation register.

	TIM1->DIER |= TIM_DIER_UIE; //Enable update interrupt in the DMA/Interrupt enable register 
	TIM1->SR &= ~TIM_SR_UIF; //clear the update interrupt flag in the status register

	TIM1->CR1 &= ~TIM_CR1_DIR; //upcount direction
	TIM1->CR1 |= TIM_CR1_CEN; //enable count
}

int main(void) {	
	// Enable High Speed Internal Clock (HSI = 16 MHz)
	RCC->CR |= RCC_CR_HSION;
	while ((RCC->CR & RCC_CR_HSIRDY) == 0); // Wait until HSI is ready
	
	// Select HSI as system clock source 
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	while ((RCC->CFGR & RCC_CFGR_SWS) == 0); // Wait until HSI is system clock source
  
	// Input Capture Setup
	Input_Capture_Setup();
	
	// Trigger Setup
	Trigger_Setup();

	uint32_t distance;
	while(1) {
		distance = timeInterval / 58;
	}
}
