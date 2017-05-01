/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MICS_VZ_89TE_IIC_H
#define __MICS_VZ_89TE_IIC_H

#include "stm32f0xx.h" 
    
#define	MICS_VZ_89TE_Addr   0x70 

//***************MICS_VZ_89TE内部寄存器***********
#define MICS_VZ_89TE_STATUS_REG 0x09


//************************************
/*模拟IIC输入输出端口设置*/
#define MICS_VZ_89TE_IIC_SCL_H         GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define MICS_VZ_89TE_IIC_SCL_L         GPIO_ResetBits(GPIOB, GPIO_Pin_0)
   
#define MICS_VZ_89TE_IIC_SDA_H         GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define MICS_VZ_89TE_IIC_SDA_L         GPIO_ResetBits(GPIOB, GPIO_Pin_1)
    
//IO方向设置
#define MICS_VZ_89TE_IIC_SDA_IN()  {GPIOB->MODER&=~(3<<(1*2));GPIOB->MODER|=0<<1*2;}	//PB1输入模式
#define MICS_VZ_89TE_IIC_SDA_OUT() {GPIOB->MODER&=~(3<<(1*2));GPIOB->MODER|=1<<1*2;} //PB1输出模式

#define MICS_VZ_89TE_IIC_SCL_read      GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)
#define MICS_VZ_89TE_IIC_SDA_read      GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)
    
  
//MICS_VZ_89TE IIC控制函数
void MICS_VZ_89TE_IIC_I2C_delay(void);
uint8_t MICS_VZ_89TE_IIC_I2C_Start(void);
void MICS_VZ_89TE_IIC_I2C_Stop(void);
void MICS_VZ_89TE_IIC_I2C_Ack(void);
void MICS_VZ_89TE_IIC_I2C_NoAck(void);
uint8_t MICS_VZ_89TE_IIC_I2C_WaitAck(void);
void MICS_VZ_89TE_IIC_I2C_SendByte(uint8_t SendByte);
uint8_t MICS_VZ_89TE_IIC_I2C_ReadByte(void);
uint8_t MICS_VZ_89TE_IIC_Single_Write(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data);
uint8_t MICS_VZ_89TE_IIC_Single_Read(uint8_t SlaveAddress,uint8_t REG_Address);
void MICS_VZ_89TE_IIC_I2C_Init(void);
uint8_t MiCS_VZ_89TE_IIC_ReadStatus(uint8_t *pBuffer);

#endif /* __MICS_VZ_89TE_IIC_H */


