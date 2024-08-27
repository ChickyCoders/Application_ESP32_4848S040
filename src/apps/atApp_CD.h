/**
@file
*/
/*
  Application

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_CD_
#define _Application_atApp_CD_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/PCF8575/atService_PCF8575.h"
/* _____DEFINITIONS__________________________________________________________ */
#define RELAY_PIN               PCF8575_PIN_P15
#define RELAY_FEEDBACK_PIN      PCF8575_PIN_P16
#define CONTACTOR_FEEDBACK_PIN  PCF8575_PIN_P14
#define APTOMAT_FEEDBACK_PIN     27// esp32 pin
#define LED_PIN                 PCF8575_PIN_P17
/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_CD;  
void atApp_CD_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Application class is the application to manage the 
 */
class App_CD : public Application
{
public:
  App_CD();
 	~App_CD();
   
  bool relay = 1;
  bool Led = 0;
  bool relay_feedback = 0;
  bool contactor_feedback = 0;
  bool aptomat_feedback = 0;
  uint16_t port = 0;

protected:

private:
  static void  App_CD_Pend();
	static void  App_CD_Start();
	static void  App_CD_Restart();
	static void  App_CD_Execute();
	static void  App_CD_Suspend();
	static void  App_CD_Resume();	  
	static void  App_CD_End();

} atApp_CD ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_CD::App_CD(/* args */)
{
  	_Pend_User 	     = *App_CD_Pend;
	_Start_User 	 = *App_CD_Start;
	_Restart_User 	 = *App_CD_Restart;
	_Execute_User 	 = *App_CD_Execute;
	_Suspend_User	 = *App_CD_Suspend;
	_Resume_User	 = *App_CD_Resume;
	_End_User	     = *App_CD_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"PCF8575 Application";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_CD::~App_CD()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. 
 * In the debug mode, task will send information of application to terminal to start the application.
 */
void  App_CD::App_CD_Pend()
{
  // atService_PCF8575.Debug();
}
/**
 * This start function will init some critical function 
 */
void  App_CD::App_CD_Start()
{
  atService_PCF8575.Run_Service();
  pinMode(APTOMAT_FEEDBACK_PIN,INPUT);
  atService_PCF8575.Pin_Modes[LED_PIN] = MODE_PCF8575_Output;
  atService_PCF8575.Pin_Modes[RELAY_PIN] = MODE_PCF8575_Output;
  // init contactor driver
  atApp_CD.relay = 1;
  atService_PCF8575.Pin_Vals[RELAY_PIN] =  atApp_CD.relay;
  atApp_CD.relay_feedback = atService_PCF8575.Pin_Vals[RELAY_FEEDBACK_PIN];
  atApp_CD.contactor_feedback = atService_PCF8575.Pin_Vals[CONTACTOR_FEEDBACK_PIN];
  atApp_CD.aptomat_feedback = digitalRead(APTOMAT_FEEDBACK_PIN);
}  
/**
 * Restart function of SNM  app
 */
void  App_CD::App_CD_Restart()
{
    
}
/**
 * Execute fuction of SNM app
 */
void  App_CD::App_CD_Execute()
{	
  
  if (atApp_CD.Led == 1){
    atApp_CD.Led = 0; 
    atService_PCF8575.Pin_Vals[LED_PIN] = VAL_PCF8575_High;
  }
  else{
    atApp_CD.Led = 1;
    atService_PCF8575.Pin_Vals[LED_PIN] = VAL_PCF8575_Low;
  }

  atService_PCF8575.Pin_Vals[RELAY_PIN] = atApp_CD.relay ;
  atApp_CD.relay_feedback = atService_PCF8575.Pin_Vals[RELAY_FEEDBACK_PIN];
  atApp_CD.contactor_feedback = atService_PCF8575.Pin_Vals[CONTACTOR_FEEDBACK_PIN];
  atApp_CD.aptomat_feedback = digitalRead(APTOMAT_FEEDBACK_PIN);

  atService_PCF8575.Run_Service();
  if(atApp_CD.User_Mode == APP_USER_MODE_DEBUG)
  {
    Serial.printf("Relay is %d\n",              atApp_CD.relay);
    Serial.printf("Relay feedback : %d\n",      atApp_CD.relay_feedback);
    Serial.printf("Contactor feedback : %d\n",  atApp_CD.contactor_feedback);
    Serial.printf("Aptomat feedback : %d\n",    atApp_CD.aptomat_feedback);
  } 
}
void  App_CD::App_CD_Suspend(){}
void  App_CD::App_CD_Resume(){}	  
void  App_CD::App_CD_End(){}
void atApp_CD_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_CD.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(2000/ portTICK_PERIOD_MS);
  }
}
#endif