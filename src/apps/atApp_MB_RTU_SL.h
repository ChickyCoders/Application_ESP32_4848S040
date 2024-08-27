/**
@file
*/
/*
  Application_SNM.h 

  Library:: chickyPig_OP320_V1

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_MB_RTU_SL_
#define _Application_atApp_MB_RTU_SL_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/modbus_slave/atService_MB_RTU_SL.h"
#include "../services/modbus_slave/modbus_register/General_MB_Register.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_MB_RTU_SL;  
void atApp_MB_RTU_SL_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Application class is the application to manage the 
 */
class App_Modbus_Slave : public Application
{
public:
  	App_Modbus_Slave();
 	~App_Modbus_Slave();
protected:
private:
  	static void  App_Modbus_Slave_Pend();
	static void  App_Modbus_Slave_Start();
	static void  App_Modbus_Slave_Restart();
	static void  App_Modbus_Slave_Execute();
	static void  App_Modbus_Slave_Suspend();
	static void  App_Modbus_Slave_Resume();	  
	static void  App_Modbus_Slave_End();
} atApp_MB_RTU_SL ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_Modbus_Slave::App_Modbus_Slave(/* args */)
{
  	_Pend_User 	     = *App_Modbus_Slave_Pend;
	_Start_User 	 = *App_Modbus_Slave_Start;
	_Restart_User 	 = *App_Modbus_Slave_Restart;
	_Execute_User 	 = *App_Modbus_Slave_Execute;
	_Suspend_User	 = *App_Modbus_Slave_Suspend;
	_Resume_User	 = *App_Modbus_Slave_Resume;
	_End_User	     = *App_Modbus_Slave_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"Modbus_Slave Application";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_Modbus_Slave::~App_Modbus_Slave()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. 
 * In the debug mode, task will send information of application to terminal to start the application.
 */
void  App_Modbus_Slave::App_Modbus_Slave_Pend()
{
    atService_MB_RTU_SL.baudrate = 9600;
	atService_MB_RTU_SL.Slave_ID = 2;
	atService_MB_RTU_SL.Serial_config = SERIAL_8E1;
}
/**
 * This start function will init some critical function 
 */
void  App_Modbus_Slave::App_Modbus_Slave_Start()
{
	// init atXYZ Service in the fist running time
	atService_MB_RTU_SL.Run_Service();
	

  	// for( int count = GENERAL_REGISTER_RW_MODBUS_RTU_ID; count <= GENERAL_REGISTER_R_HUMIDITY; count++)
  	// {
	// 	atService_MB_RTU_SL.addHreg(count,count);
	// }

     

  	// for( int count = SMM_REGISTER_RW_SHT30_SENSOR_STATE; count <= SNM_REGISTER_R_MIN_ETHANOL; count++)
	// {
    // 	atService_MB_RTU_SL.addHreg(count,count);
    // }
}  
/**
 * Restart function of Modbus_Slave  app
 */
void  App_Modbus_Slave::App_Modbus_Slave_Restart()
{

}
/**
 * Execute fuction of Modbus_Slave app
 */
void  App_Modbus_Slave::App_Modbus_Slave_Execute()
{	
	atService_MB_RTU_SL.Run_Service();
    if(atApp_MB_RTU_SL.User_Mode == APP_USER_MODE_DEBUG)
    {
		
    }   
}
void  App_Modbus_Slave::App_Modbus_Slave_Suspend(){}
void  App_Modbus_Slave::App_Modbus_Slave_Resume(){}	  
void  App_Modbus_Slave::App_Modbus_Slave_End(){}
void atApp_MB_RTU_SL_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_MB_RTU_SL.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1/ portTICK_PERIOD_MS);
  }
}
#endif