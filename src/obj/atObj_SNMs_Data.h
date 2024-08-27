/**
@file
Objective for control with Esp32 Wrover.
*/
/*
  Object_SNMs_Data.h - Arduino library for control with ESP32
  Library:: Object_SNMs_Data
  This version is
  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/
#ifndef Object_SNMs_Data_h
#define Object_SNMs_Data_h


/* _____PROJECT INCLUDES____________________________________________________ */
#include "Arduino.h"
#include "Object.h"

/* _____DEFINITIONS__________________________________________________________ */
#define Max_SNM  10

struct SNMs_data
{
  bool Status_of_SNMs = 0;
  //value IPv4 
  uint8_t IP[4]        = 	{192,168,0,0};
  // parameter value received
  uint16_t Temperature;
  uint16_t Humidity;
  uint16_t CO2;
  uint16_t TVOC;
  uint16_t H2;
  uint16_t Ethanol;
};


/* _____GLOBAL VARIABLES_____________________________________________________ */


/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This class is the application to manage the 
 */

class Object_SNMs_Data :public Object
{
public:
  static void   Object_Cont_Start();
  static void   Object_Cont_Execute();    
  static void   Object_Cont_End();
  
  uint8_t Get_Fault_State();
  Object_SNMs_Data(/* args */);
  ~Object_SNMs_Data();
  uint8_t SNM_number = 0;
  //Max number of devices = 20;
  SNMs_data SNM[Max_SNM + 1];

protected: 
private:
    /* data */ 
} atObject_SNMs_Data;

/**
 * @brief This function code is executed one time when class is init
 * 
 */
Object_SNMs_Data::Object_SNMs_Data(/* args */)
{
     _Start_User      = *Object_Cont_Start;
     _Execute_User    = *Object_Cont_Execute;
     _End_User        = *Object_Cont_End;
}
/**
 * @brief This function code is executed one time when class is deinit
 * 
 */
Object_SNMs_Data::~Object_SNMs_Data()
{
}
/**
 * This start function will init some critical function 
 */
void  Object_SNMs_Data::Object_Cont_Start()
{
  
} 
/**
 * Execute fuction of SNM app
 */
void  Object_SNMs_Data:: Object_Cont_Execute()
{   
  
}    
void  Object_SNMs_Data:: Object_Cont_End(){}

#endif