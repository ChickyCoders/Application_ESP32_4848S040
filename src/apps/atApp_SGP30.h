/**
@file
Application for communicating with SGP30 via i2c.
*/
/*
  Application

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atSGP30_
#define _Application_atSGP30_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "SparkFun_SGP30_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP30
#include "../services/i2c/atService_I2C.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
SGP30 sgp30; //create an object of the SGP30 class
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */
TaskHandle_t Task_atApp_SGP30;  
void atApp_SGP30_Task_Func(void *parameter);
/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Application class is the application to manage the 
 */
class App_SGP30 : public Application
{
public:
  	App_SGP30();
 	~App_SGP30();
	 
	float CO2 = 0;
	float TVOC = 0;
	float H2  = 0;
	float Ethanol = 0;
	bool Plugging = 0;

protected:

private:
  	static void  App_SGP30_Pend();
	static void  App_SGP30_Start();
	static void  App_SGP30_Restart();
	static void  App_SGP30_Execute();
	static void  App_SGP30_Suspend();
	static void  App_SGP30_Resume();	  
	static void  App_SGP30_End();
} atApp_SGP30 ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_SGP30::App_SGP30(/* args */)
{
  	_Pend_User 	     = *App_SGP30_Pend;
	_Start_User 	 = *App_SGP30_Start;
	_Restart_User 	 = *App_SGP30_Restart;
	_Execute_User 	 = *App_SGP30_Execute;
	_Suspend_User	 = *App_SGP30_Suspend;
	_Resume_User	 = *App_SGP30_Resume;
	_End_User	     = *App_SGP30_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"SGP30 Application";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_SGP30::~App_SGP30()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debug mode, task will send information of application to terminal to start the application.
 */
void  App_SGP30::App_SGP30_Pend()
{
    
}
/**
 * This start function will init some critical function 
 */
void  App_SGP30::App_SGP30_Start()
{
	// init atXYZ Service in the fist running time
	atService_I2C.Run_Service();
  	//Initialize sensor

	atService_I2C.check_In();
	bool beginning_Result =  sgp30.begin();
	atService_I2C.check_Out();

  	if (beginning_Result == false) {
		if(atApp_SGP30.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.println("No SGP30 Detected. Check connections.");
		}
		atApp_SGP30.Application_State = APP_STATE_PENDING;
		atApp_SGP30.Plugging = 0;
		atApp_SGP30.Application_State = APP_STATE_PENDING;
  	}
	else{
		atService_I2C.check_In();
		sgp30.initAirQuality();
		atService_I2C.check_Out();
		atApp_SGP30.Plugging = 1;
	}
	delay(100);
}  
/**
 * Restart function of SNM  app
 */
void  App_SGP30::App_SGP30_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_SGP30::App_SGP30_Execute()
{	
	atService_I2C.check_In();
	SGP30ERR reading_Error = sgp30.measureAirQuality();
	atService_I2C.check_Out();

	if(reading_Error != SGP30_SUCCESS)
	{
		atApp_SGP30.Application_State = APP_STATE_PENDING;
	}

	atApp_SGP30.CO2 = sgp30.CO2;
	atApp_SGP30.TVOC = sgp30.TVOC;
	atApp_SGP30.H2  = sgp30.H2;
	atApp_SGP30.Ethanol = sgp30.ethanol;

	if(atApp_SGP30.User_Mode == APP_USER_MODE_DEBUG)
	{
		Serial.printf("CO2: %d  PPM\n",(int)atApp_SGP30.CO2);
		Serial.printf("TVOC: %d  PPM\n",(int)atApp_SGP30.TVOC);
		Serial.printf("H2: %d  PPM\n",(int)atApp_SGP30.H2);
		Serial.printf("Ethanol: %d  PPM\n\n",(int)atApp_SGP30.Ethanol);
	}
    if(atApp_SGP30.User_Mode == APP_USER_MODE_DEBUG)
    {
		
    }   
}
void  App_SGP30::App_SGP30_Suspend(){}
void  App_SGP30::App_SGP30_Resume(){}	  
void  App_SGP30::App_SGP30_End(){}
void atApp_SGP30_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_SGP30.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif