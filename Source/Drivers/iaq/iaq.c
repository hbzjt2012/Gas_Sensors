#include "main.h"

//     硬件接线 
//     VCC  -> +5V
//     GND  -> GND
//     SDA  -> PA11
//     SCL  -> PA12
  
/*******************************************************************************/
void IAQ_Init(void)
{ 
	 GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);     //使能GPIOA时钟

	 //配置I2C1_SCL(PA11)和I2C1_SDA(PA12)开漏输出
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	 SDAH;
	 SCLH;
}

void I2C_SDA_OUT(void)//SDA输出
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 		 //开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.12	
}
void I2C_SDA_IN(void)//SDA输入
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 		 //上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.12	
}
  
/*******************************************************************************/
static uint8_t I2C_Start(void)
{
	  I2C_SDA_OUT();//SDA输出
	
		SDAH;
		SysTick_delay_us(1);
		SCLH;
		SysTick_delay_us(1);
		if(!SDA_STATE) {
						printf("I2C is busy!\r\n");
						return I2C_BUSY;         
		}
		SDAL;
		SysTick_delay_us(10);
		SCLL;
		SysTick_delay_us(10);
		if(SDA_STATE) {
						printf("I2C is error!\r\n");
						return I2C_ERROR;
		}
		return I2C_READY;
}
/*******************************************************************************/
static void I2C_Stop(void)
{
		I2C_SDA_OUT();//SDA输出
	
		SCLL;
		SysTick_delay_us(1);
		SDAL;
	  SysTick_delay_us(1);
		SCLH;
		SysTick_delay_us(10);
		SDAH;
		SysTick_delay_us(10);
}
/*******************************************************************************/
static void I2C_Ack(uint8_t i)
{
	  SCLL;
	  I2C_SDA_OUT();//SDA输出
	
		if(i)
						SDAL;                                //ACK
		else                                        
						SDAH;                                //NACK
		SysTick_delay_us(2);
		SCLH;
		SysTick_delay_us(2);
		SCLL;
		SysTick_delay_us(2); 
}
/*******************************************************************************/
static uint8_t I2C_Wait_Ack(void)
{
		uint8_t ucErrTime = 0;
	  I2C_SDA_IN();//SDA输入
	
		SDAH;
		SysTick_delay_us(10);
		SCLH;
		SysTick_delay_us(10);
		while(SDA_STATE)
		{
						ucErrTime++;
						if(ucErrTime > 250)
						{
										I2C_Stop();
										printf("I2C NACK!\r\n");
										return I2C_NACK;
						}
		}
		SCLL;
		SysTick_delay_us(2);
		return I2C_ACK;
}
/*******************************************************************************/
static void I2C_SendByte(uint8_t d)
{
		uint8_t i;
	
		I2C_SDA_OUT();//SDA输出

		SCLL;
		SysTick_delay_us(2);
		for(i=0x80;i!=0;i/=2)
		{
							if(i&d)
											 SDAH;
							else
											 SDAL;
						SysTick_delay_us(2);
							SCLH;
							SysTick_delay_us(10);
							SCLL;
							SysTick_delay_us(10);
		}
		SCLH;    //拉高使数据稳定传输
		SysTick_delay_us(10);
		SCLL;    //拉低继续发送数据
		SysTick_delay_us(10);
}
/*******************************************************************************/
static uint8_t I2C_ReceiveByte(void)
{
		uint8_t i, d=0;
	
    I2C_SDA_IN();  //SDA输入
	
		SDAH;
		SCLL;
		SysTick_delay_us(2);
		for(i=0x80;i!=0;i/=2)
		{
							SCLH;
						SysTick_delay_us(2);
						if(SDA_STATE)
											 d |= i;
						 SCLL;
							SysTick_delay_us(2);
		}
		return d;
}
/*******************************************************************************/
uint8_t IAQ_Read(uint8_t *pBuffer, uint8_t NumByteToRead)
{
        
		if(I2C_Start()) {
						printf("Start error!\r\n");
						return 1;
		}
		SysTick_delay_us(20);
		I2C_SendByte(0xB5);
		SysTick_delay_us(20);
		if(!I2C_Wait_Ack()) {
						printf("No Ack after send address!\r\n");
						return 2;
		}

		while(NumByteToRead--) {
										SysTick_delay_us(20);
										*pBuffer++ = I2C_ReceiveByte();
										SysTick_delay_us(20);
										if(NumByteToRead)
														I2C_Ack(1);
										else
														I2C_Ack(0);        
		}
		return 0;
}

