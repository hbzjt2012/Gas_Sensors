#include "main.h"

//     硬件接线 
//     G+        -> 5V
//     UART_RxD  -> PC0
//     UART_TxD  -> PC1
//     G0        -> GND

uint8_t USART6_RX_STA;
uint8_t USART6_RX_BUF[64];  //接收数据缓冲,最大64个字节

unsigned char ReadCO2_S8_Cmd[]={0xFE,0x04,0x00,0x03,0x00,0x01,0xD5,0xC5};

/**
  * @brief  USART5初始化
**/
void USART6_CO2_S8_0053_Init(void)
{
		//GPIO端口设置
		GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);   //使能USART6时钟

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);     //使能GPIOC时钟

    //USART6_TX   GPIOC.0
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //PC.0
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC.0

		//USART6_RX   GPIOC.1
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//PC.1
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//浮空输入
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC.1 
	
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource0,GPIO_AF_2);  //复用串口功能2
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource1,GPIO_AF_2);
		
		//USART初始化设置

    USART_InitStructure.USART_BaudRate = 9600; //串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一位停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式
		USART_Init(USART6, &USART_InitStructure); //初始化串口6
		
		//USART6 NVIC 设置
		NVIC_InitStructure.NVIC_IRQChannel = USART3_8_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority=1 ;//抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure); //根据指定参数初始化NVIC
                    
		USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);//开启串口6接收中断
		USART_ITConfig(USART6, USART_IT_ORE, ENABLE);
		USART_Cmd(USART6, ENABLE);                    //使能串口6 

}

/**
  * @brief  USART6发送一个字符串
**/
void USART6_SendStr(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len)
{
    uint32_t i;
		USART_ClearFlag(USART6,USART_FLAG_TC); 
    for(i=0; i<len; i++)
    {                                         
        USART_SendData(USARTx, *Data++);
        while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
    }
}

