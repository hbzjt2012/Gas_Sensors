#ifndef _USART4_CO2_T6703_H
#define _USART4_CO2_T6703_H

#include "stm32f0xx.h"

void USART4_CO2_T6703_Init(void);
void USART4_SendStr(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len);


#endif

