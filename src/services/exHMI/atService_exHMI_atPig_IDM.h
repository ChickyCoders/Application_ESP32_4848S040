/**
@file
*/
/*
  Service_atService_exHMI_atPig_IDM.h

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Service_atService_exHMI_atPig_IDM_
#define _Service_atService_exHMI_atPig_IDM_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "../Service.h"
#include "../modbus_master/atService_MB_RTU_MA.h"
/* _____DEFINETIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */

/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the 
 */
class Service_exHMI_atPig_IDM : public Service
{
public:
  Service_exHMI_atPig_IDM();
  ~Service_exHMI_atPig_IDM();
  uint8_t ID_Modbus;
  uint8_t SendDataToHMI_1st(void);
  uint8_t SendDataToHMI(void);
  uint8_t GetDataFromHMI(void);
  uint8_t Application(void);
  // internal data : the user definition
  uint16_t HMI_Fan_Speed               = 0 ;
  uint16_t HMI_Fan_Speed_High_Limit    = 0 ;
  uint16_t HMI_Fan_Speed_Low_Limit     = 0 ;
  bool HMI_Temperature_On_Off      = 0 ;

  uint16_t HMI_Temperature_Monitoring = 0 ;
  uint16_t HMI_Temperature_High_Limit  = 0 ;
  uint16_t HMI_Temperature_Low_Limit   = 0 ;
  bool HMI_Humidity_On_Off         = 0 ;

  uint16_t HMI_Humidity_Monitoring    = 0 ;
  uint16_t HMI_Humidity_High_Limit     = 0 ;
  uint16_t HMI_Humidity_Low_Limit      = 0 ;
  bool HMI_CO2_On_Off              = 0 ;

  uint16_t HMI_CO2_Monitoring         = 0 ;
  uint16_t HMI_CO2_High_Limit          = 0 ;
  uint16_t HMI_CO2_Low_Limit           = 0 ;
  bool HMI_Plugging                = 0 ;

  uint16_t HMI_Number_Of_Holding_Registers = 19;
  // the address of variables  in HMI
private:
  static const uint8_t ADDRESS_HMI_Fan_Speed               = 0;
  static const uint8_t ADDRESS_HMI_Fan_Speed_High_Limit    = 1;
  static const uint8_t ADDRESS_HMI_Fan_Speed_Low_Limit     = 2;

  static const uint8_t ADDRESS_HMI_Temperature_On_Off      = 3;
  static const uint8_t ADDRESS_HMI_Temperature_Monitoring  = 4;
  static const uint8_t ADDRESS_HMI_Temperature_High_Limit  = 5;
  static const uint8_t ADDRESS_HMI_Temperature_Low_Limit   = 6;

  static const uint8_t ADDRESS_HMI_Humidity_On_Off         = 7;
  static const uint8_t ADDRESS_HMI_Humidity_Monitoring     = 8;
  static const uint8_t ADDRESS_HMI_Humidity_High_Limit     = 9;
  static const uint8_t ADDRESS_HMI_Humidity_Low_Limit      = 10;

  static const uint8_t ADDRESS_HMI_CO2_On_Off              = 11;
  static const uint8_t ADDRESS_HMI_CO2_Monitoring          = 12;
  static const uint8_t ADDRESS_HMI_CO2_High_Limit          = 14;
  static const uint8_t ADDRESS_HMI_CO2_Low_Limit           = 16;
  static const uint8_t ADDRESS_HMI_Plugging                = 18; 
    
private:

  static void  Service_exHMI_atPig_IDM_Start();
  static void  Service_exHMI_atPig_IDM_Execute();    
  static void  Service_exHMI_atPig_IDM_End();
} atService_exHMI_atPig_IDM ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_exHMI_atPig_IDM::Service_exHMI_atPig_IDM(/* args */)
{
    _Start_User      = *Service_exHMI_atPig_IDM_Start;
    _Execute_User    = *Service_exHMI_atPig_IDM_Execute;
    _End_User        = *Service_exHMI_atPig_IDM_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char*)"exHMI_atPig_IDM Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_exHMI_atPig_IDM::~Service_exHMI_atPig_IDM()
{
    
}
/**
 * This start function will init some critical function 
 */
void  Service_exHMI_atPig_IDM::Service_exHMI_atPig_IDM_Start()
{
    atService_MB_RTU_MA.Run_Service();
}  

/**
 * Execute fuction of SNM app
 */
void  Service_exHMI_atPig_IDM::Service_exHMI_atPig_IDM_Execute()
{   
    if(atService_exHMI_atPig_IDM.User_Mode == SER_USER_MODE_DEBUG)
    {
        
    }   
}    
void  Service_exHMI_atPig_IDM::Service_exHMI_atPig_IDM_End(){}


/**
 * Send the data form internal data to hmi. Firstly, this function will push data ro TX buffer, the register 0 will be wrote to TransmitBuffer[0], 
 * the register 1 will be wrote to TransmitBuffer[1] ... Thus, they will be sent to HMI by Modbus. This function will send all data event output 
 * register and input register form LMC to HMI. Just call one time when power up system
 * @param HMI_Fan_Speed                
 * @param HMI_Fan_Speed_High_Limit     
 * @param HMI_Fan_Speed_Low_Limit      
 * @param HMI_Temperature_On_Off       
 * @param HMI_Temperature_Monitoring  
 * @param HMI_Temperature_High_Limit   
 * @param HMI_Temperature_Low_Limit    
 * @param HMI_Humidity_On_Off              
 * @param HMI_Humidity_Monitoring     
 * @param HMI_Humidity_High_Limit      
 * @param HMI_Humidity_Low_Limit       
 * @param HMI_CO2_On_Off               
 * @param HMI_CO2_Monitoring          
 * @param HMI_CO2_High_Limit           
 * @param HMI_CO2_Low_Limit            
 * @param HMI_Plugging   
 * @return 0 on success; exception number on failure
 * @ingroup Operate
*/
uint8_t Service_exHMI_atPig_IDM::SendDataToHMI_1st(void)
{
  // write the use data to Transmit buffer
  // write the information of fan speed
  atService_MB_RTU_MA.setTransmitBuffer(ADDRESS_HMI_Fan_Speed, HMI_Fan_Speed);
  atService_MB_RTU_MA.setTransmitBuffer(ADDRESS_HMI_Fan_Speed_High_Limit, HMI_Fan_Speed_High_Limit);
  atService_MB_RTU_MA.setTransmitBuffer(ADDRESS_HMI_Fan_Speed_Low_Limit, HMI_Fan_Speed_Low_Limit);

  atService_MB_RTU_MA.setTransmitBuffer(ADDRESS_HMI_Temperature_On_Off, HMI_Temperature_On_Off);
  atService_MB_RTU_MA.setTransmitBuffer(ADDRESS_HMI_Temperature_Monitoring, HMI_Temperature_Monitoring);
  atService_MB_RTU_MA.setTransmitBuffer(ADDRESS_HMI_Temperature_High_Limit, HMI_Temperature_High_Limit);
  atService_MB_RTU_MA.setTransmitBuffer(ADDRESS_HMI_Temperature_Low_Limit, HMI_Temperature_Low_Limit);
  
  atService_MB_RTU_MA.setTransmitBuffer(ADDRESS_HMI_Humidity_On_Off, HMI_Humidity_On_Off);
  atService_MB_RTU_MA.setTransmitBuffer(ADDRESS_HMI_Humidity_Monitoring, HMI_Humidity_Monitoring);
  atService_MB_RTU_MA.setTransmitBuffer(ADDRESS_HMI_Humidity_High_Limit, HMI_Humidity_High_Limit);
  atService_MB_RTU_MA.setTransmitBuffer(ADDRESS_HMI_Humidity_Low_Limit, HMI_Humidity_Low_Limit);    

  atService_MB_RTU_MA.setTransmitBuffer(ADDRESS_HMI_CO2_On_Off, HMI_CO2_On_Off);
  atService_MB_RTU_MA.setTransmitBuffer(ADDRESS_HMI_CO2_Monitoring, HMI_CO2_Monitoring);
  atService_MB_RTU_MA.setTransmitBuffer(ADDRESS_HMI_CO2_High_Limit, HMI_CO2_High_Limit);
  atService_MB_RTU_MA.setTransmitBuffer(ADDRESS_HMI_CO2_Low_Limit, HMI_CO2_Low_Limit); 

// this register will always be wrote by 1 - Plugged
  atService_MB_RTU_MA.setTransmitBuffer(ADDRESS_HMI_Plugging, 1);
  // try to send 3 times til successfully sending data
  uint8_t result =  0;
  for(int i = 0; i<3; i++)
  {
    result = atService_MB_RTU_MA.writeMultipleRegisters_at(ID_Modbus, 0, atService_exHMI_atPig_IDM.HMI_Number_Of_Holding_Registers);
    if ( result == 0) break;
  }
  return result;
}
/**
 * Send the data form internal data to hmi. Firstly, this function will push data ro TX buffer, the register
 *  0 will be wrote to TransmitBuffer[0], the register 1 will be wrote to TransmitBuffer[1] ... Thus, they will
 *  be sent to HMI by Modbus. This function will send all output register from LCM to HMI.
 * @param HMI_Fan_Speed                
 * @param HMI_Temperature_Monitoring  
 * @param HMI_Humidity_Monitoring     
 * @param HMI_CO2_Monitoring          
 * @param HMI_Plugging   
 * @return 0 on success; exception number on failure
 * @ingroup Operate
*/
uint8_t Service_exHMI_atPig_IDM::SendDataToHMI(void)
{
  uint8_t result = 0;
  // send the tha data of fan speed to HMI
  result =+ atService_MB_RTU_MA.writeSingleRegister_at(ID_Modbus,ADDRESS_HMI_Fan_Speed, HMI_Fan_Speed);
  // Send the infomation of Temperature to HMI
  result =+ atService_MB_RTU_MA.writeSingleRegister_at(ID_Modbus,ADDRESS_HMI_Temperature_Monitoring, HMI_Temperature_Monitoring);
  // Send the infomation of Humidity to HMI
  result =+ atService_MB_RTU_MA.writeSingleRegister_at(ID_Modbus,ADDRESS_HMI_Humidity_Monitoring, HMI_Humidity_Monitoring);
  // Send the infomation of Co2 to HMI
  result =+ atService_MB_RTU_MA.writeSingleRegister_at(ID_Modbus,ADDRESS_HMI_CO2_Monitoring, HMI_CO2_Monitoring);
  // this register will always be wrote by 1 - Plugged
  // result =+ atService_MB_RTU_MA.writeSingleRegister(ID_Modbus,ADDRESS_HMI_Plugging, 1);
  // try to send 3 times til successfully sending data
  return result;
}

/**
 * Get data from the hmi and write to user data. This funcion reads data form hmi what will be back to ResponseBuffer, 
 * and take to to the user data. Just the inputs register will be read back thi buffer
 * @param HMI_Fan_Speed_High_Limit     
 * @param HMI_Fan_Speed_Low_Limit      
 * @param HMI_Temperature_On_Off       
 * @param HMI_Temperature_High_Limit   
 * @param HMI_Temperature_Low_Limit    
 * @param HMI_Humidity_On_Off              
 * @param HMI_Humidity_High_Limit      
 * @param HMI_Humidity_Low_Limit       
 * @param HMI_CO2_On_Off               
 * @param HMI_CO2_High_Limit           
 * @param HMI_CO2_Low_Limit            
 * @param HMI_Plugging   
 * @return 0 on success; exception number on failure
 * @ingroup Operate
 **/
uint8_t Service_exHMI_atPig_IDM::GetDataFromHMI(void)
{
// Read all the holding register form HMI 3 if there any fault.
  uint8_t result =  0;
  for(int i = 0; i<3; i++)
  {
    result = atService_MB_RTU_MA.readHoldingRegisters_at(ID_Modbus,0,HMI_Number_Of_Holding_Registers);
    if ( result == 0) break;
  }
// if there is any fault will update the data that is read from HMI, to user data
  if (result != 0) 
  {
    HMI_Plugging = 0;
    return result;
  }
// unless, update the data what is read from HMI, to user data
  if (result == atService_MB_RTU_MA.ku8MBSuccess)
  {
    HMI_Plugging = atService_MB_RTU_MA.getResponseBuffer(ADDRESS_HMI_Plugging);
    if(HMI_Plugging)
    {
      HMI_Fan_Speed_High_Limit = atService_MB_RTU_MA.getResponseBuffer(ADDRESS_HMI_Fan_Speed_High_Limit);
      HMI_Fan_Speed_Low_Limit  = atService_MB_RTU_MA.getResponseBuffer(ADDRESS_HMI_Fan_Speed_Low_Limit );

      HMI_Temperature_On_Off     = atService_MB_RTU_MA.getResponseBuffer(ADDRESS_HMI_Temperature_On_Off );
      HMI_Temperature_High_Limit = atService_MB_RTU_MA.getResponseBuffer(ADDRESS_HMI_Temperature_High_Limit);
      HMI_Temperature_Low_Limit = atService_MB_RTU_MA.getResponseBuffer(ADDRESS_HMI_Temperature_Low_Limit);

      HMI_Humidity_On_Off     = atService_MB_RTU_MA.getResponseBuffer(ADDRESS_HMI_Humidity_On_Off );
      HMI_Humidity_High_Limit = atService_MB_RTU_MA.getResponseBuffer(ADDRESS_HMI_Humidity_High_Limit);
      HMI_Humidity_Low_Limit = atService_MB_RTU_MA.getResponseBuffer(ADDRESS_HMI_Humidity_Low_Limit);;               

      HMI_CO2_On_Off     = atService_MB_RTU_MA.getResponseBuffer(ADDRESS_HMI_CO2_On_Off );
      HMI_CO2_High_Limit = atService_MB_RTU_MA.getResponseBuffer(ADDRESS_HMI_CO2_High_Limit);
      HMI_CO2_Low_Limit = atService_MB_RTU_MA.getResponseBuffer(ADDRESS_HMI_CO2_Low_Limit);
    }
  }
  atService_MB_RTU_MA.clearResponseBuffer();
  return result;
}

/**
 * The default application for OP320A&S class, Use an run this application at 1HZ fo slower
 * The application has no critical process,
 */ 
#endif


