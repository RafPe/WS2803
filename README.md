# WS2803
Library to control WS2803 LED Driver IC. 
Uses hardware SPI which is attached to this repository and have been written on Atmega32.

# Define buffer pointer
Define name for buffer and pointer to it. Initialise with amount of outputs you want to use.
```
define WS2803_LED_CNT 18 

uint8_t ws_buf[ WS2803_LED_CNT ];
uint8_t * ptrBuf = ws_buf;
```


# Sending out 
In order to send out buffer to outputs use the following function 
```
ws2803_shift_out( ptrBuf );	
```

# Customised
Custom delay function being used in the library so we are in control of variable lenght of the delay
```
static inline void delay_ms(uint16_t count) 
{
  while(count--) 
  {
      delay_ms(1);
  }
}
```

# Examples

## Specific outputs and its brightness ( 8bit ) 
```
ws2803_set_pix_brightness(1, 98, ptrBuf);
ws2803_shift_out(ptrBuf);
delay_ms(200);

ws2803_set_pix_brightness(5, 120, ptrBuf);
ws2803_shift_out(ptrBuf);
delay_ms(200);

ws2803_set_pix_brightness(9, 60, ptrBuf);
ws2803_shift_out(ptrBuf);
delay_ms(200);

ws2803_set_pix_brightness(15, 230, ptrBuf);
ws2803_shift_out(ptrBuf);
delay_ms(200);
```

## Set all utputs 
```
	ws2803_set_all( ptrBuf , 255);	  
	ws2803_shift_out( ptrBuf );	
	delay_ms(3000);
```

## Fade all in/out 
```
ws2803_fade(1 , 10 , ptrBuf);
ws2803_fade(0 , 10 , ptrBuf);
```

## One by One with custom delay in ms
```
ws2803_oneByOne(5, ptrBuf);
```

## Draw a line 
```
		for (int var = 0; var < WS2803_LED_CNT+1 ; var++)
		{
			if(var>0) ws_line(ptrBuf, var-1, 2,0);	
			ws_line(ptrBuf, var,     2,30);			
			ws_line(ptrBuf, var+2,   2,150);		
			ws_line(ptrBuf, var+4,   2,240);		

			ws2803_shift_out( ptrBuf);				
			_delay_ms(100);
		}
```
