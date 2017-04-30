#include "main.h"

void TIM2_Init(void)
{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);   
  
    TIM_DeInit(TIM2);  
  
    TIM_TimeBaseStructure.TIM_Period=2000-1;  //自动重装载寄存器的值 
    TIM_TimeBaseStructure.TIM_Prescaler=(24000-1);         //时钟预分频数  
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;  //采样分频  
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);  
	
		//TIM2 NVIC 设置
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority=3 ;//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure); //根据指定参数初始化NVIC

    TIM_ClearFlag(TIM2,TIM_FLAG_Update);               //清除溢出中断标志
  
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);       //开启TIM2中断
  
    TIM_Cmd(TIM2,ENABLE);                              //使能TIM2 
}

