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
    RCC->AHB2ENR |= ((uint32_t)0x00000005U) //Enables GPIO A and C

    // Initialize Green LED
    GPIOA->MODER &=  ~(3UL<<10);
    GPIOA->MODER |= 1UL<<10;
    GPIOA->OTYPER &= ~(1UL<<5);
    GPIOA->PUPDR &= ~(3UL<<10);

    //GPIOB->ODR |= 1UL << 2; // Output 1 to turn on red LED
    // Initialize User Button
    GPIOC->MODER &= ~(3UL<<26);
    GPIOC->PUPDR &= ~(3UL<<26);
}

int main(void){
    // Initialization
    Init();

    // Polling to Check for User Button Presses
    // [TODO]

    return 0;
}
