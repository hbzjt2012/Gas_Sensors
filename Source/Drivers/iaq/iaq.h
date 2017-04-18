/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IAQ_H
#define __IAQ_H

#include "stm32f0xx.h"

#define TRUE 1
#define FALSE 0

#define Sensor_ADDRESS 0xb5 //读取sensor地址

//************************************
/*模拟IIC端口输出输入定义*/
#define IAQ_SCL_H         GPIOB->BSRR = GPIO_Pin_8
#define IAQ_SCL_L         GPIOB->BRR  = GPIO_Pin_8 
   
#define IAQ_SDA_H         GPIOB->BSRR = GPIO_Pin_9
#define IAQ_SDA_L         GPIOB->BRR  = GPIO_Pin_9

#define IAQ_SCL_read      GPIOB->IDR  & GPIO_Pin_8
#define IAQ_SDA_read      GPIOB->IDR  & GPIO_Pin_9

//IO方向控制
#define IAQ_SDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9输入模式
#define IAQ_SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9输出模式

//IAQ IIC控制函数
void IAQ_I2C_Delay(void);
uint8_t IAQ_I2C_Start(void);
void IAQ_I2C_Stop(void);
void IAQ_I2C_Ack(void);
void IAQ_I2C_NoAck(void);
uint8_t IAQ_I2C_WaitAck(void);
void IAQ_I2C_SendByte(uint8_t SendByte);
unsigned char IAQ_I2C_ReadByte(void);
uint8_t IAQ_ingle_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
unsigned char IAQ_Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);


void IAQ_Init(void);
void ReadIAQ(uint8_t *s,uint8_t length);
void Get_CO2_TVOC(void);

#endif /* __IAQ_H */
