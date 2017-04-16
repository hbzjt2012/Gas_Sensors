#include "main.h"

//     硬件接线 
//     LD2  -> PA5

//LED IO初始化
void LED_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	 //使能PB,PE端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 端口配置
 	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.5
	 GPIO_SetBits(GPIOA,GPIO_Pin_5);						 //PA5 输出高

}
