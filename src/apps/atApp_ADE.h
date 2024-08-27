/**
@file
*/
/*
  Library
  This version is
  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_ADE_
#define _Application_atApp_ADE_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "math.h"
#include "../services/ADE7758/atService_ADE7758.h"
#include "../services/PCF8575/atService_PCF8575.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */

///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */
TaskHandle_t Task_atApp_ADE;  
void atApp_ADE_Task_Func(void *parameter);
/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This application class is the application to manage the 
 */
class App_ADE : public Application
{
public:
  	App_ADE();
 	~App_ADE();
	// formula to cal data form raw data 
	// data = Calib_Index_A * raw_data + Calib_Index_B;
	float Calib_Index_A_RMS_Volatge[PHASE_NUMBER];
	float Calib_Index_B_RMS_Volatge[PHASE_NUMBER];
	float RMS_Voltage[PHASE_NUMBER];

	float Calib_Index_A_RMS_Current[PHASE_NUMBER];
	float Calib_Index_B_RMS_Current[PHASE_NUMBER];
	float RMS_Current[PHASE_NUMBER];

	float Calib_Index_A_Active_Power[PHASE_NUMBER];
	float Calib_Index_B_Active_Power[PHASE_NUMBER];
	float Active_Power[PHASE_NUMBER];

	float Calib_Index_A_Reactive_Power[PHASE_NUMBER];
	float Calib_Index_B_Reactive_Power[PHASE_NUMBER];
	float Reactive_Power[PHASE_NUMBER];

	float Calib_Index_A_Apparent_Power[PHASE_NUMBER];
	float Calib_Index_B_Apparent_Power[PHASE_NUMBER];
	float Apparent_Power[PHASE_NUMBER];

	float Cosfi[PHASE_NUMBER];

	float Calib_Index_A_Frequency;
	float Calib_Index_B_Frequency;
	float Frequency = 0;
protected:
	float Round(float numb);
private:
  	static void  App_ADE_Pend();
	static void  App_ADE_Start();
	static void  App_ADE_Restart();
	static void  App_ADE_Execute();
	static void  App_ADE_Suspend();
	static void  App_ADE_Resume();	  
	static void  App_ADE_End();
} atApp_ADE ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_ADE::App_ADE(/* args */)
{
  	_Pend_User 	     = *App_ADE_Pend;
	_Start_User 	 = *App_ADE_Start;
	_Restart_User 	 = *App_ADE_Restart;
	_Execute_User 	 = *App_ADE_Execute;
	_Suspend_User	 = *App_ADE_Suspend;
	_Resume_User	 = *App_ADE_Resume;
	_End_User	     = *App_ADE_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"ADE Application";
	// change the ID of SNM

	// init default calib index of phase A RMS voltage 
	atApp_ADE.Calib_Index_A_RMS_Volatge[PHASE_A] = 7313.915858;
	atApp_ADE.Calib_Index_B_RMS_Volatge[PHASE_A] = -7.81;
	// init default calib index of phase B RMS voltage 
	atApp_ADE.Calib_Index_A_RMS_Volatge[PHASE_B] = 7313.91;
	atApp_ADE.Calib_Index_B_RMS_Volatge[PHASE_B] = -5.75;
	// init default calib index of phase C RMS voltage 
	atApp_ADE.Calib_Index_A_RMS_Volatge[PHASE_C] = 7313.91;
	atApp_ADE.Calib_Index_B_RMS_Volatge[PHASE_C] = -7.87;

	// init default calib index of phase A RMS current
	atApp_ADE.Calib_Index_A_RMS_Current[PHASE_A] = 718.58;
	atApp_ADE.Calib_Index_B_RMS_Current[PHASE_A] = -0.01;
	// init default calib index of phase B RMS current
	atApp_ADE.Calib_Index_A_RMS_Current[PHASE_B] = 560;
	atApp_ADE.Calib_Index_B_RMS_Current[PHASE_B] = -0.01;
	// init default calib index of phase C RMS current
	atApp_ADE.Calib_Index_A_RMS_Current[PHASE_C] = 560;
	atApp_ADE.Calib_Index_B_RMS_Current[PHASE_C] = -0.01;

	// init default calib index of phase A active power
	atApp_ADE.Calib_Index_A_Active_Power[PHASE_A] = 1;
	atApp_ADE.Calib_Index_B_Active_Power[PHASE_A] = 0;
	// init default calib index of phase B active power
	atApp_ADE.Calib_Index_A_Active_Power[PHASE_B] = 1;
	atApp_ADE.Calib_Index_B_Active_Power[PHASE_B] = 0;
	// init default calib index of phase C active power
	atApp_ADE.Calib_Index_A_Active_Power[PHASE_C] = 1;
	atApp_ADE.Calib_Index_B_Active_Power[PHASE_C] = 0;

	// init default calib index of phase A Reactive power
	atApp_ADE.Calib_Index_A_Reactive_Power[PHASE_A] = 1;
	atApp_ADE.Calib_Index_B_Reactive_Power[PHASE_A] = 0;
	// init default calib index of phase B Reactive power
	atApp_ADE.Calib_Index_A_Reactive_Power[PHASE_B] = 1;
	atApp_ADE.Calib_Index_B_Reactive_Power[PHASE_B] = 0;
	// init default calib index of phase C Reactive power
	atApp_ADE.Calib_Index_A_Reactive_Power[PHASE_C] = 1;
	atApp_ADE.Calib_Index_B_Reactive_Power[PHASE_C] = 0;

	// init default calib index of phase A Apparent power
	atApp_ADE.Calib_Index_A_Apparent_Power[PHASE_A] = 1;
	atApp_ADE.Calib_Index_B_Apparent_Power[PHASE_A] = 0;
	// init default calib index of phase B Apparent power
	atApp_ADE.Calib_Index_A_Apparent_Power[PHASE_B] = 1;
	atApp_ADE.Calib_Index_B_Apparent_Power[PHASE_B] = 0;
	// init default calib index of phase C Apparent power
	atApp_ADE.Calib_Index_A_Apparent_Power[PHASE_C] = 1;
	atApp_ADE.Calib_Index_B_Apparent_Power[PHASE_C] = 0;

	Cosfi[PHASE_A] = 1;
	Cosfi[PHASE_B] = 1;
	Cosfi[PHASE_C] = 1;

	Calib_Index_A_Frequency = 1;
	Calib_Index_B_Frequency = 0;

}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_ADE::~App_ADE()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition.
 *  In the debug mode, task will send information of application to terminal to start the application.
 */
void  App_ADE::App_ADE_Pend()
{
    // atService_ADE7758.Debug();
	// atService_PCF8575.Debug();
}
/**
 * This start function will init some critical function 
 */
void  App_ADE::App_ADE_Start()
{
	// init atXYZ Service in the fist running time
	atService_ADE7758.Run_Service();
	atService_PCF8575.Run_Service();

	atService_PCF8575.Pin_Modes[PCF8575_PIN_P1] = MODE_PCF8575_Output;
	atService_PCF8575.Pin_Vals[PCF8575_PIN_P1]	= VAL_PCF8575_Low;
	atService_PCF8575.Run_Service();
}  
/**
 * Restart function of SNM  app
 */
void  App_ADE::App_ADE_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_ADE::App_ADE_Execute()
{	
	
	atService_ADE7758.Run_Service();
	float RMS_Voltage_raw[PHASE_NUMBER];
	float RMS_Current_raw[PHASE_NUMBER];
	float Active_Power_raw[PHASE_NUMBER];
	float Reactive_Power_raw[PHASE_NUMBER];
	float Apparent_Power_raw[PHASE_NUMBER];
	float Frequency_raw = 0;
	float Temperature_raw = 0;
	uint8_t Version_Die_Raw = 0;

	RMS_Voltage_raw[PHASE_A] = atService_ADE7758.get_RMS_Voltage(PHASE_A);
	RMS_Voltage_raw[PHASE_B] = atService_ADE7758.get_RMS_Voltage(PHASE_B);
	RMS_Voltage_raw[PHASE_C] = atService_ADE7758.get_RMS_Voltage(PHASE_C);

	RMS_Current_raw[PHASE_A] = atService_ADE7758.get_RMS_Current(PHASE_A);
	RMS_Current_raw[PHASE_B] = atService_ADE7758.get_RMS_Current(PHASE_B);
	RMS_Current_raw[PHASE_C] = atService_ADE7758.get_RMS_Current(PHASE_C);

	Active_Power_raw[PHASE_A] = atService_ADE7758.get_Active_Power(PHASE_A);
	Active_Power_raw[PHASE_B] = atService_ADE7758.get_Active_Power(PHASE_B);
	Active_Power_raw[PHASE_C] = atService_ADE7758.get_Active_Power(PHASE_C);

	Reactive_Power_raw[PHASE_A] = atService_ADE7758.get_Reactive_Power(PHASE_A);
	Reactive_Power_raw[PHASE_B] = atService_ADE7758.get_Reactive_Power(PHASE_B);
	Reactive_Power_raw[PHASE_C] = atService_ADE7758.get_Reactive_Power(PHASE_C);

	Apparent_Power_raw[PHASE_A] = atService_ADE7758.get_Apparent_Power(PHASE_A);
	Apparent_Power_raw[PHASE_B] = atService_ADE7758.get_Apparent_Power(PHASE_B);
	Apparent_Power_raw[PHASE_C] = atService_ADE7758.get_Apparent_Power(PHASE_C);

	Frequency_raw = atService_ADE7758.get_Frequency();
	Version_Die_Raw = atService_ADE7758.get_Version();
	atApp_ADE.RMS_Voltage[PHASE_A] = atApp_ADE.Round(atApp_ADE.Calib_Index_A_RMS_Volatge[PHASE_A] * RMS_Voltage_raw[PHASE_A]  + atApp_ADE.Calib_Index_B_RMS_Volatge[PHASE_A]);
	atApp_ADE.RMS_Voltage[PHASE_B] = atApp_ADE.Round(atApp_ADE.Calib_Index_A_RMS_Volatge[PHASE_B] * RMS_Voltage_raw[PHASE_B]  + atApp_ADE.Calib_Index_B_RMS_Volatge[PHASE_B]);
	atApp_ADE.RMS_Voltage[PHASE_C] = atApp_ADE.Round(atApp_ADE.Calib_Index_A_RMS_Volatge[PHASE_C] * RMS_Voltage_raw[PHASE_C]  + atApp_ADE.Calib_Index_B_RMS_Volatge[PHASE_C]);

	atApp_ADE.RMS_Current[PHASE_A] = atApp_ADE.Round(atApp_ADE.Calib_Index_A_RMS_Current[PHASE_A] * RMS_Current_raw[PHASE_A]  + atApp_ADE.Calib_Index_B_RMS_Current[PHASE_A]);
	atApp_ADE.RMS_Current[PHASE_B] = atApp_ADE.Round(atApp_ADE.Calib_Index_A_RMS_Current[PHASE_B] * RMS_Current_raw[PHASE_B]  + atApp_ADE.Calib_Index_B_RMS_Current[PHASE_B]);
	atApp_ADE.RMS_Current[PHASE_C] = atApp_ADE.Round(atApp_ADE.Calib_Index_A_RMS_Current[PHASE_C] * RMS_Current_raw[PHASE_C]  + atApp_ADE.Calib_Index_B_RMS_Current[PHASE_C]);

	atApp_ADE.Active_Power[PHASE_A] = atApp_ADE.Calib_Index_A_Active_Power[PHASE_A] * Active_Power_raw[PHASE_A]  + atApp_ADE.Calib_Index_B_Active_Power[PHASE_A];
	atApp_ADE.Active_Power[PHASE_B] = atApp_ADE.Calib_Index_A_Active_Power[PHASE_B] * Active_Power_raw[PHASE_B]  + atApp_ADE.Calib_Index_B_Active_Power[PHASE_B];
	atApp_ADE.Active_Power[PHASE_C] = atApp_ADE.Calib_Index_A_Active_Power[PHASE_C] * Active_Power_raw[PHASE_C]  + atApp_ADE.Calib_Index_B_Active_Power[PHASE_C]; 

	atApp_ADE.Reactive_Power[PHASE_A] = atApp_ADE.Calib_Index_A_Reactive_Power[PHASE_A] * Reactive_Power_raw[PHASE_A] + atApp_ADE.Calib_Index_B_Reactive_Power[PHASE_A];
	atApp_ADE.Reactive_Power[PHASE_B] = atApp_ADE.Calib_Index_A_Reactive_Power[PHASE_B] * Reactive_Power_raw[PHASE_B] + atApp_ADE.Calib_Index_B_Reactive_Power[PHASE_B];
	atApp_ADE.Reactive_Power[PHASE_C] = atApp_ADE.Calib_Index_A_Reactive_Power[PHASE_C] * Reactive_Power_raw[PHASE_C] + atApp_ADE.Calib_Index_B_Reactive_Power[PHASE_C];

	atApp_ADE.Apparent_Power[PHASE_A] = atApp_ADE.Calib_Index_A_Apparent_Power[PHASE_A] * Apparent_Power_raw[PHASE_A] + atApp_ADE.Calib_Index_B_Apparent_Power[PHASE_A];
	atApp_ADE.Apparent_Power[PHASE_B] = atApp_ADE.Calib_Index_A_Apparent_Power[PHASE_B] * Apparent_Power_raw[PHASE_B] + atApp_ADE.Calib_Index_B_Apparent_Power[PHASE_B];
	atApp_ADE.Apparent_Power[PHASE_C] = atApp_ADE.Calib_Index_A_Apparent_Power[PHASE_C] * Apparent_Power_raw[PHASE_C] + atApp_ADE.Calib_Index_B_Apparent_Power[PHASE_C];

	atApp_ADE.Cosfi[PHASE_A] = atApp_ADE.Active_Power[PHASE_A] / atApp_ADE.Apparent_Power[PHASE_A];
	atApp_ADE.Cosfi[PHASE_B] = atApp_ADE.Active_Power[PHASE_B] / atApp_ADE.Apparent_Power[PHASE_B];
	atApp_ADE.Cosfi[PHASE_C] = atApp_ADE.Active_Power[PHASE_C] / atApp_ADE.Apparent_Power[PHASE_C];

	if (atApp_ADE.RMS_Current[PHASE_A] != 0)
	{
		atApp_ADE.Active_Power[PHASE_A] = atApp_ADE.Round(atApp_ADE.RMS_Voltage[PHASE_A] * atApp_ADE.RMS_Current[PHASE_A] * atApp_ADE.Cosfi[PHASE_A]);
		atApp_ADE.Reactive_Power[PHASE_A] = atApp_ADE.Round(atApp_ADE.RMS_Voltage[PHASE_A] * atApp_ADE.RMS_Current[PHASE_A] * atApp_ADE.Reactive_Power[PHASE_A] / atApp_ADE.Apparent_Power[PHASE_A]);
		atApp_ADE.Apparent_Power[PHASE_A] = atApp_ADE.Round(atApp_ADE.RMS_Voltage[PHASE_A] * atApp_ADE.RMS_Current[PHASE_A] );
	}
	else
	{
		atApp_ADE.Active_Power[PHASE_A] = 0;
		atApp_ADE.Reactive_Power[PHASE_A] = 0;
		atApp_ADE.Apparent_Power[PHASE_A] = 0;
		atApp_ADE.Cosfi[PHASE_A] = 0;
	}
	
	if (atApp_ADE.RMS_Current[PHASE_B] != 0)
	{
		atApp_ADE.Active_Power[PHASE_B] = atApp_ADE.Round(atApp_ADE.RMS_Voltage[PHASE_B] * atApp_ADE.RMS_Current[PHASE_B] * atApp_ADE.Cosfi[PHASE_B]);
		atApp_ADE.Reactive_Power[PHASE_B] = atApp_ADE.Round(atApp_ADE.RMS_Voltage[PHASE_B] * atApp_ADE.RMS_Current[PHASE_B] * atApp_ADE.Reactive_Power[PHASE_B] / atApp_ADE.Apparent_Power[PHASE_B]);
		atApp_ADE.Apparent_Power[PHASE_B] = atApp_ADE.Round(atApp_ADE.RMS_Voltage[PHASE_B] * atApp_ADE.RMS_Current[PHASE_B] );
	}
	else
	{
		atApp_ADE.Active_Power[PHASE_B] = 0;
		atApp_ADE.Reactive_Power[PHASE_B] = 0;
		atApp_ADE.Apparent_Power[PHASE_B] = 0;
		atApp_ADE.Cosfi[PHASE_B] = 0;
	}

	if (atApp_ADE.RMS_Current[PHASE_C] != 0)
	{
		atApp_ADE.Active_Power[PHASE_C] = atApp_ADE.Round(atApp_ADE.RMS_Voltage[PHASE_C] * atApp_ADE.RMS_Current[PHASE_C] * atApp_ADE.Cosfi[PHASE_C]);
		atApp_ADE.Reactive_Power[PHASE_C] = atApp_ADE.Round(atApp_ADE.RMS_Voltage[PHASE_C] * atApp_ADE.RMS_Current[PHASE_C] * atApp_ADE.Reactive_Power[PHASE_C] / atApp_ADE.Apparent_Power[PHASE_C]);
		atApp_ADE.Apparent_Power[PHASE_C] = atApp_ADE.Round(atApp_ADE.RMS_Voltage[PHASE_C] * atApp_ADE.RMS_Current[PHASE_C] );
	}
	else
	{
		atApp_ADE.Active_Power[PHASE_C] = 0;
		atApp_ADE.Reactive_Power[PHASE_C] = 0; 
		atApp_ADE.Apparent_Power[PHASE_C] = 0;
		atApp_ADE.Cosfi[PHASE_C] = 0;
	}

	atApp_ADE.Frequency = atApp_ADE.Calib_Index_A_Frequency * Frequency_raw + atApp_ADE.Calib_Index_B_Frequency;

    if(atApp_ADE.User_Mode == APP_USER_MODE_DEBUG)
    {
		Serial.printf("Raw data form ADE7758\n");
		Serial.printf("	RMS voltage phase A: %.9f \n",	RMS_Voltage_raw[PHASE_A]);
		Serial.printf("	RMS voltage phase B: %.9f \n",	RMS_Voltage_raw[PHASE_B]);
		Serial.printf("	RMS voltage phase C: %.9f \n\n",RMS_Voltage_raw[PHASE_C]);

		Serial.printf("	RMS current phase A: %.9f \n",RMS_Current_raw[PHASE_A]);
		Serial.printf("	RMS current phase B: %.9f \n",RMS_Current_raw[PHASE_B]);
		Serial.printf("	RMS current phase C: %.9f \n\n",RMS_Current_raw[PHASE_C]);

		Serial.printf("	Active power phase A:   %.9f \n",Active_Power_raw[PHASE_A]);
		Serial.printf("	Active power phase B:   %.9f \n",Active_Power_raw[PHASE_B]);
		Serial.printf("	Active power phase C:   %.9f \n\n",Active_Power_raw[PHASE_C]);

		Serial.printf("	Reactive power phase A: %.9f \n",Reactive_Power_raw[PHASE_A]);
		Serial.printf("	Reactive power phase B: %.9f \n",Reactive_Power_raw[PHASE_B]);
		Serial.printf("	Reactive power phase C: %.9f \n\n",Reactive_Power_raw[PHASE_C]);

		Serial.printf("	Apparent power phase A: %.9f \n",Apparent_Power_raw[PHASE_A]);
		Serial.printf("	Apparent power phase B: %.9f \n",Apparent_Power_raw[PHASE_B]);
		Serial.printf("	Apparent power phase C: %.9f \n\n",Apparent_Power_raw[PHASE_C]);

		Serial.printf("Frequency : %.9f\n",Frequency_raw);
		Serial.printf("Temperature: %.2f \n",Temperature_raw);
		Serial.printf("Version die: %d \n\n",Version_Die_Raw);

		Serial.printf("Data after being calculated\n");
		Serial.printf("	RMS voltage phase A: %.2f \n",		atApp_ADE.RMS_Voltage[PHASE_A]);
		Serial.printf("	RMS voltage phase B: %.2f \n",		atApp_ADE.RMS_Voltage[PHASE_B]);
		Serial.printf("	RMS voltage phase C: %.2f \n\n",	atApp_ADE.RMS_Voltage[PHASE_C]);

		Serial.printf("	RMS current phase A: %.2f \n", 		atApp_ADE.RMS_Current[PHASE_A]);
		Serial.printf("	RMS current phase B: %.2f \n",		atApp_ADE.RMS_Current[PHASE_B]);
		Serial.printf("	RMS current phase C: %.2f \n\n",	atApp_ADE.RMS_Current[PHASE_C]);

		Serial.printf("	Active power phase A:   %.2f \n",	atApp_ADE.Active_Power[PHASE_A]);
		Serial.printf("	Active power phase B:   %.2f \n",	atApp_ADE.Active_Power[PHASE_B]);
		Serial.printf("	Active power phase C:   %.2f \n\n",	atApp_ADE.Active_Power[PHASE_C]);

		Serial.printf("	Reactive power phase A: %.2f \n",	atApp_ADE.Reactive_Power[PHASE_A]);
		Serial.printf("	Reactive power phase B: %.2f \n",	atApp_ADE.Reactive_Power[PHASE_B]);
		Serial.printf("	Reactive power phase C: %.2f \n\n",	atApp_ADE.Reactive_Power[PHASE_C]);

		Serial.printf("	Apparent power phase A: %.2f \n",	atApp_ADE.Apparent_Power[PHASE_A]);
		Serial.printf("	Apparent power phase B: %.2f \n",	atApp_ADE.Apparent_Power[PHASE_B]);
		Serial.printf("	Apparent power phase C: %.2f \n\n",	atApp_ADE.Apparent_Power[PHASE_C]);

		Serial.printf("	Cosfi  phase A: %.3f \n",	atApp_ADE.Cosfi[PHASE_A]);
		Serial.printf("	Cosfi  phase B: %.3f \n",	atApp_ADE.Cosfi[PHASE_B]);
		Serial.printf("	Cosfi  phase C: %.3f \n\n",	atApp_ADE.Cosfi[PHASE_C]);

		Serial.printf("Frequency : %.2f\n",atApp_ADE.Frequency); 
    }   
}
void  App_ADE::App_ADE_Suspend(){}
void  App_ADE::App_ADE_Resume(){}	  
void  App_ADE::App_ADE_End(){}
float  App_ADE::Round(float numb)
{
	return float(int(numb*100))/100;
	// return numb;
}
void atApp_ADE_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_ADE.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}

#endif