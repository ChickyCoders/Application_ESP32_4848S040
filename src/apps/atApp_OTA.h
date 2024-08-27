/**
@file

*/
/*
  Application example t

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_OTA_
#define _Application_atApp_OTA_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_XYZ.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
/* _____DEFINITIONS__________________________________________________________ */
enum OTA_Enable
{
	FALSE,
	TRUE,
	OFF = 0,
	ON
};
/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_OTA;  
void atApp_OTA_Task_Func(void *parameter);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_OTA : public Application
{
public:
  	App_OTA();
 	~App_OTA();
	bool Enable = FALSE;
	bool Server_State = OFF;
protected:
private:
  	static void  App_OTA_Pend();
	static void  App_OTA_Start();
	static void  App_OTA_Restart();
	static void  App_OTA_Execute();
	static void  App_OTA_Suspend();
	static void  App_OTA_Resume();	  
	static void  App_OTA_End();

} atApp_OTA ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_OTA::App_OTA(/* args */)
{
  	_Pend_User 	     = *App_OTA_Pend;
	_Start_User 	 = *App_OTA_Start;
	_Restart_User 	 = *App_OTA_Restart;
	_Execute_User 	 = *App_OTA_Execute;
	_Suspend_User	 = *App_OTA_Suspend;
	_Resume_User	 = *App_OTA_Resume;
	_End_User	     = *App_OTA_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"OTA Application";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_OTA::~App_OTA()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_OTA::App_OTA_Pend()
{
    // atService_XYZ.Debug();
}
/**
 * This start function will init some critical function 
 */
void  App_OTA::App_OTA_Start()
{
	// init atXYZ Service in the fist running time
	// atService_XYZ.Run_Service();
	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP32.");
  	});
	AsyncElegantOTA.begin(&server);    // Start ElegantOTA
	  
}  
/**
 * Restart function of SNM  app
 */
void  App_OTA::App_OTA_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_OTA::App_OTA_Execute()
{	
	// atService_XYZ.Run_Service();
	if(atApp_OTA.Enable)
	{
		if(!atApp_OTA.Server_State)
		{
			atApp_OTA.Server_State = ON;
			server.begin();
			if(atApp_OTA.User_Mode == APP_USER_MODE_DEBUG)
			{	
				Serial.println("HTTP server started");
			} 
		}
	}
	else 
	{
		if(atApp_OTA.Server_State)
		{			
			atApp_OTA.Server_State = OFF;
			server.end();
		}
	}
    if(atApp_OTA.User_Mode == APP_USER_MODE_DEBUG)
    {
		
    }   
}
void  App_OTA::App_OTA_Suspend(){}
void  App_OTA::App_OTA_Resume(){}	  
void  App_OTA::App_OTA_End(){}
void atApp_OTA_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_OTA.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif