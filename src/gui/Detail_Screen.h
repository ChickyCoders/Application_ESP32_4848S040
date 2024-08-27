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
#ifndef _Detail_Screen_
#define _Detail_Screen_
/* _____PROJECT INCLUDES____________________________________________________ */

#include "Arduino.h"
#include "lvgl.h"
#include "Screen.h"
/* _____GLOBAL VARIABLES_____________________________________________________ */

/* _____DEFINITIONS__________________________________________________________ */
/*____CLASS DEFINITION_____________________________________________________ */
/**
 * This Screen class is base class for implement another class by inheritance 
 */
class Detail_Screen: public Screen
{
public:
    // to go to forward screen and backward screen
    lv_obj_t **Backward_Screen;
    void (*setup_Backward_Screen)();
    // 
    
protected: 

private:
};

#endif