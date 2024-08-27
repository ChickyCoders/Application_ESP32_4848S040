/**
@file
Service for communicating with OP320A&S SNM over RS232/485 (via RTU protocol).
*/
/*
  Service_atService_MB_RTU_SL.h - Arduino library for communicating with OP320A&S SNM
  over RS232/485 (via RTU protocol).

  Library:: chickyPig_OP320_V1

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Service_atService_MB_RTU_Slave_
#define _Service_atService_MB_RTU_Slave_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "../Service.h"
#include <ModbusRTU.h>
/* _____DEFINETIONS__________________________________________________________ */
/* _____GLOBAL VARIABLES_____________________________________________________ */
// #define RX2 27
// #define TX2 25
// ModbusRTU Modbus_RTU_Slave;
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the 
 */
class Service_Modbus_RTU_Slave : public Service, public ModbusRTU
{
public:
    Service_Modbus_RTU_Slave();
    ~Service_Modbus_RTU_Slave();
    
    unsigned int baudrate = 9600;
    uint32_t Serial_config = SERIAL_8N1;
    int Slave_ID = 1;

protected:
     
private:
    static void  Service_Modbus_RTU_Slave_Start();
    static void  Service_Modbus_RTU_Slave_Execute();    
    static void  Service_Modbus_RTU_Slave_End();
} atService_MB_RTU_SL ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_Modbus_RTU_Slave::Service_Modbus_RTU_Slave(/* args */)
{
    _Start_User      = *Service_Modbus_RTU_Slave_Start;
    _Execute_User    = *Service_Modbus_RTU_Slave_Execute;
    _End_User        = *Service_Modbus_RTU_Slave_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char*)"Modbus_RTU_Slave Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_Modbus_RTU_Slave::~Service_Modbus_RTU_Slave()
{
    
}
/**
 * This start function will init some critical function 
 */
void  Service_Modbus_RTU_Slave::Service_Modbus_RTU_Slave_Start()
{
    Serial2.begin(atService_MB_RTU_SL.baudrate, atService_MB_RTU_SL.Serial_config);
    atService_MB_RTU_SL.begin(&Serial2);
    atService_MB_RTU_SL.slave(atService_MB_RTU_SL.Slave_ID);
}  

/**
 * Execute fuction of SNM app
 */
void  Service_Modbus_RTU_Slave::Service_Modbus_RTU_Slave_Execute()
{   
    atService_MB_RTU_SL.task();
    yield();
    if(atService_MB_RTU_SL.User_Mode == SER_USER_MODE_DEBUG)
    {
        
    }   
}    
void  Service_Modbus_RTU_Slave::Service_Modbus_RTU_Slave_End(){}

#endif


