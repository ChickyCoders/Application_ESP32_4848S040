/**
@file
*/
/*

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_HMI_
#define _Application_atApp_HMI_
// #define HMI_Lite
#define HMI
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#ifdef HMI_Lite
	#include "../services/lvgl/atService_LVGL_HMI_Lite.h"
#endif
#include "../gui/screen_system/Sources.h"
#ifdef HMI
	#include "../services/lvgl/atService_LVGL_HMI.h"
#endif
#include "../gui/screen_system/atScr_Monitoring.h"
#include "../gui/screen_system/atScr_Detail_1.h"
#include "../gui/screen_system/atScr_Detail_2.h"
#include "../gui/screen_system/atScr_Detail_3.h"
#include "../gui/screen_system/atScr_Menu.h"
#include "../services/SPI/atService_VSPI.h"

/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
static TimerHandle_t screen_monitoring_update_timer = NULL;
///////////////////////////////////////////////Testing part//

/* _____GLOBAL FUNCTION______________________________________________________ */
TaskHandle_t Task_atApp_HMI;  
void atApp_HMI_Task_Func(void *parameter);
void update_data_to_screens(TimerHandle_t xTimer);
/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Application class is the application to manage the 
 */
class App_HMI : public Application
{
public:
  	App_HMI();
 	~App_HMI();
  	static void  App_HMI_Pend();
	static void  App_HMI_Start();
	static void  App_HMI_Restart();
	static void  App_HMI_Execute();
	static void  App_HMI_Suspend();
	static void  App_HMI_Resume();	  
	static void  App_HMI_End();

	static const TickType_t update_screen_time = 1000/ portTICK_PERIOD_MS;;   // 1 second
	// bool update = 0;
	bool wifi_active        = ON;
    bool warning_active     = ON;
    bool SD_active          = ON;
    bool modbus_active      = ON;

	int notified_hour = 1;
	int notified_minute = 15;
protected:
private:
}  atApp_HMI ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_HMI::App_HMI(/* args */)
{
  	_Pend_User 	     = *App_HMI_Pend;
	_Start_User 	 = *App_HMI_Start;
	_Restart_User 	 = *App_HMI_Restart;
	_Execute_User 	 = *App_HMI_Execute;
	_Suspend_User	 = *App_HMI_Suspend;
	_Resume_User	 = *App_HMI_Resume;
	_End_User	     = *App_HMI_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"HMI Application";
	// change the ID of SNM

}	
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_HMI::~App_HMI()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. 
 * In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_HMI::App_HMI_Pend()
{
	// atService_LVGL_HMI.Debug();
	// atButtons_LEDs_PCF8575.Debug();
}
/**
 * This start function will init some critical function 
 */
void  App_HMI::App_HMI_Start()
{
	//screens map
	atScr_Monitoring.setup_Forward_Screen = atScr_Menu.Start;
	atScr_Monitoring.Forward_Screen = &atScr_Menu.Object;

	atScr_Menu.setup_Backward_Screen = *atScr_Monitoring.Start;
	atScr_Menu.Backward_Screen = &atScr_Monitoring.Object;

	atScr_Detail_1.setup_Backward_Screen = *atScr_Menu.Start;
	atScr_Detail_1.Backward_Screen = &atScr_Menu.Object;

	atScr_Detail_2.setup_Backward_Screen = *atScr_Menu.Start;
	atScr_Detail_2.Backward_Screen = &atScr_Menu.Object;

	atScr_Detail_3.setup_Backward_Screen = *atScr_Menu.Start;
	atScr_Detail_3.Backward_Screen = &atScr_Menu.Object;

	//init timer
	screen_monitoring_update_timer = xTimerCreate(
										"screen monitoring update timer",       // Name of timer
										update_screen_time,  					// Period of timer (in ticks)
										pdTRUE,                    				// Auto-reload
										(void *)0,                  			// Timer ID
										update_data_to_screens);           		// Callback function
	atService_VSPI.Run_Service();
	// atService_VSPI.check_In();
	atService_LVGL_HMI.Run_Service();	
	atScr_Monitoring.Start();
	//start timer
	xTimerStart(screen_monitoring_update_timer, portMAX_DELAY);
	lv_scr_load_anim(atScr_Monitoring.Object, LV_SCR_LOAD_ANIM_NONE, LOAD_PAGE_TIME, LOAD_PAGE_TIME, true);
	// atService_VSPI.check_Out();
}  
/**
 * Restart function of SNM  app
 */
void  App_HMI::App_HMI_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_HMI::App_HMI_Execute()
{	
	atService_VSPI.check_In();
	atService_LVGL_HMI.Run_Service();
	atService_VSPI.check_Out();
	
	if(atScr_Menu.State == ACTIVE)
	{
		int roller_select = atScr_Menu.get_roller_selected(atScr_Menu.roller_1);
		switch (roller_select)
		{
		case Detail_1:
			atScr_Menu.setup_Forward_Screen = *atScr_Detail_1.Start;
			atScr_Menu.Forward_Screen = &atScr_Detail_1.Object;
			break;
		case Detail_2:
			atScr_Menu.setup_Forward_Screen = *atScr_Detail_2.Start;
			atScr_Menu.Forward_Screen = &atScr_Detail_2.Object;
			break;
		case Detail_3:
			atScr_Menu.setup_Forward_Screen = *atScr_Detail_3.Start;
			atScr_Menu.Forward_Screen = &atScr_Detail_3.Object;
			break;
		default:
			break;
		}
	}	
	
	// atScr_Monitoring.Update_Scr_Monitoring();

	//get roller selected

	if(atApp_HMI.User_Mode == APP_USER_MODE_DEBUG)
    {
		
    }   
}
void  App_HMI::App_HMI_Suspend(){}
void  App_HMI::App_HMI_Resume(){}	  
void  App_HMI::App_HMI_End(){}
void atApp_HMI_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_HMI.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(10/ portTICK_PERIOD_MS);
  }
}

void update_data_to_screens(TimerHandle_t xTimer)
{
	atScr_Monitoring.Notified_Bar_1.SD_active 		= atApp_HMI.SD_active;
	atScr_Monitoring.Notified_Bar_1.wifi_active 	= atApp_HMI.wifi_active;
	atScr_Monitoring.Notified_Bar_1.modbus_active 	= atApp_HMI.modbus_active;
	atScr_Monitoring.Notified_Bar_1.warning_active 	= atApp_HMI.warning_active;
	atScr_Monitoring.Notified_Bar_1.hour 			= atApp_HMI.notified_hour;
	atScr_Monitoring.Notified_Bar_1.minute 			= atApp_HMI.notified_minute;

	atScr_Menu.Notified_Bar_1.SD_active 			= atApp_HMI.SD_active;
	atScr_Menu.Notified_Bar_1.wifi_active 			= atApp_HMI.wifi_active;
	atScr_Menu.Notified_Bar_1.modbus_active 		= atApp_HMI.modbus_active;
	atScr_Menu.Notified_Bar_1.warning_active 		= atApp_HMI.warning_active;
	atScr_Menu.Notified_Bar_1.hour 					= atApp_HMI.notified_hour;
	atScr_Menu.Notified_Bar_1.minute 				= atApp_HMI.notified_minute;

	atScr_Detail_1.Notified_Bar_1.SD_active 		= atApp_HMI.SD_active;
	atScr_Detail_1.Notified_Bar_1.wifi_active 		= atApp_HMI.wifi_active;
	atScr_Detail_1.Notified_Bar_1.modbus_active 	= atApp_HMI.modbus_active;
	atScr_Detail_1.Notified_Bar_1.warning_active 	= atApp_HMI.warning_active;
	atScr_Detail_1.Notified_Bar_1.hour 				= atApp_HMI.notified_hour;
	atScr_Detail_1.Notified_Bar_1.minute 			= atApp_HMI.notified_minute;

	atScr_Detail_2.Notified_Bar_1.SD_active 		= atApp_HMI.SD_active;
	atScr_Detail_2.Notified_Bar_1.wifi_active 		= atApp_HMI.wifi_active;
	atScr_Detail_2.Notified_Bar_1.modbus_active 	= atApp_HMI.modbus_active;
	atScr_Detail_2.Notified_Bar_1.warning_active 	= atApp_HMI.warning_active;
	atScr_Detail_2.Notified_Bar_1.hour 				= atApp_HMI.notified_hour;
	atScr_Detail_2.Notified_Bar_1.minute 			= atApp_HMI.notified_minute;

	atScr_Detail_3.Notified_Bar_1.SD_active 		= atApp_HMI.SD_active;
	atScr_Detail_3.Notified_Bar_1.wifi_active 		= atApp_HMI.wifi_active;
	atScr_Detail_3.Notified_Bar_1.modbus_active 	= atApp_HMI.modbus_active;
	atScr_Detail_3.Notified_Bar_1.warning_active 	= atApp_HMI.warning_active;
	atScr_Detail_3.Notified_Bar_1.hour 				= atApp_HMI.notified_hour;
	atScr_Detail_3.Notified_Bar_1.minute 			= atApp_HMI.notified_minute;
	
	atApp_HMI.notified_minute++;
	
	if(atScr_Monitoring.State == ACTIVE)
	{
		atScr_Monitoring.Run_Screen();
	}
	else if(atScr_Menu.State == ACTIVE)
	{
		atScr_Menu.Run_Screen();
	}
	else if(atScr_Detail_1.State == ACTIVE)
	{
		atScr_Detail_1.Run_Screen();
	}
	else if(atScr_Detail_2.State == ACTIVE)
	{
		atScr_Detail_2.Run_Screen();
	}
	if(atScr_Detail_3.State == ACTIVE)
	{
		atScr_Detail_3.Run_Screen();
	}

}
#endif