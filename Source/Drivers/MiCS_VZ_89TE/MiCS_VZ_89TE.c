#include "main.h"

/*******************************************************************************/
void MiCS_VZ_89TE_Init(void)
{ 
	 GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);     //使能GPIOB时钟

	 //配置I2C1_SCL(PB8)和I2C1_SDA(PB9)开漏输出
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		MiCS_VZ_89TE_SDAH;
		MiCS_VZ_89TE_SCLH;
}
  
/*******************************************************************************/
static uint8_t MiCS_VZ_89TE_I2C_Start(void)
{
		MiCS_VZ_89TE_SDAH;
		SysTick_delay_us(1);
		MiCS_VZ_89TE_SCLH;
		SysTick_delay_us(1);
		if(!MiCS_VZ_89TE_SDA_STATE) {
						printf("MiCS_VZ_89TE_I2C is busy!\r\n");
						return MiCS_VZ_89TE_I2C_BUSY;         
		}
		MiCS_VZ_89TE_SDAL;
		SysTick_delay_us(10);
		MiCS_VZ_89TE_SCLL;
		SysTick_delay_us(10);
		if(MiCS_VZ_89TE_SDA_STATE) {
						printf("MiCS_VZ_89TE_I2C is error!\r\n");
						return MiCS_VZ_89TE_I2C_ERROR;
		}
		return MiCS_VZ_89TE_I2C_READY;
}
/*******************************************************************************/
static void MiCS_VZ_89TE_I2C_Stop(void)
{
		MiCS_VZ_89TE_SCLL;
		SysTick_delay_us(1);
		MiCS_VZ_89TE_SDAL;
		SysTick_delay_us(1);
		MiCS_VZ_89TE_SCLH;
		SysTick_delay_us(10);
		MiCS_VZ_89TE_SDAH;
		SysTick_delay_us(10);
}
/*******************************************************************************/
static void MiCS_VZ_89TE_I2C_Ack(uint8_t i)
{
		MiCS_VZ_89TE_SCLL;
		SysTick_delay_us(2);
		if(i)
						MiCS_VZ_89TE_SDAL;                                //ACK
		else                                        
						MiCS_VZ_89TE_SDAH;                                //NACK
		SysTick_delay_us(2);
		MiCS_VZ_89TE_SCLH;
		SysTick_delay_us(2);
		MiCS_VZ_89TE_SCLL;
		SysTick_delay_us(2); 
}
/*******************************************************************************/
static uint8_t MiCS_VZ_89TE_I2C_Wait_Ack(void)
{
		uint8_t ucErrTime = 0;
		MiCS_VZ_89TE_SCLL;
		SysTick_delay_us(2);
		MiCS_VZ_89TE_SDAH;
		SysTick_delay_us(2);
		MiCS_VZ_89TE_SCLH;
		SysTick_delay_us(2);
		while(MiCS_VZ_89TE_SDA_STATE)
		{
						ucErrTime++;
						if(ucErrTime > 250)
						{
										MiCS_VZ_89TE_I2C_Stop();
										printf("MiCS_VZ_89TE_I2C NACK!\r\n");
										return MiCS_VZ_89TE_I2C_NACK;
						}
		}
		MiCS_VZ_89TE_SCLL;
		SysTick_delay_us(2);
		return MiCS_VZ_89TE_I2C_ACK;
}
/*******************************************************************************/
static void MiCS_VZ_89TE_I2C_SendByte(uint8_t d)
{
		uint8_t i;

		MiCS_VZ_89TE_SCLL;
		SysTick_delay_us(2);
		for(i=0x80;i!=0;i/=2)
		{
			if(i&d)
							 MiCS_VZ_89TE_SDAH;
			else
							 MiCS_VZ_89TE_SDAL;
			SysTick_delay_us(2);
			MiCS_VZ_89TE_SCLH;
			SysTick_delay_us(2);
			MiCS_VZ_89TE_SCLL;
			SysTick_delay_us(2);
		}
}
/*******************************************************************************/
static uint8_t MiCS_VZ_89TE_I2C_ReceiveByte(void)
{
		uint8_t i, d=0;
		MiCS_VZ_89TE_SDAH;
		MiCS_VZ_89TE_SCLL;
		SysTick_delay_us(2);
		for(i=0x80;i!=0;i/=2)
		{
			MiCS_VZ_89TE_SCLH;
			SysTick_delay_us(2);
			if(MiCS_VZ_89TE_SDA_STATE)
					 d |= i;
		  MiCS_VZ_89TE_SCLL;
			SysTick_delay_us(2);
		}
		return d;
}
/*******************************************************************************/
uint8_t MiCS_VZ_89TE_Read(uint8_t *pBuffer, uint8_t NumByteToRead)
{
        
		if(MiCS_VZ_89TE_I2C_Start()) {
						printf("MiCS_VZ_89TE_Start error!\r\n");
						return 1;
		}
		SysTick_delay_us(20);
		MiCS_VZ_89TE_I2C_SendByte(MiCS_VZ_89TE_Sensor_ADDRESS);
		SysTick_delay_us(20);
		if(!MiCS_VZ_89TE_I2C_Wait_Ack()) {
						printf("MiCS_VZ_89TE No Ack after send address!\r\n");
						return 2;
		}
		
		MiCS_VZ_89TE_I2C_SendByte(MICS_VZ_89TE_ADDR_CMD_GETSTATUS);
		SysTick_delay_us(20);
		if(!MiCS_VZ_89TE_I2C_Wait_Ack()) {
						printf("MiCS_VZ_89TE No Ack after send CMD_GETSTATUS!\r\n");
						return 2;
		}
		
		MiCS_VZ_89TE_I2C_SendByte(0x00);
		SysTick_delay_us(20);
		if(!MiCS_VZ_89TE_I2C_Wait_Ack()) {
						printf("MiCS_VZ_89TE No Ack after send Data byte 1 MSB!\r\n");
						return 2;
		}
		
		MiCS_VZ_89TE_I2C_SendByte(0x00);
		SysTick_delay_us(20);
		if(!MiCS_VZ_89TE_I2C_Wait_Ack()) {
						printf("MiCS_VZ_89TE No Ack after send Data byte 1 LSB!\r\n");
						return 2;
		}
		
		MiCS_VZ_89TE_I2C_SendByte(0xE1);
		SysTick_delay_us(20);
		if(!MiCS_VZ_89TE_I2C_Wait_Ack()) {
						printf("MiCS_VZ_89TE No Ack after send CMD_TRANSMISSION!\r\n");
						return 2;
		}	
		
		MiCS_VZ_89TE_I2C_SendByte(MICS_VZ_89TE_ADDR_CMD_GETSTATUS);
		SysTick_delay_us(20);
		if(!MiCS_VZ_89TE_I2C_Wait_Ack()) {
						printf("MiCS_VZ_89TE No Ack after send CMD_GETSTATUS!\r\n");
						return 2;
		}

		while(NumByteToRead--) {
										SysTick_delay_us(20);
										*pBuffer++ = MiCS_VZ_89TE_I2C_ReceiveByte();
										SysTick_delay_us(20);
										if(NumByteToRead)
														MiCS_VZ_89TE_I2C_Ack(1);
										else
														MiCS_VZ_89TE_I2C_Ack(0);        
		}
		return 0;
}


