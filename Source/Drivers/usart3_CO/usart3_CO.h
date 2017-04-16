#ifndef _USART3_CO_H
#define _USART3_CO_H

#include "stm32f0xx.h"

void USART3_CO_Init(void);
void USART3_SendStr(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len);

#endif
