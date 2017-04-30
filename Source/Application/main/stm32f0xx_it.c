/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
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
#include "stm32f0xx_it.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

//USART1变量定义
extern	uint8_t USART_RX_STA;
extern	uint8_t USART_RX_BUF[64];  //接收数据缓冲区,最大64个字节

//USART3变量定义
extern	uint8_t USART3_RX_STA;
extern	uint8_t USART3_RX_BUF[64];  //接收数据缓冲区,最大64个字节

//USART4变量定义
extern	uint8_t USART4_RX_STA;
extern	uint8_t USART4_RX_BUF[64];  //接收数据缓冲区,最大64个字节

//USART5变量定义
extern	uint8_t USART5_RX_STA;
extern	uint8_t USART5_RX_BUF[64];  //接收数据缓冲区,最大64个字节

//USART6变量定义
extern	uint8_t USART6_RX_STA;
extern	uint8_t USART6_RX_BUF[64];  //接收数据缓冲区,最大64个字节

//USART7变量定义
extern	uint8_t USART7_RX_STA;
extern	uint8_t USART7_RX_BUF[64];  //接收数据缓冲区,最大64个字节

//USART8变量定义
extern	uint8_t USART8_RX_STA;
extern	uint8_t USART8_RX_BUF[64];  //接收数据缓冲区,最大64个字节
extern unsigned char USART8_Send_Cmd_01[];
extern unsigned char USART8_Send_Cmd_0C[];
extern unsigned char USART8_Send_Cmd_0C_Data;
extern uint32_t USART8_Send_Cmd_04_Data[10];
extern uint8_t USART8_Cmd_04_Data[64];
extern uint8_t SPI_Flash_ReadBuffer[25];

extern unsigned char ReadCO_Cmd[];
extern unsigned char T6703_ReadGas_Cmd[];
extern unsigned char ReadCH2O_Cmd[];
extern unsigned char ReadCO2_S8_Cmd[];
extern unsigned char USART8_Send_Gas_Data[];

extern etError   error;       // error code
extern uint32_t      serialNumber;// serial number
extern regStatus status;      // sensor status
extern float        temperature; // temperature [癈]
extern float        humidity;    // relative humidity [%RH]

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  This function handles TIM2 interrupt request.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
	 if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		{
			TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
			
			USART3_SendStr(USART3,ReadCO_Cmd,8);
			USART4_SendStr(USART4,T6703_ReadGas_Cmd,8);
			USART5_SendStr(USART5,ReadCH2O_Cmd,8);
			USART6_SendStr(USART6,ReadCO2_S8_Cmd,8);
			USART8_SendStr(USART8,USART8_Send_Gas_Data,17);

			// read measurment buffer
			error = SHT3X_ReadMeasurementBuffer(&temperature, &humidity); 
			if(error != NO_ERROR) // do error handling here	
			{
				printf("SHT3x-Dis Read Error!\r\n");
			}					
			
			//更新温湿度数据
			USART8_Send_Gas_Data[13]=((int)(temperature*10))/256;   //温度高位
			USART8_Send_Gas_Data[14]=((int)(temperature*10))%256;   //温度低位
			USART8_Send_Gas_Data[15]=((int)(humidity*10))/256;      //湿度高位
			USART8_Send_Gas_Data[16]=((int)(humidity*10))%256;      //湿度低位
			
			printf("serialNumber=%d  error=%d\n",serialNumber,error);
			printf("temperature=%.1f humidity=%.1f \n",temperature,humidity);
			
			printf("TIM2 ...\r\n");
		}
}

/**
  * @brief  This function handles USART1 interrupt request.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)     //串口1中断服务函数
{
		uint8_t Res;
    static char start=0;
		
		if (USART_GetITStatus(USART1, USART_IT_ORE) == SET)  
    {  
        USART_ClearITPendingBit(USART1,USART_IT_ORE);      
        USART_ReceiveData( USART1 );  
  
    }

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
		{
				USART_ClearITPendingBit(USART1,USART_IT_RXNE);  
				Res =USART_ReceiveData(USART1); //读取接收到的数据
				//USART_SendData(USART1,Res);
				if(Res == 0x42) //如果接收到的第一位数据是0X42(这个是查看传感器手册得知的)
				{
						USART_RX_STA = 0;     //让数组索引值从0开始
						start = 1;  //这个变量用来确定第二位是否接收到了0X4D(这个也是查看传感器手册得知的)
				}

				if(start == 1)
				{
					USART_RX_BUF[USART_RX_STA] = Res ; //把接收到的数据存到数组里面
					USART_RX_STA++;
					if(USART_RX_STA >= 23 && (USART_RX_BUF[1]==0x4d))
					{
							//USART_SendData(USART1,USART_RX_BUF[12]*256+USART_RX_BUF[13]);
						  
						  //更新PM2.5和PM10数据
						  USART8_Send_Gas_Data[1]=USART_RX_BUF[6];
							USART8_Send_Gas_Data[2]=USART_RX_BUF[7];
							USART8_Send_Gas_Data[3]=USART_RX_BUF[14];
							USART8_Send_Gas_Data[4]=USART_RX_BUF[15];
						  
							printf("PM2.5:%d\n",USART_RX_BUF[6]*256+USART_RX_BUF[7]);
							printf("PM10:%d\n",USART_RX_BUF[14]*256+USART_RX_BUF[15]);
							start  = 0;
							USART_RX_STA=0;//重新开始接收   
							USART_RX_BUF[0] = 0;
					}
				}                   
    }
}

/**
  * @brief  This function handles USARTy global interrupt request.
  * @param  None
  * @retval None
  */
void USART3_8_IRQHandler(void)
{
		uint8_t USART3_Res;
    static char USART3_start=0;
	
		uint8_t USART4_Res;
    static char USART4_start=0;
	
		uint8_t USART5_Res;
    static char USART5_start=0;
	
		uint8_t USART6_Res;
    static char USART6_start=0;
	
		uint8_t USART7_Res;
    static char USART7_start=0;
	
		uint8_t USART8_Res;
    static char USART8_start=0;
		
	
	  //USART3串口中断处理
		if (USART_GetITStatus(USART3, USART_IT_ORE) == SET)  
    {  
        USART_ClearITPendingBit(USART3,USART_IT_ORE);      
        USART_ReceiveData( USART3 );  
  
    }

    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断
		{
				USART_ClearITPendingBit(USART3,USART_IT_RXNE);  
				USART3_Res =USART_ReceiveData(USART3); //读取接收到的数据
				//USART_SendData(USART1,Res);
				if(USART3_Res == 0x01) //如果接收到的第一位数据是0X42(这个是查看传感器手册得知的)
				{
						USART3_RX_STA = 0;     //让数组索引值从0开始
						USART3_start = 1;  //这个变量用来确定第二位是否接收到了0X4D(这个也是查看传感器手册得知的)
				}

				if(USART3_start == 1)
				{
					USART3_RX_BUF[USART3_RX_STA] = USART3_Res ; //把接收到的数据存到数组里面
					USART3_RX_STA++;
					if(USART3_RX_STA >= 7 && (USART3_RX_BUF[1]==0x03))
					{
							//USART_SendData(USART1,USART_RX_BUF[12]*256+USART_RX_BUF[13]);
						
							//更新CO数据
						  USART8_Send_Gas_Data[11]=USART3_RX_BUF[3];
							USART8_Send_Gas_Data[12]=USART3_RX_BUF[4];
						
							printf("CO:%d\n",USART3_RX_BUF[3]*256+USART3_RX_BUF[4]);
							USART3_start  = 0;
							USART3_RX_STA=0;//重新开始接收   
							USART3_RX_BUF[0] = 0;
					}
				}                   
    }
		
		//USART4串口中断处理
		if (USART_GetITStatus(USART4, USART_IT_ORE) == SET)  
    {  
        USART_ClearITPendingBit(USART4,USART_IT_ORE);      
        USART_ReceiveData( USART4 );  
  
    }

    if(USART_GetITStatus(USART4, USART_IT_RXNE) != RESET)  //接收中断
		{
				USART_ClearITPendingBit(USART4,USART_IT_RXNE);  
				USART4_Res =USART_ReceiveData(USART4); //读取接收到的数据
				//USART_SendData(USART1,Res);
				if(USART4_Res == 0x15) //如果接收到的第一位数据是0X15(这个是查看传感器手册得知的)
				{
						USART4_RX_STA = 0;     //让数组索引值从0开始
						USART4_start = 1;  //这个变量用来确定第二位是否接收到了0X04(这个也是查看传感器手册得知的)
				}

				if(USART4_start == 1)
				{
					USART4_RX_BUF[USART4_RX_STA] = USART4_Res ; //把接收到的数据存到数组里面
					USART4_RX_STA++;
					if(USART4_RX_STA >= 6 && (USART4_RX_BUF[1]==0x04))
					{
							//USART_SendData(USART1,USART_RX_BUF[12]*256+USART_RX_BUF[13]);
							printf("CO2:%d\n",USART4_RX_BUF[3]*256+USART4_RX_BUF[4]);
							USART4_start  = 0;
							USART4_RX_STA=0;//重新开始接收   
							USART4_RX_BUF[0] = 0;
					}
				}                   
    }
		
		//USART5串口中断处理
		if (USART_GetITStatus(USART5, USART_IT_ORE) == SET)  
    {  
        USART_ClearITPendingBit(USART5,USART_IT_ORE);      
        USART_ReceiveData( USART5 );  
  
    }

    if(USART_GetITStatus(USART5, USART_IT_RXNE) != RESET)  //接收中断
		{
				USART_ClearITPendingBit(USART5,USART_IT_RXNE);  
				USART5_Res =USART_ReceiveData(USART5); //读取接收到的数据
				//USART_SendData(USART1,Res);
				if(USART5_Res == 0x01) //如果接收到的第一位数据是0X01(这个是查看传感器手册得知的)
				{
						USART5_RX_STA = 0;     //让数组索引值从0开始
						USART5_start = 1;  //这个变量用来确定第二位是否接收到了0X03(这个也是查看传感器手册得知的)
				}

				if(USART5_start == 1)
				{
					USART5_RX_BUF[USART5_RX_STA] = USART5_Res ; //把接收到的数据存到数组里面
					USART5_RX_STA++;
					if(USART5_RX_STA >= 7 && (USART5_RX_BUF[1]==0x03))
					{
							//USART_SendData(USART1,USART_RX_BUF[12]*256+USART_RX_BUF[13]);
							printf("CH2O:%d\n",USART5_RX_BUF[3]*256+USART5_RX_BUF[4]);
							USART5_start  = 0;
							USART5_RX_STA=0;//重新开始接收   
							USART5_RX_BUF[0] = 0;
					}
				}                   
    }
		
	  //USART6串口中断处理
		if (USART_GetITStatus(USART6, USART_IT_ORE) == SET)  
    {  
        USART_ClearITPendingBit(USART6,USART_IT_ORE);      
        USART_ReceiveData( USART6 );  
  
    }

    if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)  //接收中断
		{
				USART_ClearITPendingBit(USART6,USART_IT_RXNE);  
				USART6_Res =USART_ReceiveData(USART6); //读取接收到的数据
				//USART_SendData(USART1,Res);
				if(USART6_Res == 0xFE) //如果接收到的第一位数据是0XFE(这个是查看传感器手册得知的)
				{
						USART6_RX_STA = 0;     //让数组索引值从0开始
						USART6_start = 1;  //这个变量用来确定第二位是否接收到了0X04(这个也是查看传感器手册得知的)
				}

				if(USART6_start == 1)
				{
					USART6_RX_BUF[USART6_RX_STA] = USART6_Res ; //把接收到的数据存到数组里面
					USART6_RX_STA++;
					if(USART6_RX_STA >= 7 && (USART6_RX_BUF[1]==0x04))
					{
							//USART_SendData(USART1,USART_RX_BUF[12]*256+USART_RX_BUF[13]);
						
							//更新CO数据
						  USART8_Send_Gas_Data[9]=USART6_RX_BUF[3];
							USART8_Send_Gas_Data[10]=USART6_RX_BUF[4];
						
							printf("CO2 From S8:%d\n",USART6_RX_BUF[3]*256+USART6_RX_BUF[4]);
							USART6_start  = 0;
							USART6_RX_STA=0;//重新开始接收   
							USART6_RX_BUF[0] = 0;
					}
				}                   
    }
		
		//USART7串口中断处理
		if (USART_GetITStatus(USART7, USART_IT_ORE) == SET)  
    {  
        USART_ClearITPendingBit(USART7,USART_IT_ORE);      
        USART_ReceiveData( USART7 );  
  
    }

    if(USART_GetITStatus(USART7, USART_IT_RXNE) != RESET)  //接收中断
		{
				USART_ClearITPendingBit(USART7,USART_IT_RXNE);  
				USART7_Res =USART_ReceiveData(USART7); //读取接收到的数据
				//USART_SendData(USART1,Res);
				if(USART7_Res == 0xFF) //如果接收到的第一位数据是0XFF(这个是查看传感器手册得知的)
				{
						USART7_RX_STA = 0;     //让数组索引值从0开始
						USART7_start = 1;  //这个变量用来确定第二位是否接收到了0X17(这个也是查看传感器手册得知的)
				}

				if(USART7_start == 1)
				{
					USART7_RX_BUF[USART7_RX_STA] = USART7_Res ; //把接收到的数据存到数组里面
					USART7_RX_STA++;
					if(USART7_RX_STA >= 8 && (USART7_RX_BUF[1]==0x17))
					{
							//USART_SendData(USART1,USART_RX_BUF[12]*256+USART_RX_BUF[13]);
						
							//更新CH2O数据
						  USART8_Send_Gas_Data[7]=USART7_RX_BUF[4];
							USART8_Send_Gas_Data[8]=USART7_RX_BUF[5];
						
							printf("CH2O From Dart 2-FE5:%d\n",USART7_RX_BUF[4]*256+USART7_RX_BUF[5]);
							USART7_start  = 0;
							USART7_RX_STA=0;//重新开始接收   
							USART7_RX_BUF[0] = 0;
					}
				}                   
    }
		
		//USART8串口中断处理
		if (USART_GetITStatus(USART8, USART_IT_ORE) == SET)  
    {  
        USART_ClearITPendingBit(USART8,USART_IT_ORE);      
        USART_ReceiveData( USART8 );  
  
    }

    if(USART_GetITStatus(USART8, USART_IT_RXNE) != RESET)  //接收中断
		{
				USART_ClearITPendingBit(USART8,USART_IT_RXNE);  
				USART8_Res =USART_ReceiveData(USART8); //读取接收到的数据
				//USART_SendData(USART1,Res);
				if(USART8_Res == 0x53) //如果接收到的第一位数据是0X53(这个是查看传感器手册得知的)
				{
						USART8_RX_STA = 0;     //让数组索引值从0开始
						USART8_start = 1;  //这个变量用来确定第二位是否接收到了0X17(这个也是查看传感器手册得知的)
				}

				if(USART8_start == 1)
				{
					USART8_RX_BUF[USART8_RX_STA] = USART8_Res ; //把接收到的数据存到数组里面
					USART8_RX_STA++;
					if(USART8_RX_STA >= 3 && (USART8_RX_BUF[1]==0x32) && (USART8_RX_BUF[2]==0x01))
					{
							//USART_SendData(USART1,USART_RX_BUF[12]*256+USART_RX_BUF[13]);
							//printf("CH2O From Dart 2-FE5:%d\n",USART8_RX_BUF[4]*256+USART8_RX_BUF[5]);
						  USART8_SendStr(USART8,USART8_Send_Cmd_01,7);
							USART8_start  = 0;
							USART8_RX_STA=0;//重新开始接收   
							USART8_RX_BUF[0] = 0;
							USART8_RX_BUF[2] = 0;
					}
					else if(USART8_RX_STA >= 4 && (USART8_RX_BUF[1]==0x32) && (USART8_RX_BUF[2]==0x0C))
					{
							USART8_Send_Cmd_0C_Data = USART8_RX_BUF[3];
							USART8_Send_Cmd_0C[3]=USART8_RX_BUF[3];
							USART8_SendStr(USART8,USART8_Send_Cmd_0C,7);
							USART8_start  = 0;
							USART8_RX_STA=0;//重新开始接收   
							USART8_RX_BUF[0] = 0;
							USART8_RX_BUF[2] = 0;
					}
					else if(USART8_RX_STA >= 18 && (USART8_RX_BUF[1]==0x32) && (USART8_RX_BUF[2]==0x04))
					{
							char str[40];
							uint8_t i=0;
						
							for(i=0;i<64;i++)
							{
								USART8_Cmd_04_Data[i]=USART8_RX_BUF[i];
							}
											
							USART8_Send_Cmd_04_Data[0] = USART8_Cmd_04_Data[4]*256 + USART8_Cmd_04_Data[5];
							USART8_Send_Cmd_04_Data[1] = USART8_Cmd_04_Data[7]*256 + USART8_Cmd_04_Data[8];
							USART8_Send_Cmd_04_Data[2] = USART8_Cmd_04_Data[10]*256 + USART8_Cmd_04_Data[11];
							USART8_Send_Cmd_04_Data[3] = USART8_Cmd_04_Data[13]*256 + USART8_Cmd_04_Data[14];
							USART8_Send_Cmd_04_Data[4] = USART8_Cmd_04_Data[16]*256 + USART8_Cmd_04_Data[17];
							sprintf(str,"Cmd_04_Data[0]: %d\r\n",USART8_Send_Cmd_04_Data[0]);
							USART8_SendStr(USART8,(uint8_t *)str,strlen(str));
							sprintf(str,"Cmd_04_Data[1]: %d\r\n",USART8_Send_Cmd_04_Data[1]);
							USART8_SendStr(USART8,(uint8_t *)str,strlen(str));
							sprintf(str,"Cmd_04_Data[2]: %d\r\n",USART8_Send_Cmd_04_Data[2]);
							USART8_SendStr(USART8,(uint8_t *)str,strlen(str));
							sprintf(str,"Cmd_04_Data[3]: %d\r\n",USART8_Send_Cmd_04_Data[3]);
							USART8_SendStr(USART8,(uint8_t *)str,strlen(str));
							sprintf(str,"Cmd_04_Data[4]: %d\r\n",USART8_Send_Cmd_04_Data[4]);
							USART8_SendStr(USART8,(uint8_t *)str,strlen(str));
							
							//写入Flash中
							SPI_Flash_Erase_Sector(FLASH_SectorToErase);	 
							SPI_Flash_Write(USART8_Cmd_04_Data,FLASH_WriteAddress, 19);
							SPI_Flash_Read(SPI_Flash_ReadBuffer,FLASH_ReadAddress,19);
							USART8_SendStr(USART8,SPI_Flash_ReadBuffer,19);
							
							USART8_start  = 0;
							USART8_RX_STA=0;//重新开始接收   
						  for(i=0;i<64;i++)
							{
								USART8_RX_BUF[i]=0;
							}
					}
				}                   
    }
}

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
