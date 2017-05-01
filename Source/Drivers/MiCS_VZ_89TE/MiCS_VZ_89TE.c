#include "main.h"

//-- Global variables ---------------------------------------------------------
static uint8_t MiCS_VZ_89TE_I2CAddress; // I2C Address

/*******************************************************************************/
void MiCS_VZ_89TE_I2C_Init(void)
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
	
		MiCS_VZ_89TE_SDAH;
		MiCS_VZ_89TE_SCLH;
}
 
//-----------------------------------------------------------------------------
void MiCS_VZ_89TE_I2C_StartCondition(void)
{
  MiCS_VZ_89TE_SDAH;
  SysTick_delay_us(1);
  MiCS_VZ_89TE_SCLH;
  SysTick_delay_us(1);
  MiCS_VZ_89TE_SDAL;
  SysTick_delay_us(10);  // hold time start condition (t_HD;STA)
  MiCS_VZ_89TE_SCLL;
  SysTick_delay_us(10);
}

//-----------------------------------------------------------------------------
void MiCS_VZ_89TE_I2C_StopCondition(void)
{
  MiCS_VZ_89TE_SCLL;
  SysTick_delay_us(1);
  MiCS_VZ_89TE_SDAL;
  SysTick_delay_us(1);
  MiCS_VZ_89TE_SCLH;
  SysTick_delay_us(10);  // set-up time stop condition (t_SU;STO)
  MiCS_VZ_89TE_SDAH;
  SysTick_delay_us(10);
}

//-----------------------------------------------------------------------------
etError MiCS_VZ_89TE_I2C_WriteByte(uint8_t txByte)
{
  etError error = NO_ERROR;
  uint8_t     mask;
  for(mask = 0x80; mask > 0; mask >>= 1)// shifloat bit for masking (8 times)
  {
    if((mask & txByte) == 0) MiCS_VZ_89TE_SDAL; // masking txByte, write bit to SDA-Line
    else                     MiCS_VZ_89TE_SDAH;
    SysTick_delay_us(5);               // data set-up time (t_SU;DAT)
    MiCS_VZ_89TE_SCLH;                         // generate clock pulse on SCL
    SysTick_delay_us(10);               // SCL high time (t_HIGH)
    MiCS_VZ_89TE_SCLL;
    SysTick_delay_us(5);               // data hold time(t_HD;DAT)
  }
  MiCS_VZ_89TE_SDAH;                           // release SDA-line
  MiCS_VZ_89TE_SCLH;                           // clk #9 for ack
  SysTick_delay_us(15);                 // data set-up time (t_SU;DAT)
  if(MiCS_VZ_89TE_SDA_STATE) error = ACK_ERROR;       // check ack from i2c slave
  MiCS_VZ_89TE_SCLL;
  SysTick_delay_us(20);                // wait to see byte package on scope
  return error;                         // return error code
}

//-----------------------------------------------------------------------------
etError MiCS_VZ_89TE_I2C_ReadByte(uint8_t *rxByte, etI2cAck ack, uint8_t timeout)
{
  etError error = NO_ERROR;
  uint8_t mask;
  *rxByte = 0x00;
  MiCS_VZ_89TE_SDAH;                            // release SDA-line
  for(mask = 0x80; mask > 0; mask >>= 1) // shifloat bit for masking (8 times)
  { 
    MiCS_VZ_89TE_SCLH;                          // start clock on SCL-line
    SysTick_delay_us(1);                // clock set-up time (t_SU;CLK)
    error = MiCS_VZ_89TE_I2C_WaitWhileClockStreching(timeout);// wait while clock streching
    SysTick_delay_us(3);                // SCL high time (t_HIGH)
    if(MiCS_VZ_89TE_SDA_STATE) *rxByte |= mask;        // read bit
    MiCS_VZ_89TE_SCLL;
    SysTick_delay_us(1);                // data hold time(t_HD;DAT)
  }
  if(ack == ACK) MiCS_VZ_89TE_SDAL;              // send acknowledge if necessary
  else           MiCS_VZ_89TE_SDAH;
  SysTick_delay_us(1);                  // data set-up time (t_SU;DAT)
  MiCS_VZ_89TE_SCLH;                            // clk #9 for ack
  SysTick_delay_us(5);                  // SCL high time (t_HIGH)
  MiCS_VZ_89TE_SCLL;
  MiCS_VZ_89TE_SDAH;                            // release SDA-line
  SysTick_delay_us(20);                 // wait to see byte package on scope
  
  return error;                          // return with no error
}

//-----------------------------------------------------------------------------
etError MiCS_VZ_89TE_I2C_GeneralCallReset(void)
{
  etError error;
  
  MiCS_VZ_89TE_I2C_StartCondition();
                        error = MiCS_VZ_89TE_I2C_WriteByte(0x00);
  if(error == NO_ERROR) error = MiCS_VZ_89TE_I2C_WriteByte(0x06);
  
  return error;
}

//-----------------------------------------------------------------------------
static etError MiCS_VZ_89TE_I2C_WaitWhileClockStreching(uint8_t timeout)
{
  etError error = NO_ERROR;
  
  while(MiCS_VZ_89TE_SCL_STATE == 0)
  {
    if(timeout-- == 0) return TIMEOUT_ERROR;
    SysTick_delay_us(1000);
  }
  
  return error;
}


//-----------------------------------------------------------------------------
void MiCS_VZ_89TE_Init(uint8_t i2cAddress)          /* -- adapt the init for your uC -- */
{

  MiCS_VZ_89TE_I2C_Init(); // init I2C
  MiCS_VZ_89TE_SetI2CAdr(i2cAddress);

}

//-----------------------------------------------------------------------------
void MiCS_VZ_89TE_SetI2CAdr(uint8_t i2cAddress)
{
  MiCS_VZ_89TE_I2CAddress = i2cAddress;
}

//-----------------------------------------------------------------------------
static etError MiCS_VZ_89TE_StartWriteAccess(void)
{
  etError error; // error code

  // write a start condition
  MiCS_VZ_89TE_I2C_StartCondition();

  // write the sensor I2C address with the write flag
  error = MiCS_VZ_89TE_I2C_WriteByte(MiCS_VZ_89TE_I2CAddress << 1);

  return error;
}

//-----------------------------------------------------------------------------
static etError MiCS_VZ_89TE_StartReadAccess(void)
{
  etError error; // error code

  // write a start condition
  MiCS_VZ_89TE_I2C_StartCondition();

  // write the sensor I2C address with the read flag
  error = MiCS_VZ_89TE_I2C_WriteByte(MiCS_VZ_89TE_I2CAddress << 1 | 0x01);

  return error;
}

//-----------------------------------------------------------------------------
static void MiCS_VZ_89TE_StopAccess(void)
{
  // write a stop condition
  MiCS_VZ_89TE_I2C_StopCondition();
}

//-----------------------------------------------------------------------------
static etError MiCS_VZ_89TE_WriteCommand(uint8_t command)
{
  etError error; // error code

  // write the  8 bits of the command to the sensor
  error  = MiCS_VZ_89TE_I2C_WriteByte(command);

  return error;
}



/*******************************************************************************/
etError MiCS_VZ_89TE_ReadStatus(uint8_t *pBuffer, etI2cAck finaleAckNack, uint8_t timeout)
{
    etError error; // error code
  
    error = MiCS_VZ_89TE_StartWriteAccess();
  
		// if no error, write "read status" command
		if(error == NO_ERROR) error = MiCS_VZ_89TE_WriteCommand(MICS_VZ_89TE_ADDR_CMD_GETSTATUS);
		// if no error, start read access
		if(error == NO_ERROR) error = MiCS_VZ_89TE_StartReadAccess(); 
		// if no error, read status
		if(error == NO_ERROR) error = MiCS_VZ_89TE_I2C_ReadByte(&pBuffer[0], ACK, timeout);
		if(error == NO_ERROR) error = MiCS_VZ_89TE_I2C_ReadByte(&pBuffer[1], ACK, 0);
		if(error == NO_ERROR) error = MiCS_VZ_89TE_I2C_ReadByte(&pBuffer[2], ACK, 0);
		if(error == NO_ERROR) error = MiCS_VZ_89TE_I2C_ReadByte(&pBuffer[3], ACK, 0);
		if(error == NO_ERROR) error = MiCS_VZ_89TE_I2C_ReadByte(&pBuffer[4], ACK, 0);
		if(error == NO_ERROR) error = MiCS_VZ_89TE_I2C_ReadByte(&pBuffer[5], finaleAckNack, 0);
	  
		MiCS_VZ_89TE_StopAccess();
		
		return error;
     

}

/**************************************************************************************
        以下代码用于读取L3G400传感器,测试IIC
**************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////

//单字节写入*******************************************
etError Single_Write(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data)	
{
	  etError error; // error code
	
    error = MiCS_VZ_89TE_StartWriteAccess();
	
	  if(error == NO_ERROR) error = MiCS_VZ_89TE_I2C_WriteByte(REG_Address);
		if(error == NO_ERROR) error = MiCS_VZ_89TE_I2C_WriteByte(REG_data);
	
		MiCS_VZ_89TE_StopAccess();
		
		return error;
}

//单字节读取*****************************************
etError Single_Read(uint8_t REG_data,uint8_t SlaveAddress,uint8_t REG_Address)
{       	
		etError error; // error code
	
    error = MiCS_VZ_89TE_StartWriteAccess();
	  
	  if(error == NO_ERROR) error = MiCS_VZ_89TE_I2C_WriteByte(REG_Address);
		if(error == NO_ERROR) error = MiCS_VZ_89TE_StartReadAccess();
	  if(error == NO_ERROR) error = MiCS_VZ_89TE_I2C_ReadByte(&REG_data, NACK, 0);
	  
		MiCS_VZ_89TE_StopAccess();
		
		return error;
}

 //************初始化L3G4200D*********************************
void Init_L3G4200D(void)
{
	Single_Write(L3G4200_Addr,CTRL_REG1, 0x0f);
	Single_Write(L3G4200_Addr,CTRL_REG2, 0x00);
	Single_Write(L3G4200_Addr,CTRL_REG3, 0x08);
	Single_Write(L3G4200_Addr,CTRL_REG4, 0x30);	//+-2000dps
	Single_Write(L3G4200_Addr,CTRL_REG5, 0x00);
}	

//******读取L3G4200D数据****************************************
void READ_L3G4200D(uint8_t *pBuffer)
{
   Single_Read(pBuffer[0],L3G4200_Addr,OUT_X_L);
   Single_Read(pBuffer[1],L3G4200_Addr,OUT_X_H);

   Single_Read(pBuffer[2],L3G4200_Addr,OUT_Y_L);
   Single_Read(pBuffer[3],L3G4200_Addr,OUT_Y_H);

   Single_Read(pBuffer[4],L3G4200_Addr,OUT_Z_L);
   Single_Read(pBuffer[5],L3G4200_Addr,OUT_Z_H);

}

//////////////////////////////////////////////////////////////////////////////////////////

