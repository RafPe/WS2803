/*
 * WS2803.h
 *
 *  Created on: Sep 21, 2014
 *      Author: RafPE
 */

#ifndef WS2803_H_
#define WS2803_H_

/*
 *  Configuration of number of connected LEDs 
 *  and if we use GAMMA correction
 */
#define WS2803_LED_CNT      18
#define WS2803_USE_GAMMA    1
#define GAMMAR(a) (pgm_read_byte(&gamma_correctionR[a]))  // macro for 


extern const uint8_t gamma_correctionR[];

void ws2803_shift_out(uint8_t * bufor);
void ws2803_set_all(uint8_t * bufor,uint8_t value);
void ws2803_fade(uint8_t direction , double effect_delay , uint8_t * bufor);
void ws2803_set_pix_brightness(int oNum , uint8_t brightnes , uint8_t * bufor);
void ws2803_oneByOne( double between_delay , uint8_t * bufor);
void ws_line ( uint8_t * bufor , int x , uint16_t length, uint8_t brightness);


#endif /* WS2803_H_ */
