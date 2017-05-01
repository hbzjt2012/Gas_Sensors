/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MICS_VZ_89TE_H
#define __MICS_VZ_89TE_H

#include "stm32f0xx.h"
#include "sht30.h"

/**************************************************************************************
        以下代码用于读取L3G400传感器,测试IIC
**************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////
//#define	L3G4200_Addr   0xD2 
////***************L3G4200D内部寄存器地址***********
//#define WHO_AM_I 0x0F
//#define CTRL_REG1 0x20
//#define CTRL_REG2 0x21
//#define CTRL_REG3 0x22
//#define CTRL_REG4 0x23
//#define CTRL_REG5 0x24
//#define REFERENCE 0x25
//#define OUT_TEMP 0x26
//#define STATUS_REG 0x27
//#define OUT_X_L 0x28
//#define OUT_X_H 0x29
//#define OUT_Y_L 0x2A
//#define OUT_Y_H 0x2B
//#define OUT_Z_L 0x2C
//#define OUT_Z_H 0x2D
//#define FIFO_CTRL_REG 0x2E
//#define FIFO_SRC_REG 0x2F
//#define INT1_CFG 0x30
//#define INT1_SRC 0x31
//#define INT1_TSH_XH 0x32
//#define INT1_TSH_XL 0x33
//#define INT1_TSH_YH 0x34
//#define INT1_TSH_YL 0x35
//#define INT1_TSH_ZH 0x36
//#define INT1_TSH_ZL 0x37
//#define INT1_DURATION 0x38

etError Single_Write(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data);
etError Single_Read(uint8_t REG_data,uint8_t SlaveAddress,uint8_t REG_Address);
void Init_L3G4200D(void);
void READ_L3G4200D(uint8_t *pBuffer);

/////////////////////////////////////////////////////////////////////////////////////////////


#define MiCS_VZ_89TE_Sensor_ADDRESS 0x70 //0x70 default I2C address
#define MICS_VZ_89TE_ADDR_CMD_GETSTATUS	0x09	// This command is used to read the VZ89 status coded with 6 bytes:

#define MiCS_VZ_89TE_SCLL       (GPIOB->BRR = GPIO_Pin_0)      // set SCL to low
#define MiCS_VZ_89TE_SCLH       (GPIOB->BSRR = GPIO_Pin_0)      // set SCL to open-drain                                         
#define MiCS_VZ_89TE_SDAL       (GPIOB->BRR = GPIO_Pin_1)      // set SDA to low
#define MiCS_VZ_89TE_SDAH       (GPIOB->BSRR = GPIO_Pin_1)      // set SDA to open-drain 

#define MiCS_VZ_89TE_SDA_STATE     (GPIOB->IDR&GPIO_Pin_1)      // read SDA
#define MiCS_VZ_89TE_SCL_STATE     (GPIOB->IDR&GPIO_Pin_0)      // read SCL

/* Private functions ---------------------------------------------------------*/
void MiCS_VZ_89TE_I2C_Init(void);
void MiCS_VZ_89TE_I2C_StartCondition(void);
void MiCS_VZ_89TE_I2C_StopCondition(void);
etError MiCS_VZ_89TE_I2C_WriteByte(uint8_t txByte);
etError MiCS_VZ_89TE_I2C_ReadByte(uint8_t *rxByte, etI2cAck ack, uint8_t timeout);
etError MiCS_VZ_89TE_I2C_GeneralCallReset(void);
static etError MiCS_VZ_89TE_I2C_WaitWhileClockStreching(uint8_t timeout);

void MiCS_VZ_89TE_Init(uint8_t i2cAddress);
void MiCS_VZ_89TE_SetI2CAdr(uint8_t i2cAddress);
static etError MiCS_VZ_89TE_StartWriteAccess(void);
static etError MiCS_VZ_89TE_StartReadAccess(void);
static void MiCS_VZ_89TE_StopAccess(void);


etError MiCS_VZ_89TE_ReadStatus(uint8_t *pBuffer, etI2cAck finaleAckNack, uint8_t timeout);


#endif /* __MICS_VZ_89TE_H */


