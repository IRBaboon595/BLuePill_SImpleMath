/*
 * melt.c
 *
 * Created: 19.02.2017 15:54:11
 *  Author: Vega
 */ 


#include "melt.h"

void mt_LCD_init(void)
{
	LCD_PORT->ODR &=~ 0x00FE;
	HAL_Delay(22);
	LCD_PORT->ODR |= 0x0030;
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	DWT_Delay(50);
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	DWT_Delay(50);
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	DWT_Delay(50);
	LCD_PORT->ODR &=~ (1 << D4);
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	DWT_Delay(50);
	
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	LCD_PORT->ODR &=~ 0x00F0;
	LCD_PORT->ODR |= (1 << D7);
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	LCD_PORT->ODR &=~ 0x00F0;
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	LCD_PORT->ODR |= (1 << D7);
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);	
	LCD_PORT->ODR &=~ 0x00F0;
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	LCD_PORT->ODR |= (1 << D4);
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	LCD_PORT->ODR &=~ 0x00F0;
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	LCD_PORT->ODR |= 0x0060;
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);	
	DWT_Delay(50);
}

void mt_lcd_clear_display(void)
{
	LCD_PORT->ODR &=~ 0x00FE;
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	LCD_PORT->ODR |= (1 << D4);
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	HAL_Delay(3);
	LCD_PORT->ODR &=~ 0x00F0;
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	LCD_PORT->ODR |= (1 << D5);
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	DWT_Delay(50);
	LCD_PORT->ODR &=~ 0x00F0;
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	LCD_PORT->ODR |= 0x00F0;
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	DWT_Delay(50);
}

void mt_lcd_write_byte(char data, uint8_t address)
{
	LCD_PORT->ODR &=~ (1 << A0);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ 0x00FE;
	LCD_PORT->ODR |= (0x0080 | (address & 0x00F0));
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	LCD_PORT->ODR &=~ 0x00FE;
	LCD_PORT->ODR |= ((address << 4) & 0x00F0);
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	DWT_Delay(50);
	LCD_PORT->ODR |= (1 << A0);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ 0x00F0;
	LCD_PORT->ODR |= ((data & 0x00F0));
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	LCD_PORT->ODR &=~ 0x00F0;
	LCD_PORT->ODR |= ((data << 4) & 0x00F0);
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	DWT_Delay(50);
}

void mt_lcd_shift(bool sc, bool rl)
{
	uint16_t data = 0;
	
	LCD_PORT->ODR &=~ 0x00FE;
	LCD_PORT->ODR |= 0x0010;
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	LCD_PORT->ODR &=~ 0x00F0;
	if(sc == true)
	{
		data |= 0x0080;
	}
	if(rl == true)
	{
		data |= 0x0040;
	}
	LCD_PORT->ODR |= (data & 0x00F0);
	DWT_Delay(2);
	LCD_PORT->ODR |= (1 << E);
	DWT_Delay(2);
	LCD_PORT->ODR &=~ (1 << E);
	DWT_Delay(50);
}
