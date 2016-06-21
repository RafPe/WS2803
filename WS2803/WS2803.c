/*
 * WS2803.c
 *
 *  Created on: Sep 21, 2014
 *      Author: RafPe
 */

#include <avr/io.h>

#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>

#include "../SPI/SPI.h"
#include "WS2803.h"


// ------ gamma  correction
const uint8_t gamma_correctionR[] PROGMEM = {
		  0,  1,  1,  1,  2,  3,  4,  6,  7,  9, 10, 12, 14, 16, 18, 21, 23, 25,
		 28, 31, 34, 37, 40, 43, 46, 50, 53, 57, 61, 65, 69, 73, 77, 81, 86, 90,
		 95, 99,104,109,114,119,124,129,135,140,146,151,157,163,169,175,181,187,
		194,200,207,213,220,227,233,240,247,255
		};
/*
 * Send using hardware SPI to our device
 */
void ws2803_shift_out(uint8_t * bufor)
{
	for (uint8_t var = 0; var < WS2803_LED_CNT; var++)
	{
		SPI_send_byte( bufor[var] );

	}
	_delay_us(500);						// default time to shift out the data - TODO:potential to be replaced with interrupt
}

/*
 * Set complete bufffer with single value
 *
 * bufor : pointer to our buffer
 * value : value which we will be filling it with
 */
void ws2803_set_all(uint8_t * bufor,uint8_t value)
{
	memset( bufor , value , WS2803_LED_CNT );
}

/*
 * function providing dim out/in effect of all outputs
 *
 * direction    : 1 dim in / 0 dim out
 * effect_delay : delay between output to all ports
 * bufor        : pointer to our buffer
 */
void ws2803_fade(uint8_t direction , double effect_delay , uint8_t * bufor)
{
	if(direction)																													// if dim in
	{
		#if WS2803_USE_GAMMA==1																							// conditional compilation if we use GAMMA table
			for (uint8_t var = 0; var < sizeof(gamma_correctionR); var++)
			{
				ws2803_set_all( bufor , GAMMAR(var) );													// set values
				ws2803_shift_out( bufor);																				// send out
				_delay_ms( effect_delay );																			// delay
			}
		#else
			for (uint8_t var = 0; var < 255; var++)														// same as above but without gamma correction
			{																																	// linear effect from od 0-255
				ws2803_set_all( bufor , var);
				ws2803_shift_out( bufor);
				_delay_ms( effect_delay );
			}
		#endif

	}
	else																																			// if dim out
	{
		#if WS2803_USE_GAMMA==1																									// 	conditional compilation if we use GAMMA table
			for (uint8_t var = ( sizeof(gamma_correctionR)-1 ); var > 0; var--)		//  Iteration from max gamma correction TODO: potentially wrong implementation of size_of
			{
				ws2803_set_all( bufor , GAMMAR(var) );															// set values
				ws2803_shift_out( bufor);																						// send out
				_delay_ms( effect_delay );																					// delay
			}

			ws2803_set_all( bufor , GAMMAR(0) );																	// still need to do the 0 
			ws2803_shift_out( bufor);											    										// and send it out 

		#else																																	  // same as above but without gamma correction
			for (uint8_t var = 255; var > 0; var--)
			{
				ws2803_set_all( bufor , var);
				ws2803_shift_out( bufor);
				_delay_ms( effect_delay );
			}

			ws2803_set_all( bufor , GAMMAR(0) );									                // still need to do the 0 
			ws2803_shift_out( bufor);											                        // and send it out 
		#endif

	}
}

/*
 * Function setting single output to specific value
 *
 * oNum 			: pixel number
 * brightnes  : value  0-255
 * bufor      : pointer to our buffer
 *
 */
void ws2803_set_pix_brightness(int oNum , uint8_t brightnes , uint8_t * bufor)
{
	if ( ( oNum < 0 ) || ( oNum >= WS2803_LED_CNT+1 ) ) return;	// if not visible do not draw anything :) 
	bufor[ oNum ] = brightnes;																	// set value 0-255
}


/*
 * Function to light one by one 
 *
 * between_delay  : delay for efektu
 * bufor          : pointer to our buffer
 */
void ws2803_oneByOne( double between_delay , uint8_t * bufor)
{
	for (uint8_t var = 0; var < WS2803_LED_CNT; var++)
	{
		#if WS2803_USE_GAMMA==1																						
		for (int var2 = 0; var2 < sizeof(gamma_correctionR); var2++)
		{
			ws2803_set_pix_brightness( var , GAMMAR(var2) , bufor);	    
			ws2803_shift_out( bufor );  																	
			_delay_ms( between_delay );																			
		}
		#else													
		for (int var2 = 0; var2 < 255; var2++)
		{
			ws2803_set_pix_brightness( var , var2 , bufor);		
			ws2803_shift_out( bufor );  							
			_delay_ms( between_delay );							
		}
		#endif
	}
}

void ws_line ( uint8_t * bufor , int x , uint16_t length, uint8_t brightness)
{
	int i;	//can take negative values

	for (i = x; i < (int)(x+length) ; i++)
	{
		ws2803_set_pix_brightness( i,brightness, bufor );
	}

}

