#include "main.h"

//     硬件接线 
//     Pin10-+5V  -> 5V
//     Pin9 - RX  -> PB3
//     Pin8 - TX  -> PB4
//     Pin6 -GND  -> GND

uint8_t USART5_RX_STA;
uint8_t USART5_RX_BUF[64];  //接收数据缓冲,最大64个字节

unsigned char ReadCH2O_Cmd[]={0x01,0x03,0x00,0x00,0x00,0x01,0x84,0x0A};

/**
  * @brief  USART5初始化
**/
void USART5_CH2O_AS04_Init(void)
{
		//GPIO端口设置
		GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART5,ENABLE);   //使能USART5时钟

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);     //使能GPIOB时钟

    //USART3_TX   GPIOB.3
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //PB.3
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.3

		//USART3_RX   GPIOB.4
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//PB.4
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//浮空输入
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.4 
	
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_4);  //复用串口功能4
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_4);
		
		//USART初始化设置

    USART_InitStructure.USART_BaudRate = 9600; //串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一位停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式
		USART_Init(USART5, &USART_InitStructure); //初始化串口5
		
		//USART5 NVIC 设置
		NVIC_InitStructure.NVIC_IRQChannel = USART3_8_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority=1 ;//抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure); //根据指定参数初始化NVIC
                    
		USART_ITConfig(USART5, USART_IT_RXNE, ENABLE);//开启串口5接收中断
		USART_ITConfig(USART5, USART_IT_ORE, ENABLE);
		USART_Cmd(USART5, ENABLE);                    //使能串口5 

}

/**
  * @brief  USART3发送一个字符串
**/
void USART5_SendStr(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len)
{
    uint32_t i;
		USART_ClearFlag(USART5,USART_FLAG_TC); 
    for(i=0; i<len; i++)
    {                                         
        USART_SendData(USARTx, *Data++);
        while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
    }
}

