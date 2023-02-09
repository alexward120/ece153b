#include "UART.h"

void UART1_Init(void) {
	// [TODO]
}

void UART2_Init(void) {
	RCC->APB1ENR1 = RCC_APB1ENR1_USART2EN; //enable the uart2 clock
	RCC->CFGR &= ~RCC_CFGR_MCOSEL;
	RCC->CFGR |= RCC_CFGR_MCOSEL_0;  //setting the uart2 port clock to be system clock
}

void UART1_GPIO_Init(void) {
	// [TODO]
}

void UART2_GPIO_Init(void) { //pa2 , pa3
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; //turning on clock for gpioA
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED2; //turning on highest speed pin 2
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED3; //turning on highest speed pin 3
	
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT2; //setting pushpull (0)
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT3;

	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD2; //setting pin to pull up
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD2_0;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD3;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD3_0;

	GPIOA->MODER &= ~GPIO_MODER_MODE2; //setting the mode type to alternate functions
	GPIOA->MODER |= GPIO_MODER_MODE2_1;
	GPIOA->MODER &= ~GPIO_MODER_MODE3;
	GPIOA->MODER |= GPIO_MODER_MODE3_1;
	
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL2; //setting pin2(channel 7 which has usart2_tx)
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL2_3;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL3; //setting pin3(channel 7 which has usart2_rx)
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL3_3;

}

void USART_Init(USART_TypeDef* USARTx) {
	// [TODO]
}

uint8_t USART_Read (USART_TypeDef * USARTx) {
	// SR_RXNE (Read data register not empty) bit is set by hardware
	while (!(USARTx->ISR & USART_ISR_RXNE));  // Wait until RXNE (RX not empty) bit is set
	// USART resets the RXNE flag automatically after reading DR
	return ((uint8_t)(USARTx->RDR & 0xFF));
	// Reading USART_DR automatically clears the RXNE flag 
}

void USART_Write(USART_TypeDef * USARTx, uint8_t *buffer, uint32_t nBytes) {
	int i;
	// TXE is cleared by a write to the USART_DR register.
	// TXE is set by hardware when the content of the TDR 
	// register has been transferred into the shift register.
	for (i = 0; i < nBytes; i++) {
		while (!(USARTx->ISR & USART_ISR_TXE));   	// wait until TXE (TX empty) bit is set
		// Writing USART_DR automatically clears the TXE flag 	
		USARTx->TDR = buffer[i] & 0xFF;
		USART_Delay(300);
	}
	while (!(USARTx->ISR & USART_ISR_TC));   		  // wait until TC bit is set
	USARTx->ISR &= ~USART_ISR_TC;
}   

void USART_Delay(uint32_t us) {
	uint32_t time = 100*us/7;    
	while(--time);   
}
