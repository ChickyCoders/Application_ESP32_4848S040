/**
@file
*/
/*
  Service_atService_HSPI.h - 

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Service_atService_HSPI_
#define _Service_atService_HSPI_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "../Service.h"
#include "SPI.h"
/* _____DEFINETIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
SemaphoreHandle_t xMutex_HSPI = NULL;
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the 
 */
class Service_HSPI : public Service
{
public:
    Service_HSPI();
    ~Service_HSPI();
    
    void check_In();
    void check_Out();

protected:
     
private:
    static void  Service_HSPI_Start();
    static void  Service_HSPI_Execute();    
    static void  Service_HSPI_End();
} atService_HSPI ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_HSPI::Service_HSPI(/* args */)
{
    _Start_User      = *Service_HSPI_Start;
    _Execute_User    = *Service_HSPI_Execute;
    _End_User        = *Service_HSPI_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char*)"HSPI Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_HSPI::~Service_HSPI()
{
    
}
/**
 * This start function will init some critical function 
 */
void  Service_HSPI::Service_HSPI_Start()
{
    xMutex_HSPI = xSemaphoreCreateMutex();
    // HSPI.begin();
}  

/**
 * Execute fuction of SNM app
 */
void  Service_HSPI::Service_HSPI_Execute()
{   
    if(atService_HSPI.User_Mode == SER_USER_MODE_DEBUG)
    {
    
    }   
}    
void  Service_HSPI::Service_HSPI_End(){}
/**
 * @brief Must call before using HSPI to read or write ...
 * 
 * @return * void 
 */
void  Service_HSPI::check_In()
{
    xSemaphoreTake( xMutex_HSPI, portMAX_DELAY );
}
/**
 * @brief Must call after using HSPI to read or write ...
 * 
 * @return * void 
 */
void  Service_HSPI::check_Out()
{
    xSemaphoreGive( xMutex_HSPI );
}

#endif


