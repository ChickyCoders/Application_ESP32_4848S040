/**
@file

*/
/*
  Application example t

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_HDM_
#define _Application_atApp_HDM_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "..\App.h"
#include "..\src\services\modbus_master\atService_MB_TCP_MA.h"
#include "..\src\obj\atObj_HDMs_Data.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_HDM;  
void atApp_HDM_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_HDM : public Application
{
public:
  App_HDM();
 	~App_HDM();
  uint8_t number_of_try_to_connect = 3;

protected:
  uint8_t buffer;
  uint8_t number_device;
private:
  static void  App_HDM_Pend();
	static void  App_HDM_Start();
	static void  App_HDM_Restart();
	static void  App_HDM_Execute();
	static void  App_HDM_Suspend();
	static void  App_HDM_Resume();	  
	static void  App_HDM_End();
} atApp_HDM ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_HDM::App_HDM(/* args */)
{
  	_Pend_User 	     = *App_HDM_Pend;
	_Start_User 	 = *App_HDM_Start;
	_Restart_User 	 = *App_HDM_Restart;
	_Execute_User 	 = *App_HDM_Execute;
	_Suspend_User	 = *App_HDM_Suspend;
	_Resume_User	 = *App_HDM_Resume;
	_End_User	     = *App_HDM_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"HDM Application";
	// change the ID of HDM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_HDM::~App_HDM()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_HDM::App_HDM_Pend()
{
    atService_MB_TCP_MA.Run_Service();
}
/**
 * This start function will init some critical function 
 */
void  App_HDM::App_HDM_Start()
{
	// init atXYZ Service in the fist running time
	
}  
/**
 * Restart function of HDM  app
 */
void  App_HDM::App_HDM_Restart()
{

}
/**
 * Execute fuction of HDM app
 */
void  App_HDM::App_HDM_Execute()
{	
  if(atObject_HDMs_Data.HDM_number >= 1)
  {
    for( atApp_HDM.number_device = 1; atApp_HDM.number_device <= atObject_HDMs_Data.HDM_number;
                                                                    atApp_HDM.number_device++ )
    {	
      IPAddress IP_module( 	atObject_HDMs_Data.HDM[atApp_HDM.number_device].IP[0], 
                         	  atObject_HDMs_Data.HDM[atApp_HDM.number_device].IP[1],
                         	  atObject_HDMs_Data.HDM[atApp_HDM.number_device].IP[2],
		  					            atObject_HDMs_Data.HDM[atApp_HDM.number_device].IP[3]);         
      // try to connect slave device
      for( uint8_t try_connect = 1; try_connect <= atApp_HDM.number_of_try_to_connect; try_connect++)
      {     
        if(atService_MB_TCP_MA.isConnected(IP_module) == false)
		{           
            atService_MB_TCP_MA.check_In();
            atService_MB_TCP_MA.connect(IP_module);   
            atService_MB_TCP_MA.check_Out();
            atApp_HDM.buffer++;    
        }
        else
        {
            for( uint8_t try_read = 0; try_read <= 2; try_read++)
            {
                atService_MB_TCP_MA.check_In();
                // Write DID for slave
                atService_MB_TCP_MA.writeHreg(IP_module, GENERAL_REGISTER_RW_DEVICE_ID, atApp_HDM.number_device);
                
                //read data
                atService_MB_TCP_MA.readCoil(IP_module,HDM_REGISTER_RW_MODE_OPERATION,
                                           &atObject_HDMs_Data.HDM[atApp_HDM.number_device].operation_mode_old);
                atService_MB_TCP_MA.readHreg(IP_module, HDM_REGISTER_RW_LOW_LIMIT_TEMPERATURE,
                                             &atObject_HDMs_Data.HDM[atApp_HDM.number_device].low_limit_temperature_old);
                atService_MB_TCP_MA.readHreg(IP_module, HDM_REGISTER_RW_HIGH_LIMIT_TEMPERATURE,
                                             &atObject_HDMs_Data.HDM[atApp_HDM.number_device].high_limit_temperature_old);
                atService_MB_TCP_MA.readHreg(IP_module, HDM_REGISTER_RW_POWER,
                                             &atObject_HDMs_Data.HDM[atApp_HDM.number_device].power_old);
                atService_MB_TCP_MA.readHreg(IP_module, HDM_REGISTER_RW_LOW_LIMIT_POWER,
                                             &atObject_HDMs_Data.HDM[atApp_HDM.number_device].low_limit_power_old);  
                atService_MB_TCP_MA.readHreg(IP_module, HDM_REGISTER_RW_HIGH_LIMIT_POWER,
                                             &atObject_HDMs_Data.HDM[atApp_HDM.number_device].high_limit_power_old); 
                atService_MB_TCP_MA.readIreg(IP_module, HDM_REGISTER_R_TEMPERATURE,
                                             &atObject_HDMs_Data.HDM[atApp_HDM.number_device].temperature); 
                
                // Write operation mode for HDM
                if(atObject_HDMs_Data.HDM[atApp_HDM.number_device].operation_mode != 
                    atObject_HDMs_Data.HDM[atApp_HDM.number_device].operation_mode_old)
                {
                  atService_MB_TCP_MA.writeCoil(IP_module,HDM_REGISTER_RW_MODE_OPERATION,
                                                atObject_HDMs_Data.HDM[atApp_HDM.number_device].operation_mode);
                
                }
                // Write low limit temperature
                if(atObject_HDMs_Data.HDM[atApp_HDM.number_device].low_limit_temperature != 
                    atObject_HDMs_Data.HDM[atApp_HDM.number_device].low_limit_temperature_old)
                {
                  atService_MB_TCP_MA.writeHreg(IP_module, HDM_REGISTER_RW_LOW_LIMIT_TEMPERATURE,
                                                atObject_HDMs_Data.HDM[atApp_HDM.number_device].low_limit_temperature);
                }
                // Write high limit temperature
                if(atObject_HDMs_Data.HDM[atApp_HDM.number_device].high_limit_temperature != 
                    atObject_HDMs_Data.HDM[atApp_HDM.number_device].high_limit_temperature_old)
                {
                  atService_MB_TCP_MA.writeHreg(IP_module, HDM_REGISTER_RW_HIGH_LIMIT_TEMPERATURE,
                                                atObject_HDMs_Data.HDM[atApp_HDM.number_device].high_limit_temperature);
                }
                // Write low power
                if(atObject_HDMs_Data.HDM[atApp_HDM.number_device].power != 
                    atObject_HDMs_Data.HDM[atApp_HDM.number_device].power_old)
                {
                  atService_MB_TCP_MA.writeHreg(IP_module, HDM_REGISTER_RW_POWER,
                                                atObject_HDMs_Data.HDM[atApp_HDM.number_device].power);
                }      
                // Write low limit power
                if(atObject_HDMs_Data.HDM[atApp_HDM.number_device].low_limit_power != 
                    atObject_HDMs_Data.HDM[atApp_HDM.number_device].low_limit_power_old)
                {       
                  atService_MB_TCP_MA.writeHreg(IP_module, HDM_REGISTER_RW_LOW_LIMIT_POWER,
                                                atObject_HDMs_Data.HDM[atApp_HDM.number_device].low_limit_power);
                }
                // Write high limit power
                if(atObject_HDMs_Data.HDM[atApp_HDM.number_device].high_limit_power != 
                    atObject_HDMs_Data.HDM[atApp_HDM.number_device].high_limit_power_old)
                { 
                  atService_MB_TCP_MA.writeHreg(IP_module, HDM_REGISTER_RW_HIGH_LIMIT_POWER,
                                                atObject_HDMs_Data.HDM[atApp_HDM.number_device].high_limit_power);
                }

                atService_MB_TCP_MA.check_Out();
            }
            atApp_HDM.buffer = 0;
        }                                                                                                                   
      }
    if(atApp_HDM.buffer >= 1)
    {
      atObject_HDMs_Data.HDM[atApp_HDM.number_device].Status_of_HDMs = Offline;
      atObject_HDMs_Data.HDM[atApp_HDM.number_device].operation_mode = 0;
      atObject_HDMs_Data.HDM[atApp_HDM.number_device].low_limit_power = 0;
      atObject_HDMs_Data.HDM[atApp_HDM.number_device].high_limit_power = 0;
      atObject_HDMs_Data.HDM[atApp_HDM.number_device].power = 0;
      atObject_HDMs_Data.HDM[atApp_HDM.number_device].low_limit_temperature = 0;
      atObject_HDMs_Data.HDM[atApp_HDM.number_device].high_limit_temperature = 0;
      atObject_HDMs_Data.HDM[atApp_HDM.number_device].temperature = 0;
    //   atObject_HDMs_Data.HDM[atApp_HDM.number_device].IP[0] = 0; 
    //   atObject_HDMs_Data.HDM[atApp_HDM.number_device].IP[1] = 0;    
    //   atObject_HDMs_Data.HDM[atApp_HDM.number_device].IP[2] = 0;    
    //   atObject_HDMs_Data.HDM[atApp_HDM.number_device].IP[3] = 0;     
    //   atObject_HDMs_Data.HDM_number = atObject_HDMs_Data.HDM_number - 1 ;  
    }
    if(atApp_HDM.User_Mode == APP_USER_MODE_DEBUG)
    {
        Serial.printf("   HDM %d ",atApp_HDM.number_device);
        Serial.print("\n");
        Serial.print(atObject_HDMs_Data.HDM[atApp_HDM.number_device].operation_mode_old);
        Serial.print("\n");
        Serial.print(atObject_HDMs_Data.HDM[atApp_HDM.number_device].low_limit_power_old);
        Serial.print("\n");
        Serial.print(atObject_HDMs_Data.HDM[atApp_HDM.number_device].high_limit_power_old);
        Serial.print("\n");
        Serial.print(atObject_HDMs_Data.HDM[atApp_HDM.number_device].power_old);
        Serial.print("\n");
        Serial.print(atObject_HDMs_Data.HDM[atApp_HDM.number_device].low_limit_temperature_old);
        Serial.print("\n");
        Serial.print(atObject_HDMs_Data.HDM[atApp_HDM.number_device].high_limit_temperature_old);
        Serial.print("\n");
        Serial.print(atObject_HDMs_Data.HDM[atApp_HDM.number_device].temperature);
        Serial.print("\n");
    }
  }
}
}
void  App_HDM::App_HDM_Suspend(){}
void  App_HDM::App_HDM_Resume(){}	  
void  App_HDM::App_HDM_End(){}
void atApp_HDM_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_HDM.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif