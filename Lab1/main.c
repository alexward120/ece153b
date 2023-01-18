/*
 * ECE 153B - Winter 2023
 *
 * Name(s):
 * Section:
 * Lab: 1A
 */
#include "stm32l476xx.h"

void Init(){
    // Enable HSI
    RCC->CR |= ((uint32_t)RCC_CR_HSION);
    while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 );

    // Select HSI as system clock source
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 );

    // Enable GPIO Clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; //Enables GPIO A and C
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    // Initialize Green LED
    GPIOA->MODER &= ~GPIO_MODER_MODE5;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT_5;
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;

    //GPIOB->ODR |= 1UL << 2; // Output 1 to turn on red LED
    // Initialize User Button
    GPIOC->MODER &= ~GPIO_MODER_MODE13;
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;
}

int main(void) {
    // Initialization
    Init();
    while(1)
    {
        // Polling to Check for User Button Presses
        if (!((GPIOC->IDR) & GPIO_IDR_ID13))
        {
            GPIOA->ODR ^= GPIO_ODR_OD5;
			while(!((GPIOC->IDR) & GPIO_IDR_ID13));
        }
    }
    return 0;
}
