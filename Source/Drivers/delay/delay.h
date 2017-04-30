#ifndef __DELAY_H
#define __DELAY_H 	

#include "stm32f0xx.h"
	 
void delay_init(void);
void SysTick_SysTick_delay_ms(uint16_t nms);
void SysTick_SysTick_delay_us(uint32_t nus);

void SysTick_delay_ms(uint32_t nbrOfMs);
void SysTick_delay_us(uint32_t nbrOfUs);	

#endif





























