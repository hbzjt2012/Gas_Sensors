/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IAQ_H
#define __IAQ_H

#include "stm32f0xx.h"

#define Sensor_ADDRESS 0xb5 //¶ÁÈ¡sensorµØÖ·

#define SCLL       (GPIOB->BRR = GPIO_Pin_8)       // set SCL to low
#define SCLH       (GPIOB->BSRR = GPIO_Pin_8)      // set SCL to open-drain                                       
#define SDAL       (GPIOB->BRR = GPIO_Pin_9)       // set SDA to low
#define SDAH       (GPIOB->BSRR = GPIO_Pin_9)      // set SDA to open-drain

#define SDA_STATE     (GPIOB->IDR&GPIO_Pin_9)      // read SDA

enum I2C_REPLY {I2C_NACK = 0, I2C_ACK = 1};

enum I2C_STATE {I2C_READY = 0, I2C_BUSY = 1, I2C_ERROR = 2};

/* Private functions ---------------------------------------------------------*/
void IAQ_Init(void);
static uint8_t I2C_Start(void);
static void I2C_Stop(void);
static void I2C_Ack(uint8_t);
static uint8_t I2C_Wait_Ack(void);
static void I2C_SendByte(uint8_t);
static uint8_t I2C_ReceiveByte(void);
uint8_t IAQ_Read(uint8_t *pBuffer, uint8_t NumByteToRead);

#endif /* __IAQ_H */
