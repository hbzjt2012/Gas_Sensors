#ifndef _USART5_CH2O_AS04_H
#define _USART5_CH2O_AS04_H

#include "stm32f0xx.h"

void USART5_CH2O_AS04_Init(void);
void USART5_SendStr(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len);

#endif
