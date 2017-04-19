#ifndef _USART8_COMM_H
#define _USART8_COMM_H

#include "stm32f0xx.h"

void USART8_Comm_Init(void);
void USART8_SendStr(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len);

#endif
