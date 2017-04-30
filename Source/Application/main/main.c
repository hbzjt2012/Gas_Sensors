/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-May-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
etError   error;       // error code
uint32_t      serialNumber;// serial number
regStatus status;      // sensor status
float        temperature; // temperature [癈]
float        humidity;    // relative humidity [%RH]
 // bt        heater;      // heater, false: off, true: on

uint8_t buf[15];
uint8_t dd=0;

/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
		SystemInit();
	  delay_init();
		TIM2_Init();    //定时器2初始化
		USART1_PM25_Init();         //USART1串口初始化,用于接收PM2.5传感器数据
		USART2_Init(); 			        //USART2串口初始化函数
		USART3_CO_Init();           //USART3串口初始化,用于接收CO传感器数据
	  USART4_CO2_T6703_Init();    //USART4串口初始化,用于接收CO2传感器数据 T6703传感器
		USART5_CH2O_AS04_Init();    //USART5串口初始化,用于接收CH2O传感器数据 AS04传感器
		USART6_CO2_S8_0053_Init();  //USART6串口初始化,用于接收CO2传感器数据 S8-0053传感器
		USART7_CH2O_Dart_2_FE5_Init(); //USART7串口初始化,用于接收CH2O传感器数据 Dart_2_FE5传感器
		USART8_Comm_Init();         //USART8串口初始化,用于发送所有传感器数据与命令传输
	  LED_Init();    //板载LED灯 LD2绿色
		SHT3X_Init(0x44); // Address: 0x44 = Sensor on EvalBoard connector
                    //          0x45 = Sensor on EvalBoard  //SHT30温湿度传感器初始化
	  // wait 50ms after power on
		SysTick_delay_ms(50);
	  error = SHT3x_ReadSerialNumber(&serialNumber);
		if(error != NO_ERROR){} // do error handling here
		//start periodic measurement, with high repeatability and 1 measurements per second
		error = SHT3X_StartPeriodicMeasurment(REPEATAB_HIGH, FREQUENCY_1HZ);
		if(error != NO_ERROR)  {}// do error handling here	
		
	  IAQ_Init();   //IAQ传感器初始化
		SPI_Flash_Init();  		//SPI FLASH 初始化		
		while(SPI_Flash_ReadID()!=W25Q64)							//检测不到W25Q64
		{
			LD2_OFF();
			SysTick_delay_ms(500);
			LD2_ON();
			SysTick_delay_ms(500);
			printf(" SPI_Flash ID Read Failed!\r\n");
		} 
		printf(" SPI_Flash ID:%x\r\nr\n",SPI_FLASH_TYPE);
		


		while(1)
		{		
				dd=IAQ_Read(buf,8);
			  
				//USART8_SendStr(USART8,buf,8);
				
				
				SysTick_delay_ms(2000);
				printf("Hello world! \r\n");
		}
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
