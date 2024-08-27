/**
@file

*/
/*
  Application

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_CP_
#define _Application_atApp_CP_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "atApp_Wifi.h"
#include "atApp_OTA.h"
#include "atApp_DID.h"
#include "..\apps\app_data_module\atApp_SNM.h"
#include "..\apps\app_data_module\atApp_IDM.h"
#include "..\apps\app_data_module\atApp_HDM.h"
#include "..\apps\app_data_module\atApp_EMM.h"
#include "..\apps\atApp_MB_TCP_MA.h"


/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_CP;  
void atApp_CP_Task_Func(void *parameter);

///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_CP : public Application
{
public:
  	App_CP();
 	~App_CP();

protected:

private:
  	static void  App_CP_Pend();
	static void  App_CP_Start();
	static void  App_CP_Restart();
	static void  App_CP_Execute();
	static void  App_CP_Suspend();
	static void  App_CP_Resume();	  
	static void  App_CP_End();
	int count = 0;
} atApp_CP ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_CP::App_CP(/* args */)
{
  	_Pend_User 	     = *App_CP_Pend;
	_Start_User 	 = *App_CP_Start;
	_Restart_User 	 = *App_CP_Restart;
	_Execute_User 	 = *App_CP_Execute;
	_Suspend_User	 = *App_CP_Suspend;
	_Resume_User	 = *App_CP_Resume;
	_End_User	     = *App_CP_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"CP Application";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_CP::~App_CP()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_CP::App_CP_Pend()
{

}
/**
 * This start function will init some critical function 
 */
void  App_CP::App_CP_Start()
{
	// init atXYZ Service in the fist running time
	
}  
/**
 * Restart function of SNM  app
 */
void  App_CP::App_CP_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_CP::App_CP_Execute()
{	

	if( (atApp_Wifi.scanned_Wifi_SSIDs_Number > 0) && (WiFi.status() != WL_CONNECTED))
	{
		atApp_Wifi.request = WIFI_REQUEST_Connecting;
	}
	
	if(atApp_Wifi.status == WIFI_STATUS_Connected)
	{
		vTaskResume(Task_atApp_OTA);
		// vTaskResume(Task_atApp_DID);
		// vTaskResume(Task_atApp_SNM);
		// vTaskResume(Task_atApp_IDM);
		// vTaskResume(Task_atApp_EMM);
		// vTaskResume(Task_atApp_HDM);
		// vTaskResume(Task_atApp_MB_TCP_MA);
		atApp_Wifi.Debug_Exit();
	}
	//example for OTA Enable
	if(atApp_CP.count < 50 ) atApp_OTA.Enable = TRUE;
	else
	{
		atApp_OTA.Enable = FALSE;
	}
	atApp_CP.count++;

	// Serial.printf("count %d\n",atApp_CP.count);
    // if(atApp_CP.User_Mode == APP_USER_MODE_DEBUG)
    // {
	// 	Serial.printf("server state %d\n",atApp_OTA.Server_State);
    // }   
}
void  App_CP::App_CP_Suspend(){}
void  App_CP::App_CP_Resume(){}	  
void  App_CP::App_CP_End(){}
void atApp_CP_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_CP.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif