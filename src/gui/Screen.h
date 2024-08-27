/**
@file
Screen Template.
*/
/*
  Screen

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/
#ifndef _Screen_
#define _Screen_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "Arduino.h"
#include "lvgl.h"
#include "screen_system/Sources.h"
/* _____GLOBAL VARIABLES_____________________________________________________ */


/* _____DEFINITIONS__________________________________________________________ */
enum Screen_State
{
    SCREEN_STATE_STARTING = 0,
    SCREEN_STATE_EXECUTING,
    DEACTIVE = 0,
    ACTIVE
};

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Screen class is base class for implement another class by inheritance 
 */
class Screen
{
public:
    Screen();
    void      Run_Screen();
    char*     Name_Screen = (char*)"Screen Name";
    uint16_t  ID_Screen = 0;

    bool State = DEACTIVE;

    // user can existing state of screen by change Screen_State into below state
    uint8_t Screen_State = SCREEN_STATE_EXECUTING;
    
    // this var will be set to 1 whenever ser done a state execution 
    bool Step_Forward = 0;

    lv_obj_t *Object;
    
protected:
    void (*_Start_User)();
    void (*_Execute_User)();
  
    uint8_t   State_Screen();
    char*     State_Screen_String();
    
    
private:
    //  Tasks default of Screen
    
    void Start(void);
    void Execute(void);
};

/**
 */
Screen::Screen(void)
{
  _Start_User   = 0;
  _Execute_User = 0;
}

/**
 * The main task of Screen, need to bee call regularly for attack like a 
 * task in freertos. There are 3 state of an Screen.  Starting is initting the prerequisite condition to
 * execute. Executing state is main state to handle the task of Screen. Screen will finish all task and save all
 * parameter, stop and remove all parameter. Error is the indicator for user when the 
 * Screen is executing wrongly.
 * @param autoRun  Screen_RUN_MODE_AUTO for auto execute and Screen_RUN_MODE_MANUAL for wait for execute manually by user
 */
void Screen::Run_Screen()
{
  switch (Screen_State)
  {
    // starting the task
    case SER_STATE_STARTING:
      Start();
      break;

    //the task is executing 
    case SER_STATE_EXECUTING:
      Execute();
      break;

    // default
    default:

      break;
  }
}
/**
 * This function will return a unsigned integer of Screen state at the present 
 * @return Screen_State the
 */
uint8_t Screen::State_Screen()
{
  return Screen_State;
}
char* Screen::State_Screen_String()
{
  switch (Screen_State)
  {
  case SCREEN_STATE_STARTING:
    return (char*)"Starting State";
    break;
  case SCREEN_STATE_EXECUTING:
    return (char*)"Executing State";
    break;
  default:
    return (char*)"Error state";
    break;
  }
}

/**
 *  start is the first task of this Screen it will do prerequisite
 *  condition. In the debug mode, task will send information of Screen to 
 * terminal to start the Screen.
 * @param (*_End_User)() this function pointer will be define by user
 * @param User_Mode will be specified by user
 */
void Screen::Start()
{
    // the user function
    (*_Start_User)();
    Screen_State = SCREEN_STATE_EXECUTING;
    Step_Forward = 1;
}
/**
 *  Pend to start is the first task of this Screen it will do prerequisite
 *  condition. In the debug mode, task will send Information of Screen to 
 * terminal to start the Screen.
 * @param (*_End_User)() this function pointer will be define by user
 * @param User_Mode will be specified by user
 */
void Screen::Execute()
{
  // the user function
  (*_Execute_User)();
  Step_Forward = 1;
}


#endif