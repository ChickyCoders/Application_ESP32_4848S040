
/**
@file
*/
/*
  Wifi application

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_Wifi_
#define _Application_atApp_Wifi_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "Arduino.h"
#include <WiFi.h>
#include "string.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_Wifi;  
void atApp_Wifi_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */
enum Network_Index_IPV4
{
    A = 0,
    B,
    C,
    D,
    IPV4_Index_Number
};
enum Wifi_Status
{
    WIFI_STATUS_Idle,
    WIFI_STATUS_Scanning,
    WIFI_STATUS_Scan_Completed,
    WIFI_STATUS_Connecting,
    WIFI_STATUS_Connected,
    WIFI_STATUS_Connect_Failed,
    WIFI_STATUS_Connection_Lost,
    WIFI_STATUS_Disconnecting,
    WIFI_STATUS_Disconnected
};
enum Wifi_Request
{
    WIFI_REQUEST_Idle,
    WIFI_REQUEST_Scanning,
    WIFI_REQUEST_Connecting,
    WIFI_REQUEST_Disconnecting
};
enum Wifi_IP_Mode
{
    WIFI_IP_MODE_Dynamic,
    WIFI_IP_MODE_Static
};
/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Application class is the application to manage the 
 */
class App_Wifi : public Application
{
public:
    App_Wifi();
 	~App_Wifi();

    Wifi_Status status = WIFI_STATUS_Idle;
    Wifi_Request request = WIFI_REQUEST_Scanning;

    // Scan networks WiFi
    char scanned_Wifi_SSIDs[100];
    int scanned_Wifi_SSIDs_Number = 0;
    uint8_t scanning_Time_Delay = 5;// second     
    
    // Connect to wifi  
    uint8_t wifi_SSID_Index_To_Connect = 0;
    char ssid_To_Connect[100] = "Atlab";
    char password_To_Connect[100] = "ChickyTuan";
    uint8_t waiting_time_to_connect = 15;
    Wifi_IP_Mode ip_Mode = WIFI_IP_MODE_Dynamic;
    uint8_t IP_Static[IPV4_Index_Number]        = {192,168,1,101};
    uint8_t Gateway_Static[IPV4_Index_Number]   = {192,168,0,1};
    uint8_t Subnet_Static[IPV4_Index_Number]    = {255,255,0,0};
    uint8_t DNS1_Static[IPV4_Index_Number]       = {8,8,8,8};
    uint8_t DNS2_Static[IPV4_Index_Number]       = {8,8,4,4};
    
    

    // information of connecting wifi 
    uint8_t delaying_time_to_check_collecting_wifi_RSSI = 5;// second           
    char connecting_SSID[100] = "";
    char connecting_Password[100] = "";
    int collecting_wifi_RSSI;
    char IP[20] = "";
    char Gateway[20] ="";
    char Subnet[20] = "";
    char DNS[20] = "";
    
protected:
    void scan_Network();
    void connect();
    void disconnect();
private:
  	static void  App_Wifi_Pend();
	static void  App_Wifi_Start();
	static void  App_Wifi_Restart();
	static void  App_Wifi_Execute();
	static void  App_Wifi_Suspend();
	static void  App_Wifi_Resume();	  
	static void  App_Wifi_End();

} atApp_Wifi ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_Wifi::App_Wifi(/* args */)
{
  	_Pend_User 	     = *App_Wifi_Pend;
	_Start_User 	 = *App_Wifi_Start;
	_Restart_User 	 = *App_Wifi_Restart;
	_Execute_User 	 = *App_Wifi_Execute;
	_Suspend_User	 = *App_Wifi_Suspend;
	_Resume_User	 = *App_Wifi_Resume;
	_End_User	     = *App_Wifi_End;

	// change the ID of application
	ID_Application = 4;
	// change the application name
	Name_Application = (char*)"Wifi Application";
	
}


/**
 * This function will be automaticaly called when the object of
 *  class is delete
 */
App_Wifi::~App_Wifi()
{
	
}
/**
 * Pend to start is the first task of this application it will 
 * do prerequisite condition. In the debug mode, task will send 
 * information of application to terminal to start the application.
 */
void  App_Wifi::App_Wifi_Pend()
{

}
/**
 * This start function will init some critical function 
 */
void  App_Wifi::App_Wifi_Start()
{
	// init atWifi Service in the fist running time
	Serial.begin(115200);
}  
/**
 * Restart function of Wifi  app
 */
void  App_Wifi::App_Wifi_Restart()
{

}
/**
 * Execute fuction of Wifi app
 */
void  App_Wifi::App_Wifi_Execute()
{	
    // execute the request
    switch (atApp_Wifi.request)
    {
    case WIFI_REQUEST_Scanning:
        atApp_Wifi.status = WIFI_STATUS_Scanning;
        atApp_Wifi.scan_Network();
        atApp_Wifi.status = WIFI_STATUS_Scan_Completed;
        break;

    case WIFI_REQUEST_Connecting:
        atApp_Wifi.status = WIFI_STATUS_Connecting;
        atApp_Wifi.connect();
        atApp_Wifi.request = WIFI_REQUEST_Idle;
        break;
    
    case WIFI_REQUEST_Disconnecting:
        atApp_Wifi.status = WIFI_STATUS_Disconnecting;
        atApp_Wifi.disconnect();
        atApp_Wifi.status = WIFI_STATUS_Disconnected;
        atApp_Wifi.request = WIFI_REQUEST_Idle;
        break;
    
    default:
        break;
    }
  
    // get information 
    if (WiFi.status() == WL_CONNECTED)
    {   
        atApp_Wifi.collecting_wifi_RSSI = WiFi.RSSI();
        sprintf(atApp_Wifi.connecting_SSID,     atApp_Wifi.ssid_To_Connect);
        sprintf(atApp_Wifi.connecting_Password, atApp_Wifi.password_To_Connect);
        sprintf(atApp_Wifi.IP                 , WiFi.localIP().toString().c_str());
        sprintf(atApp_Wifi.Gateway            , WiFi.gatewayIP().toString().c_str());
        sprintf(atApp_Wifi.Subnet             , WiFi.subnetMask().toString().c_str());
        sprintf(atApp_Wifi.DNS                , WiFi.dnsIP().toString().c_str());
        delay( atApp_Wifi.delaying_time_to_check_collecting_wifi_RSSI*1000);
        atApp_Wifi.status = WIFI_STATUS_Connected;
    }
    else{
        atApp_Wifi.collecting_wifi_RSSI = 0;
        sprintf(atApp_Wifi.connecting_SSID," ");
        sprintf(atApp_Wifi.connecting_Password," ");
        sprintf(atApp_Wifi.IP                 , "0.0.0.0");
        sprintf(atApp_Wifi.Gateway            , "0.0.0.0");
        sprintf(atApp_Wifi.Subnet             , "0.0.0.0");
        sprintf(atApp_Wifi.DNS                , "0.0.0.0");
        delay( atApp_Wifi.delaying_time_to_check_collecting_wifi_RSSI*1000);

    }
            
    if(atApp_Wifi.User_Mode == APP_USER_MODE_DEBUG)
    { 
        switch (atApp_Wifi.request)
        {
        case WIFI_REQUEST_Scanning:
            Serial.println("WIFI REQUEST Scanning");

        case WIFI_REQUEST_Connecting:
            Serial.println("WIFI REQUEST Connecting");

        case WIFI_REQUEST_Disconnecting:
            Serial.println("WIFI REQUEST Disconnecting");
        
        }
        
        // for scanning request
        Serial.println("Scanned networks:");
        Serial.println(atApp_Wifi.scanned_Wifi_SSIDs);

        // information
        Serial.printf("Information connecting wifi:\n");
        Serial.printf("Connecting RSSI:     %d dB\n",   atApp_Wifi.collecting_wifi_RSSI);
        Serial.printf("Connecting SSID:     ");         Serial.println(atApp_Wifi.connecting_SSID);
        Serial.printf("Connecting password: ");         Serial.println(atApp_Wifi.connecting_Password);
        Serial.printf("Connecting IP:       ");         Serial.println(atApp_Wifi.IP);
        Serial.printf("Connecting gateway:  ");         Serial.println(atApp_Wifi.Gateway);
        Serial.printf("Connecting subnet:   ");         Serial.println(atApp_Wifi.Subnet);
        Serial.printf("Connecting dns:      ");         Serial.println(atApp_Wifi.DNS);

        Serial.print("\nWifi status: ");
        switch (atApp_Wifi.status)
        {
        case WIFI_STATUS_Idle:
            Serial.println("Idle");
            break;

        case WIFI_STATUS_Scanning:
            Serial.println(" scanning");
            break;

        case WIFI_STATUS_Scan_Completed:
            Serial.println("completed scanning");
            break;

        case WIFI_STATUS_Connecting:
            Serial.println("Connecting");
            break;

        case WIFI_STATUS_Connected:
            Serial.println("connected");
            break;

        case WIFI_STATUS_Connect_Failed:
            Serial.println("failed to connect");
            break;

        case WIFI_STATUS_Connection_Lost:
            Serial.println("lost connection");
            break;

        case WIFI_STATUS_Disconnecting:
            Serial.println("Wifi is being disconnecting");
            break;

        case WIFI_STATUS_Disconnected:
            Serial.println("Wifi has disconnected");
            break;

        default:
            break;
        }
        Serial.println();
    }   

}
void  App_Wifi::App_Wifi_Suspend(){}
void  App_Wifi::App_Wifi_Resume(){}	  
void  App_Wifi::App_Wifi_End(){}
void atApp_Wifi_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_Wifi.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
void  App_Wifi::scan_Network()
{
    atApp_Wifi.scanned_Wifi_SSIDs_Number = WiFi.scanNetworks();
    atApp_Wifi.status = (Wifi_Status)WiFi.status();
    
    if (atApp_Wifi.scanned_Wifi_SSIDs_Number == 0) 
    { 
        
        sprintf(atApp_Wifi.scanned_Wifi_SSIDs,"No wifi available"); 
    }
    else 
    {   
        sprintf(atApp_Wifi.scanned_Wifi_SSIDs," ");
        for (int i = 0; i < atApp_Wifi.scanned_Wifi_SSIDs_Number; ++i) 
        {
            //insert index
            char buffer_number[2];
            sprintf(buffer_number,"%d.",i);
            strcat(atApp_Wifi.scanned_Wifi_SSIDs,buffer_number);
            //insert SSID
            strcat(atApp_Wifi.scanned_Wifi_SSIDs,WiFi.SSID(i).c_str());
            //insert RSSI
            char buffer_RSSI[4];
            sprintf(buffer_RSSI,"(%ddB) \n",WiFi.RSSI(i));
            strcat(atApp_Wifi.scanned_Wifi_SSIDs,buffer_RSSI);
            delay(10);
        }       
    }
    // Delay before scanning again
    delay(atApp_Wifi.scanning_Time_Delay*1000);
}
void  App_Wifi::connect()
{
    if( atApp_Wifi.ip_Mode ==  WIFI_IP_MODE_Static)
    {
        // Set your Static IP address
        IPAddress local_IP( atApp_Wifi.IP_Static[A], 
                            atApp_Wifi.IP_Static[B],
                            atApp_Wifi.IP_Static[C], 
                            atApp_Wifi.IP_Static[D]);
        // Set your Gateway IP address
        IPAddress gateway(  atApp_Wifi.Gateway_Static[A], 
                            atApp_Wifi.Gateway_Static[B],
                            atApp_Wifi.Gateway_Static[C],
                            atApp_Wifi.Gateway_Static[D]);

        IPAddress subnet(   atApp_Wifi.Subnet_Static[A],
                            atApp_Wifi.Subnet_Static[B],
                            atApp_Wifi.Subnet_Static[C],
                            atApp_Wifi.Subnet_Static[D]);

        IPAddress primaryDNS(   atApp_Wifi.DNS1_Static[A],
                                atApp_Wifi.DNS1_Static[B],
                                atApp_Wifi.DNS1_Static[C],
                                atApp_Wifi.DNS1_Static[D]);

        IPAddress secondaryDNS( atApp_Wifi.DNS2_Static[A],
                                atApp_Wifi.DNS2_Static[B],
                                atApp_Wifi.DNS2_Static[C], 
                                atApp_Wifi.DNS2_Static[D]);

        if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
            if(atApp_Wifi.User_Mode == APP_USER_MODE_DEBUG)
                Serial.println("    STA Failed to configure static IP");
        }
    }
    // strcpy(atApp_Wifi.ssid_To_Connect, WiFi.SSID(atApp_Wifi.wifi_SSID_Index_To_Connect).c_str());
    WiFi.begin( atApp_Wifi.ssid_To_Connect , atApp_Wifi.password_To_Connect );

    uint8_t count = 0;
    while (WiFi.status() != WL_CONNECTED) 
    {   
        delay(1000); 
        if (count >= atApp_Wifi.waiting_time_to_connect) break;
        else count++;
    }
}
void  App_Wifi::disconnect()
{
    WiFi.disconnect();  
    atApp_Wifi.status = (Wifi_Status)WiFi.status();
}
#endif