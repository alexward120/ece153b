#include "SPI.h"
#include "SysTimer.h"

// Note: When the data frame size is 8 bit, "SPIx->DR = byte_data;" works incorrectly. 
// It mistakenly send two bytes out because SPIx->DR has 16 bits. To solve the program,
// we should use "*((volatile uint8_t*)&SPIx->DR) = byte_data";

void SPI1_GPIO_Init(void) {
	// Enable the GPIO Clock
	RCC->AHB2ENR |=  RCC_AHB2ENR_GPIOBEN;
	
	// Set PB13, PB14, and PB15 to Alternative Functions
	GPIOB->MODER &= ~(GPIO_MODER_MODE3 | GPIO_MODER_MODE4 | GPIO_MODER_MODE5);
	GPIOB->MODER |= GPIO_MODER_MODE3_1 | GPIO_MODER_MODE4_1 | GPIO_MODER_MODE5_1; // 10 -> Alternative Function
	
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL3 | GPIO_AFRL_AFSEL4 | GPIO_AFRL_AFSEL5);
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL3_2 | GPIO_AFRL_AFSEL3_0 |
	                 GPIO_AFRL_AFSEL4_2 | GPIO_AFRL_AFSEL4_0 |
	                 GPIO_AFRL_AFSEL5_2 | GPIO_AFRL_AFSEL5_0; 
	
	// Set GPIO Pins to: Very High Output speed, Output Type Push-Pull, and No Pull-Up/Down
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED3 | GPIO_OSPEEDR_OSPEED4 | GPIO_OSPEEDR_OSPEED5;
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT3 | GPIO_OTYPER_OT4 | GPIO_OTYPER_OT5);
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD3 | GPIO_PUPDR_PUPD4 | GPIO_PUPDR_PUPD5);
}


void SPI2_GPIO_Init(void) {
	// Enable the GPIO Clock
	RCC->AHB2ENR |=  RCC_AHB2ENR_GPIOBEN;
	
	// Set PB13, PB14, and PB15 to Alternative Functions
	GPIOB->MODER &= ~(GPIO_MODER_MODE13 | GPIO_MODER_MODE14 | GPIO_MODER_MODE15);
	GPIOB->MODER |= GPIO_MODER_MODE13_1 | GPIO_MODER_MODE14_1 | GPIO_MODER_MODE15_1; // 10 -> Alternative Function
	
	GPIOB->AFR[1] &= ~(GPIO_AFRH_AFSEL13 | GPIO_AFRH_AFSEL14 | GPIO_AFRH_AFSEL15);
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL13_2 | GPIO_AFRH_AFSEL13_0 |
	                 GPIO_AFRH_AFSEL14_2 | GPIO_AFRH_AFSEL14_0 |
	                 GPIO_AFRH_AFSEL15_2 | GPIO_AFRH_AFSEL15_0;
	
	// Set GPIO Pins to: Very High Output speed, Output Type Push-Pull, and No Pull-Up/Down
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED13 | GPIO_OSPEEDR_OSPEED14 | GPIO_OSPEEDR_OSPEED15;
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT13 | GPIO_OTYPER_OT14 | GPIO_OTYPER_OT15);
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD13 | GPIO_PUPDR_PUPD14 | GPIO_PUPDR_PUPD15);
}

void SPI1_Init(void){
	// Enable SPI clock and Reset SPI
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;  
	RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST; // Clear Reset Bit
	
	// Disable SPI
	SPI1->CR1 &= ~SPI_CR1_SPE; 
	// Configure for Full Duplex Communication
	SPI1->CR1 &= ~SPI_CR1_RXONLY;     
	// Configure for 2-line Unidirectional Data Mode
	SPI1->CR1 &= ~SPI_CR1_BIDIMODE;
	// Disable Output in Bidirectional Mode
	SPI1->CR1 &= ~SPI_CR1_BIDIOE;
	// Set Frame Format
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;  // 0 -> MSB First
	SPI1->CR2 &= ~SPI_CR2_DS;     
	SPI1->CR2 |= SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0;  // 0111 -> 8-bit
	SPI1->CR2 &= ~SPI_CR2_FRF;
	// Configure Clock
	SPI1->CR1 &= ~SPI_CR1_CPOL; 
	SPI1->CR1 &= ~SPI_CR1_CPHA;
	// Set Baud Rate Prescaler to 16
	SPI1->CR1 &= ~SPI_CR1_BR;
	SPI1->CR1 |= SPI_CR1_BR_1 | SPI_CR1_BR_0;
	// Disable Hardware CRC Calculation
	SPI1->CR1 &= ~SPI_CR1_CRCEN;
	// Set as Master and Enable Software Slave Management and NSS Pulse Management
	SPI1->CR1 |= SPI_CR1_MSTR;
	SPI1->CR1 |= SPI_CR1_SSM;
	SPI1->CR2 |= SPI_CR2_NSSP;
	// Manage NSS using Software
	SPI1->CR1 |= SPI_CR1_SSI;
	// Set FIFO Reception Threshold
	SPI1->CR2 |= SPI_CR2_FRXTH;
	// Enable SPI
	SPI1->CR1 |= SPI_CR1_SPE;   
}

void SPI2_Init(void){
	// Enable SPI clock and Reset SPI
	RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;     
	RCC->APB1RSTR1 |= RCC_APB1RSTR1_SPI2RST;  
	RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_SPI2RST;
	
	// Disable SPI
	SPI2->CR1 &= ~SPI_CR1_SPE; 
	// Configure for Full Duplex Communication
	SPI2->CR1 |= SPI_CR1_RXONLY;     
	// Configure for 2-line Unidirectional Data Mode
	SPI2->CR1 &= ~SPI_CR1_BIDIMODE;
	// Disable Output in Bidirectional Mode
	SPI2->CR1 &= ~SPI_CR1_BIDIOE;
	// Set Frame Format
	SPI2->CR1 &= ~SPI_CR1_LSBFIRST;
	SPI2->CR2 &= ~SPI_CR2_DS;     
	SPI2->CR2 |= SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0;
	SPI2->CR2 &= ~SPI_CR2_FRF;
	// Configure Clock
	SPI2->CR1 &= ~SPI_CR1_CPOL;
	SPI2->CR1 &= ~SPI_CR1_CPHA;
	// Set Baud Rate Prescaler to 16
	SPI2->CR1 &= ~SPI_CR1_BR;
	SPI2->CR1 |= SPI_CR1_BR_1 | SPI_CR1_BR_0;
	// Disable Hardware CRC Calculation
	SPI2->CR1 &= ~SPI_CR1_CRCEN;
	// Set as Master and Enable Software Slave Management and NSS Pulse Management
	SPI2->CR1 &= ~SPI_CR1_MSTR; 
	SPI2->CR1 |= SPI_CR1_SSM;
	SPI2->CR2 |= SPI_CR2_NSSP;
	// Manage NSS using Software
	SPI2->CR1 &= ~SPI_CR1_SSI;
	// Set FIFO Reception Threshold
	SPI2->CR2 |= SPI_CR2_FRXTH;
	// Enable SPI
	SPI2->CR1 |= SPI_CR1_SPE;   
}

void SPI_Send_Byte(SPI_TypeDef* SPIx, uint8_t write_data){
	while((SPIx->SR & SPI_SR_TXE) != SPI_SR_TXE);  // Wait for TXE (Transmit buffer empty)
	*((volatile uint8_t*)&SPIx->DR) = write_data;
	while((SPIx->SR & SPI_SR_BSY) == SPI_SR_BSY);
}

void SPI_Receive_Byte(SPI_TypeDef* SPIx, uint8_t* read_data){
	while((SPIx->SR & SPI_SR_RXNE) != SPI_SR_RXNE); // Wait for RXNE (Receive buffer not empty)
	*read_data = *((volatile uint8_t*)&SPIx->DR);
}
