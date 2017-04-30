/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MICS_VZ_89TE_H
#define __MICS_VZ_89TE_H

#include "stm32f0xx.h"

#define MiCS_VZ_89TE_Sensor_ADDRESS 0x70 //0x70 default I2C address
#define MICS_VZ_89TE_ADDR_CMD_GETSTATUS	0x0C	// This command is used to read the VZ89 status coded with 6 bytes:

#define MiCS_VZ_89TE_SCLL       (GPIOB->BRR = GPIO_Pin_8)      // set SCL to low
#define MiCS_VZ_89TE_SCLH       (GPIOB->BSRR = GPIO_Pin_8)      // set SCL to open-drain                                         
#define MiCS_VZ_89TE_SDAL       (GPIOB->BRR = GPIO_Pin_9)      // set SDA to low
#define MiCS_VZ_89TE_SDAH       (GPIOB->BSRR = GPIO_Pin_9)      // set SDA to open-drain 

#define MiCS_VZ_89TE_SDA_STATE     (GPIOB->IDR&GPIO_Pin_9)      // read SDA

enum MiCS_VZ_89TE_I2C_REPLY {MiCS_VZ_89TE_I2C_NACK = 0, MiCS_VZ_89TE_I2C_ACK = 1};

enum MiCS_VZ_89TE_I2C_STATE {MiCS_VZ_89TE_I2C_READY = 0, MiCS_VZ_89TE_I2C_BUSY = 1, MiCS_VZ_89TE_I2C_ERROR = 2};

/* Private functions ---------------------------------------------------------*/
void MiCS_VZ_89TE_Init(void);
static uint8_t MiCS_VZ_89TE_I2C_Start(void);
static void MiCS_VZ_89TE_I2C_Stop(void);
static void MiCS_VZ_89TE_I2C_Ack(uint8_t);
static uint8_t MiCS_VZ_89TE_I2C_Wait_Ack(void);
static void MiCS_VZ_89TE_I2C_SendByte(uint8_t);
static uint8_t MiCS_VZ_89TE_I2C_ReceiveByte(void);
uint8_t MiCS_VZ_89TE_Read(uint8_t *pBuffer, uint8_t NumByteToRead);


#endif /* __MICS_VZ_89TE_H */


