/*
 * ECE 153B - Winter 2021
 *
 * Name(s): Alexander Ward, Diego Jerez
 * Section: W 7pm
 * Lab: 2A
 */

#include "SysClock.h"

void System_Clock_Init(void) {
	// Enable HSI
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0);
	
	// Select HSI as system clock source
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	while((RCC->CFGR & RCC_CFGR_SWS) == 0);
}
