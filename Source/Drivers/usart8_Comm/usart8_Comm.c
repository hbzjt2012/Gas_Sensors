#include "main.h"

//     硬件接线 
//     VCC  -> 3.3V
//     TXD  -> PC2
//     RXD  -> PC3
//     GND  -> GND

uint8_t USART8_RX_STA;
uint8_t USART8_RX_BUF[64];  //接收数据缓冲,最大64个字节

unsigned char USART8_Send_Cmd_01[]={0x53,0x32,0x01,0x39,0x00,0x00,0x00};
unsigned char USART8_Send_Cmd_0C[]={0x53,0x32,0x0C,0x00,0x00,0x00,0x00};
unsigned char USART8_Send_Gas_Data[]={0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char USART8_Send_Cmd_0C_Data = 0;
uint32_t USART8_Send_Cmd_04_Data[10];
uint8_t USART8_Cmd_04_Data[64];

/**
  * @brief  USART8初始化
**/
void USART8_Comm_Init(void)
{
		//GPIO端口设置
		GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART8,ENABLE);   //使能USART8时钟

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);     //使能GPIOC时钟

    //USART8_TX   GPIOC.2
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PC.2
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC.2

		//USART8_RX   GPIOC.3
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PC.3
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//浮空输入
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC.3 
	
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource2,GPIO_AF_2);  //复用串口功能2
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource3,GPIO_AF_2);
		
		//USART初始化设置

    USART_InitStructure.USART_BaudRate = 9600; //串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一位停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式
		USART_Init(USART8, &USART_InitStructure); //初始化串口8
		
		//USART8 NVIC 设置
		NVIC_InitStructure.NVIC_IRQChannel = USART3_8_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority=1 ;//抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure); //根据指定参数初始化NVIC
                    
		USART_ITConfig(USART8, USART_IT_RXNE, ENABLE);//开启串口8接收中断
		USART_ITConfig(USART8, USART_IT_ORE, ENABLE);
		USART_Cmd(USART8, ENABLE);                    //使能串口8 

}

/**
  * @brief  USART8发送一个字符串
**/
void USART8_SendStr(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len)
{
    uint32_t i;
		USART_ClearFlag(USART8,USART_FLAG_TC); 
    for(i=0; i<len; i++)
    {                                         
        USART_SendData(USARTx, *Data++);
        while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
    }
}

