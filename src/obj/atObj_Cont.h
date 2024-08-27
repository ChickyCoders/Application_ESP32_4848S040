/**
@file
Objective for control with Esp32 Wrover.
*/
/*
  Object_Contactor.h - Arduino library for control with ESP32
  Library:: Object_Contactor
  This version is
  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/
#ifndef Object_Contactor_h
#define Object_Contactor_h


/* _____PROJECT INCLUDES____________________________________________________ */
#include "Arduino.h"
#include "Object.h"
/* _____DEFINITIONS__________________________________________________________ */

enum Example
{
    default_1,
    default2,
    default3
};

/* _____GLOBAL VARIABLES_____________________________________________________ */


/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This class is the application to manage the 
 */

class Object_Contactor :public Object
{
public:
    static void   Object_Cont_Start();
    static void   Object_Cont_Execute();    
    static void   Object_Cont_End();
    
    uint8_t Get_Fault_State();
    Object_Contactor(/* args */);
    ~Object_Contactor();
protected: 
    
    
private:
    /* data */ 
} atObject_Contactor;
/**
 * @brief This function code is executed one time when class is init
 * 
 */
Object_Contactor::Object_Contactor(/* args */)
{
     _Start_User      = *Object_Cont_Start;
     _Execute_User    = *Object_Cont_Execute;
     _End_User        = *Object_Cont_End;
}
/**
 * @brief This function code is executed one time when class is deinit
 * 
 */
Object_Contactor::~Object_Contactor()
{
}
/**
 * This start function will init some critical function 
 */
void  Object_Contactor::Object_Cont_Start()
{
  
} 
/**
 * Execute fuction of SNM app
 */
void  Object_Contactor:: Object_Cont_Execute()
{   

}    
void  Object_Contactor:: Object_Cont_End(){}

#endif