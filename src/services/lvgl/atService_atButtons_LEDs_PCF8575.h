/**
@file
Service for communicating with OP320A&S SNM over RS232/485 (via RTU protocol).
*/
/*
  Service_atService_Buttons_LEDs_PCF8575.h - Arduino library for communicating with OP320A&S SNM
  over RS232/485 (via RTU protocol).

  Library:: chickyPig_OP320_V1

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Service_atService_Buttons_LEDs_PCF8575_
#define _Service_atService_Buttons_LEDs_PCF8575_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "../Service.h"
#include "PCF8575.h"
/* _____DEFINETIONS__________________________________________________________ */
#define button_Up       11
#define button_Down     13
#define button_Back     14
#define button_Ok       12
#define button_Menu     10
#define button_Alarm    15

#define LED1_R 3
#define LED1_G 2
#define LED1_B 4

#define LED2_R 6
#define LED2_G 5
#define LED2_B 7

#define LED3_R 8
#define LED3_G 9
#define LED3_B 0

#ifndef OFF
#define OFF     0
#endif
#define RED     1
#define GREEN   2
#define BLUE    3

#define LCD_BL 1
#define Pushed      1
#define Released    0
/* _____GLOBAL VARIABLES_____________________________________________________ */
PCF8575 atPCF8575_Buttons_LEDs(0x21);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the 
 */
class Buttons : public Service
{
public:
    Buttons();
    ~Buttons();
    bool Up = Released;
    bool Down = Released;
    bool Back = Released;
    bool Ok = Released;
    bool Menu = Released;
    bool Alarm = Released;
    uint8_t LED_RGB_1 = 0;
    uint8_t LED_RGB_2 = 0;
    uint8_t LED_RGB_3 = 0;
    
    bool LCD_Led = 1; 
protected:
    uint8_t LED_RGB_1_Status = 0;
    uint8_t LED_RGB_2_Status = 0;
    uint8_t LED_RGB_3_Status = 0;
    bool LCD_Led_Status = 1; 
private:

    static void  Service_Buttons_Start();
    static void  Service_Buttons_Execute();    
    static void  Service_Buttons_End();
} atService_Buttons_LEDs_PCF8575 ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Buttons::Buttons(/* args */)
{
    _Start_User      = *Service_Buttons_Start;
    _Execute_User    = *Service_Buttons_Execute;
    _End_User        = *Service_Buttons_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char*)"Buttons and led for HMI_P3_V2.1 Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Buttons::~Buttons()
{
    _Start_User      = *Service_Buttons_Start;
    _Execute_User    = *Service_Buttons_Execute;
    _End_User        = *Service_Buttons_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char*)"Buttons and led for HMI_P3_V2.1 Service";
    // change the ID of SNM
}
/**
 * This start function will init some critical function 
 */
void  Buttons::Service_Buttons_Start()
{
    if (!atPCF8575_Buttons_LEDs.begin())
    {
      if (atService_Buttons_LEDs_PCF8575.User_Mode == SER_USER_MODE_DEBUG)
        Serial.println("could not initialize...");
      
    }
    if (!atPCF8575_Buttons_LEDs.isConnected())
    {
      if (atService_Buttons_LEDs_PCF8575.User_Mode == SER_USER_MODE_DEBUG)
        Serial.println("=> not connected");
    }
    else
    {
      if (atService_Buttons_LEDs_PCF8575.User_Mode == SER_USER_MODE_DEBUG)
        Serial.println("=> connected!!");
    }
}  

/**
 * Execute fuction of SNM app
 */
void  Buttons::Service_Buttons_Execute()
{   
    atService_Buttons_LEDs_PCF8575.Up       = ! atPCF8575_Buttons_LEDs.read(button_Up);
    atService_Buttons_LEDs_PCF8575.Down     = ! atPCF8575_Buttons_LEDs.read(button_Down);
    atService_Buttons_LEDs_PCF8575.Back     = ! atPCF8575_Buttons_LEDs.read(button_Back);
    atService_Buttons_LEDs_PCF8575.Ok       = ! atPCF8575_Buttons_LEDs.read(button_Ok);
    atService_Buttons_LEDs_PCF8575.Menu     = ! atPCF8575_Buttons_LEDs.read(button_Menu);
    atService_Buttons_LEDs_PCF8575.Alarm    = ! atPCF8575_Buttons_LEDs.read(button_Alarm);

    if (atService_Buttons_LEDs_PCF8575.LED_RGB_1 != atService_Buttons_LEDs_PCF8575.LED_RGB_1_Status)
    {
        switch (atService_Buttons_LEDs_PCF8575.LED_RGB_1)
        {
        case RED:
            atPCF8575_Buttons_LEDs.write(LED1_R,0);
            atPCF8575_Buttons_LEDs.write(LED1_G,1);
            atPCF8575_Buttons_LEDs.write(LED1_B,1);
            break;
        case GREEN:
            atPCF8575_Buttons_LEDs.write(LED1_R,1);
            atPCF8575_Buttons_LEDs.write(LED1_G,0);
            atPCF8575_Buttons_LEDs.write(LED1_B,1);
            break;
        case BLUE:
            atPCF8575_Buttons_LEDs.write(LED1_R,1);
            atPCF8575_Buttons_LEDs.write(LED1_G,1);
            atPCF8575_Buttons_LEDs.write(LED1_B,0);
            break;
        default:
            atPCF8575_Buttons_LEDs.write(LED1_R,1);
            atPCF8575_Buttons_LEDs.write(LED1_G,1);
            atPCF8575_Buttons_LEDs.write(LED1_B,1);
            break;
        }
        atService_Buttons_LEDs_PCF8575.LED_RGB_1_Status = atService_Buttons_LEDs_PCF8575.LED_RGB_1 ;
    }

    if (atService_Buttons_LEDs_PCF8575.LED_RGB_2 != atService_Buttons_LEDs_PCF8575.LED_RGB_2_Status)
    {
        switch (atService_Buttons_LEDs_PCF8575.LED_RGB_2)
        {
        case RED:
            atPCF8575_Buttons_LEDs.write(LED2_R,0);
            atPCF8575_Buttons_LEDs.write(LED2_G,1);
            atPCF8575_Buttons_LEDs.write(LED2_B,1);
            break;
        case GREEN:
            atPCF8575_Buttons_LEDs.write(LED2_R,1);
            atPCF8575_Buttons_LEDs.write(LED2_G,0);
            atPCF8575_Buttons_LEDs.write(LED2_B,1);
            break;
        case BLUE:
            atPCF8575_Buttons_LEDs.write(LED2_R,1);
            atPCF8575_Buttons_LEDs.write(LED2_G,1);
            atPCF8575_Buttons_LEDs.write(LED2_B,0);
            break;
        default:
            atPCF8575_Buttons_LEDs.write(LED2_R,1);
            atPCF8575_Buttons_LEDs.write(LED2_G,1);
            atPCF8575_Buttons_LEDs.write(LED2_B,1);
            break;
        }
        atService_Buttons_LEDs_PCF8575.LED_RGB_2_Status = atService_Buttons_LEDs_PCF8575.LED_RGB_2 ;
    }

    if (atService_Buttons_LEDs_PCF8575.LED_RGB_3 != atService_Buttons_LEDs_PCF8575.LED_RGB_3_Status)
    {
        switch (atService_Buttons_LEDs_PCF8575.LED_RGB_3)
        {
        case RED:
            atPCF8575_Buttons_LEDs.write(LED3_R,0);
            atPCF8575_Buttons_LEDs.write(LED3_G,1);
            atPCF8575_Buttons_LEDs.write(LED3_B,1);
            break;
        case GREEN:
            atPCF8575_Buttons_LEDs.write(LED3_R,1);
            atPCF8575_Buttons_LEDs.write(LED3_G,0);
            atPCF8575_Buttons_LEDs.write(LED3_B,1);
            break;
        case BLUE:
            atPCF8575_Buttons_LEDs.write(LED3_R,1);
            atPCF8575_Buttons_LEDs.write(LED3_G,1);
            atPCF8575_Buttons_LEDs.write(LED3_B,0);
            break;
        default:
            atPCF8575_Buttons_LEDs.write(LED3_R,1);
            atPCF8575_Buttons_LEDs.write(LED3_G,1);
            atPCF8575_Buttons_LEDs.write(LED3_B,1);
            break;
        }
        atService_Buttons_LEDs_PCF8575.LED_RGB_3_Status = atService_Buttons_LEDs_PCF8575.LED_RGB_3 ;
    }
    // lcd led control
    if(atService_Buttons_LEDs_PCF8575.LCD_Led != atService_Buttons_LEDs_PCF8575.LCD_Led_Status)
    {
        atService_Buttons_LEDs_PCF8575.LCD_Led_Status = atService_Buttons_LEDs_PCF8575.LCD_Led;
        atPCF8575_Buttons_LEDs.write(LCD_BL,atService_Buttons_LEDs_PCF8575.LCD_Led_Status);
    }

    if(atService_Buttons_LEDs_PCF8575.User_Mode == SER_USER_MODE_DEBUG)
    {
        Serial.printf("Buttons with 2 state:  1 - Pushed, 0 - released \n");
        Serial.printf("Up: %d \n",      atService_Buttons_LEDs_PCF8575.Up);
        Serial.printf("Down: %d \n",    atService_Buttons_LEDs_PCF8575.Down);
        Serial.printf("Back: %d \n",    atService_Buttons_LEDs_PCF8575.Back);
        Serial.printf("OK: %d \n",      atService_Buttons_LEDs_PCF8575.Ok);
        Serial.printf("Menu: %d \n",    atService_Buttons_LEDs_PCF8575.Menu);
        Serial.printf("Alarm: %d \n",   atService_Buttons_LEDs_PCF8575.Alarm);
        Serial.println();
    }   
}    
void  Buttons::Service_Buttons_End(){}

#endif


