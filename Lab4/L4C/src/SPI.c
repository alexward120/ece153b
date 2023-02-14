#include "SPI.h"

// Note: When the data frame size is 8 bit, "SPIx->DR = byte_data;" works incorrectly. 
// It mistakenly send two bytes out because SPIx->DR has 16 bits. To solve the program,
// we should use "*((volatile uint8_t*)&SPIx->DR) = byte_data";

void SPI2_GPIO_Init(void) {
	// TODO: initialize SPI2 GPIO pins
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT3;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT4;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT5;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT13;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT14;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT15;

	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED3;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED4;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED5;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED13;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED14;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED15;

	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD3;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD13;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD14;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD15;
	
	GPIOB->MODER &= ~GPIO_MODER_MODE3;
	GPIOB->MODER |= GPIO_MODER_MODE3_1;
	GPIOB->MODER &= ~GPIO_MODER_MODE4;
	GPIOB->MODER |= GPIO_MODER_MODE4_1;
	GPIOB->MODER &= ~GPIO_MODER_MODE5;
	GPIOB->MODER |= GPIO_MODER_MODE5_1;
	GPIOB->MODER &= ~GPIO_MODER_MODE13;
	GPIOB->MODER |= GPIO_MODER_MODE13_1;
	GPIOB->MODER &= ~GPIO_MODER_MODE14;
	GPIOB->MODER |= GPIO_MODER_MODE14_1;
	GPIOB->MODER &= ~GPIO_MODER_MODE15;
	GPIOB->MODER |= GPIO_MODER_MODE15_1;

	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL3;
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL3_1;
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL3_3;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL4;
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL4_1;
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL4_3;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL5;
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL5_1;
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL5_3;
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL13;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL13_1;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL13_3;
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL14;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL14_1;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL14_3;
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL15;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL15_1;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL15_3;
}

void SPI2_Init(void){
	// TODO: initialize SPI2 peripheral
	RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	
	RCC->APB1RSTR1 |= RCC_APB1RSTR1_SPI2RST;
	RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;
	RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_SPI2RST;
	RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;

	SPI1->CR1 &= ~SPI_CR1_SPE;
	SPI2->CR1 &= ~SPI_CR1_SPE;

	SPI1->CR1 &= ~SPI_CR1_RXONLY;
	SPI2->CR1 &= ~SPI_CR1_RXONLY;

	SPI1->CR1 &= ~SPI_CR1_BIDIMODE;
	SPI2->CR1 &= ~SPI_CR1_BIDIMODE;
	
	SPI1->CR1 &= ~SPI_CR1_BIDIOE;
	SPI1->CR1 &= ~SPI_CR1_BIDIOE;
	
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;
	SPI2->CR1 &= ~SPI_CR1_LSBFIRST;
	
	SPI1->CR2 |= SPI_CR2_DS;
	SPI1->CR2 &= ~SPI_CR2_DS_3;
	SPI2->CR2 |= SPI_CR2_DS;
	SPI2->CR2 &= ~SPI_CR2_DS_3;

	SPI1->CR2 &= ~SPI_CR2_FRF;
	SPI2->CR2 &= ~SPI_CR2_FRF;
	
	SPI1->CR1 &= ~SPI_CR1_CPOL;
	SPI2->CR1 &= ~SPI_CR1_CPOL;
	
	SPI1->CR1 &= ~SPI_CR1_CPHA;
	SPI2->CR1 &= ~SPI_CR1_CPHA;
	
	SPI1->CR1 |= SPI_CR1_BR;
	SPI1->CR1 &= ~SPI_CR1_BR_2;
	SPI2->CR1 |= SPI_CR1_BR;
	SPI2->CR1 &= ~SPI_CR1_BR_2;
	
	SPI1->CR1 &= ~SPI_CR1_CRCEN;
	SPI2->CR1 &= ~SPI_CR1_CRCEN;
	
	SPI1->CR1 |= SPI_CR1_MSTR;
	SPI2->CR1 &= ~SPI_CR1_MSTR;

	SPI1->CR1 |= SPI_CR1_SSM;
	SPI2->CR1 |= SPI_CR1_SSM;
	
	SPI1->CR2 |= SPI_CR2_NSSP;
	SPI2->CR2 |= SPI_CR2_NSSP;
	
	SPI1->CR1 |= SPI_CR1_SSI;
	SPI2->CR1 |= SPI_CR1_SSI;
	
	SPI1->CR2 |= SPI_CR2_FRXTH;
	SPI2->CR2 |= SPI_CR2_FRXTH;

	SPI1->CR1 |= SPI_CR1_SPE;
	SPI2->CR1 |= SPI_CR1_SPE;
}
 
void SPI_Transfer_Byte(SPI_TypeDef* SPIx, uint8_t write_data, uint8_t* read_data) {
	// TODO: perform SPI transfer
	while (!(SPIx->SR & SPI_SR_TXE));
	SPIx->DR = write_data;
	while (SPIx->SR & SPI_SR_BSY);
	while (!(SPIx->SR & SPI_SR_RXNE));
	*read_data = (volatile uint8_t)SPIx->DR;
}
