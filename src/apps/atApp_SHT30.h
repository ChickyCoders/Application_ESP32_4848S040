/**
@file
Application 
*/
/*
  Application

  Library::

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atSHT30_
#define _Application_atSHT30_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/i2c/atService_I2C.h"
#include "WEMOS_SHT3X.h"
/* _____DEFINITIONS__________________________________________________________ */
/* _____GLOBAL VARIABLES_____________________________________________________ */
  SHT3X sht30(0x45);
//   SHT3X sht30(0x44);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */
TaskHandle_t Task_atApp_SHT30;  
void atApp_SHT30_Task_Func(void *parameter);
/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Application class is the application to manage the 
 */
class App_SHT30 : public Application
{
public:
  	App_SHT30();
 	~App_SHT30();
	 
	float flTemperature = 0;
   	float flHumidity = 0;
   	bool Plugging = 0;

protected:

private:
  	static void  App_SHT30_Pend();
	static void  App_SHT30_Start();
	static void  App_SHT30_Restart();
	static void  App_SHT30_Execute();
	static void  App_SHT30_Suspend();
	static void  App_SHT30_Resume();	  
	static void  App_SHT30_End();
} atApp_SHT30 ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_SHT30::App_SHT30(/* args */)
{
  	_Pend_User 	     = *App_SHT30_Pend;
	_Start_User 	 = *App_SHT30_Start;
	_Restart_User 	 = *App_SHT30_Restart;
	_Execute_User 	 = *App_SHT30_Execute;
	_Suspend_User	 = *App_SHT30_Suspend;
	_Resume_User	 = *App_SHT30_Resume;
	_End_User	     = *App_SHT30_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"SHT30 Application";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_SHT30::~App_SHT30()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debug mode, task will send information of application to terminal to start the application.
 */
void  App_SHT30::App_SHT30_Pend()
{
    
}
/**
 * This start function will init some critical function 
 */
void  App_SHT30::App_SHT30_Start()
{
	// init atXYZ Service in the fist running time
	atService_I2C.Run_Service();
}  
/**
 * Restart function of SNM  app
 */
void  App_SHT30::App_SHT30_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_SHT30::App_SHT30_Execute()
{	
	atService_I2C.check_In();
	byte SHT30_Reading_Result = sht30.get();
	atService_I2C.check_Out();

	if( SHT30_Reading_Result ==0 )
	{
		atApp_SHT30.flTemperature = sht30.cTemp;
		atApp_SHT30.flHumidity    = sht30.humidity;
		if(atApp_SHT30.User_Mode == APP_USER_MODE_DEBUG)
		{
		Serial.printf(" Temperature: %.2f\n",atApp_SHT30.flTemperature);
		Serial.printf(" Humidity: %.2f\n\n",atApp_SHT30.flHumidity);
		}
		atApp_SHT30.Plugging = 1;
	}
	else
	{
		atApp_SHT30.Plugging = 0;
		if(atApp_SHT30.User_Mode == APP_USER_MODE_DEBUG)
		{
		Serial.println("[Error] - S2C SHT30\n");
		}
	}
    if(atApp_SHT30.User_Mode == APP_USER_MODE_DEBUG)
    {
		
    }   
}
void  App_SHT30::App_SHT30_Suspend(){}
void  App_SHT30::App_SHT30_Resume(){}	  
void  App_SHT30::App_SHT30_End(){}
void atApp_SHT30_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_SHT30.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif