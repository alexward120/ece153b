#include "stm32l476xx.h"

static void DAC_Pin_Init(void) {
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODE4; //analog mode
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD4; //no pull up, no pull down
}

void DAC_Write_Value(uint32_t value) {
    // [TODO] Write DAC1Ch1 right-aligned 12-bit value
	DAC1->DHR12R1 = value;
}

void DAC_Init(void) {
    DAC_Pin_Init();

    // [TODO] Enable DAC clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_DAC1EN;
	DAC1->CR &= ~DAC_CR_EN1;
    // [TODO] Enable software trigger mode
	DAC1->CR |= DAC_CR_TSEL1;
    // [TODO] Disable trigger
	DAC1->CR &= ~DAC_CR_TEN1;
    // [TODO] DAC1 connected in normal mode to external pin only with buffer enabled
	DAC1->MCR &= ~DAC_MCR_MODE1;
    // [TODO] Enable DAC channel 1
	DAC1->CR |= DAC_CR_EN1;
	
    DAC_Write_Value(0);
}
