#include "main.h"

/*******************************************************************************
* Function Name  : MICS_VZ_89TE_IIC_I2C_delay
* Description    : Simulation IIC Timing series delay
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void MICS_VZ_89TE_IIC_I2C_delay(void)
{
		
   uint8_t i=30; //这里可以优化速度
   while(i) 
   { 
     i--; 
   }  
}

/*******************************************************************************
* Function Name  : MICS_VZ_89TE_IIC_I2C_Start
* Description    : Master Start Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : Wheather	 Start
****************************************************************************** */
uint8_t MICS_VZ_89TE_IIC_I2C_Start(void)
{
	MICS_VZ_89TE_IIC_SDA_OUT();
	MICS_VZ_89TE_IIC_SDA_H;
	MICS_VZ_89TE_IIC_SCL_H;
	MICS_VZ_89TE_IIC_I2C_delay();
	if(!MICS_VZ_89TE_IIC_SDA_read)return FALSE;	//SDA线为低电平则总线忙,退出
	MICS_VZ_89TE_IIC_SDA_L;
	MICS_VZ_89TE_IIC_I2C_delay();
	if(MICS_VZ_89TE_IIC_SDA_read) return FALSE;	//SDA线为高电平则总线出错,退出
	MICS_VZ_89TE_IIC_SDA_L;
	MICS_VZ_89TE_IIC_I2C_delay();
	return TRUE;
}

/*******************************************************************************
* Function Name  : MICS_VZ_89TE_IIC_I2C_Stop
* Description    : Master Stop Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void MICS_VZ_89TE_IIC_I2C_Stop(void)
{
	MICS_VZ_89TE_IIC_SDA_OUT();
	MICS_VZ_89TE_IIC_SCL_L;
	MICS_VZ_89TE_IIC_I2C_delay();
	MICS_VZ_89TE_IIC_SDA_L;
	MICS_VZ_89TE_IIC_I2C_delay();
	MICS_VZ_89TE_IIC_SCL_H;
	MICS_VZ_89TE_IIC_I2C_delay();
	MICS_VZ_89TE_IIC_SDA_H;
	MICS_VZ_89TE_IIC_I2C_delay();
} 

/*******************************************************************************
* Function Name  : MICS_VZ_89TE_IIC_I2C_Ack
* Description    : Master Send Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void MICS_VZ_89TE_IIC_I2C_Ack(void)
{	
	MICS_VZ_89TE_IIC_SCL_L;
	MICS_VZ_89TE_IIC_I2C_delay();
	MICS_VZ_89TE_IIC_SDA_OUT();
	MICS_VZ_89TE_IIC_SDA_L;
	MICS_VZ_89TE_IIC_I2C_delay();
	MICS_VZ_89TE_IIC_SCL_H;
	MICS_VZ_89TE_IIC_I2C_delay();
	MICS_VZ_89TE_IIC_SCL_L;
	MICS_VZ_89TE_IIC_I2C_delay();
}

/*******************************************************************************
* Function Name  : MICS_VZ_89TE_IIC_I2C_NoAck
* Description    : Master Send No Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void MICS_VZ_89TE_IIC_I2C_NoAck(void)
{	
	MICS_VZ_89TE_IIC_SCL_L;
	MICS_VZ_89TE_IIC_I2C_delay();
	MICS_VZ_89TE_IIC_SDA_OUT();
	MICS_VZ_89TE_IIC_SDA_H;
	MICS_VZ_89TE_IIC_I2C_delay();
	MICS_VZ_89TE_IIC_SCL_H;
	MICS_VZ_89TE_IIC_I2C_delay();
	MICS_VZ_89TE_IIC_SCL_L;
	MICS_VZ_89TE_IIC_I2C_delay();
} 
/*******************************************************************************
* Function Name  : MICS_VZ_89TE_IIC_I2C_WaitAck
* Description    : Master Reserive Slave Acknowledge Single
* Input          : None
* Output         : None
* Return         : Wheather	 Reserive Slave Acknowledge Single
****************************************************************************** */
uint8_t MICS_VZ_89TE_IIC_I2C_WaitAck(void) 	 //返回为:=1有ACK,=0无ACK
{
	MICS_VZ_89TE_IIC_SCL_L;
	MICS_VZ_89TE_IIC_I2C_delay();
	MICS_VZ_89TE_IIC_SDA_IN();
	MICS_VZ_89TE_IIC_SDA_H;			
	MICS_VZ_89TE_IIC_I2C_delay();
	MICS_VZ_89TE_IIC_SCL_H;
	MICS_VZ_89TE_IIC_I2C_delay();
	if(MICS_VZ_89TE_IIC_SDA_read)
	{
      MICS_VZ_89TE_IIC_SCL_L;
			MICS_VZ_89TE_IIC_I2C_delay();
      return FALSE;
	}
	MICS_VZ_89TE_IIC_SCL_L;
	MICS_VZ_89TE_IIC_I2C_delay();
	return TRUE;
}

/*******************************************************************************
* Function Name  : MICS_VZ_89TE_IIC_I2C_SendByte
* Description    : Master Send a Byte to Slave
* Input          : Will Send Date
* Output         : None
* Return         : None
****************************************************************************** */
void MICS_VZ_89TE_IIC_I2C_SendByte(uint8_t SendByte) //数据从高位到低位//
{
    uint8_t i=8;
		MICS_VZ_89TE_IIC_SDA_OUT();
    while(i--)
    {
        MICS_VZ_89TE_IIC_SCL_L;
        MICS_VZ_89TE_IIC_I2C_delay();
      if(SendByte&0x80)
        MICS_VZ_89TE_IIC_SDA_H;  
      else 
        MICS_VZ_89TE_IIC_SDA_L;   
        SendByte<<=1;
        MICS_VZ_89TE_IIC_I2C_delay();
				MICS_VZ_89TE_IIC_SCL_H;
        MICS_VZ_89TE_IIC_I2C_delay();
    }
    MICS_VZ_89TE_IIC_SCL_L;
}

/*******************************************************************************
* Function Name  : MICS_VZ_89TE_IIC_I2C_ReadByte
* Description    : Master Reserive a Byte From Slave
* Input          : None
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
uint8_t MICS_VZ_89TE_IIC_I2C_ReadByte(void)   //数据从高位到低位//
{ 
    uint8_t i=8;
    uint8_t ReceiveByte=0;
		
		MICS_VZ_89TE_IIC_SDA_IN();
    MICS_VZ_89TE_IIC_SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      MICS_VZ_89TE_IIC_SCL_L;
      MICS_VZ_89TE_IIC_I2C_delay();
			MICS_VZ_89TE_IIC_SCL_H;
      MICS_VZ_89TE_IIC_I2C_delay();	
      if(MICS_VZ_89TE_IIC_SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    MICS_VZ_89TE_IIC_SCL_L;
    return ReceiveByte;
} 

//单字节写入*******************************************
uint8_t MICS_VZ_89TE_IIC_Single_Write(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data)		     //void
{
  	if(!MICS_VZ_89TE_IIC_I2C_Start())return FALSE;
    MICS_VZ_89TE_IIC_I2C_SendByte(SlaveAddress);   
    if(!MICS_VZ_89TE_IIC_I2C_WaitAck()){MICS_VZ_89TE_IIC_I2C_Stop(); return FALSE;}
    MICS_VZ_89TE_IIC_I2C_SendByte(REG_Address );   
    MICS_VZ_89TE_IIC_I2C_WaitAck();	
    MICS_VZ_89TE_IIC_I2C_SendByte(REG_data);
    MICS_VZ_89TE_IIC_I2C_WaitAck();   
    MICS_VZ_89TE_IIC_I2C_Stop(); 
    SysTick_delay_ms(5);
    return TRUE;
}

//单字节读取*****************************************
uint8_t MICS_VZ_89TE_IIC_Single_Read(uint8_t SlaveAddress,uint8_t REG_Address)
{   
		uint8_t REG_data;     	
		if(!MICS_VZ_89TE_IIC_I2C_Start())return FALSE;
    MICS_VZ_89TE_IIC_I2C_SendByte(SlaveAddress); 
    if(!MICS_VZ_89TE_IIC_I2C_WaitAck()){MICS_VZ_89TE_IIC_I2C_Stop(); return FALSE;}
    MICS_VZ_89TE_IIC_I2C_SendByte((uint8_t) REG_Address);   
    MICS_VZ_89TE_IIC_I2C_WaitAck();
    MICS_VZ_89TE_IIC_I2C_Start();
    MICS_VZ_89TE_IIC_I2C_SendByte(SlaveAddress+1);
    MICS_VZ_89TE_IIC_I2C_WaitAck();

		REG_data= MICS_VZ_89TE_IIC_I2C_ReadByte();
    MICS_VZ_89TE_IIC_I2C_NoAck();
    MICS_VZ_89TE_IIC_I2C_Stop();
    //return TRUE;
		return REG_data;
}

/*****************MICS_VZ_89TE_IIC_I2C_Init****************************************************/
void MICS_VZ_89TE_IIC_I2C_Init(void)
{ 
	 GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);     //使能GPIOB时钟

	 //配置I2C1_SCL(PB0)和I2C1_SDA(PB1)开漏输出
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		MICS_VZ_89TE_IIC_SCL_H;
		MICS_VZ_89TE_IIC_SDA_H;
}

/*****************MiCS_VZ_89TE_IIC_ReadStatus****************************************************/
uint8_t MiCS_VZ_89TE_IIC_ReadStatus(uint8_t *pBuffer)
{
	 if(!MICS_VZ_89TE_IIC_I2C_Start())return FALSE;
   MICS_VZ_89TE_IIC_I2C_SendByte(MICS_VZ_89TE_Addr<<1); 
	 if(!MICS_VZ_89TE_IIC_I2C_WaitAck()){MICS_VZ_89TE_IIC_I2C_Stop(); return FALSE;}
	 MICS_VZ_89TE_IIC_I2C_SendByte(MICS_VZ_89TE_STATUS_REG);   
	 MICS_VZ_89TE_IIC_I2C_WaitAck();
	 MICS_VZ_89TE_IIC_I2C_Start();
   MICS_VZ_89TE_IIC_I2C_SendByte((MICS_VZ_89TE_Addr<<1)+1);
	 MICS_VZ_89TE_IIC_I2C_WaitAck();

	 pBuffer[0]= MICS_VZ_89TE_IIC_I2C_ReadByte();
	 MICS_VZ_89TE_IIC_I2C_Ack();
	 pBuffer[1]= MICS_VZ_89TE_IIC_I2C_ReadByte();
	 MICS_VZ_89TE_IIC_I2C_Ack();
	 pBuffer[2]= MICS_VZ_89TE_IIC_I2C_ReadByte();
	 MICS_VZ_89TE_IIC_I2C_Ack();
	 pBuffer[3]= MICS_VZ_89TE_IIC_I2C_ReadByte();
	 MICS_VZ_89TE_IIC_I2C_Ack();
	 pBuffer[4]= MICS_VZ_89TE_IIC_I2C_ReadByte();
	 MICS_VZ_89TE_IIC_I2C_Ack();
	 pBuffer[5]= MICS_VZ_89TE_IIC_I2C_ReadByte();
	 
	 MICS_VZ_89TE_IIC_I2C_NoAck();
	 MICS_VZ_89TE_IIC_I2C_Stop();
	 
	 return TRUE;
}
