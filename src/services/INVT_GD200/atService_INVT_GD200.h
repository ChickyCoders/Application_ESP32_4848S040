/**
@file
Arduino library for communicating with GD200 Inverter over RS/485 (via RTU protocol).
*/
/*

  INVT_GD200A_V1.h - Arduino library for communicating with OP320A&S HMI
  over RS232/485 (via RTU protocol).

  Library:: INVT_GD200A_V1

  This version sofware driver is dev for GD200 series of INVT inverter. Prequisites is
  P00.01 = 2;
  P00.06 = 8;
  P00.17 = 1 ;// if the load is low
  p02.01 = 5.5;// Load Power
  p06.04 = 5 ;
  P14.00 = 3; //MODBUS_INVT_ADDRESS 
  P14.01 = 3;
  P14.02 = 1;
  P14.03 = 0;
  _RW_ characteristics means the function is with read and write characteristics
  _R_ characteristic can only read other than write 
  _W_ characteristic can only write other than read
  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/
#ifndef _Service_atService_INVT_GD200_
#define _Service_atService_INVT_GD200_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "../Service.h"
#include"../modbus_master/atService_MB_RTU_MA.h"
#include "INVT_GD200A_Defines.h"
/* _____DEFINETIONS__________________________________________________________ */
/* _____GLOBAL VARIABLES_____________________________________________________ */

/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the 
 */
class Service_INVT_GD200 : public Service
{
public:
    Service_INVT_GD200();
    ~Service_INVT_GD200();
    uint8_t   ID_Modbus = 0;
    float     Frequency  = 0;
    bool direction = FORWARD;
    // information
    uint8_t   Fault_Code(void);
    char*     Fault_Char(void);
    uint8_t   Control_Command(void);
    float     Frequency_Operating(void);
    float     Frequency_Setting(void);
    float     Speed_Operating(void);
    float     Voltage_Bus(void);
    float     Voltage_Output(void);
    float     Current_Output(void);
    float     Power_Output(void);
    float     Torque_Output(void);
 
    // command
    uint8_t   Set_Frequency(uint16_t Set_Frequency);
    uint8_t   Set_Frequency_Limit(uint16_t Forward_Limit, uint16_t Reverse_Limit);
    uint8_t   Run(bool Direction);
    uint8_t   Stop_Running(void);
    uint8_t   Jog(bool Direction);
    uint8_t   Stop_Jogging(void);
    uint8_t   Stop_Emergency(void);
    uint8_t   Reset_Fault(void);

protected:
    uint8_t  Get_Data_From_INVT(void);
    uint16_t INVT_Buffer_RW_Registers[15];
    uint16_t INVT_Buffer_R_Registers_1[4];
    uint16_t INVT_Buffer_R_Registers_2[16];
private :
    uint16_t INVT_Buffer_Fault_Code = 0;
    static void  Service_INVT_GD200_Start();
    static void  Service_INVT_GD200_Execute();    
    static void  Service_INVT_GD200_End();

} atService_INVT_GD200 ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_INVT_GD200::Service_INVT_GD200(/* args */)
{
    _Start_User      = *Service_INVT_GD200_Start;
    _Execute_User    = *Service_INVT_GD200_Execute;
    _End_User        = *Service_INVT_GD200_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char*)"INVT_GD200 Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_INVT_GD200::~Service_INVT_GD200()
{
    
}
/**
 * This start function will init some critical function 
 */
void  Service_INVT_GD200::Service_INVT_GD200_Start()
{
    atService_MB_RTU_MA.Run_Service();

    int8_t result = 0;
    // reset all fault
    result = atService_INVT_GD200.Reset_Fault();
    if (atService_INVT_GD200.User_Mode == SER_USER_MODE_DEBUG) 
    { 
        Serial.printf_P("    reset fault : ");
        Serial.printf_P(atService_MB_RTU_MA.Modbus_Error(result));
    }
    // set limit for frequency
    result = atService_INVT_GD200.Set_Frequency_Limit(5000,5000);
    if (atService_INVT_GD200.User_Mode == SER_USER_MODE_DEBUG) 
    {
        Serial.printf_P("    set limit : ");
        Serial.printf_P(atService_MB_RTU_MA.Modbus_Error(result));
    }
}  
/**
 * Execute fuction of 
 */
void  Service_INVT_GD200::Service_INVT_GD200_Execute()
{   
    uint8_t result = 0;

  result = atService_INVT_GD200.Get_Data_From_INVT();
  
 

  // reset fault if there remain
  if (atService_INVT_GD200.Fault_Code() == FAULT10)
  {
    result = atService_INVT_GD200.Reset_Fault();
    if (atService_INVT_GD200.User_Mode == SER_USER_MODE_DEBUG) 
    { 
      Serial.printf_P("    reset fault : ");
      Serial.printf_P(atService_MB_RTU_MA.Modbus_Error(result));
    }
  }

  // Set frequency to run
  result = atService_INVT_GD200.Set_Frequency((uint16_t)(atService_INVT_GD200.Frequency*100));
  if (atService_INVT_GD200.User_Mode == SER_USER_MODE_DEBUG) 
  {  
    Serial.printf_P("    set inverter frequency to %2.2f : ",atService_INVT_GD200.Frequency);
    Serial.printf_P(atService_MB_RTU_MA.Modbus_Error(result));
  }
 
 // run the inverter with preciously setted frequency
  if(atService_INVT_GD200.Frequency_Operating() == 0)
  {
    result = atService_INVT_GD200.Stop_Running();
    if (atService_INVT_GD200.User_Mode == SER_USER_MODE_DEBUG) 
    {  
      Serial.printf_P("    Stop running : ");
      Serial.printf_P(atService_MB_RTU_MA.Modbus_Error(result));
    }
    result = atService_INVT_GD200.Run(atService_INVT_GD200.direction);
    if (atService_INVT_GD200.User_Mode == SER_USER_MODE_DEBUG) 
    {  
      Serial.printf_P("    Run inverter: ");
      Serial.printf_P(atService_MB_RTU_MA.Modbus_Error(result));
    }
  }

  // change the direction of inverter if the inverter's direction is different from user choice
  if(atService_INVT_GD200.Control_Command() <= INVT_VALUE_REVERSE_RUNNING)
    if (atService_INVT_GD200.direction != atService_INVT_GD200.Control_Command())
    {
      result = atService_INVT_GD200.Run(atService_INVT_GD200.direction);
      if (atService_INVT_GD200.User_Mode == SER_USER_MODE_DEBUG) 
      {  
        Serial.printf_P("    Run inverter: ");
        Serial.printf_P(atService_MB_RTU_MA.Modbus_Error(result));
      }
    }

 
  if (atService_INVT_GD200.User_Mode == SER_USER_MODE_DEBUG)
  {
    Serial.printf_P("    get data : ");
    Serial.printf_P(atService_MB_RTU_MA.Modbus_Error(result));

    Serial.printf_P("        INVT_Buffer_RW_Registers:");
    for ( int8_t i = 0; i < sizeof(INVT_Buffer_RW_Registers)/2; i++)
    {
      Serial.printf_P(" - [200%x]:%d",i, atService_INVT_GD200.INVT_Buffer_RW_Registers[i]);
    }
    Serial.printf_P("\n");

    Serial.printf_P("        INVT_Buffer_R_Registers_1:");
    for ( int8_t i = 0; i < sizeof(INVT_Buffer_R_Registers_1)/2; i++)
    {
      Serial.printf_P("- [210%x]:%d",i, atService_INVT_GD200.INVT_Buffer_R_Registers_1[i]);
    }
    Serial.printf_P("\n");

    Serial.printf_P("        INVT_Buffer_R_Registers_2:");
    for ( int8_t i = 0; i < sizeof(INVT_Buffer_R_Registers_2)/2; i++)
    {
      Serial.printf_P(" - [300%x]:%d",i, atService_INVT_GD200.INVT_Buffer_R_Registers_2[i]);
    }
    Serial.printf_P("\n");

    Serial.printf_P("    fault INVT : ");
    Serial.printf_P(atService_INVT_GD200.Fault_Char());

    Serial.printf_P("    Setting frequency: %.2f (Hz)\n",   atService_INVT_GD200.Frequency_Setting());
    Serial.printf_P("    Operating frequency: %.2f (Hz)\n", atService_INVT_GD200.Frequency_Operating());
    Serial.printf_P("    Operating speed: %.1f (RPM)\n",    atService_INVT_GD200.Speed_Operating());
    Serial.printf_P("    Bus voltage: %.1f (V)\n",          atService_INVT_GD200.Voltage_Bus());
    Serial.printf_P("    Output voltage: %.1f (V)\n",       atService_INVT_GD200.Voltage_Output());
    Serial.printf_P("    Output currentL %.1f (A)\n",       atService_INVT_GD200.Current_Output());
    Serial.printf_P("    Output Power: %.1f (%%)\n",        atService_INVT_GD200.Power_Output());
    Serial.printf_P("    Output torque: %.1f (N.m)\n",      atService_INVT_GD200.Torque_Output());
  }
}    
/**
 * End fuction of
 */
void  Service_INVT_GD200::Service_INVT_GD200_End(){}
/**
 * Get read registers from inverter. 
 * This function will read all read register from form inverter and write it to INVT_Buffer.
 * Need to be call regularly to get data from 
 */
uint8_t Service_INVT_GD200::Get_Data_From_INVT(void)
{
  // INVT_Buffer_RW_Register
  // Read all the holding register form HMI 3 if there any fault.
  uint8_t result =  0;
  uint8_t atCount = 0;
  for(int i = 0; i<3; i++)
  {
    // read the
    result = atService_MB_RTU_MA.readHoldingRegisters_at(atService_INVT_GD200.ID_Modbus,INVT_REGISTER_RW_CONTROL_COMMAND,sizeof(atService_INVT_GD200.INVT_Buffer_RW_Registers)/2);
    delay(Time_Delay_5ms);
    if ( result == 0) break;
  }
  // if there is any fault will update the data that is read from HMI, to user data
  if (result != 0) return result;
  else
  {
    for(atCount = 0; atCount < sizeof(INVT_Buffer_RW_Registers)/2; atCount ++)
    {
      // read data from modbus buffer and write to INVT buffer
      INVT_Buffer_RW_Registers[atCount] = atService_MB_RTU_MA.getResponseBuffer(atCount);      
    }
  }

  // INVT_Buffer_R_Registers_1
  for(int i = 0; i<3; i++)
  {
    // read the
    result = atService_MB_RTU_MA.readHoldingRegisters_at(atService_INVT_GD200.ID_Modbus,INVT_REGISTER_R_SW1,sizeof(atService_INVT_GD200.INVT_Buffer_R_Registers_1)/2);
    delay(Time_Delay_5ms);
    if ( result == 0) break;
  }
  // if there is any fault will update the data that is read from HMI, to user data
  if (result != 0) return result;
  else
  {
    for(atCount = 0; atCount < sizeof(INVT_Buffer_R_Registers_1)/2; atCount ++)
    {
      // read data from modbus buffer and write to INVT buffer
      INVT_Buffer_R_Registers_1[atCount] = atService_MB_RTU_MA.getResponseBuffer(atCount);      
    }
  }

  // INVT_Buffer_R_Registers_2
  for(int i = 0; i<3; i++)
  {
    // read the
    result = atService_MB_RTU_MA.readHoldingRegisters_at(atService_INVT_GD200.ID_Modbus,INVT_REGISTER_R_OPERATION_FREQUENCY,sizeof(atService_INVT_GD200.INVT_Buffer_R_Registers_2)/2);
    delay(Time_Delay_5ms);
    if ( result == 0) break;
  }
  // if there is any fault will update the data that is read from HMI, to user data
  if (result != 0) return result;
  else
  {
    for(atCount = 0; atCount < sizeof(INVT_Buffer_R_Registers_2)/2; atCount ++)
    {
      // read data from modbus buffer and write to INVT buffer
      INVT_Buffer_R_Registers_2[atCount] = atService_MB_RTU_MA.getResponseBuffer(atCount);      
    }
  }

  // inverter fault code
  for(int i = 0; i<3; i++)
  {
    // read the
    result = atService_MB_RTU_MA.readHoldingRegisters_at(atService_INVT_GD200.ID_Modbus,INVT_REGISTER_R_FAULT_CODE,1);
    delay(Time_Delay_5ms);
    if ( result == 0) break;
  }
  // if there is any fault will  update the data that is read from HMI, to user data
  if (result != 0) return result;
  else
  {
    atService_INVT_GD200.INVT_Buffer_Fault_Code = atService_MB_RTU_MA.getResponseBuffer(0);      
  }
    
  atService_MB_RTU_MA.clearResponseBuffer();
  return result;
}
/**
 * Run the inverter fellow the direction and the frequency that have been set.
 * @param Direction : FORWARD or REVERSE
 */
uint8_t Service_INVT_GD200::Run(bool Direction)
{
  uint8_t result =  0;
  if (Direction == FORWARD)
    result = atService_MB_RTU_MA.writeSingleRegister_at(atService_INVT_GD200.ID_Modbus,INVT_REGISTER_RW_CONTROL_COMMAND, INVT_VALUE_FORWARD_RUNNING);
  else
    result = atService_MB_RTU_MA.writeSingleRegister_at(atService_INVT_GD200.ID_Modbus,INVT_REGISTER_RW_CONTROL_COMMAND, INVT_VALUE_REVERSE_RUNNING);
  delay(Time_Delay_5ms);
  return result;
}
/**
 * Stop running.
 * This will stop the inverter 
 */
uint8_t Service_INVT_GD200::Stop_Running(void)
{
  uint8_t result =  0;
  result = atService_MB_RTU_MA.writeSingleRegister_at(atService_INVT_GD200.ID_Modbus,INVT_REGISTER_RW_CONTROL_COMMAND, INVT_VALUE_STOP);
  delay(Time_Delay_5ms);
  return result;
}
/**
 * Jogging 
 * @param Direction  FORWARD or REVERSE
 */
uint8_t Service_INVT_GD200::Jog(bool Direction)
{
  uint8_t result =  0;
  if (Direction == FORWARD)
    result = atService_MB_RTU_MA.writeSingleRegister_at(atService_INVT_GD200.ID_Modbus,INVT_REGISTER_RW_CONTROL_COMMAND, INVT_VALUE_FORWARD_JOGGING);
  else
    result = atService_MB_RTU_MA.writeSingleRegister_at(atService_INVT_GD200.ID_Modbus,INVT_REGISTER_RW_CONTROL_COMMAND, INVT_VALUE_REVERSE_JOGGING);
    delay(Time_Delay_5ms);
  return result;
}
/**
 * Stop jogging
 */
uint8_t Service_INVT_GD200::Stop_Jogging()
{
  uint8_t result =  0;
  result = atService_MB_RTU_MA.writeSingleRegister_at(atService_INVT_GD200.ID_Modbus,INVT_REGISTER_RW_CONTROL_COMMAND, INVT_VALUE_JOGGING_STOP);
  delay(Time_Delay_5ms);
  return result;
}
/**
 * Emergency stop. Just use in emergency case
 */
uint8_t Service_INVT_GD200::Stop_Emergency(void)
{
  uint8_t result =  0;
  result = atService_MB_RTU_MA.writeSingleRegister_at(atService_INVT_GD200.ID_Modbus,INVT_REGISTER_RW_CONTROL_COMMAND, INVT_VALUE_COAST_TO_STOP);
  delay(Time_Delay_5ms);
  return result;
}
/**
 * reset fault.
 * This function will erase the fault history in inverter. Should be call after an electrical fault
 */
uint8_t Service_INVT_GD200::Reset_Fault(void)
{
  uint8_t result =  0;
  delay(Time_Delay_5ms);
  result = atService_MB_RTU_MA.writeSingleRegister_at(atService_INVT_GD200.ID_Modbus,INVT_REGISTER_RW_CONTROL_COMMAND, INVT_VALUE_FAULT_RESET);
  delay(Time_Delay_500ms);
  return result;
}
/**
 * Set frequency for inverter.
 * this frequency will be send to inverter and udpate to operate inverter. To
 * ensure if the defined user frequency, user can check by Frequency_Setting();
 * There are 2 Fmaxs for 2 rotation direction: forward and reverse rotation frequency
 * Range: 0~Fmax
 * Unit: 0.01Hz
 * @param Set_Frequency the frequency will be set for inverter
 */
uint8_t Service_INVT_GD200::Set_Frequency(uint16_t Set_Frequency)
{
  uint8_t result =  0;
  result = atService_MB_RTU_MA.writeSingleRegister_at(atService_INVT_GD200.ID_Modbus,INVT_REGISTER_RW_SETTING_FREQUENCY, Set_Frequency);
  delay(Time_Delay_5ms);
  return result;
}

/**
 * Set limits for forward and reverse rotation frequency. The setting frequency must be less than limit
 * @param Forward_Limit the upper forward rotation frequency (0.00Hz)
 * @param Reverse_Limit the upper reverse rotation frequency (0.00Hz)
 */
uint8_t Service_INVT_GD200::Set_Frequency_Limit(uint16_t Forward_Limit, uint16_t Reverse_Limit)
{
  uint8_t result =  0;
  result = atService_MB_RTU_MA.writeSingleRegister_at(ID_Modbus,INVT_REGISTER_RW_FORWARD_ROTATION_LIMIT_FREQ, Forward_Limit);
  delay(Time_Delay_5ms);
  // if there is any fault, return error code
  if (result == 0) return result;
  INVT_Buffer_Fault_Code = atService_MB_RTU_MA.writeSingleRegister_at(atService_INVT_GD200.ID_Modbus, INVT_REGISTER_RW_REVERSE_ROTATION_LIMIT_FREQ, Reverse_Limit);
  delay(Time_Delay_5ms);
  return result;
}
/**
 * read the code of inverter fault 
 */
uint8_t Service_INVT_GD200::Fault_Code()
{
  return INVT_Buffer_Fault_Code;
}
/**
 * return the fault by char*
 */
char* Service_INVT_GD200::Fault_Char(void)
{
  switch (INVT_Buffer_Fault_Code)
  {
  case FAULT1:
    return FAULT1_Char;
    break;
  case FAULT2:
    return FAULT2_Char;
    break;
  case FAULT3:
    return FAULT3_Char;
    break;
  case FAULT4:
    return FAULT4_Char;
    break;
  case FAULT5:
    return FAULT5_Char;
    break;
  case FAULT6:
    return FAULT6_Char;
    break;
  case FAULT7:
    return FAULT7_Char;
    break;
  case FAULT8:
    return FAULT8_Char;
    break;
  case FAULT9:
    return FAULT9_Char;
    break;
  case FAULT10:
    return FAULT10_Char;
    break;
  case FAULT11:
    return FAULT11_Char;
    break;
  case FAULT12:
    return FAULT12_Char;
    break;
  case FAULT13:
    return FAULT13_Char;
    break;
  case FAULT14:
    return FAULT14_Char;
    break;
  case FAULT15:
    return FAULT15_Char;
    break;
  case FAULT16:
    return FAULT16_Char;
    break;
  case FAULT17:
    return FAULT17_Char;
    break;
  case FAULT18:
    return FAULT18_Char;
    break;
  case FAULT19:
    return FAULT19_Char;
    break;
  case FAULT20:
    return FAULT20_Char;
    break;
  case FAULT21:
    return FAULT21_Char;
    break;
  case FAULT22:
    return FAULT22_Char;
    break;
  case FAULT23:
    return FAULT23_Char;
    break;
  case FAULT24:
    return FAULT24_Char;
    break;
  case FAULT25:
    return FAULT25_Char;
    break;
  case FAULT26:
    return FAULT26_Char;
    break;
  case FAULT27:
    return FAULT27_Char;
    break;
  case FAULT28:
    return FAULT28_Char;
    break;
  case FAULT32:
    return FAULT32_Char;
    break;
  case FAULT33:
    return FAULT33_Char;
    break;
  case FAULT36:
    return FAULT36_Char;
    break;

  default:
    return FAULT0_Char;
    break;
  }
}

uint8_t Service_INVT_GD200::Control_Command(void)
{
  return atService_INVT_GD200.INVT_Buffer_RW_Registers[INVT_Buffer_RW_Index_Control_Command];
}
/**
 * return the operating frequency
 * Unit: Hz
 */
float Service_INVT_GD200::Frequency_Operating(void)
{
  return (float)INVT_Buffer_R_Registers_2[INVT_Buffer_R_Index_OPERATION_FREQUENCY] / 100;
}
/**
 * return the setting frequency
 * Unit: Hz
 */
float Service_INVT_GD200::Frequency_Setting(void)
{
  return (float)INVT_Buffer_R_Registers_2[INVT_Buffer_R_Index_SETTING_FREQUENCY] / 100;
}
/**
 * Bus voltage. 
 * Range: 0~1200V
 * Unit: V
 */
float Service_INVT_GD200::Voltage_Bus(void)
{
  return (float)INVT_Buffer_R_Registers_2[INVT_Buffer_R_Index_BUS_VOLTAGE]/10;
}
/**
 * output voltage
 * Range: 0~1200V
 * Unit: V
 */
float Service_INVT_GD200::Voltage_Output(void)
{
  return INVT_Buffer_R_Registers_2[INVT_Buffer_R_Index_OUTPUT_VOLTAGE];
}
/**
 * Output current
 * Range: 0.0~5000.0A
 * Unit; A
 */
float Service_INVT_GD200::Current_Output(void)
{
  return (float)INVT_Buffer_R_Registers_2[INVT_Buffer_R_Index_OUTPUT_CURRENT]/10;
}
/**
 * output power
 * Range: -300.0~300.0%
 * Unit: %
 */
float  Service_INVT_GD200::Power_Output(void)
{
  return (float)INVT_Buffer_R_Registers_2[INVT_Buffer_R_Index_OUTPUT_POWER]/10;
}

/**
 * operation speed
 * Range: 0-65535 
 * Unit: RPM
 */
float Service_INVT_GD200::Speed_Operating()
{
  return (float)INVT_Buffer_R_Registers_2[INVT_Buffer_R_Index_OPERATION_SPEED];
}

/**
 * output torque
 * Range: 0.0 - 6553.5
 * Unit: N.m
 */
float Service_INVT_GD200::Torque_Output()
{
  return (float)((int16_t)INVT_Buffer_R_Registers_2[INVT_Buffer_R_Index_OUTPUT_TORQUE])/10;
}
#endif


