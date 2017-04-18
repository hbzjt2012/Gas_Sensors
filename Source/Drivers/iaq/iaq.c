#include "main.h"

/*******************************************************************************
* Function Name  : IAQ_I2C_delay
* Description    : Simulation IIC Timing series delay
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void IAQ_I2C_delay(void)
{
		
   uint8_t i=30; //这里可以优化速度
   while(i) 
   { 
     i--; 
   }  
}

/*******************************************************************************
* Function Name  : IAQ_I2C_Start
* Description    : Master Start Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : Wheather	 Start
****************************************************************************** */
uint8_t IAQ_I2C_Start(void)
{
	IAQ_SDA_OUT();
	IAQ_SDA_H;
	IAQ_SCL_H;
	IAQ_I2C_delay();
	if(!IAQ_SDA_read)return FALSE;	//IAQ_SDA线为低电平则总线忙,退出
	IAQ_SDA_L;
	IAQ_I2C_delay();
	if(IAQ_SDA_read) return FALSE;	//IAQ_SDA线为高电平则总线出错,退出
	IAQ_SDA_L;
	IAQ_I2C_delay();
	return TRUE;
}

/*******************************************************************************
* Function Name  : IAQ_I2C_Stop
* Description    : Master Stop Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void IAQ_I2C_Stop(void)
{
	IAQ_SDA_OUT();
	IAQ_SCL_L;
	IAQ_I2C_delay();
	IAQ_SDA_L;
	IAQ_I2C_delay();
	IAQ_SCL_H;
	IAQ_I2C_delay();
	IAQ_SDA_H;
	IAQ_I2C_delay();
} 

/*******************************************************************************
* Function Name  : IAQ_I2C_Ack
* Description    : Master Send Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void IAQ_I2C_Ack(void)
{	
	IAQ_SCL_L;
	IAQ_I2C_delay();
	IAQ_SDA_OUT();
	IAQ_SDA_L;
	IAQ_I2C_delay();
	IAQ_SCL_H;
	IAQ_I2C_delay();
	IAQ_SCL_L;
	IAQ_I2C_delay();
}

/*******************************************************************************
* Function Name  : IAQ_I2C_NoAck
* Description    : Master Send No Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void IAQ_I2C_NoAck(void)
{	
	IAQ_SCL_L;
	IAQ_I2C_delay();
	IAQ_SDA_OUT();
	IAQ_SDA_H;
	IAQ_I2C_delay();
	IAQ_SCL_H;
	IAQ_I2C_delay();
	IAQ_SCL_L;
	IAQ_I2C_delay();
} 
/*******************************************************************************
* Function Name  : IAQ_I2C_WaitAck
* Description    : Master Reserive Slave Acknowledge Single
* Input          : None
* Output         : None
* Return         : Wheather	 Reserive Slave Acknowledge Single
****************************************************************************** */
uint8_t IAQ_I2C_WaitAck(void) 	//返回为:=1有ACK,=0无ACK
{
	IAQ_SCL_L;
	IAQ_I2C_delay();
	IAQ_SDA_IN();
	IAQ_SDA_H;			
	IAQ_I2C_delay();
	IAQ_SCL_H;
	IAQ_I2C_delay();
	if(IAQ_SDA_read)
	{
      IAQ_SCL_L;
	  IAQ_I2C_delay();
      return FALSE;
	}
	IAQ_SCL_L;
	IAQ_I2C_delay();
	return TRUE;
}

/*******************************************************************************
* Function Name  : IAQ_I2C_SendByte
* Description    : Master Send a Byte to Slave
* Input          : Will Send Date
* Output         : None
* Return         : None
****************************************************************************** */
void IAQ_I2C_SendByte(uint8_t SendByte) //数据从高位到低位//
{
    uint8_t i=8;
		IAQ_SDA_OUT();
    while(i--)
    {
        IAQ_SCL_L;
        IAQ_I2C_delay();
      if(SendByte&0x80)
        IAQ_SDA_H;  
      else 
        IAQ_SDA_L;   
        SendByte<<=1;
        IAQ_I2C_delay();
				IAQ_SCL_H;
        IAQ_I2C_delay();
    }
    IAQ_SCL_L;
}

/*******************************************************************************
* Function Name  : IAQ_I2C_RadeByte
* Description    : Master Reserive a Byte From Slave
* Input          : None
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
unsigned char IAQ_I2C_ReadByte(void)  //数据从高位到低位//
{ 
    uint8_t i=8;
    uint8_t ReceiveByte=0;
		
		IAQ_SDA_IN();
    IAQ_SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      IAQ_SCL_L;
      IAQ_I2C_delay();
			IAQ_SCL_H;
      IAQ_I2C_delay();	
      if(IAQ_SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    IAQ_SCL_L;
    return ReceiveByte;
} 

//单字节写入*******************************************
uint8_t IAQ_Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  	if(!IAQ_I2C_Start())return FALSE;
    IAQ_I2C_SendByte(SlaveAddress);   //发送设备地址+写信号//IAQ_I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!IAQ_I2C_WaitAck()){IAQ_I2C_Stop(); return FALSE;}
    IAQ_I2C_SendByte(REG_Address );   //设置低起始地址  
    IAQ_I2C_WaitAck();	
    IAQ_I2C_SendByte(REG_data);
    IAQ_I2C_WaitAck();   
    IAQ_I2C_Stop(); 
    delay_ms(5);
    return TRUE;
}

//单字节读取*****************************************
unsigned char IAQ_Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{   unsigned char REG_data;     	
		if(!IAQ_I2C_Start())return FALSE;
    IAQ_I2C_SendByte(SlaveAddress); //IAQ_I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    if(!IAQ_I2C_WaitAck()){IAQ_I2C_Stop(); return FALSE;}
    IAQ_I2C_SendByte((uint8_t) REG_Address);   //设置低起始地址  
    IAQ_I2C_WaitAck();
    IAQ_I2C_Start();
    IAQ_I2C_SendByte(SlaveAddress+1);
    IAQ_I2C_WaitAck();

		REG_data= IAQ_I2C_ReadByte();
    IAQ_I2C_NoAck();
    IAQ_I2C_Stop();
    //return TRUE;
	return REG_data;
}

void IAQ_Init(void)
{
	  
	  GPIO_InitTypeDef  GPIO_InitStructure; 
	
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
 
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : ReadIAQ
* Description    : Read IAQ Data
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void ReadIAQ(uint8_t *s,uint8_t length)
{	
	uint8_t i;
  IAQ_I2C_Start();
	IAQ_I2C_SendByte(Sensor_ADDRESS);
	for(i=0;i<(length-1);i++)
	{
		*s=IAQ_I2C_ReadByte();
		IAQ_I2C_Ack();
		s++;
	}
	*s=IAQ_I2C_ReadByte();
	IAQ_I2C_NoAck();
	IAQ_I2C_Stop();
} 

/*******************************************************************************
* Function Name  : Get_CO2_IAQ
* Description    : Get CO2 and IAQ Value from IAQ
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void Get_CO2_TVOC(void)
{
	uint8_t buf[7];
	ReadIAQ(buf,14);
	printf((const char *)buf);
}

