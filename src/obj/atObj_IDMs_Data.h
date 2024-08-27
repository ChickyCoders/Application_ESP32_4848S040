/**
@file
Objective for control with Esp32 Wrover.
*/
/*
  Object_IDMs_Data.h - Arduino library for control with ESP32
  Library:: Object_IDMs_Data
  This version is
  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/
#ifndef Object_IDMs_Data_h
#define Object_IDMs_Data_h


/* _____PROJECT INCLUDES____________________________________________________ */
#include "Arduino.h"
#include "Object.h"

/* _____DEFINITIONS__________________________________________________________ */
#define Max_IDM  10

enum direction_run
{
	Forward,
	Reverse
};

struct IDMs_data
{
    bool Status_of_IDMs = 0;
    //value in IPv4 
    uint8_t IP[4]        = 	{192,168,0,0};

    uint16_t invt_type = 2;  
    bool direction_run = 1;
    uint16_t set_frequency = 50;
	uint16_t operating_frequency;
	uint16_t input_voltage;
	uint16_t input_current;
	uint16_t output_voltage;
	uint16_t output_current;
    uint16_t fault_code; 
    uint16_t set_frequency_old;
    bool direction_run_old;
};

/* _____GLOBAL VARIABLES_____________________________________________________ */


/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This class is the application to manage the 
 */

class Object_IDMs_Data :public Object
{
public:
    static void   Object_Cont_Start();
    static void   Object_Cont_Execute();    
    static void   Object_Cont_End();
    
    uint8_t Get_Fault_State();
    Object_IDMs_Data(/* args */);
    ~Object_IDMs_Data();
    uint8_t IDM_number = 0;
    //Max number of devices = 20;
    IDMs_data IDM[Max_IDM + 1];

protected: 
    
    
private:
    /* data */ 
} atObject_IDMs_Data;
/**
 * @brief This function code is executed one time when class is init
 * 
 */
Object_IDMs_Data::Object_IDMs_Data(/* args */)
{
     _Start_User      = *Object_Cont_Start;
     _Execute_User    = *Object_Cont_Execute;
     _End_User        = *Object_Cont_End;
}
/**
 * @brief This function code is executed one time when class is deinit
 * 
 */
Object_IDMs_Data::~Object_IDMs_Data()
{
}
/**
 * This start function will init some critical function 
 */
void  Object_IDMs_Data::Object_Cont_Start()
{
  
} 
/**
 * Execute fuction of IDM app
 */
void  Object_IDMs_Data:: Object_Cont_Execute()
{   

}    
void  Object_IDMs_Data:: Object_Cont_End(){}

#endif