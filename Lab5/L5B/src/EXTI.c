#include "EXTI.h"

#include "DAC.h"

void EXTI_Init(void) {
    // Initialize User Button
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	GPIOC->MODER &= ~GPIO_MODER_MODE13;
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;
	
	// Configure SYSCFG EXTI
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
	
	// Configure EXTI Trigger
	EXTI->FTSR1 |= EXTI_FTSR1_FT13;
	
	// Enable EXTI
	EXTI->IMR1 |= EXTI_IMR1_IM13;
	
	// Configure and Enable in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	NVIC_SetPriority(EXTI15_10_IRQn, 0);
}

#define DAC_MIN 0
#define DAC_MAX 4095
#define DAC_INCREMENT 256

static uint32_t dac_value = 0;
static enum {
    DOWN,
    UP,
} direction = UP;

// [TODO] Interrupt handler
void EXTI15_10_IRQHandler(void) {
	EXTI->PR1 |= EXTI_PR1_PIF13;
	if (direction == UP && (dac_value + DAC_INCREMENT > DAC_MAX)) {
		//set brightness to max value
		direction = DOWN;
		DAC_Write_Value(DAC_MAX);
	}
	else if (direction == DOWN && (dac_value < DAC_INCREMENT)) {
		//set brightness to min value
		direction = UP;
		DAC_Write_Value(DAC_MIN);
	}
	else if (direction == UP) {
		dac_value += DAC_INCREMENT;
		DAC_Write_Value(dac_value);
	}
	else if (direction == DOWN) {
		dac_value -= DAC_INCREMENT;
		DAC_Write_Value(dac_value);
	}
}
