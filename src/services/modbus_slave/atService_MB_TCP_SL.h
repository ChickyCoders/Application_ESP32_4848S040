/**
@file
*/
/*
  Library::

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Service_atService_MB_TCP_SL_
#define _Service_atService_MB_TCP_SL_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "..\src\services\Service.h"
#include <ModbusIP_ESP8266.h>

/* _____DEFINETIONS__________________________________________________________ */


/* _____GLOBAL VARIABLES_____________________________________________________ */


/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the 
 */
class Service_Modbus_TCP : public Service, public ModbusIP
{
public:
    Service_Modbus_TCP();
    ~Service_Modbus_TCP();


protected:
     
private:
    static void  Service_Modbus_Start();
    static void  Service_Modbus_Execute();    
    static void  Service_Modbus_End();

}  atService_MB_TCP_SL ;

/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_Modbus_TCP::Service_Modbus_TCP(/* args */)
{
    _Start_User      = *Service_Modbus_Start;
    _Execute_User    = *Service_Modbus_Execute;
    _End_User        = *Service_Modbus_End;

    // change the ID of Service
    ID_Service = 3;
    // change the Service name
    Name_Service = (char*)"Modbus TCP Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_Modbus_TCP::~Service_Modbus_TCP()
{
    
}
/**
 * This start function will init some critical function 
 */
void  Service_Modbus_TCP::Service_Modbus_Start()
{
    atService_MB_TCP_SL.server();
}  

/**
 * Execute fuction of SNM app
 */
void  Service_Modbus_TCP::Service_Modbus_Execute()
{   
        atService_MB_TCP_SL.task();
        yield();
}    
void  Service_Modbus_TCP::Service_Modbus_End(){}

#endif


