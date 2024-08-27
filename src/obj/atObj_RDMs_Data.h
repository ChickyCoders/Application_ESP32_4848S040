/**
@file
Objective for control with Esp32 Wrover.
*/
/*
  Object_RDMs_Data.h - Arduino library for control with ESP32
  Library:: Object_RDMs_Data
  This version is
  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/
#ifndef Object_RDMs_Data_h
#define Object_RDMs_Data_h


/* _____PROJECT INCLUDES____________________________________________________ */
#include "Arduino.h"
#include "Object.h"

/* _____DEFINITIONS__________________________________________________________ */

struct RDMs_data
{
  bool Status_of_RDMs = 0;
  //value in IPv4 
  uint8_t IP[4]        = 	{192,168,0,0};
  
  bool In0;
  bool In1; 
  bool In2;
  bool In3;
  bool In4;
  bool In5;
  bool In6; 
  bool In7;
  bool In8;
  bool In9;
  bool In10;
  bool In11; 
  bool In12;
  bool In13;
  bool In14;
  bool In15;
  bool Out0;
  bool Out1; 
  bool Out2;
  bool Out3;
  bool Out4;
  bool Out5;
  bool Out6; 
  bool Out7;
  bool Out8;
  bool Out9;
  bool Out10;
  bool Out11; 
  bool Out12;
  bool Out13;
  bool Out14;
  bool Out15;
};


/* _____GLOBAL VARIABLES_____________________________________________________ */


/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This class is the application to manage the 
 */

class Object_RDMs_Data :public Object
{
public:
    static void   Object_Cont_Start();
    static void   Object_Cont_Execute();    
    static void   Object_Cont_End();
    
    uint8_t Get_Fault_State();
    Object_RDMs_Data(/* args */);
    ~Object_RDMs_Data();
    uint8_t RDM_number = 0;
    //Max number of devices = 20;
    RDMs_data RDM[21];
protected: 
    
    
private:
    /* data */ 
} atObject_RDMs_Data;
/**
 * @brief This function code is executed one time when class is init
 * 
 */
Object_RDMs_Data::Object_RDMs_Data(/* args */)
{
     _Start_User      = *Object_Cont_Start;
     _Execute_User    = *Object_Cont_Execute;
     _End_User        = *Object_Cont_End;
}
/**
 * @brief This function code is executed one time when class is deinit
 * 
 */
Object_RDMs_Data::~Object_RDMs_Data()
{
}
/**
 * This start function will init some critical function 
 */
void  Object_RDMs_Data::Object_Cont_Start()
{
  
} 
/**
 * Execute fuction of RDM app
 */
void  Object_RDMs_Data:: Object_Cont_Execute()
{   

}    
void  Object_RDMs_Data:: Object_Cont_End(){}

#endif