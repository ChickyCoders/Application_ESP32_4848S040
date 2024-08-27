/**
@file
Service for communicating with OP320A&S SNM over RS232/485 (via RTU protocol).
*/
/*
  Service_atService_I2C.h - Arduino library for communicating with OP320A&S SNM
  over RS232/485 (via RTU protocol).

  Library:: chickyPig_OP320_V1

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Service_atService_I2C_
#define _Service_atService_I2C_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "../Service.h"
#include "Wire.h"
/* _____DEFINETIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
SemaphoreHandle_t xMutex_I2C = NULL;
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the 
 */
class Service_I2C : public Service
{
public:
    Service_I2C();
    ~Service_I2C();
    void check_In();
    void check_Out();
protected:
     
private:
    static void  Service_I2C_Start();
    static void  Service_I2C_Execute();    
    static void  Service_I2C_End();
} atService_I2C ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_I2C::Service_I2C(/* args */)
{
    _Start_User      = *Service_I2C_Start;
    _Execute_User    = *Service_I2C_Execute;
    _End_User        = *Service_I2C_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char*)"I2C Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_I2C::~Service_I2C()
{
    
}
/**
 * This start function will init some critical function 
 */
void  Service_I2C::Service_I2C_Start()
{
    xMutex_I2C = xSemaphoreCreateMutex();
    Wire.begin();
}  

/**
 * Execute fuction of SNM app
 */
void  Service_I2C::Service_I2C_Execute()
{   
    if(atService_I2C.User_Mode == SER_USER_MODE_DEBUG)
    {
    
    }   
}    
void  Service_I2C::Service_I2C_End(){}
/**
 * @brief Must call before using i2c to read or write ...
 * 
 * @return * void 
 */
void  Service_I2C::check_In()
{
    xSemaphoreTake( xMutex_I2C, portMAX_DELAY );
}
/**
 * @brief Must call after using i2c to read or write ...
 * 
 * @return * void 
 */
void  Service_I2C::check_Out()
{
    xSemaphoreGive( xMutex_I2C );
}

#endif


