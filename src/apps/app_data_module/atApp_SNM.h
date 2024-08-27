/**
@file

*/
/*
  Application example t

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_SNM_
#define _Application_atApp_SNM_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "..\\App.h"
#include "..\src\services\modbus_master\atService_MB_TCP_MA.h"
#include "..\src\obj\atObj_SNMs_Data.h"

/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_SNM;  
void atApp_SNM_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_SNM : public Application
{
public:
  App_SNM();
 	~App_SNM();
  uint8_t number_of_try_to_connect = 3;
protected:
  uint8_t buffer;
  uint8_t number_device;
private:
  static void  App_SNM_Pend();
	static void  App_SNM_Start();
	static void  App_SNM_Restart();
	static void  App_SNM_Execute();
	static void  App_SNM_Suspend();
	static void  App_SNM_Resume();	  
	static void  App_SNM_End();
} atApp_SNM ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_SNM::App_SNM(/* args */)
{
  	_Pend_User 	     = *App_SNM_Pend;
	_Start_User 	 = *App_SNM_Start;
	_Restart_User 	 = *App_SNM_Restart;
	_Execute_User 	 = *App_SNM_Execute;
	_Suspend_User	 = *App_SNM_Suspend;
	_Resume_User	 = *App_SNM_Resume;
	_End_User	     = *App_SNM_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"SNM Application";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_SNM::~App_SNM()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_SNM::App_SNM_Pend()
{
    
}
/**
 * This start function will init some critical function 
 */
void  App_SNM::App_SNM_Start()
{
	// init atXYZ Service in the fist running time
  atService_MB_TCP_MA.Run_Service();
}  
/**
 * Restart function of SNM  app
 */
void  App_SNM::App_SNM_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_SNM::App_SNM_Execute()
{	
  if(atObject_SNMs_Data.SNM_number >= 1)
  {
    if(atApp_SNM.User_Mode == APP_USER_MODE_DEBUG)
    {
      Serial.println(" SNM number | Temperature (C) |  Humidity  |  CO2  |  H2  |  TVOC  |  Ethanol  ");
    }
    for( atApp_SNM.number_device = 1; atApp_SNM.number_device <= atObject_SNMs_Data.SNM_number;
                                                                    atApp_SNM.number_device++ )
    {	
      IPAddress IP_module( 	atObject_SNMs_Data.SNM[atApp_SNM.number_device].IP[0], 
                         	  atObject_SNMs_Data.SNM[atApp_SNM.number_device].IP[1],
                         	  atObject_SNMs_Data.SNM[atApp_SNM.number_device].IP[2],
		  					            atObject_SNMs_Data.SNM[atApp_SNM.number_device].IP[3]);         
      // try to connect slave device
      for( uint8_t try_connect = 1; try_connect <= atApp_SNM.number_of_try_to_connect; try_connect++)
      {     
        if(atService_MB_TCP_MA.isConnected(IP_module) == false)
		    {    
          atService_MB_TCP_MA.check_In();
          atService_MB_TCP_MA.connect(IP_module);
          atService_MB_TCP_MA.check_Out();
          atApp_SNM.buffer++;
        }
        else
        {
          atService_MB_TCP_MA.check_In();
          atService_MB_TCP_MA.writeHreg(IP_module, GENERAL_REGISTER_RW_DEVICE_ID, atApp_SNM.number_device);
          atService_MB_TCP_MA.readIreg(IP_module,SNM_REGISTER_R_TEMPERATURE_REAL_TIME, 
                          &atObject_SNMs_Data.SNM[atApp_SNM.number_device].Temperature);
          atService_MB_TCP_MA.readIreg(IP_module, SNM_REGISTER_R_HUMIDITY_REAL_TIME,
                          &atObject_SNMs_Data.SNM[atApp_SNM.number_device].Humidity);
          atService_MB_TCP_MA.readIreg(IP_module, SNM_REGISTER_R_CO2_REAL_TIME,
                          &atObject_SNMs_Data.SNM[atApp_SNM.number_device].CO2);
          atService_MB_TCP_MA.readIreg(IP_module, SNM_REGISTER_R_H2_REAL_TIME,
                          &atObject_SNMs_Data.SNM[atApp_SNM.number_device].H2);
          atService_MB_TCP_MA.readIreg(IP_module, SNM_REGISTER_R_TVOC_REAL_TIME,
                          &atObject_SNMs_Data.SNM[atApp_SNM.number_device].TVOC);  
          atService_MB_TCP_MA.readIreg(IP_module, SNM_REGISTER_R_ETHANOL_REAL_TIME,
                          &atObject_SNMs_Data.SNM[atApp_SNM.number_device].Ethanol); 
          atService_MB_TCP_MA.check_Out();
    
          atObject_SNMs_Data.SNM[atApp_SNM.number_device].Status_of_SNMs = Online;
          atApp_SNM.buffer = 0;
        }                                                                                                                   
      }
      
    if(atApp_SNM.buffer >= 1)
    {
      atObject_SNMs_Data.SNM[atApp_SNM.number_device].Status_of_SNMs = Offline;
      atObject_SNMs_Data.SNM[atApp_SNM.number_device].Temperature = 0;
      atObject_SNMs_Data.SNM[atApp_SNM.number_device].Humidity = 0;
      atObject_SNMs_Data.SNM[atApp_SNM.number_device].CO2 = 0;
      atObject_SNMs_Data.SNM[atApp_SNM.number_device].H2 = 0;
      atObject_SNMs_Data.SNM[atApp_SNM.number_device].TVOC = 0;
      atObject_SNMs_Data.SNM[atApp_SNM.number_device].Ethanol = 0;
      // atObject_SNMs_Data.SNM[atApp_SNM.number_device].IP[0] = 0; 
      // atObject_SNMs_Data.SNM[atApp_SNM.number_device].IP[1] = 0;    
      // atObject_SNMs_Data.SNM[atApp_SNM.number_device].IP[2] = 0;    
      // atObject_SNMs_Data.SNM[atApp_SNM.number_device].IP[3] = 0;     
      // atObject_SNMs_Data.SNM_number = atObject_SNMs_Data.SNM_number - 1 ;  
    }
    if(atApp_SNM.User_Mode == APP_USER_MODE_DEBUG)
    { 
      Serial.printf("   SNM %d ",atApp_SNM.number_device);
      Serial.print(" |       ");
			Serial.print(atObject_SNMs_Data.SNM[atApp_SNM.number_device].Temperature);
      Serial.print("       |     ");
			Serial.print(atObject_SNMs_Data.SNM[atApp_SNM.number_device].Humidity);
      Serial.print("    |   ");
			Serial.print(atObject_SNMs_Data.SNM[atApp_SNM.number_device].CO2);
      Serial.print("   |  ");
			Serial.print(atObject_SNMs_Data.SNM[atApp_SNM.number_device].H2);
      Serial.print("  |   ");
			Serial.print(atObject_SNMs_Data.SNM[atApp_SNM.number_device].TVOC);
      Serial.print("   |    ");
			Serial.print(atObject_SNMs_Data.SNM[atApp_SNM.number_device].Ethanol);
      Serial.print("\n");

      atObject_SNMs_Data.SNM[atApp_SNM.number_device].Temperature = 0;
      atObject_SNMs_Data.SNM[atApp_SNM.number_device].Humidity = 0;
      atObject_SNMs_Data.SNM[atApp_SNM.number_device].CO2 = 0;
      atObject_SNMs_Data.SNM[atApp_SNM.number_device].H2 = 0;
      atObject_SNMs_Data.SNM[atApp_SNM.number_device].TVOC = 0;
      atObject_SNMs_Data.SNM[atApp_SNM.number_device].Ethanol = 0;
    }
  }
}
}
void  App_SNM::App_SNM_Suspend(){}
void  App_SNM::App_SNM_Resume(){}	  
void  App_SNM::App_SNM_End(){}
void atApp_SNM_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_SNM.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif