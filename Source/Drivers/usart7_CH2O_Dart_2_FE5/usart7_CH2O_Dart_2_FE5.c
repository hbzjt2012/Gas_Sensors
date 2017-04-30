#include "main.h"

//     硬件接线 
//     Pin1-VCC  -> 5V
//     Pin2-TXD  -> PC7
//     Pin3-RXD  -> PC6
//     Pin4-GND  -> GND

uint8_t USART7_RX_STA;
uint8_t USART7_RX_BUF[64];  //接收数据缓冲,最大64个字节

/**
  * @brief  USART7初始化
**/
void USART7_CH2O_Dart_2_FE5_Init(void)
{
		//GPIO端口设置
		GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART7,ENABLE);   //使能USART7时钟

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);     //使能GPIOC时钟

    //USART7_TX   GPIOC.6
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //PC.6
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC.6

		//USART7_RX   GPIOC.7
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//PC.7
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//浮空输入
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC.7 
	
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_1);  //复用串口功能1
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_1);
		
		//USART初始化设置

    USART_InitStructure.USART_BaudRate = 9600; //串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一位停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式
		USART_Init(USART7, &USART_InitStructure); //初始化串口7
		
		//USART7 NVIC 设置
		NVIC_InitStructure.NVIC_IRQChannel = USART3_8_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority=2 ;//抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure); //根据指定参数初始化NVIC
                    
		USART_ITConfig(USART7, USART_IT_RXNE, ENABLE);//开启串口7接收中断
		USART_ITConfig(USART7, USART_IT_ORE, ENABLE);
		USART_Cmd(USART7, ENABLE);                    //使能串口7 

}

/**
  * @brief  USART7发送一个字符串
**/
void USART7_SendStr(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len)
{
    uint32_t i;
		USART_ClearFlag(USART7,USART_FLAG_TC); 
    for(i=0; i<len; i++)
    {                                         
        USART_SendData(USARTx, *Data++);
        while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
    }
}

