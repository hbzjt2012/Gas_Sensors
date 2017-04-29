#include "main.h"
  
/*******************************************************************************/
void IAQ_Init(void)
{ 
	 GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);     //使能GPIOB时钟

	 //配置I2C1_SCL(PB8)和I2C1_SDA(PB9)开漏输出
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
}
  
/*******************************************************************************/
static uint8_t I2C_Start(void)
{
		SDAH;
		SCLH;
		delay_us(5);
		if(!SDA_STATE) {
						printf("I2C is busy!\r\n");
						return I2C_BUSY;         
		}
		SDAL;
		delay_us(5);
		SCLL;
		delay_us(10);
		if(SDA_STATE) {
						printf("I2C is error!\r\n");
						return I2C_ERROR;
		}
		return I2C_READY;
}
/*******************************************************************************/
static void I2C_Stop(void)
{
		SDAL;
		delay_us(5);
		SCLH;
		delay_us(5);
		SDAH;
		delay_us(5);
}
/*******************************************************************************/
static void I2C_Ack(uint8_t i)
{
		if(i)
						SDAL;                                //ACK
		else                                        
						SDAH;                                //NACK
		delay_us(2);
		SCLH;
		delay_us(2);
		SCLL;
		delay_us(2); 
}
/*******************************************************************************/
static uint8_t I2C_Wait_Ack(void)
{
		uint8_t ucErrTime = 0;
		SDAH;
		delay_us(2);
		SCLH;
		delay_us(2);
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
		delay_us(2);
		return I2C_ACK;
}
/*******************************************************************************/
static void I2C_SendByte(uint8_t d)
{
		uint8_t i;

		SCLL;
		delay_us(2);
		for(i=0x80;i!=0;i/=2)
		{
							if(i&d)
											 SDAH;
							else
											 SDAL;
						delay_us(2);
							SCLH;
							delay_us(2);
							SCLL;
							delay_us(2);
		}
}
/*******************************************************************************/
static uint8_t I2C_ReceiveByte(void)
{
		uint8_t i, d=0;
		SDAH;
		SCLL;
		delay_us(2);
		for(i=0x80;i!=0;i/=2)
		{
							SCLH;
						delay_us(2);
						if(SDA_STATE)
											 d |= i;
						 SCLL;
							delay_us(2);
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
		delay_us(20);
		I2C_SendByte(0xB5);
		delay_us(20);
		if(!I2C_Wait_Ack()) {
						printf("No Ack after send address!\r\n");
						return 2;
		}

		while(NumByteToRead--) {
										delay_us(20);
										*pBuffer++ = I2C_ReceiveByte();
										delay_us(20);
										if(NumByteToRead)
														I2C_Ack(1);
										else
														I2C_Ack(0);        
		}
		return 0;
}

