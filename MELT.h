/*
 * melt.h
 *
 * Created: 19.02.2017 15:54:27
 *  Author: Vega
 */ 


#ifndef MELT_H_
#define MELT_H_

#include "stm32f1xx_hal.h"
#include "dwt_delay.h"

#define LCD_PORT GPIOA
#define A0 	3
#define RW 	2	
#define E 	1	
#define D7 	7
#define D6 	6	
#define D5 	5
#define D4 	4	
#define PAGE1 0
#define PAGE2 64	
#define STRING_LEN	10

void mt_LCD_init(void);
void mt_lcd_clear_display(void);
void mt_lcd_write_byte(char data, uint8_t address);


#endif /* MELT_H_ */