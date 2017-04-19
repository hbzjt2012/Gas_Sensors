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
					if(USART7_RX_STA >= 9 && (USART7_RX_BUF[1]==0x17))
					{
							//USART_SendData(USART1,USART_RX_BUF[12]*256+USART_RX_BUF[13]);
							printf("CH2O From Dart 2-FE5:%d\n",USART7_RX_BUF[4]*256+USART7_RX_BUF[5]);
							USART7_start  = 0;
							USART7_RX_STA=0;//重新开始接收   
							USART7_RX_BUF[0] = 0;
					}
				}                   
    }
}

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
