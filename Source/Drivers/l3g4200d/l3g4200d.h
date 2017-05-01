/******************************************************************************
  * @file    L3G4200D.h
  * @author  xxx
	* @from    hbzjt2011 QQ956139733
  * @date    03-13-2017
  ******************************************************************************/ 
#ifndef __L3G4200D_H
#define __L3G4200D_H		
 
#include "stm32f0xx.h" 
    
#define	L3G4200_Addr   0xD2 
//***************L3G4200D内部寄存器***********
#define WHO_AM_I 0x0F
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define REFERENCE 0x25
#define OUT_TEMP 0x26
#define STATUS_REG 0x27
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D
#define FIFO_CTRL_REG 0x2E
#define FIFO_SRC_REG 0x2F
#define INT1_CFG 0x30
#define INT1_SRC 0x31
#define INT1_TSH_XH 0x32
#define INT1_TSH_XL 0x33
#define INT1_TSH_YH 0x34
#define INT1_TSH_YL 0x35
#define INT1_TSH_ZH 0x36
#define INT1_TSH_ZL 0x37
#define INT1_DURATION 0x38

//************************************
/*模拟IIC输入输出端口设置*/
#define L3G4200D_SCL_H         GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define L3G4200D_SCL_L         GPIO_ResetBits(GPIOB, GPIO_Pin_8)
   
#define L3G4200D_SDA_H         GPIO_SetBits(GPIOB, GPIO_Pin_9)
#define L3G4200D_SDA_L         GPIO_ResetBits(GPIOB, GPIO_Pin_9)
    
//IO方向设置
#define L3G4200D_SDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9输入模式
#define L3G4200D_SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9输出模式

#define L3G4200D_SCL_read      GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)
#define L3G4200D_SDA_read      GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)
    
  
//L3G4200D IIC控制函数
void L3G4200D_I2C_delay(void);
uint8_t L3G4200D_I2C_Start(void);
void L3G4200D_I2C_Stop(void);
void L3G4200D_I2C_Ack(void);
void L3G4200D_I2C_NoAck(void);
uint8_t L3G4200D_I2C_WaitAck(void);
void L3G4200D_I2C_SendByte(uint8_t SendByte);
uint8_t L3G4200D_I2C_RadeByte(void);
uint8_t L3G4200D_Single_Write(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data);
uint8_t L3G4200D_Single_Read(uint8_t SlaveAddress,uint8_t REG_Address);
void L3G4200D_I2C_Init(void);
void L3G4200D_Init(void);
void L3G4200D_Read(void);
void L3G4200D_Send_data(uint8_t axis);
void L3G4200D_DATA_printf(uint8_t *s,short temp_data);

#endif  
