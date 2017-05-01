/******************************************************************************
  * @file    L3G4200D.c
  * @author  xxx
	* @from    hbzjt2011 QQ956139733
  * @date    03-13-2017
  ******************************************************************************/ 
#include "main.h"

uint8_t TX_DATA[4];  
uint8_t BUF[8];                       //接收数据缓存区
char  test=0; 
short T_X,T_Y,T_Z;

/*******************************************************************************
* Function Name  : L3G4200D_I2C_delay
* Description    : Simulation IIC Timing series delay
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void L3G4200D_I2C_delay(void)
{
		
   uint8_t i=30; //这里可以优化速度
   while(i) 
   { 
     i--; 
   }  
}

/*******************************************************************************
* Function Name  : L3G4200D_I2C_Start
* Description    : Master Start Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : Wheather	 Start
****************************************************************************** */
uint8_t L3G4200D_I2C_Start(void)
{
	L3G4200D_SDA_OUT();
	L3G4200D_SDA_H;
	L3G4200D_SCL_H;
	L3G4200D_I2C_delay();
	if(!L3G4200D_SDA_read)return FALSE;	//SDA线为低电平则总线忙,退出
	L3G4200D_SDA_L;
	L3G4200D_I2C_delay();
	if(L3G4200D_SDA_read) return FALSE;	//SDA线为高电平则总线出错,退出
	L3G4200D_SDA_L;
	L3G4200D_I2C_delay();
	return TRUE;
}

/*******************************************************************************
* Function Name  : L3G4200D_I2C_Stop
* Description    : Master Stop Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void L3G4200D_I2C_Stop(void)
{
	L3G4200D_SDA_OUT();
	L3G4200D_SCL_L;
	L3G4200D_I2C_delay();
	L3G4200D_SDA_L;
	L3G4200D_I2C_delay();
	L3G4200D_SCL_H;
	L3G4200D_I2C_delay();
	L3G4200D_SDA_H;
	L3G4200D_I2C_delay();
} 

/*******************************************************************************
* Function Name  : L3G4200D_I2C_Ack
* Description    : Master Send Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void L3G4200D_I2C_Ack(void)
{	
	L3G4200D_SCL_L;
	L3G4200D_I2C_delay();
	L3G4200D_SDA_OUT();
	L3G4200D_SDA_L;
	L3G4200D_I2C_delay();
	L3G4200D_SCL_H;
	L3G4200D_I2C_delay();
	L3G4200D_SCL_L;
	L3G4200D_I2C_delay();
}

/*******************************************************************************
* Function Name  : L3G4200D_I2C_NoAck
* Description    : Master Send No Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void L3G4200D_I2C_NoAck(void)
{	
	L3G4200D_SCL_L;
	L3G4200D_I2C_delay();
	L3G4200D_SDA_OUT();
	L3G4200D_SDA_H;
	L3G4200D_I2C_delay();
	L3G4200D_SCL_H;
	L3G4200D_I2C_delay();
	L3G4200D_SCL_L;
	L3G4200D_I2C_delay();
} 
/*******************************************************************************
* Function Name  : L3G4200D_I2C_WaitAck
* Description    : Master Reserive Slave Acknowledge Single
* Input          : None
* Output         : None
* Return         : Wheather	 Reserive Slave Acknowledge Single
****************************************************************************** */
uint8_t L3G4200D_I2C_WaitAck(void) 	 //返回为:=1有ACK,=0无ACK
{
	L3G4200D_SCL_L;
	L3G4200D_I2C_delay();
	L3G4200D_SDA_IN();
	L3G4200D_SDA_H;			
	L3G4200D_I2C_delay();
	L3G4200D_SCL_H;
	L3G4200D_I2C_delay();
	if(L3G4200D_SDA_read)
	{
      L3G4200D_SCL_L;
			L3G4200D_I2C_delay();
      return FALSE;
	}
	L3G4200D_SCL_L;
	L3G4200D_I2C_delay();
	return TRUE;
}

/*******************************************************************************
* Function Name  : L3G4200D_I2C_SendByte
* Description    : Master Send a Byte to Slave
* Input          : Will Send Date
* Output         : None
* Return         : None
****************************************************************************** */
void L3G4200D_I2C_SendByte(uint8_t SendByte) //数据从高位到低位//
{
    uint8_t i=8;
		L3G4200D_SDA_OUT();
    while(i--)
    {
        L3G4200D_SCL_L;
        L3G4200D_I2C_delay();
      if(SendByte&0x80)
        L3G4200D_SDA_H;  
      else 
        L3G4200D_SDA_L;   
        SendByte<<=1;
        L3G4200D_I2C_delay();
				L3G4200D_SCL_H;
        L3G4200D_I2C_delay();
    }
    L3G4200D_SCL_L;
}

/*******************************************************************************
* Function Name  : L3G4200D_I2C_RadeByte
* Description    : Master Reserive a Byte From Slave
* Input          : None
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
uint8_t L3G4200D_I2C_RadeByte(void)   //数据从高位到低位//
{ 
    uint8_t i=8;
    uint8_t ReceiveByte=0;
		
		L3G4200D_SDA_IN();
    L3G4200D_SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      L3G4200D_SCL_L;
      L3G4200D_I2C_delay();
			L3G4200D_SCL_H;
      L3G4200D_I2C_delay();	
      if(L3G4200D_SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    L3G4200D_SCL_L;
    return ReceiveByte;
} 

//单字节写入*******************************************
uint8_t L3G4200D_Single_Write(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data)		     //void
{
  	if(!L3G4200D_I2C_Start())return FALSE;
    L3G4200D_I2C_SendByte(SlaveAddress);   
    if(!L3G4200D_I2C_WaitAck()){L3G4200D_I2C_Stop(); return FALSE;}
    L3G4200D_I2C_SendByte(REG_Address );   
    L3G4200D_I2C_WaitAck();	
    L3G4200D_I2C_SendByte(REG_data);
    L3G4200D_I2C_WaitAck();   
    L3G4200D_I2C_Stop(); 
    SysTick_delay_ms(5);
    return TRUE;
}

//单字节读取*****************************************
uint8_t L3G4200D_Single_Read(uint8_t SlaveAddress,uint8_t REG_Address)
{   
		uint8_t REG_data;     	
		if(!L3G4200D_I2C_Start())return FALSE;
    L3G4200D_I2C_SendByte(SlaveAddress); 
    if(!L3G4200D_I2C_WaitAck()){L3G4200D_I2C_Stop();test=1; return FALSE;}
    L3G4200D_I2C_SendByte((uint8_t) REG_Address);   
    L3G4200D_I2C_WaitAck();
    L3G4200D_I2C_Start();
    L3G4200D_I2C_SendByte(SlaveAddress+1);
    L3G4200D_I2C_WaitAck();

		REG_data= L3G4200D_I2C_RadeByte();
    L3G4200D_I2C_NoAck();
    L3G4200D_I2C_Stop();
    //return TRUE;
		return REG_data;
}

/*****************L3G4200D_I2C_Init****************************************************/
void L3G4200D_I2C_Init(void)
{ 
	 GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);     //使能GPIOB时钟

	 //配置I2C1_SCL(PB8)和I2C1_SDA(PB9)开漏输出
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		L3G4200D_SCL_H;
		L3G4200D_SDA_H;
}

 //************初始化L3G4200D*********************************
void L3G4200D_Init(void)
{
	L3G4200D_I2C_Init();
	
	SysTick_delay_us(200);
	
	L3G4200D_Single_Write(L3G4200_Addr,CTRL_REG1, 0x0f);
	L3G4200D_Single_Write(L3G4200_Addr,CTRL_REG2, 0x00);
	L3G4200D_Single_Write(L3G4200_Addr,CTRL_REG3, 0x08);
	L3G4200D_Single_Write(L3G4200_Addr,CTRL_REG4, 0x30);	//+-2000dps
	L3G4200D_Single_Write(L3G4200_Addr,CTRL_REG5, 0x00);
}	
//******读取L3G4200D数据****************************************
void L3G4200D_Read(void)
{
   BUF[0]=L3G4200D_Single_Read(L3G4200_Addr,OUT_X_L);
   BUF[1]=L3G4200D_Single_Read(L3G4200_Addr,OUT_X_H);
   T_X=	(BUF[1]<<8)|BUF[0];
 
   BUF[2]=L3G4200D_Single_Read(L3G4200_Addr,OUT_Y_L);
   BUF[3]=L3G4200D_Single_Read(L3G4200_Addr,OUT_Y_H);
   T_Y=	(BUF[3]<<8)|BUF[2];
  
   BUF[4]=L3G4200D_Single_Read(L3G4200_Addr,OUT_Z_L);
   BUF[5]=L3G4200D_Single_Read(L3G4200_Addr,OUT_Z_H);
   T_Z=	(BUF[5]<<8)|BUF[4];

	 L3G4200D_DATA_printf(TX_DATA,T_X);
	 L3G4200D_Send_data('X');	
}

 //********串口发送数据***************************************
 void L3G4200D_Send_data(uint8_t axis)
 {
    char i;
    putchar(axis);
    putchar(':');
    for(i=0;i<4;i++)
        putchar(TX_DATA[i]);
    putchar(' ');
    putchar(' ');
 }

/*******************************/
void L3G4200D_DATA_printf(uint8_t *s,short temp_data)
{   
    float temp_dis;
    temp_dis=(float)(temp_data*0.07);  //转换成单位 度/秒
		temp_data=(int)temp_dis;
		if(temp_data<0)
    {
    	temp_data=-temp_data;
        *s='-';
		}
		else 
        *s=' ';
    *++s =temp_data/100+0x30;
    temp_data=temp_data%100;     //取余运算
    *++s =temp_data/10+0x30;
    temp_data=temp_data%10;      //取余运算
    *++s =temp_data+0x30; 	
}
