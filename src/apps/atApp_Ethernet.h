/**
@file
*/
/*
  Application example t

  Library:: 
  
  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/
#ifndef _Application_atApp_Ethernet_
#define _Application_atApp_Ethernet_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "SPI.h"
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "../services/PCF8575/atService_PCF8575.h"
/* _____DEFINITIONS__________________________________________________________ */
#ifndef Ethernet_CS_Pin
#define Ethernet_CS_Pin 5
#define Ethernet_Reset_Pin	PCF8575_PIN_P13
#endif
enum Ethernet_Status
{
    Ethernet_STATUS_Connected,
    Ethernet_STATUS_Disconnected
};
enum Ethernet_IP_Mode
{
    Ethernet_IP_MODE_Dynamic,
    Ethernet_IP_MODE_Static
};
    uint8_t Ethernet_MAC[6] = { 0x5C,0xA6, 0xE6 , 0xD8, 0x21, 0x70 };
    IPAddress Ethernet_IP_Static    (192, 168, 1, 103);		// *** CHANGE THIS to something relevant for YOUR LAN. ***
    IPAddress Ethernet_MASK_Static  (255, 255, 255, 0);		// Subnet mask.
    IPAddress Ethernet_DNS_Static   (192, 168, 1, 2);		// *** CHANGE THIS to match YOUR DNS server.           ***
    IPAddress Ethernet_GW_Static    (192, 168, 1, 1);		// *** CHANGE THIS to match YOUR Gateway (router).     ***
/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_Ethernet;  
void atApp_Ethernet_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */
void W5500_Reset();
void prt_hwval(uint8_t refval);
void prt_ethval(uint8_t refval);
/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_Ethernet : public Application
{
public:

    Ethernet_Status status = Ethernet_STATUS_Disconnected;
    Ethernet_IP_Mode ip_mode = Ethernet_IP_MODE_Static; 
    const uint16_t localPort = 55432;		// Local port for UDP packets.
    char IP[20] ="";

    EthernetUDP Udp;
protected:
private:
  	App_Ethernet();
 	~App_Ethernet();
  	static void  App_Ethernet_Pend();
	static void  App_Ethernet_Start();
	static void  App_Ethernet_Restart();
	static void  App_Ethernet_Execute();
	static void  App_Ethernet_Suspend();
	static void  App_Ethernet_Resume();	  
	static void  App_Ethernet_End();
} atApp_Ethernet ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_Ethernet::App_Ethernet(/* args */)
{
  	_Pend_User 	     = *App_Ethernet_Pend;
	_Start_User 	 = *App_Ethernet_Start;
	_Restart_User 	 = *App_Ethernet_Restart;
	_Execute_User 	 = *App_Ethernet_Execute;
	_Suspend_User	 = *App_Ethernet_Suspend;
	_Resume_User	 = *App_Ethernet_Resume;
	_End_User	     = *App_Ethernet_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"Ethernet Application";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_Ethernet::~App_Ethernet()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_Ethernet::App_Ethernet_Pend()
{
}
/**
 * This start function will init some critical function 
 */
void  App_Ethernet::App_Ethernet_Start()
{
    // Use Ethernet.init(pin) to configure the CS pin.
    Ethernet.init(Ethernet_CS_Pin);           // GPIO5 on the ESP32.
    W5500_Reset();

    if(atApp_Ethernet.User_Mode == APP_USER_MODE_DEBUG)
        Serial.println("Starting ETHERNET connection...");
    if (atApp_Ethernet.ip_mode == Ethernet_IP_MODE_Static)
    {
        Ethernet.begin( Ethernet_MAC,
                        Ethernet_IP_Static,
                        Ethernet_DNS_Static,
                        Ethernet_GW_Static,
                        Ethernet_MASK_Static);
        delay(200);
    }
    else Ethernet.begin(Ethernet_MAC);
    /*
     * Sanity checks for W5500 and cable connection.
     */
    if(atApp_Ethernet.User_Mode == APP_USER_MODE_DEBUG)
        Serial.print("Checking connection.");
    bool rdy_flag = false;
    for (uint8_t i = 0; i <= 20; i++) {
        if ((Ethernet.hardwareStatus() == EthernetNoHardware)|| (Ethernet.linkStatus() != LinkON)) 
        {
            if(atApp_Ethernet.User_Mode == APP_USER_MODE_DEBUG)   
                Serial.print(".");
            rdy_flag = false;
            delay(80);
        } 
        else {
            rdy_flag = true;
            break;
        }
    }
    if (rdy_flag == false) {
        if(atApp_Ethernet.User_Mode == APP_USER_MODE_DEBUG)
        {
            atApp_Ethernet.status = Ethernet_STATUS_Connected;
            Serial.println("\n\r\tHardware fault, or cable problem... cannot continue.");
            Serial.print("Hardware Status: ");
            prt_hwval(Ethernet.hardwareStatus());
            Serial.print("   Cable Status: ");
            prt_ethval(Ethernet.linkStatus());
            while (true) {
                delay(10);          // Halt.
            }
        }
    } else {
        if(atApp_Ethernet.User_Mode == APP_USER_MODE_DEBUG)
            Serial.printf(" OK\n");
        }
    atApp_Ethernet.Udp.begin(atApp_Ethernet.localPort);
}  
/**
 * Restart function of SNM  app
 */
void  App_Ethernet::App_Ethernet_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_Ethernet::App_Ethernet_Execute()
{	
    
    if(atApp_Ethernet.User_Mode == APP_USER_MODE_DEBUG)
    {
		Serial.printf("Ethernet Status is: ");
        switch (atApp_Ethernet.status)
        {
        case Ethernet_STATUS_Connected:
            Serial.printf("Connected\n");
            break;
        case Ethernet_STATUS_Disconnected:
            Serial.printf("Disconnected\n");
            break;
        default:
            break;
        }
        Serial.print("Ethernet IP is: ");
        Serial.println(Ethernet.localIP());
        Serial.print("Ethernet Mode is: ");
        switch (atApp_Ethernet.ip_mode)
        {
        case Ethernet_IP_MODE_Dynamic:
            Serial.printf("IP Dynamic\n");
            break;
        case Ethernet_IP_MODE_Static:
            Serial.printf("IP Static\n");
            break;
        default:
            break;
        }
    }   
}
void  App_Ethernet::App_Ethernet_Suspend(){}
void  App_Ethernet::App_Ethernet_Resume(){}	  
void  App_Ethernet::App_Ethernet_End(){}

void W5500_Reset() {
    if(atApp_Ethernet.User_Mode == APP_USER_MODE_DEBUG)
        Serial.print("Resetting Wiz W5500 Ethernet Board...  ");
    atService_PCF8575.Pin_Modes[Ethernet_Reset_Pin] = MODE_PCF8575_Output;
    atService_PCF8575.Pin_Vals[Ethernet_Reset_Pin] = VAL_PCF8575_High;
    delay(250);
    atService_PCF8575.Pin_Vals[Ethernet_Reset_Pin] = VAL_PCF8575_High;
    delay(50);
    atService_PCF8575.Pin_Vals[Ethernet_Reset_Pin] = VAL_PCF8575_Low;
    delay(350);
    if(atApp_Ethernet.User_Mode == APP_USER_MODE_DEBUG)
        Serial.println("Done.");
}
void prt_hwval(uint8_t refval) {
    switch (refval) {
    case 0:
        Serial.println("No hardware detected.");
        break;
    case 1:
        Serial.println("WizNet W5100 detected.");
        break;
    case 2:
        Serial.println("WizNet W5200 detected.");
        break;
    case 3:
        Serial.println("WizNet W5500 detected.");
        break;
    default:
        Serial.println
            ("UNKNOWN - Update espnow_gw.ino to match Ethernet.h");
    }
}
void prt_ethval(uint8_t refval) {
    switch (refval) {
    case 0:
        Serial.println("Uknown status.");
        break;
    case 1:
        Serial.println("Link flagged as UP.");
        break;
    case 2:
        Serial.println("Link flagged as DOWN. Check cable connection.");
        break;
    default:
        Serial.println
            ("UNKNOWN - Update espnow_gw.ino to match Ethernet.h");
    }
}
void atApp_Ethernet_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_Ethernet.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif