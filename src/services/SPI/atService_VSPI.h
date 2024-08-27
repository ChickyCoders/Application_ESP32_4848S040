/**
@file
Service for communicating with OP320A&S SNM over RS232/485 (via RTU protocol).
*/
/*
  Service_atService_VSPI.h - Arduino library for communicating with OP320A&S SNM
  over RS232/485 (via RTU protocol).

  Library:: chickyPig_OP320_V1

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Service_atService_VSPI_
#define _Service_atService_VSPI_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "../Service.h"
#include "SPI.h"
/* _____DEFINETIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
SemaphoreHandle_t xMutex_VSPI = NULL;
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the 
 */
class Service_VSPI : public Service
{
public:
    Service_VSPI();
    ~Service_VSPI();
    
    void check_In();
    void check_Out();

protected:
     
private:
    static void  Service_VSPI_Start();
    static void  Service_VSPI_Execute();    
    static void  Service_VSPI_End();
} atService_VSPI ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_VSPI::Service_VSPI(/* args */)
{
    _Start_User      = *Service_VSPI_Start;
    _Execute_User    = *Service_VSPI_Execute;
    _End_User        = *Service_VSPI_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char*)"VSPI Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_VSPI::~Service_VSPI()
{
    
}
/**
 * This start function will init some critical function 
 */
void  Service_VSPI::Service_VSPI_Start()
{
    xMutex_VSPI = xSemaphoreCreateMutex();
    // SPI.begin();
}  

/**
 * Execute fuction of SNM app
 */
void  Service_VSPI::Service_VSPI_Execute()
{   
    if(atService_VSPI.User_Mode == SER_USER_MODE_DEBUG)
    {
    
    }   
}    
void  Service_VSPI::Service_VSPI_End(){}
/**
 * @brief Must call before using VSPI to read or write ...
 * 
 * @return * void 
 */
void  Service_VSPI::check_In()
{
    xSemaphoreTake( xMutex_VSPI, portMAX_DELAY );
}
/**
 * @brief Must call after using VSPI to read or write ...
 * 
 * @return * void 
 */
void  Service_VSPI::check_Out()
{
    xSemaphoreGive( xMutex_VSPI );
}

#endif


