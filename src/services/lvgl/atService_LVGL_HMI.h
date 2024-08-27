/**
@file
Service for communicating with OP320A&S SNM over RS232/485 (via RTU protocol).
*/
/*
  Service_atService_LVGL_HMI.h - Arduino library for communicating with OP320A&S SNM
  over RS232/485 (via RTU protocol).

  Library:: chickyPig_OP320_V1

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com

#1 configure LVGL
copy lv_conf_template.h and rename to lv_conf.h. Open file and change #if 0 /*Set it to "1" to enable content*/
//#if 1 /*Set it to "1" to enable content*/ change the LV_TICK_CUSTOM to 1

//#2 configure TFT
// #include <User_Setups/Setup24_ST7789.h>            // Setup file configured for ST7789 240 x 240 and copy the below code 
/*

#define ST7789_DRIVER     // Configure all registers

#define TFT_WIDTH  240
#define TFT_HEIGHT 240

#define TFT_RGB_ORDER TFT_BGR  // Colour order Blue-Green-Red

#define TFT_MISO 19
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS    32  // Chip select control pin
#define TFT_DC    26  // Data Command control pin
#define TFT_RST   33  // Reset pin (could connect to RST pin)

// #define SPI_FREQUENCY  20000000
  #define SPI_FREQUENCY  27000000 // Actually sets it to 26.67MHz = 80/3
*/
#ifndef _Service_atService_LVGL_HMI_
#define _Service_atService_LVGL_HMI_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "../Service.h"
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "lvgl.h"
#include "atService_atButtons_LEDs_PCF8575.h"
#include "Arduino.h"
/* _____DEFINETIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
/*Change to your screen resolution*/
static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 260;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];

TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */
/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1 , area->y1 , w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}
byte my_button_read()
{
    if (atService_Buttons_LEDs_PCF8575.Menu == 1 )   return 0;
    if (atService_Buttons_LEDs_PCF8575.Up == 1 )     return 1;
    if (atService_Buttons_LEDs_PCF8575.Ok == 1 )     return 2;
    if (atService_Buttons_LEDs_PCF8575.Down == 1 )   return 3;
    if (atService_Buttons_LEDs_PCF8575.Back == 1 )   return 4;
    if (atService_Buttons_LEDs_PCF8575.Alarm == 1 )  return 5;
    return 255;
}
void button_read(lv_indev_drv_t * drv, lv_indev_data_t*data){
    static uint32_t last_btn = 0;   /*Store the last pressed button*/
    int btn_pr = my_button_read();     /*Get the ID (0,1,2...) of the pressed button*/
    if(btn_pr >= 0) {               /*Is there a button press? (E.g. -1 indicated no button was pressed)*/
       last_btn = btn_pr;           /*Save the ID of the pressed button*/
       data->state = LV_INDEV_STATE_PRESSED;  /*Set the pressed state*/
    } else {
       data->state = LV_INDEV_STATE_RELEASED; /*Set the released state*/
    }
    data->btn_id = last_btn;            /*Save the last button*/
}
/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the 
 */
class Service_lvgl : public Service
{
public:
    Service_lvgl();
    ~Service_lvgl();

protected:
     
private:
    static void  Service_lvgl_Start();
    static void  Service_lvgl_Execute();    
    static void  Service_lvgl_End();
} atService_LVGL_HMI ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_lvgl::Service_lvgl(/* args */)
{
    _Start_User      = *Service_lvgl_Start;
    _Execute_User    = *Service_lvgl_Execute;
    _End_User        = *Service_lvgl_End;

    // change the ID of Service
    ID_Service = 2;
    // change the Service name
    Name_Service = (char*)"HMI lvgl Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_lvgl::~Service_lvgl()
{
    
}
/**
 * This start function will init some critical function 
 */
void  Service_lvgl::Service_lvgl_Start()
{
    
    atService_Buttons_LEDs_PCF8575.Run_Service();
    // atService_Buttons_LEDs_PCF8575.Debug();
    //Set up the display
	tft.init();
    // tft.setSwapBytes(true);
	// tft.setRotation(1);
	lv_init();
	lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );
    
    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    //init button input device lvgl
    lv_disp_drv_register(&disp_drv);
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);      /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_BUTTON;
    indev_drv.read_cb = button_read;
    lv_indev_t * my_indev = lv_indev_drv_register(&indev_drv);
    /*Assign buttons to points on the screen*/
    static const lv_point_t btn_points[6] = {
            {230 , 250},   /*Button 0 -> x:10; y:10*/
            {130 , 250},
            {180 , 250},  /*Button 1 -> x:40; y:100*/
            {90  , 250},
            {60  , 250},
            {10  , 250},
    };
    lv_indev_set_button_points(my_indev, btn_points);
}  

/**
 * Execute fuction of SNM app
 */
void  Service_lvgl::Service_lvgl_Execute()
{   
    lv_timer_handler(); /* let the GUI do its work */
    atService_Buttons_LEDs_PCF8575.Run_Service();
    if(atService_LVGL_HMI.User_Mode == SER_USER_MODE_DEBUG)
    {
        if (my_button_read() != 255)
        {
            Serial.printf("Button %d Pressed",my_button_read());
        }
    }   
}    
void  Service_lvgl::Service_lvgl_End(){}

#endif


