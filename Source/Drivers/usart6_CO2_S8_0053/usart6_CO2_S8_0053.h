#ifndef _USART6_CO2_S8_0053_H
#define _USART6_CO2_S8_0053_H

#include "stm32f0xx.h"

void USART6_CO2_S8_0053_Init(void);
void USART6_SendStr(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len);

#endif
