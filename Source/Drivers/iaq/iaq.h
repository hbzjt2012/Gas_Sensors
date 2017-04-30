/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IAQ_H
#define __IAQ_H

#include "stm32f0xx.h"

#define Sensor_ADDRESS 0xb5 //读取sensor地址

#define SCLL       (GPIOA->BRR = GPIO_Pin_11)       // set SCL to low
#define SCLH       (GPIOA->BSRR = GPIO_Pin_11)      // set SCL to open-drain                                       
#define SDAL       (GPIOA->BRR = GPIO_Pin_12)       // set SDA to low
#define SDAH       (GPIOA->BSRR = GPIO_Pin_12)      // set SDA to open-drain

#define SDA_STATE     (GPIOA->IDR&GPIO_Pin_12)      // read SDA

enum I2C_REPLY {I2C_NACK = 0, I2C_ACK = 1};

enum I2C_STATE {I2C_READY = 0, I2C_BUSY = 1, I2C_ERROR = 2};

/* Private functions ---------------------------------------------------------*/
void IAQ_Init(void);
void I2C_SDA_OUT(void);//SDA输出
void I2C_SDA_IN(void); //SDA输入
static uint8_t I2C_Start(void);
static void I2C_Stop(void);
static void I2C_Ack(uint8_t);
static uint8_t I2C_Wait_Ack(void);
static void I2C_SendByte(uint8_t);
static uint8_t I2C_ReceiveByte(void);
uint8_t IAQ_Read(uint8_t *pBuffer, uint8_t NumByteToRead);

#endif /* __IAQ_H */
