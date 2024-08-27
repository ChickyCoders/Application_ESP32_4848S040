/**
@file
Servicelication for communicating with OP320A&S SNM over RS232/485 (via RTU protocol).
*/
/*
  Servicelication_SNM.h - Arduino library for communicating with OP320A&S SNM
  over RS232/485 (via RTU protocol).

  Library:: chickyPig_OP320_V1

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Servicelication_atPCF8575_
#define _Servicelication_atPCF8575_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "../Service.h"
#include "PCF8575.h"
#include "../i2c/atService_I2C.h"
/* _____DEFINETIONS__________________________________________________________ */
enum Val_PCF8575
{
    VAL_PCF8575_Low,
    VAL_PCF8575_High
};
enum Mode_PCF8575
{
    MODE_PCF8575_Input,
    MODE_PCF8575_Output
};
/* _____GLOBAL FUNCTION______________________________________________________ */
enum pin_PCF8575
{   PCF8575_PIN_P0,
    PCF8575_PIN_P1,
    PCF8575_PIN_P2,
    PCF8575_PIN_P3,
    PCF8575_PIN_P4,
    PCF8575_PIN_P5,
    PCF8575_PIN_P6,
    PCF8575_PIN_P7,
    PCF8575_PIN_P10,
    PCF8575_PIN_P11,
    PCF8575_PIN_P12,
    PCF8575_PIN_P13,
    PCF8575_PIN_P14,
    PCF8575_PIN_P15,
    PCF8575_PIN_P16,
    PCF8575_PIN_P17,
    PCF8575_PIN_NUMBER
};
/* _____GLOBAL VARIABLES_____________________________________________________ */
PCF8575 atPCF8575(0x20);
/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Servicelication class is the Servicelication to manage the 
 */
class Service_PCF8575 : public Service
{
public:
  Service_PCF8575();
 	~Service_PCF8575();
  bool Pin_Modes[PCF8575_PIN_NUMBER]  = {MODE_PCF8575_Input};
  bool Pin_Vals[PCF8575_PIN_NUMBER]   = {VAL_PCF8575_Low};

protected:

private:
	static void  Service_PCF8575_Start();
	static void  Service_PCF8575_Execute();
	static void  Service_PCF8575_End();
} atService_PCF8575 ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_PCF8575::Service_PCF8575(/* args */)
{
	_Start_User 	 = *Service_PCF8575_Start;
	_Execute_User 	 = *Service_PCF8575_Execute;
	_End_User	     = *Service_PCF8575_End;

	// change the ID of Servicelication
	ID_Service = 1;
	// change the Servicelication name
	Name_Service = (char*)"PCF8575 Servicelication";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_PCF8575::~Service_PCF8575()
{
	
}

/**
 * This start function will init some critical function 
 */
void  Service_PCF8575::Service_PCF8575_Start()
{
  atService_I2C.Run_Service();
  atService_I2C.check_In();
  if (!atPCF8575.begin())
  {
    if(atService_PCF8575.User_Mode == SER_USER_MODE_DEBUG)
      Serial.println("could not initialize...");
  }
  if (!atPCF8575.isConnected())
  {
    if(atService_PCF8575.User_Mode == SER_USER_MODE_DEBUG)
      Serial.println("=> not connected");
  }
  else
  {
    if(atService_PCF8575.User_Mode == SER_USER_MODE_DEBUG)
      Serial.println("=> connected!!");
  } 
  atService_I2C.check_Out();
  // read pins to init pins with input modes
  for (uint8_t i = 0; i < PCF8575_PIN_NUMBER; i++)
  {
    atService_I2C.check_In();
    atService_PCF8575.Pin_Vals[i] = atPCF8575.read(i);
    atService_I2C.check_Out();
  }

}  

/**
 * Execute fuction of SNM Service
 */
void  Service_PCF8575::Service_PCF8575_Execute()
{	
  for (uint8_t i = 0; i < PCF8575_PIN_NUMBER; i++)
  {
      // if pin'mode is input, reading vals from pins
      if (atService_PCF8575.Pin_Modes[i] == MODE_PCF8575_Input)
      {
        atService_I2C.check_In();
        atService_PCF8575.Pin_Vals[i] = atPCF8575.read(i);
        atService_I2C.check_Out();
      }
      // pinmode is output, write vals to these pins
      else
      {
        atService_I2C.check_In();
        atPCF8575.write(i,atService_PCF8575.Pin_Vals[i]);
        atService_I2C.check_Out();
      }
  }

  if(atService_PCF8575.User_Mode == SER_USER_MODE_DEBUG)
  {
      for (uint8_t i = 0; i < PCF8575_PIN_NUMBER; i++)
      {
          Serial.printf("    Pin %d is in ",i);
          if (atService_PCF8575.Pin_Modes[i] == MODE_PCF8575_Input)
              Serial.print("input");
          else 
              Serial.print("output");
          Serial.printf(" mode and value is %d\n",atService_PCF8575.Pin_Vals[i]);
      }    
  }
}
void  Service_PCF8575::Service_PCF8575_End(){}

#endif