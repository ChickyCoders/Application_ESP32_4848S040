/**
@file
*/
/*
  Library::

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Service_atService_MB_TCP_MA_
#define _Service_atService_MB_TCP_MA_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "..\src\services\Service.h"
#include <ModbusIP_ESP8266.h>
#include "..\src\services\modbus_slave\modbus_register/SNM_MB_Register.h"
#include "..\src\services\modbus_slave\modbus_register/EMM_MB_Register.h"
#include "..\src\services\modbus_slave\modbus_register/HDM_MB_Register.h"
#include "..\src\services\modbus_slave\modbus_register/IDM_MB_Register.h"
#include "..\src\services\modbus_slave\modbus_register/RDM_MB_Register.h"
#include "..\src\services\modbus_slave\modbus_register/General_MB_Register.h"

/* _____DEFINETIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
SemaphoreHandle_t xMutex_MB_TCP_MA = NULL;

/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the 
 */
class Service_Modbus_TCP_MA : public Service, public ModbusIP
{
public:
    Service_Modbus_TCP_MA();
    ~Service_Modbus_TCP_MA();
    void check_In();
    void check_Out();
    
protected:
     
private:
    static void  Service_Modbus_Start();
    static void  Service_Modbus_Execute();    
    static void  Service_Modbus_End();
}  atService_MB_TCP_MA ;

/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_Modbus_TCP_MA::Service_Modbus_TCP_MA(/* args */)
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
Service_Modbus_TCP_MA::~Service_Modbus_TCP_MA()
{
    
}
/**
 * This start function will init some critical function 
 */
void  Service_Modbus_TCP_MA::Service_Modbus_Start()
{
    xMutex_MB_TCP_MA = xSemaphoreCreateMutex();
    atService_MB_TCP_MA.client();
}  

/**
 * Execute fuction of SNM app
 */
void  Service_Modbus_TCP_MA::Service_Modbus_Execute()
{   
    
}    
void  Service_Modbus_TCP_MA::Service_Modbus_End(){}
/**
 * @brief Must call before using Modbus TCP Master to read or write ...
 * 
 * @return * void 
 */
void  Service_Modbus_TCP_MA::check_In()
{
    xSemaphoreTake( xMutex_MB_TCP_MA, portMAX_DELAY );
}
/**
 * @brief Must call after using Modbus TCP Master to read or write ...
 * 
 * @return * void 
 */
void  Service_Modbus_TCP_MA::check_Out()
{
    atService_MB_TCP_MA.task();
    yield();
    xSemaphoreGive( xMutex_MB_TCP_MA );
}

#endif


