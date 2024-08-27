/**
@file
*/
/*
  Application
  Library:: chickyPig_OP320_V1

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_DS18B20_
#define _Application_atApp_DS18B20_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"

#include <OneWire.h>
/* _____DEFINITIONS__________________________________________________________ */
#define MAX_TEMPERATURE_SENSOR_NUMBER 20
#define INVALID_CRC 1

#define SENSOR_TYPE_DS18S20 0
#define SENSOR_TYPE_DS18B20 1
#define SENSOR_TYPE_DS1822 	2

#define PIN_DS18B20 27
/* _____GLOBAL VARIABLES_____________________________________________________ */
OneWire  ds18b20(PIN_DS18B20);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */
TaskHandle_t Task_atApp_DS18B20;  
void atApp_DS18B20_Task_Func(void *parameter);
/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Application class is the application to manage the 
 */
class App_DS : public Application
{
public:
  	App_DS();
 	~App_DS();
	// for process each sensor
	byte present = 0;
	uint8_t type_Sensor;
	byte data[12];
	byte addr[8];
	uint8_t Error = 0;
	// for store data for ever sensor
	float Temperature_At_Sensor[MAX_TEMPERATURE_SENSOR_NUMBER]; //in Celsius
	uint8_t Temp_Sen_Index = 0;
	uint8_t Present_Plugging_Sensor_Number = 0;
	bool noMore_Sensor = 0;
	float celsius, fahrenheit;
protected:
private:
  	static void  App_DS_Pend();
	static void  App_DS_Start();
	static void  App_DS_Restart();
	static void  App_DS_Execute();
	static void  App_DS_Suspend();
	static void  App_DS_Resume();
	static void  App_DS_End();
} atApp_DS18B20 ;
/**
 * This function will be auto called when a object is created by this class
 */
App_DS::App_DS(/* args */)
{
  	_Pend_User 	     = *App_DS_Pend;
	_Start_User 	 = *App_DS_Start;
	_Restart_User 	 = *App_DS_Restart;
	_Execute_User 	 = *App_DS_Execute;
	_Suspend_User	 = *App_DS_Suspend;
	_Resume_User	 = *App_DS_Resume;
	_End_User	     = *App_DS_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"DS Application";
	
	// change the set all data to 0
	for (uint8_t i = 0; i < MAX_TEMPERATURE_SENSOR_NUMBER; i++)
	{
		atApp_DS18B20.Temperature_At_Sensor[i] = 0;
	}
}
/**
 * This function will be auto called when the object of class is delete
 */
App_DS::~App_DS()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. 
 * In the debug mode, task will send information of application to terminal to start the application.
 */
void  App_DS::App_DS_Pend()
{

}
/**
 * This start function will init some critical function 
 */
void  App_DS::App_DS_Start()
{
    
}  
/**
 * Restart function of SNM  app
 */
void  App_DS::App_DS_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_DS::App_DS_Execute()
{	
	atApp_DS18B20.noMore_Sensor = 0;
	if ( !ds18b20.search(atApp_DS18B20.addr)) {
		atApp_DS18B20.noMore_Sensor = 1; // there is no more sensor have address what is greater than present address
		ds18b20.reset_search();
		atApp_DS18B20.Temp_Sen_Index = 0;
  	}
	else
	{
		if (OneWire::crc8(atApp_DS18B20.addr, 7) != atApp_DS18B20.addr[7]) {
			atApp_DS18B20.Error = INVALID_CRC;
			// Serial.println("CRC is not valid!");
  		}
		else
		{
			// the first ROM byte indicates which chip
			switch (atApp_DS18B20.addr[0]) {
				case 0x10:
				atApp_DS18B20.type_Sensor = SENSOR_TYPE_DS18S20;
				break;

				case 0x28:
				atApp_DS18B20.type_Sensor = SENSOR_TYPE_DS18B20;
				break;

				case 0x22:
				atApp_DS18B20.type_Sensor = SENSOR_TYPE_DS1822;
				break;

				default:
				atApp_DS18B20.type_Sensor = 0;
			} 
			ds18b20.reset();
  			ds18b20.select(atApp_DS18B20.addr);
  			ds18b20.write(0x44, 1);        // start conversion, with parasite power on at the end

			// vTaskDelay(1000/portTICK_PERIOD_MS);// maybe 750ms is enough, maybe not
			delay(1000);
			// we might do a ds.de power() here, but the reset will take care of it.

			atApp_DS18B20.present = ds18b20.reset();
  			ds18b20.select(atApp_DS18B20.addr);    
  			ds18b20.write(0xBE);         // Read Scratchpad

			// read 9 data bytes
			for ( uint8_t i = 0; i < 9; i++) {
				atApp_DS18B20.data[i] = ds18b20.read();
			}

			// Convert the data to actual temperature
			// because the result is a 16 bit signed integer, it should
			// be stored to an "int16_t" type, which is always 16 bits
			// even when compiled on a 32 bit processor.
			int16_t raw = (atApp_DS18B20.data[1] << 8) | atApp_DS18B20.data[0];
			if (atApp_DS18B20.type_Sensor == SENSOR_TYPE_DS18S20) // if sensor type is DS18S20
			{  
				raw = raw << 3; // 9 bit resolution default
				if (atApp_DS18B20.data[7] == 0x10) 
				{
					// "count remain" gives full 12 bit resolution
					raw = (raw & 0xFFF0) + 12 - atApp_DS18B20.data[6];
				}
			} 
			if( (atApp_DS18B20.type_Sensor == SENSOR_TYPE_DS18B20) || (atApp_DS18B20.type_Sensor == SENSOR_TYPE_DS1822) )
			{
				byte cfg = (atApp_DS18B20.data[4] & 0x60);
				// at lower res, the low bits are undefined, so let's zero them
				if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
				else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
				else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
				//// default is 12 bit resolution, 750 ms conversion time
			}
			atApp_DS18B20.celsius = (float)raw / 16.0;
  			atApp_DS18B20.fahrenheit = atApp_DS18B20.celsius * 1.8 + 32.0;

			atApp_DS18B20.Temperature_At_Sensor[atApp_DS18B20.Temp_Sen_Index] = atApp_DS18B20.celsius;
			atApp_DS18B20.Temp_Sen_Index ++;
			// update plugging sensor number
			if (atApp_DS18B20.Present_Plugging_Sensor_Number < atApp_DS18B20.Temp_Sen_Index)
			{
				atApp_DS18B20.Present_Plugging_Sensor_Number = atApp_DS18B20.Temp_Sen_Index;
			}
			
			
		}
	}

	if(atApp_DS18B20.User_Mode == APP_USER_MODE_DEBUG)
	{
		if (atApp_DS18B20.noMore_Sensor)
		{
			Serial.println("No more addresses \n");
		}

		switch (atApp_DS18B20.type_Sensor)
		{
		case 1:
			Serial.println("  Chip = DS18S20");
			break;

		case 2:
			Serial.println("  Chip = DS18B20");
			break;

		case 3:
			Serial.println("  Chip = DS1822");
			break;

		default:
			Serial.println("Device is not a DS18x20 family device.");
			break;
		}

		Serial.print("  Data = ");
		Serial.print(atApp_DS18B20.present, HEX);
		Serial.print(" ");
		for ( uint8_t i = 0; i < 9; i++) {
			Serial.print(atApp_DS18B20.data[i], HEX);
			Serial.print(" ");
  		}
		Serial.print(" CRC=");
		Serial.print(OneWire::crc8(atApp_DS18B20.data, 8), HEX);
		Serial.println();

		Serial.print("  Temperature = ");
		Serial.print(atApp_DS18B20.celsius);
		Serial.print(" Celsius, ");
		Serial.print(atApp_DS18B20.fahrenheit);
		Serial.println(" Fahrenheit");

		for (uint8_t i = 0; i < atApp_DS18B20.Present_Plugging_Sensor_Number; i++)
		{
			Serial.print("Temperature Sensor ");
			Serial.print(i);
			Serial.print(" : ");
			Serial.print(atApp_DS18B20.Temperature_At_Sensor[i]);
			Serial.println(" oC ");
		}		
	}
}
void  App_DS::App_DS_Suspend(){}
void  App_DS::App_DS_Resume(){}	  
void  App_DS::App_DS_End(){}
void atApp_DS18B20_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_ABC.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif