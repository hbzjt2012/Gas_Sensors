#ifndef _LED_H
#define _LED_H

#define LD2_ON() GPIO_SetBits(GPIOA,GPIO_Pin_5)
#define LD2_OFF() GPIO_ResetBits(GPIOA,GPIO_Pin_5)

void LED_Init(void);



#endif
