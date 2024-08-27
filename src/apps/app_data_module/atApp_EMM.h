/**
@file

*/
/*
  Application example t

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_EMM_
#define _Application_atApp_EMM_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "..\App.h"
#include "..\src\services\modbus_master\atService_MB_TCP_MA.h"
#include "..\src\obj\atObj_EMMs_Data.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_EMM;  
void atApp_EMM_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_EMM : public Application
{
public:
  App_EMM();
 	~App_EMM();
  uint8_t number_of_try_to_connect = 3;
protected:
  uint8_t buffer;
  uint8_t number_device;
private:
  static void  App_EMM_Pend();
	static void  App_EMM_Start();
	static void  App_EMM_Restart();
	static void  App_EMM_Execute();
	static void  App_EMM_Suspend();
	static void  App_EMM_Resume();	  
	static void  App_EMM_End();
} atApp_EMM ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_EMM::App_EMM(/* args */)
{
  	_Pend_User 	     = *App_EMM_Pend;
	_Start_User 	 = *App_EMM_Start;
	_Restart_User 	 = *App_EMM_Restart;
	_Execute_User 	 = *App_EMM_Execute;
	_Suspend_User	 = *App_EMM_Suspend;
	_Resume_User	 = *App_EMM_Resume;
	_End_User	     = *App_EMM_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"EMM Application";
	// change the ID of EMM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_EMM::~App_EMM()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_EMM::App_EMM_Pend()
{
}
/**
 * This start function will init some critical function 
 */
void  App_EMM::App_EMM_Start()
{
	// init atXYZ Service in the fist running time
	atService_MB_TCP_MA.Run_Service();

}  
/**
 * Restart function of EMM  app
 */
void  App_EMM::App_EMM_Restart()
{

}
/**
 * Execute fuction of EMM app
 */
void  App_EMM::App_EMM_Execute()
{	
  if(atObject_EMMs_Data.EMM_number >= 1)
  {

    for( atApp_EMM.number_device = 1; atApp_EMM.number_device <= atObject_EMMs_Data.EMM_number;
                                                                    atApp_EMM.number_device++ )
    {	
      IPAddress IP_module( 	atObject_EMMs_Data.EMM[atApp_EMM.number_device].IP[0], 
                         	  atObject_EMMs_Data.EMM[atApp_EMM.number_device].IP[1],
                         	  atObject_EMMs_Data.EMM[atApp_EMM.number_device].IP[2],
		  					            atObject_EMMs_Data.EMM[atApp_EMM.number_device].IP[3]);         
      // try to connect slave device
      for( uint8_t try_connect = 1; try_connect <= atApp_EMM.number_of_try_to_connect; try_connect++)
      {     
        if(atService_MB_TCP_MA.isConnected(IP_module) == false)
		{    
            atService_MB_TCP_MA.check_In();  
            atService_MB_TCP_MA.connect(IP_module); 
            atService_MB_TCP_MA.check_Out();
            atApp_EMM.buffer++;
        }
        else
        {
            atService_MB_TCP_MA.check_In();
            atService_MB_TCP_MA.writeHreg(IP_module, GENERAL_REGISTER_RW_DEVICE_ID, atApp_EMM.number_device);
            
            // read data
            atService_MB_TCP_MA.readHreg(IP_module,EMM_REGISTER_RW_ALERT, 
                                        &atObject_EMMs_Data.EMM[atApp_EMM.number_device].Alert_old);
            atService_MB_TCP_MA.readIreg(IP_module, EMM_REGISTER_R_VOLTAGE_PHASE_A,
                                        &atObject_EMMs_Data.EMM[atApp_EMM.number_device].voltage_phase_A);
            atService_MB_TCP_MA.readIreg(IP_module, EMM_REGISTER_R_VOLTAGE_PHASE_B,
                                        &atObject_EMMs_Data.EMM[atApp_EMM.number_device].voltage_phase_B);
            atService_MB_TCP_MA.readIreg(IP_module, EMM_REGISTER_R_VOLTAGE_PHASE_C,
                                        &atObject_EMMs_Data.EMM[atApp_EMM.number_device].voltage_phase_C);
            atService_MB_TCP_MA.readIreg(IP_module, EMM_REGISTER_R_CURRENT_PHASE_A,
                                        &atObject_EMMs_Data.EMM[atApp_EMM.number_device].current_phase_A);  
            atService_MB_TCP_MA.readIreg(IP_module, EMM_REGISTER_R_CURRENT_PHASE_B,
                                        &atObject_EMMs_Data.EMM[atApp_EMM.number_device].current_phase_B); 
            atService_MB_TCP_MA.readIreg(IP_module, EMM_REGISTER_R_CURRENT_PHASE_C,
                                        &atObject_EMMs_Data.EMM[atApp_EMM.number_device].current_phase_C); 
            atService_MB_TCP_MA.readIreg(IP_module, EMM_REGISTER_R_ACTIVE_POWER,
                                        &atObject_EMMs_Data.EMM[atApp_EMM.number_device].active_power);  
            atService_MB_TCP_MA.readIreg(IP_module, EMM_REGISTER_R_REACTIVE_POWER,
                                        &atObject_EMMs_Data.EMM[atApp_EMM.number_device].reactive_power); 
            atService_MB_TCP_MA.readIreg(IP_module, EMM_REGISTER_R_APPARENT_POWER,
                                        &atObject_EMMs_Data.EMM[atApp_EMM.number_device].apparent_power);
            atService_MB_TCP_MA.readIreg(IP_module, EMM_REGISTER_R_COSPHI,
                                        &atObject_EMMs_Data.EMM[atApp_EMM.number_device].cosfi);
            atService_MB_TCP_MA.readIreg(IP_module, EMM_REGISTER_R_FREQUENCY,
                                        &atObject_EMMs_Data.EMM[atApp_EMM.number_device].frequency);
            atService_MB_TCP_MA.readIsts(IP_module, EMM_REGISTER_RW_CONTROL_RELAY,
                                        &atObject_EMMs_Data.EMM[atApp_EMM.number_device].control_relay_old);
            atService_MB_TCP_MA.readIsts(IP_module, EMM_REGISTER_R_APTOMAT_FEEDBACK,
                                        &atObject_EMMs_Data.EMM[atApp_EMM.number_device].aptomat_feedback);
            atService_MB_TCP_MA.readIsts(IP_module, EMM_REGISTER_R_CONTACTOR_FEEDBACK,
                                        &atObject_EMMs_Data.EMM[atApp_EMM.number_device].contactor_feedback);
            atService_MB_TCP_MA.readIsts(IP_module, EMM_REGISTER_R_RELAY_FEEDBACK,
                                        &atObject_EMMs_Data.EMM[atApp_EMM.number_device].relay_feedback);   
            
            // control relay
            if( atObject_EMMs_Data.EMM[atApp_EMM.number_device].control_relay != 
                atObject_EMMs_Data.EMM[atApp_EMM.number_device].control_relay_old)
            {
              atService_MB_TCP_MA.writeCoil(IP_module, EMM_REGISTER_RW_CONTROL_RELAY, 
                                            atObject_EMMs_Data.EMM[atApp_EMM.number_device].control_relay);
            }
            // Write Alert
            if( atObject_EMMs_Data.EMM[atApp_EMM.number_device].Alert != 
                atObject_EMMs_Data.EMM[atApp_EMM.number_device].Alert_old)
            {
              atService_MB_TCP_MA.writeCoil(IP_module, EMM_REGISTER_RW_CONTROL_RELAY, 
                                            atObject_EMMs_Data.EMM[atApp_EMM.number_device].Alert);
            }

            atService_MB_TCP_MA.check_Out();    
            atApp_EMM.buffer = 0;
        }                                                                                                                   
    }
    if(atApp_EMM.buffer >= 1)
    {
      atObject_EMMs_Data.EMM[atApp_EMM.number_device].Status_of_EMMs = Offline;
      atObject_EMMs_Data.EMM[atApp_EMM.number_device].voltage_phase_A = 0;
      atObject_EMMs_Data.EMM[atApp_EMM.number_device].voltage_phase_B = 0;
      atObject_EMMs_Data.EMM[atApp_EMM.number_device].voltage_phase_C = 0;
      atObject_EMMs_Data.EMM[atApp_EMM.number_device].current_phase_A = 0;
      atObject_EMMs_Data.EMM[atApp_EMM.number_device].current_phase_B = 0;
      atObject_EMMs_Data.EMM[atApp_EMM.number_device].current_phase_C = 0;
      atObject_EMMs_Data.EMM[atApp_EMM.number_device].active_power = 0; 
      atObject_EMMs_Data.EMM[atApp_EMM.number_device].apparent_power = 0;    
      atObject_EMMs_Data.EMM[atApp_EMM.number_device].reactive_power = 0;    
      atObject_EMMs_Data.EMM[atApp_EMM.number_device].cosfi = 0;    
      atObject_EMMs_Data.EMM[atApp_EMM.number_device].frequency = 0; 
      atObject_EMMs_Data.EMM[atApp_EMM.number_device].relay_feedback = 0;
      atObject_EMMs_Data.EMM[atApp_EMM.number_device].aptomat_feedback = 0;
      atObject_EMMs_Data.EMM[atApp_EMM.number_device].contactor_feedback = 0;
      atObject_EMMs_Data.EMM_number = atObject_EMMs_Data.EMM_number - 1 ;  
    }
    if(atApp_EMM.User_Mode == APP_USER_MODE_DEBUG)
    {
        Serial.printf(" - Module EMM %d \n",atApp_EMM.number_device);
        Serial.printf("voltage_phase_A EMM %d:",atApp_EMM.number_device); 
	    Serial.print(atObject_EMMs_Data.EMM[atApp_EMM.number_device].voltage_phase_A);
        Serial.print("\n");
        Serial.printf("voltage_phase_B EMM %d:",atApp_EMM.number_device); 
	    Serial.print(atObject_EMMs_Data.EMM[atApp_EMM.number_device].voltage_phase_B);
        Serial.print("\n");
        Serial.printf("voltage_phase_C EMM %d:",atApp_EMM.number_device); 
	    Serial.print(atObject_EMMs_Data.EMM[atApp_EMM.number_device].voltage_phase_C);
        Serial.print("\n");
        Serial.printf("current_phase_A EMM %d:",atApp_EMM.number_device); 
	    Serial.print(atObject_EMMs_Data.EMM[atApp_EMM.number_device].current_phase_A);
        Serial.print("\n");
        Serial.printf("current_phase_B EMM %d:",atApp_EMM.number_device); 
	    Serial.print(atObject_EMMs_Data.EMM[atApp_EMM.number_device].current_phase_B);
        Serial.print("\n");
        Serial.printf("current_phase_C EMM %d:",atApp_EMM.number_device); 
	    Serial.print(atObject_EMMs_Data.EMM[atApp_EMM.number_device].current_phase_C);
        Serial.print("\n");
        Serial.printf("active_power EMM %d:",atApp_EMM.number_device); 
	    Serial.print(atObject_EMMs_Data.EMM[atApp_EMM.number_device].active_power);
        Serial.print("\n");
        Serial.printf("apparent_power EMM %d:",atApp_EMM.number_device); 
	    Serial.print(atObject_EMMs_Data.EMM[atApp_EMM.number_device].apparent_power);
        Serial.print("\n");
        Serial.printf("reactive_power EMM %d:",atApp_EMM.number_device); 
	    Serial.print(atObject_EMMs_Data.EMM[atApp_EMM.number_device].reactive_power);
        Serial.print("\n");
        Serial.printf("cosfi EMM %d:",atApp_EMM.number_device); 
	    Serial.print(atObject_EMMs_Data.EMM[atApp_EMM.number_device].cosfi);
        Serial.print("\n");
        Serial.printf("frequency EMM %d:",atApp_EMM.number_device); 
	    Serial.print(atObject_EMMs_Data.EMM[atApp_EMM.number_device].frequency);
        Serial.print("\n");
        Serial.printf("control relay EMM %d:",atApp_EMM.number_device); 
	    Serial.print(atObject_EMMs_Data.EMM[atApp_EMM.number_device].control_relay);
        Serial.print("\n");
        Serial.printf("relay_feedback EMM %d:",atApp_EMM.number_device); 
	    Serial.print(atObject_EMMs_Data.EMM[atApp_EMM.number_device].relay_feedback);
        Serial.print("\n");
        Serial.printf("aptomat_feedback EMM %d:",atApp_EMM.number_device); 
	    Serial.print(atObject_EMMs_Data.EMM[atApp_EMM.number_device].aptomat_feedback);
        Serial.print("\n");
        Serial.printf("contactor_feedback EMM %d:",atApp_EMM.number_device); 
	    Serial.print(atObject_EMMs_Data.EMM[atApp_EMM.number_device].contactor_feedback);
        Serial.print("\n");
    }
  }
}
}

void  App_EMM::App_EMM_Suspend(){}
void  App_EMM::App_EMM_Resume(){}	  
void  App_EMM::App_EMM_End(){}
void atApp_EMM_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_EMM.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif