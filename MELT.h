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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
#define STRING_LEN		10
#define SPACE_1_FIRST 0x00
#define SPACE_1_LAST 	0x27
#define SPACE_2_FIRST 0x40
#define SPACE_2_LAST 	0x67

typedef enum{
	SYM_1 = 0,
	SYM_2,
	SYM_3,
	SYM_4,
	SYM_5,
	SYM_6,
	SYM_7,
	SYM_8,
	SYM_9 = 64,
	SYM_10
}symbol_addr;

void mt_LCD_init(void);
void mt_lcd_clear_display(void);
void mt_lcd_write_byte(char data, uint8_t address);
void mt_lcd_shift(bool sc, bool rl);


#endif /* MELT_H_ */
