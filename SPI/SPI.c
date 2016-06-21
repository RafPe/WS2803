/*
 * SPI.c
 *
 *  Created on: Sep 21, 2014
 *      Author: RafPe
 */


#include <avr/io.h>

#include "SPI.h"


void SPI_Init(void)
{
	// Set pin directions
	DDRB |= (1 << MOSI)|(1 << SCK)|(1 << CS);
	// enable SPI
	SPCR |= (1 << SPE)|(1 << MSTR)|(1 << SPR1);

}

void SPI_send_byte(uint8_t byte)
{
	SPDR = byte;
	while (!(SPSR & (1 << SPIF)));
}

uint8_t SPI_receive_byte(uint8_t byte)
{
	while (!(SPSR & (1 << SPIF)));
	return SPDR;
}

uint8_t SPI_transfer_byte(uint8_t byte)
{
	SPDR = byte;
	while (!(SPSR & (1 << SPIF)));
	return SPDR;
}
