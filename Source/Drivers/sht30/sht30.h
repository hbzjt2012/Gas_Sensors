/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SHT30_H
#define __SHT30_H

#include "stm32f0xx.h"

#define SHT30_ADDR 0x44  //ADDR (pin 2)connected to VDD

#define TRUE 1
#define FALSE 0

//************************************
/*模拟IIC端口输出输入定义*/
#define SCL_H         GPIOC->BSRR = GPIO_Pin_11
#define SCL_L         GPIOC->BRR  = GPIO_Pin_11 
   
#define SDA_H         GPIOD->BSRR = GPIO_Pin_2
#define SDA_L         GPIOD->BRR  = GPIO_Pin_2

#define SCL_read      GPIOC->IDR  & GPIO_Pin_11
#define SDA_read      GPIOD->IDR  & GPIO_Pin_2

//IO方向控制
#define SDA_IN()  {GPIOD->MODER&=~(3<<(2*2));GPIOD->MODER|=0<<2*2;}	//PD2输入模式
#define SDA_OUT() {GPIOD->MODER&=~(3<<(2*2));GPIOD->MODER|=1<<2*2;} //PD2输出模式

//SHT30-Dis IIC控制函数
void I2C_Delay(void);
uint8_t I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_NoAck(void);
uint8_t I2C_WaitAck(void);
void I2C_SendByte(uint8_t SendByte);
unsigned char I2C_ReadByte(void);
uint8_t Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);

void Cmd_Write_SHT30(uint8_t MSB,uint8_t LSB);
void Read_SHT30(void);
void Convert_SHT30(void);
void SHT30_Init(void);

#endif /* __SHT30_H */
