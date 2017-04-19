#ifndef _USART7_CH2O_DART_2_FE5_H
#define _USART7_CH2O_DART_2_FE5_H

#include "stm32f0xx.h"

void USART7_CH2O_Dart_2_FE5_Init(void);
void USART7_SendStr(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len);

#endif
