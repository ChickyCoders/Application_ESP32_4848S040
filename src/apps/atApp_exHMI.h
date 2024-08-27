/**
@file

*/
/*
  Application

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_exHMI_
#define _Application_atApp_exHMI_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/exHMI/atService_exHMI_atPig_IDM.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_exHMI;  
void atApp_exHMI_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_exHMI : public Application
{
public:
  	App_exHMI();
 	~App_exHMI();
protected:
private:
  	static void  App_exHMI_Pend();
	static void  App_exHMI_Start();
	static void  App_exHMI_Restart();
	static void  App_exHMI_Execute();
	static void  App_exHMI_Suspend();
	static void  App_exHMI_Resume();	  
	static void  App_exHMI_End();
} atApp_exHMI ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_exHMI::App_exHMI(/* args */)
{
  	_Pend_User 	     = *App_exHMI_Pend;
	_Start_User 	 = *App_exHMI_Start;
	_Restart_User 	 = *App_exHMI_Restart;
	_Execute_User 	 = *App_exHMI_Execute;
	_Suspend_User	 = *App_exHMI_Suspend;
	_Resume_User	 = *App_exHMI_Resume;
	_End_User	     = *App_exHMI_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"exHMI Application";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_exHMI::~App_exHMI()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_exHMI::App_exHMI_Pend()
{
    atService_XYZ.Debug();
}
/**
 * This start function will init some critical function 
 */
void  App_exHMI::App_exHMI_Start()
{
	// init atXYZ Service in the fist running time
	atService_XYZ.Run_Service();
}  
/**
 * Restart function of SNM  app
 */
void  App_exHMI::App_exHMI_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_exHMI::App_exHMI_Execute()
{	
	atService_XYZ.Run_Service();
    if(atApp_exHMI.User_Mode == APP_USER_MODE_DEBUG)
    {
		
    }   
}
void  App_exHMI::App_exHMI_Suspend(){}
void  App_exHMI::App_exHMI_Resume(){}	  
void  App_exHMI::App_exHMI_End(){}
void atApp_exHMI_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_exHMI.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif