/**
@file
Objective for control with Esp32 Wrover.
*/
/*
  Object_EMMs_Data.h - Arduino library for control with ESP32
  Library:: Object_EMMs_Data
  This version is
  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/
#ifndef Object_EMMs_Data_h
#define Object_EMMs_Data_h


/* _____PROJECT INCLUDES____________________________________________________ */
#include "Arduino.h"
#include "Object.h"

/* _____DEFINITIONS__________________________________________________________ */
#define Max_EMM  10

enum Status_of_relay
{
	Open,
	Close
};

struct EMMs_data
{
    bool Status_of_EMMs = 0;
    //value in IPv4 
    uint16_t IP[4]        = 	{192,168,0,0};
    uint16_t Alert;
    uint16_t voltage_phase_A;
    uint16_t voltage_phase_B;
    uint16_t voltage_phase_C;
    uint16_t current_phase_A;
    uint16_t current_phase_B;
    uint16_t current_phase_C;
    uint16_t active_power;
    uint16_t reactive_power;
    uint16_t apparent_power;
    uint16_t cosfi;
    uint16_t frequency;
    bool control_relay;
    bool aptomat_feedback;
    bool contactor_feedback;
    bool relay_feedback;
    uint16_t Alert_old;
    bool control_relay_old;

};

/* _____GLOBAL VARIABLES_____________________________________________________ */


/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This class is the application to manage the 
 */

class Object_EMMs_Data :public Object
{
public:
    static void   Object_Cont_Start();
    static void   Object_Cont_Execute();    
    static void   Object_Cont_End();
    
    uint8_t Get_Fault_State();
    Object_EMMs_Data(/* args */);
    ~Object_EMMs_Data();
    uint8_t EMM_number = 0;
    //Max number of devices = 20;
    EMMs_data EMM[Max_EMM + 1];

protected: 
    
private:
    /* data */ 
} atObject_EMMs_Data;
/**
 * @brief This function code is executed one time when class is init
 * 
 */
Object_EMMs_Data::Object_EMMs_Data(/* args */)
{
     _Start_User      = *Object_Cont_Start;
     _Execute_User    = *Object_Cont_Execute;
     _End_User        = *Object_Cont_End;
}
/**
 * @brief This function code is executed one time when class is deinit
 * 
 */
Object_EMMs_Data::~Object_EMMs_Data()
{
}
/**
 * This start function will init some critical function 
 */
void  Object_EMMs_Data::Object_Cont_Start()
{
  
} 
/**
 * Execute fuction of EMM app
 */
void  Object_EMMs_Data:: Object_Cont_Execute()
{   

}    
void  Object_EMMs_Data:: Object_Cont_End(){}

#endif