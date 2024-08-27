#ifndef SOURCES_H
#define SOURCES_H
#include "lvgl.h"
#include "Arduino.h"

#ifdef HMI_Lite
    #define ICON_WIFI_POS_X         0
    #define ICON_SD_CARD_POS_X      15
    #define ICON_MODBUS_POS_X       30
    #define ICON_WARNING_POS_X      45
    #define ICON_TIME_POS_X         120
    #define ICON_IP_DEVICE_POS_X    75
    #define ICON_WIFI_POS_Y         0
    #define ICON_SD_CARD_POS_Y      0
    #define ICON_MODBUS_POS_Y       0
    #define ICON_WARNING_POS_Y      0
    #define ICON_TIME_POS_Y         0
    #define ICON_IP_DEVICE_POS_Y    0
    #define ICON_TIME_W             40
    #define ICON_SIZE               15
    #define ROLLER_ROW_COUNT        2
    #define ROLLER_WIDTH            150
    #define ROLLER_POS_X            0
    #define ROLLER_POS_Y            5
    #define LABEL_POS_X             30
    #define LABEL_POS_Y             30
    #define LOAD_PAGE_TIME          50 //ms
#endif
#ifdef HMI
    #define ICON_WIFI_POS_X         0
    #define ICON_SD_CARD_POS_X      20
    #define ICON_MODBUS_POS_X       40
    #define ICON_WARNING_POS_X      60
    #define ICON_TIME_POS_X         200
    #define ICON_IP_DEVICE_POS_X    150
    #define ICON_IP_DEVICE_POS_Y    0
    #define ICON_WIFI_POS_Y         0
    #define ICON_SD_CARD_POS_Y      0
    #define ICON_MODBUS_POS_Y       0
    #define ICON_WARNING_POS_Y      0
    #define ICON_TIME_POS_Y         0
    #define ICON_TIME_W             40
    #define ICON_SIZE               20
    #define ROLLER_ROW_COUNT        5
    #define ROLLER_WIDTH            180
    #define ROLLER_POS_X            0
    #define ROLLER_POS_Y            5
    #define LABEL_POS_X             70
    #define LABEL_POS_Y             70
    #define LOAD_PAGE_TIME          50 //ms
#endif

// enum ICON_ACTIVE
// {
//     OFF,
//     ON = 1
// };
typedef struct Notified_Bar
{
    int hour = 14, minute = 10;
    bool wifi_active        = ON;
    bool warning_active     = ON;
    bool SD_active          = ON;
    bool modbus_active      = ON;
    uint8_t IP[4] = {192,168,1,101};
};
typedef struct Notified_Bar_old
{
    bool wifi_active        = OFF;
    bool warning_active     = OFF;
    bool SD_active          = OFF;
    bool modbus_active      = OFF;
    uint8_t IP[4] = {192,168,1,101};
    int minute = 14;
    int hour = 10;
};

class Sources
{
public:
    
	int    get_roller_selected(lv_obj_t *roller);

    Notified_Bar Notified_Bar_1;
	lv_obj_t *roller_1;

protected:
    void   setup_button(lv_obj_t *button, int pos_x, int pos_y, char * button_label_str);
    char   char_time[10];

    lv_obj_t *Screen;
    lv_obj_t *Screen_label_ip_device;
    lv_obj_t *Screen_label_wifi;
    lv_obj_t *Screen_label_warning;
    lv_obj_t *Screen_label_SD;
    lv_obj_t *Screen_label_modbus;
    lv_obj_t *Screen_label_time;

    lv_obj_t *btn_UP;
    lv_obj_t *btn_DOWN;
    lv_obj_t *btn_BACK;
    lv_obj_t *btn_OK;

    #ifdef HMI
    lv_obj_t *btn_MENU;
    lv_obj_t *btn_ALARM;
    #endif
    lv_obj_t *label_screen;

    Notified_Bar_old   Notified_Bar_old_1;
    
    void   setup_label(lv_obj_t *label, char* label_text,int pos_x, int pos_y, int width,int height);
    void   setup_label(lv_obj_t *label, char* label_text);
    void   setup_label(lv_obj_t *label, char* label_text,int pos_x, int pos_y, int width,int height, int align);
    void   setup_roller(lv_obj_t *roller, char* option,int row_count, int align,int width, int pos_x, int pos_y,uint8_t selected);
    void   setup_roller(lv_obj_t *roller, char* option);
    void   create_notified_bar  (lv_obj_t *screen);

    void   render_modbus_icon(lv_obj_t *icon_label, bool icon_active, int pos_x,int pos_y);
    void   render_modbus_icon(lv_obj_t *icon_label, bool icon_active);

    void   render_SD_Card_icon(lv_obj_t *icon_label, bool icon_active, int pos_x,int pos_y);
    void   render_SD_Card_icon(lv_obj_t *icon_label, bool icon_active);

    void   render_wifi_icon(lv_obj_t *icon_label, bool icon_active, int pos_x,int pos_y);
    void   render_wifi_icon(lv_obj_t *icon_label, bool icon_active);

    void   render_warning_icon(lv_obj_t *icon_label, bool icon_active, int pos_x,int pos_y);
    void   render_warning_icon(lv_obj_t *icon_label, bool icon_active);

    void   render_time(lv_obj_t *icon_label, int hour, int minute, int pos_x,int pos_y);
    void   render_time(lv_obj_t *icon_label, int hour, int minute);

    void   create_buttons(lv_obj_t *object); 

    void   render_ip_device(lv_obj_t *icon_label, uint8_t IP[4], int pos_x,int pos_y);
    void   render_ip_device(lv_obj_t *icon_label, uint8_t IP[4]);


    

private:
    /* data */

};
void Sources::setup_button( lv_obj_t *button,int pos_x, int pos_y, char * button_label_str)
{
    lv_obj_set_pos(button, pos_x, pos_y);
	lv_obj_set_size(button, 30, 15);

	//Write style state: LV_STATE_DEFAULT for style_screen_btn
	static lv_style_t style_button ;
	if (style_button.prop_cnt > 1)
		lv_style_reset(&style_button);
	else
		lv_style_init(&style_button);
    // lv_style_set_radius(&style_button, 5);
    // lv_style_set_bg_color(&style_button, lv_color_make(0x21, 0x95, 0xf6));
    // lv_style_set_bg_grad_color(&style_button, lv_color_make(0x21, 0x95, 0xf6));
    // lv_style_set_bg_grad_dir(&style_button, LV_GRAD_DIR_VER);
    // lv_style_set_bg_opa(&style_button, 255);
    // lv_style_set_shadow_color(&style_button, lv_color_make(0x21, 0x95, 0xf6));
    // lv_style_set_shadow_opa(&style_button, 255);
    // lv_style_set_border_color(&style_button, lv_color_make(0x21, 0x95, 0xf6));
    // lv_style_set_border_width(&style_button, 0);
    // lv_style_set_border_opa(&style_button, 255);
    // lv_obj_add_style(button, &style_button, LV_PART_MAIN|LV_STATE_DEFAULT);

	lv_obj_t *btn_label;
	btn_label = lv_label_create(button);
    lv_label_set_text(btn_label, button_label_str);
    // lv_obj_set_style_text_color(btn_label, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(btn_label, &lv_font_montserrat_8, LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_all(button, 0, LV_STATE_DEFAULT);
    lv_obj_align(btn_label, LV_ALIGN_CENTER, 0, 0);
}
void Sources::setup_label(lv_obj_t *label, char* label_text,int pos_x, int pos_y, int width,int height, int align)
{
	lv_obj_set_pos(label, pos_x, pos_y);
	lv_obj_set_size(label, width, height);
    lv_label_set_recolor(label, true);
	lv_label_set_text(label, label_text);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_12, LV_STATE_DEFAULT);
	lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(label, align, 0);
}
void Sources::setup_label(lv_obj_t *label, char* label_text,int pos_x, int pos_y, int width,int height)
{
	lv_obj_set_pos(label, pos_x, pos_y);
	lv_obj_set_size(label, width, height);
    lv_label_set_recolor(label, true);
	lv_label_set_text(label, label_text);
	lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
}
void Sources::setup_label(lv_obj_t *label, char* label_text)
{
    lv_label_set_recolor(label, true);
	lv_label_set_text(label, label_text);
	lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
}
void Sources::setup_roller(lv_obj_t *roller, char* option,int row_count, int align,int width, int pos_x, int pos_y,uint8_t selected)
{
	 static lv_style_t style_sel;
    lv_style_init(&style_sel);
    lv_style_set_text_font(&style_sel, &lv_font_montserrat_12);
	lv_roller_set_options(roller, option, LV_ROLLER_MODE_NORMAL);
    lv_obj_add_style(roller, &style_sel, LV_PART_SELECTED);
    lv_roller_set_visible_row_count(roller, row_count);
    lv_obj_set_width(roller, width);
	lv_obj_align(roller, align, pos_x, pos_y);
    lv_roller_set_selected(roller, selected, LV_ANIM_OFF);
}
void Sources::setup_roller(lv_obj_t *roller, char* option)
{
	lv_roller_set_options(roller, option, LV_ROLLER_MODE_NORMAL);
}

/*
Create notified bar for screen: icon wifi, bluetooth, warning, modbus active, SD Card, time
*/
void   Sources::create_notified_bar(lv_obj_t *screen)
{

	//create font wifi
	Screen_label_wifi = lv_label_create(screen);
	//create font warning
	Screen_label_warning = lv_label_create(screen);
	//create font modbus
	Screen_label_modbus = lv_label_create(screen);
	//create font SD
	Screen_label_SD = lv_label_create(screen);
	//create label time
	Screen_label_time = lv_label_create(screen);  


}
void   Sources::render_modbus_icon(lv_obj_t *icon_label, bool icon_active, int pos_x,int pos_y)
{
    if(icon_active == ON)
	{
		setup_label(icon_label,LV_SYMBOL_REFRESH, pos_x,pos_y,ICON_SIZE,ICON_SIZE);
	}
	else setup_label(icon_label,"  ",pos_x,pos_y,ICON_SIZE,ICON_SIZE);
}
void   Sources::render_modbus_icon(lv_obj_t *icon_label, bool icon_active)
{
    if(icon_active == ON)
	{
		setup_label(icon_label,LV_SYMBOL_REFRESH);
	}
	else setup_label(icon_label,"  ");
}
void   Sources::render_SD_Card_icon(lv_obj_t *icon_label, bool icon_active, int pos_x,int pos_y)
{
    if(icon_active == ON)
	{
		setup_label(icon_label,LV_SYMBOL_SD_CARD, pos_x,pos_y,ICON_SIZE,ICON_SIZE);
	}
	else setup_label(icon_label,"  ",pos_x,pos_y,ICON_SIZE,ICON_SIZE);
}
void   Sources::render_SD_Card_icon(lv_obj_t *icon_label, bool icon_active)
{
    if(icon_active == ON)
	{
		setup_label(icon_label,LV_SYMBOL_SD_CARD);
	}
	else setup_label(icon_label,"  ");
}
void   Sources::render_wifi_icon(lv_obj_t *icon_label, bool icon_active, int pos_x,int pos_y)
{
    if(icon_active == ON)
	{
		setup_label(icon_label,LV_SYMBOL_WIFI, pos_x,pos_y,ICON_SIZE,ICON_SIZE);
	}
	else setup_label(icon_label,"  ",pos_x,pos_y,ICON_SIZE,ICON_SIZE);
}
void   Sources::render_wifi_icon(lv_obj_t *icon_label, bool icon_active)
{
    if(icon_active == ON)
	{
		setup_label(icon_label,LV_SYMBOL_WIFI);
	}
	else setup_label(icon_label,"  ");
}
void   Sources::render_warning_icon(lv_obj_t *icon_label, bool icon_active, int pos_x,int pos_y)
{
    if(icon_active == ON)
	{
		setup_label(icon_label,LV_SYMBOL_WARNING, pos_x,pos_y,ICON_SIZE,ICON_SIZE);
	}
	else setup_label(icon_label,"  ",pos_x,pos_y,ICON_SIZE,ICON_SIZE);
}
void   Sources::render_warning_icon(lv_obj_t *icon_label, bool icon_active)
{
    if(icon_active == ON)
	{
		setup_label(icon_label,LV_SYMBOL_WARNING);
	}
	else setup_label(icon_label,"  ");
}
void   Sources::render_time(lv_obj_t *icon_label, int hour, int minute, int pos_x,int pos_y)
{
    char temp[50];
    sprintf(temp,"%d:%d",hour,minute);
    setup_label(icon_label,temp,pos_x,pos_y,40,ICON_SIZE);
}
void   Sources::render_time(lv_obj_t *icon_label, int hour, int minute)
{
    char temp[50];
    sprintf(temp,"%d:%d",hour,minute);
    setup_label(icon_label,temp);
}
void   Sources::render_ip_device(lv_obj_t *icon_label,uint8_t IP[4], int pos_x,int pos_y)
{
    char temp[50];
    sprintf(temp,"%d.%d.%d.%d",IP[0],IP[1],IP[2],IP[3]);
    setup_label(icon_label,temp,pos_x,pos_y,100,ICON_SIZE);
}
void   Sources::render_ip_device(lv_obj_t *icon_label,uint8_t IP[4])
{
    char temp[50];
    sprintf(temp,"%d.%d.%d.%d",IP[0],IP[1],IP[2],IP[3]);
    setup_label(icon_label,temp);
}

int    Sources::get_roller_selected(lv_obj_t *roller)
{
    return lv_roller_get_selected(roller);
}
void   Sources::create_buttons(lv_obj_t *Object)
{
#ifdef HMI_Lite
    btn_BACK= lv_btn_create(Object);
    setup_button(btn_BACK,5,85,"BACK");
	//Write codes screen_btn_UP
	btn_UP = lv_btn_create(Object);
	setup_button(btn_UP,45,85,"UP");
	//Write codes screen_btn_DOWN
	btn_DOWN = lv_btn_create(Object);
	setup_button(btn_DOWN,85,85,"DOWN");
	//Write codes screen_btn_OK
	btn_OK = lv_btn_create(Object);
	setup_button(btn_OK,125,85,"OK");
#endif
#ifdef HMI
    btn_MENU = lv_btn_create(Object);
    setup_button(btn_MENU,5,245,"MENU");
    //Write code button UP
    btn_UP = lv_btn_create(Object);
    setup_button(btn_UP,85,245,"UP");
    //Write code button BACK
    btn_BACK= lv_btn_create(Object);
    setup_button(btn_BACK,45,245,"BACK");
    //Write code button DOWN
    btn_DOWN= lv_btn_create(Object);
    setup_button(btn_DOWN,125,245,"DOWN");
    //Write code button OK
    btn_OK = lv_btn_create(Object);
    setup_button(btn_OK,165,245,"OK");
    //Write code button ALARM
    btn_ALARM = lv_btn_create(Object);
    setup_button(btn_ALARM,205,245,"ALARM");
#endif
}
#endif
