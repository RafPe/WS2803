/*
 * SPI.h
 *
 *  Created on: Sep 21, 2014
 *      Author: RafPe
 */

#ifndef SPI_H_
#define SPI_H_

/* PING definitions for hardware SPI */
#define MOSI PB5
#define SCK  PB7
#define CS   PB4

/* exported functions */
void SPI_Init(void);
void SPI_send_byte(uint8_t byte);

#endif /* SPI_H_ */
