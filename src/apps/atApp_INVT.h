/**
@file
*/
/*
  Application_INVT.h - Arduino library


  This version is

  Library:: 
  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_INVT_
#define _Application_atApp_INVT_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/INVT_GD200/atService_INVT_GD200.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_INVT;  
void atApp_INVT_Task_Func(void *parameter);
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Application class is the application to manage the 
 */
class App_INVT: public Application
{
public:
  App_INVT();
  ~App_INVT();
  float Frequency = 25.25 ;// Unit (Hz)
  bool direction = FORWARD;
protected:
private:
  static void  App_INVT_Pend();
	static void  App_INVT_Start();
	static void  App_INVT_Restart();
	static void  App_INVT_Execute();
	static void  App_INVT_Suspend();
	static void  App_INVT_Resume();	  
	static void  App_INVT_End();
} atApp_INVT ;
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_INVT::App_INVT()
{
	_Pend_User 	    = *App_INVT_Pend;
	_Start_User 	  = *App_INVT_Start;
	_Restart_User   = *App_INVT_Restart;
	_Execute_User 	= *App_INVT_Execute;
	_Suspend_User	  = *App_INVT_Suspend;
	_Resume_User	  = *App_INVT_Resume;
	_End_User	      = *App_INVT_End;
  	// change the ID of application
	atApp_INVT.ID_Application = 2;
	// change the application name
	atApp_INVT.Name_Application = (char*)"INVT GD200A";
  // change the ID
  atService_INVT_GD200.ID_Modbus = 3;
}
/**
 * 
 * This function will be automaticaly called when the object of class is delete
 */

App_INVT::~App_INVT()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. 
 * In the debug mode, task will send information of application to terminal to start the application.
 */
void  App_INVT::App_INVT_Pend()
{
	
}
/**
 * This start function will init some critical function 
 */
void  App_INVT::App_INVT_Start(){
  atService_INVT_GD200.Debug();
  atService_INVT_GD200.Run_Service();
  
  atService_INVT_GD200.ID_Modbus = 3;
  atService_INVT_GD200.Frequency = 25.5;
} 

/**
 * Restart function of inverter app
 */
void  App_INVT::App_INVT_Restart()
{
  
}
/**
 * Execute fuction of INVT app
 */
void App_INVT::App_INVT_Execute()
{
  atService_INVT_GD200.Frequency = 25.5;
  atService_INVT_GD200.Run_Service();
}
void  App_INVT::App_INVT_Suspend(){}
void  App_INVT::App_INVT_Resume(){}	  
void  App_INVT::App_INVT_End(){}

void atApp_INVT_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_INVT.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif
