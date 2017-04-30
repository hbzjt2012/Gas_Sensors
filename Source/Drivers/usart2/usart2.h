#ifndef _USART2_H
#define _USART2_H

#include "stm32f0xx.h"

extern void USART2_Init(void);
void USART2_SendStr(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len);


#endif
