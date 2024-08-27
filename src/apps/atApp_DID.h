/**
@file

*/
/*
  Application example t

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_DID_
#define _Application_atApp_DID_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "..\services\modbus_master\atService_MB_TCP_MA.h"
#include "..\obj\atObj_EMMs_Data.h"
#include "..\obj\atObj_HDMs_Data.h"
#include "..\obj\atObj_IDMs_Data.h"
#include "..\obj\atObj_RDMs_Data.h"
#include "..\obj\atObj_SNMs_Data.h"
/* _____DEFINITIONS__________________________________________________________ */
enum Status_of_device
{
	Offline,
	Online
};

enum 
{
	Yes,
	No
};

enum 
{
	Connection_failed,
	Successful_connection
};

enum Device_type
{
	RCM = 1,
	LCM,
	SNM,
	EMM,
	IDM,
	RDM,
	HDM
};
/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_DID;  
void atApp_DID_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */
bool cbWrite(Modbus::ResultCode event, uint16_t transactionId, void* data) {
  Serial.printf_P("Request result: 0x%02X, Mem: %d\n", event, ESP.getFreeHeap());
  return true;
}
/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_DID : public Application
{
public:
  	App_DID();
 	~App_DID();

	//value of host in IPv4 : (192, 168, Host_1, Host_2)
	uint8_t IP[4]        = 	{192,168,1,14};

	bool request_connecting = Yes;
	bool connecting_result = 0;

protected:
	void create_did_for_SNM();
	void create_did_for_EMM();
	void create_did_for_IDM();
	void create_did_for_RDM();
	void create_did_for_HDM();

	// Number buffer
	uint8_t SNM_number = 0;
	uint8_t IDM_number = 0;
	uint8_t EMM_number = 0;
	uint8_t RDM_number = 0;
	uint8_t HDM_number = 0;
	uint8_t buffer = 0;
	//Device type
	uint16_t DT = 0;
	//Device Identify
	uint16_t DID = 0;
private:
  	static void  App_DID_Pend();
	static void  App_DID_Start();
	static void  App_DID_Restart();
	static void  App_DID_Execute();
	static void  App_DID_Suspend();
	static void  App_DID_Resume();	  
	static void  App_DID_End();
} atApp_DID ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_DID::App_DID(/* args */)
{
  	_Pend_User 	     = *App_DID_Pend;
	_Start_User 	 = *App_DID_Start;
	_Restart_User 	 = *App_DID_Restart;
	_Execute_User 	 = *App_DID_Execute;
	_Suspend_User	 = *App_DID_Suspend;
	_Resume_User	 = *App_DID_Resume;
	_End_User	     = *App_DID_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"DID Application";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_DID::~App_DID()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_DID::App_DID_Pend()
{
}
/**
 * This start function will init some critical function 
 */
void  App_DID::App_DID_Start()
{
	// init atXYZ Service in the fist running time
    atService_MB_TCP_MA.Run_Service();
}  
/**
 * Restart function of SNM  app
 */
void  App_DID::App_DID_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_DID::App_DID_Execute()
{	
	// Connect to Slave has IP address
	IPAddress IP_module( 	atApp_DID.IP[0], 
                        	atApp_DID.IP[1],
                        	atApp_DID.IP[2], 
                        	atApp_DID.IP[3]);

	// Try to connect to read Device type and Device ID
	if( atApp_DID.request_connecting == Yes)
	{
		for( uint8_t count = 0; count <= 2; count++)
		{
			if(atService_MB_TCP_MA.isConnected(IP_module) == false)
			{
				if(atApp_DID.User_Mode == APP_USER_MODE_DEBUG)
    			{
					Serial.println(" Connecting");
				}
				atService_MB_TCP_MA.check_In();
				atService_MB_TCP_MA.connect(IP_module); 
				atService_MB_TCP_MA.check_Out();
				atApp_DID.buffer = atApp_DID.buffer + 1;
			}
			else 
			{
				if(atApp_DID.User_Mode == APP_USER_MODE_DEBUG)
    			{
					Serial.println(" Successful_connection");
				}
				for( uint8_t count = 0; count <= 3; count++)
				{
					atService_MB_TCP_MA.check_In();
					atService_MB_TCP_MA.readHreg(IP_module, GENERAL_REGISTER_R_DEVICE_TYPE, &atApp_DID.DT);
					atService_MB_TCP_MA.readHreg(IP_module, GENERAL_REGISTER_RW_DEVICE_ID, &atApp_DID.DID);
					atService_MB_TCP_MA.check_Out();
				}

				if(atApp_DID.User_Mode == APP_USER_MODE_DEBUG)
    			{
					Serial.print(" Device type ");
					Serial.println(atApp_DID.DT);
					Serial.print(" Device ID ");
					Serial.println(atApp_DID.DID);
				}

				atApp_DID.connecting_result = Successful_connection;
				atApp_DID.buffer = 0;
				break;
			}
		}

		if(atApp_DID.buffer > 0)
		{
			atApp_DID.connecting_result = Connection_failed;
			if(atApp_DID.User_Mode == APP_USER_MODE_DEBUG)
    		{
				Serial.print(" IP not available");
			}
		}

		// Device type identification
		switch (atApp_DID.DT)
		{
			case SNM:
				atApp_DID.SNM_number++;
				atApp_DID.create_did_for_SNM();
				atApp_DID.DT = 0;
				atApp_DID.DID = 0;
				break;
			case EMM:
				atApp_DID.EMM_number++;
				atApp_DID.create_did_for_EMM();
				atApp_DID.DT = 0;
				atApp_DID.DID = 0;
				break;
			case IDM:
				atApp_DID.IDM_number++;
				atApp_DID.create_did_for_IDM();
				atApp_DID.DT = 0;
				atApp_DID.DID = 0;
				break;
			case RDM:
				atApp_DID.RDM_number++;
				atApp_DID.create_did_for_RDM();
				atApp_DID.DT = 0;
				atApp_DID.DID = 0;
				break;
			case HDM:
				atApp_DID.HDM_number++;
				atApp_DID.create_did_for_HDM();
				atApp_DID.DT = 0;
				atApp_DID.DID = 0;
				break;
		}

		// Save the number of module
		atObject_SNMs_Data.SNM_number = atApp_DID.SNM_number;
		atObject_EMMs_Data.EMM_number = atApp_DID.EMM_number;
		atObject_IDMs_Data.IDM_number = atApp_DID.IDM_number;
		atObject_RDMs_Data.RDM_number = atApp_DID.RDM_number;
		atObject_HDMs_Data.HDM_number = atApp_DID.HDM_number;

		// Clear buffer number
		atApp_DID.SNM_number = 0;
		atApp_DID.EMM_number = 0;
		atApp_DID.IDM_number = 0;
		atApp_DID.RDM_number = 0;
		atApp_DID.HDM_number = 0;
		atApp_DID.request_connecting = No;
	}

    if(atApp_DID.User_Mode == APP_USER_MODE_DEBUG)
    {
		Serial.print("Device number of SNM: ");
		Serial.println(atObject_SNMs_Data.SNM_number);
		Serial.println("   SNM number    |     IP of device ");
		for( uint8_t count = 1; count <= 20; count++)
		{
			if(atObject_SNMs_Data.SNM[count].Status_of_SNMs == Online)
			{
				Serial.print("   SNM");
				Serial.print(count);
				Serial.print("     |     ");
				Serial.print(atObject_SNMs_Data.SNM[count].IP[0]);
				Serial.print(".");
				Serial.print(atObject_SNMs_Data.SNM[count].IP[1]);
				Serial.print(".");
				Serial.print(atObject_SNMs_Data.SNM[count].IP[2]);
				Serial.print(".");
				Serial.print(atObject_SNMs_Data.SNM[count].IP[3]);
				Serial.print("\n");
			}
		}

		Serial.print("Device number of EMM: ");
		Serial.println(atObject_EMMs_Data.EMM_number);
		Serial.println("   EMM number    |     IP of device ");
		for( uint8_t count = 1; count <= 20; count++)
		{
			if(atObject_EMMs_Data.EMM[count].Status_of_EMMs == Online)
			{
				Serial.print("   EMM");
				Serial.print(count);
				Serial.print("        |     ");
				Serial.print(atObject_EMMs_Data.EMM[count].IP[0]);
				Serial.print(".");
				Serial.print(atObject_EMMs_Data.EMM[count].IP[1]);
				Serial.print(".");
				Serial.print(atObject_EMMs_Data.EMM[count].IP[2]);
				Serial.print(".");
				Serial.print(atObject_EMMs_Data.EMM[count].IP[3]);
				Serial.print("\n");
			}
		}

		Serial.print("Device number of IDM: ");
		Serial.println(atObject_IDMs_Data.IDM_number);
		Serial.println("   IDM number    |     IP of device ");
		for( uint8_t count = 1; count <= 20; count++)
		{
			if(atObject_IDMs_Data.IDM[count].Status_of_IDMs == Online)
			{
				Serial.print("   IDM");
				Serial.print(count);
				Serial.print("         |     ");
				Serial.print(atObject_IDMs_Data.IDM[count].IP[0]);
				Serial.print(".");
				Serial.print(atObject_IDMs_Data.IDM[count].IP[1]);
				Serial.print(".");
				Serial.print(atObject_IDMs_Data.IDM[count].IP[2]);
				Serial.print(".");
				Serial.print(atObject_IDMs_Data.IDM[count].IP[3]);
				Serial.print("\n");
			}
		}

		Serial.print("Device number of RDM: ");
		Serial.println(atObject_RDMs_Data.RDM_number);
		Serial.println("   RDM number    |     IP of device ");
		for( uint8_t count = 1; count <= 20; count++)
		{
			if(atObject_RDMs_Data.RDM[count].Status_of_RDMs == Online)
			{
				Serial.print("   RDM");
				Serial.print(count);
				Serial.print("          ");
				Serial.print(atObject_RDMs_Data.RDM[count].IP[0]);
				Serial.print(".");
				Serial.print(atObject_RDMs_Data.RDM[count].IP[1]);
				Serial.print(".");
				Serial.print(atObject_RDMs_Data.RDM[count].IP[2]);
				Serial.print(".");
				Serial.print(atObject_RDMs_Data.RDM[count].IP[3]);
				Serial.print("\n");
			}
		}

		Serial.print("Device number of HDM: ");
		Serial.println(atObject_HDMs_Data.HDM_number);
		Serial.println("   HDM number    |     IP of device ");
		for( uint8_t count = 1; count <= 20; count++)
		{
			if(atObject_HDMs_Data.HDM[count].Status_of_HDMs == Online)
			{
				Serial.print("   HDM");
				Serial.print(count);
				Serial.print("     |     ");
				Serial.print(atObject_HDMs_Data.HDM[count].IP[0]);
				Serial.print(".");
				Serial.print(atObject_HDMs_Data.HDM[count].IP[1]);
				Serial.print(".");
				Serial.print(atObject_HDMs_Data.HDM[count].IP[2]);
				Serial.print(".");
				Serial.print(atObject_HDMs_Data.HDM[count].IP[3]);
				Serial.print("\n");
			}
		}
    }   
}
void  App_DID::App_DID_Suspend(){}
void  App_DID::App_DID_Resume(){}	  
void  App_DID::App_DID_End(){}
void atApp_DID_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_DID.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}

//Allocate a new did for the SNM module
void App_DID::create_did_for_SNM()
{	
	if (atApp_DID.DID == 0)
	{	
		IPAddress IP_module( 	atApp_DID.IP[0], 
    	                    	atApp_DID.IP[1],
    	                    	atApp_DID.IP[2],
								atApp_DID.IP[3]);
		for (uint16_t a = 1; a <= 20; a++)
		{
			if(atObject_SNMs_Data.SNM[a].Status_of_SNMs == Offline)
			{
			// try to write DID to SNM device
			for(uint8_t count = 1; count<= 3; count++)
				{
					atService_MB_TCP_MA.check_In();
					atService_MB_TCP_MA.writeHreg(IP_module, GENERAL_REGISTER_RW_DEVICE_ID, a);
					atService_MB_TCP_MA.check_Out();
				}
				// save status device to obj
				atObject_SNMs_Data.SNM[a].Status_of_SNMs = Online;
				// save device IP to obj
				atObject_SNMs_Data.SNM[a].IP[0] = atApp_DID.IP[0];
				atObject_SNMs_Data.SNM[a].IP[1] = atApp_DID.IP[1];
				atObject_SNMs_Data.SNM[a].IP[2] = atApp_DID.IP[2];
				atObject_SNMs_Data.SNM[a].IP[3] = atApp_DID.IP[3];
				break;
			}	
		}
	}
}

//Allocate a new did for the EMM module
void App_DID::create_did_for_EMM()
{	
	if (atApp_DID.DID == 0)
	{	
		IPAddress IP_module( 	atApp_DID.IP[0], 
    	                   		atApp_DID.IP[1],
    	                   		atApp_DID.IP[2],
								atApp_DID.IP[3]);
		for (uint16_t a = 1; a <= 20; a++)
		{
			
			if(atObject_EMMs_Data.EMM[a].Status_of_EMMs == Offline)
			{
				for(uint8_t count = 1; count<= 3; count++)
				{
					atService_MB_TCP_MA.check_In();
					atService_MB_TCP_MA.writeHreg(IP_module, GENERAL_REGISTER_RW_DEVICE_ID, a);
					atService_MB_TCP_MA.check_Out();
				}
				// save status device to obj
				atObject_EMMs_Data.EMM[1].Status_of_EMMs = Online;
				// save device IP to obj
				atObject_EMMs_Data.EMM[a].IP[0] = atApp_DID.IP[0];
				atObject_EMMs_Data.EMM[a].IP[1] = atApp_DID.IP[1];
				atObject_EMMs_Data.EMM[a].IP[2] = atApp_DID.IP[2];
				atObject_EMMs_Data.EMM[a].IP[3] = atApp_DID.IP[3];
				break;
			}	
		}
	}
}

//Allocate a new did for the IDM module
void App_DID::create_did_for_IDM()
{	
	if (atApp_DID.DID == 0)
	{	
		IPAddress IP_module( 	atApp_DID.IP[0], 
    	                    	atApp_DID.IP[1],
    	                    	atApp_DID.IP[2],
								atApp_DID.IP[3]);
		for (uint16_t a = 1; a <= 20; a++)
		{
			if(atObject_IDMs_Data.IDM[a].Status_of_IDMs == Offline)
			{
			for(uint8_t count = 1; count<= 3; count++)
				{
					atService_MB_TCP_MA.check_In();
					atService_MB_TCP_MA.writeHreg(IP_module, GENERAL_REGISTER_RW_DEVICE_ID, a);
					atService_MB_TCP_MA.check_Out();
				}
				// save status device to obj
				atObject_IDMs_Data.IDM[a].Status_of_IDMs = Online;
				// save device IP to obj
				atObject_IDMs_Data.IDM[a].IP[0] = atApp_DID.IP[0];
				atObject_IDMs_Data.IDM[a].IP[1] = atApp_DID.IP[1];
				atObject_IDMs_Data.IDM[a].IP[2] = atApp_DID.IP[2];
				atObject_IDMs_Data.IDM[a].IP[3] = atApp_DID.IP[3];
				break;
			}	
		}
	}
}

//Allocate a new did for the RDM module
void App_DID::create_did_for_RDM()
{	
	if (atApp_DID.DID == 0)
	{	
		IPAddress IP_module( 	atApp_DID.IP[0], 
    	                    	atApp_DID.IP[1],
    	                    	atApp_DID.IP[2],
								atApp_DID.IP[3]);
		for (uint16_t a = 1; a <= 20; a++)
		{
			if(atObject_RDMs_Data.RDM[a].Status_of_RDMs == Offline)
			{
			for(uint8_t count = 1; count<= 3; count++)
				{
					atService_MB_TCP_MA.check_In();
					atService_MB_TCP_MA.writeHreg(IP_module, GENERAL_REGISTER_RW_DEVICE_ID, a);
					atService_MB_TCP_MA.check_Out();
				}
				// save status device to obj
				atObject_RDMs_Data.RDM[a].Status_of_RDMs = Online;
				// save device IP to obj
				atObject_RDMs_Data.RDM[a].IP[0] = atApp_DID.IP[0];
				atObject_RDMs_Data.RDM[a].IP[1] = atApp_DID.IP[1];
				atObject_RDMs_Data.RDM[a].IP[2] = atApp_DID.IP[2];
				atObject_RDMs_Data.RDM[a].IP[3] = atApp_DID.IP[3];
				break;
			}	
		}
	}
}

//Allocate a new did for the HDM module
void App_DID::create_did_for_HDM()
{	
	if (atApp_DID.DID == 0)
	{	
		IPAddress IP_module( 	atApp_DID.IP[0], 
    	                    	atApp_DID.IP[1],
    	                    	atApp_DID.IP[2],
								atApp_DID.IP[3]);
		for (uint16_t a = 1; a <= 20; a++)
		{
			if(atObject_HDMs_Data.HDM[a].Status_of_HDMs == Offline)
			{
			for(uint8_t count = 1; count<= 3; count++)
				{
					atService_MB_TCP_MA.check_In();
					atService_MB_TCP_MA.writeHreg(IP_module, GENERAL_REGISTER_RW_DEVICE_ID, a);
					atService_MB_TCP_MA.check_Out();
				}
				// save status device to obj
				atObject_HDMs_Data.HDM[a].Status_of_HDMs = Online;
				// save device IP to obj
				atObject_HDMs_Data.HDM[a].IP[0] = atApp_DID.IP[0];
				atObject_HDMs_Data.HDM[a].IP[1] = atApp_DID.IP[1];
				atObject_HDMs_Data.HDM[a].IP[2] = atApp_DID.IP[2];
				atObject_HDMs_Data.HDM[a].IP[3] = atApp_DID.IP[3];
				break;
			}	
		}
	}
}

#endif