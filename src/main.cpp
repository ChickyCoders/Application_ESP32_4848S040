// Template_Application_ESP32_V2.0

#include "../src/apps/atApp_ABC.h"
#include "../src/apps/atApp_Wifi.h"
#include "../src/apps/atApp_CP.h"
#include "../src/apps/atApp_MB_TCP_MA.h"
#include "../src/apps/atApp_MB_RTU_SL.h"
#include "../src/apps/atApp_MB_TCP_SL.h"
#include "../src/apps/atApp_INVT.h"
#include "../src/apps/atApp_ADE.h"
#include "../src/apps/atApp_CD.h"
#include "../src/apps/atApp_SHT30.h"
#include "../src/apps/atApp_SGP30.h"
#include "../src/apps/atApp_exHMI.h"
#include "../src/apps/atApp_DS18B20.h"
#include "../src/apps/atApp_HMI.h"
#include "../src/apps/atApp_DID.h"
#include "../src/apps/atApp_RTC.h"
#include "../src/apps/atApp_OTA.h"

#include "../src/apps/app_data_module/atApp_SNM.h"
#include "../src/apps/app_data_module/atApp_EMM.h"
#include "../src/apps/app_data_module/atApp_HDM.h"
#include "../src/apps/app_data_module/atApp_IDM.h"
#include "../src/apps/app_data_module/atApp_RDM.h"

void setup() {

Serial.begin(115200);
// Serial.printf("Flash size : %f",ESP.getFlashChipSize());


// uncomment to put the app in debug mod
  // atApp_ABC.Debug();
  // atApp_RTC.Debug();
  // atApp_Wifi.Debug();
  // atApp_MB_RTU_SL.Debug();
  // atApp_MB_TCP_MA.Debug();
  // atApp_MB_TCP_SL.Debug();
  // atApp_INVT.Debug();
  // atApp_CD.Debug();
  // atApp_SGP30.Debug();
  // atApp_SHT30.Debug();
  // atApp_ADE.Debug();
  // atApp_exHMI.Debug();
  // atApp_HMI.Debug();
  // atApp_OTA.Debug();

  // atApp_SNM.Debug();
  // atApp_DID.Debug();

  // atApp_CP.Debug();
  
//--------------------------------------------------------------------Tasks table ----------------------------------------------------------------------------------//     
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// || Creation           ||     Task function         ||     PC name                    || heap size  || Parameter || Priority  || Task handle          || CoreID   ||
  // xTaskCreatePinnedToCore(  atApp_ABC_Task_Func       , "atApp_ABC_Application"         ,  1000       ,     NULL    ,   1       , &Task_atApp_ABC       ,    0     );
  // xTaskCreatePinnedToCore(  atApp_RTC_Task_Func       , "atApp_RTC_Application"         ,  10000      ,     NULL    ,   1       , &Task_atApp_RTC       ,    0     );
  // xTaskCreatePinnedToCore(  atApp_CP_Task_Func        , "atApp_CP_Application"          ,  10000      ,     NULL    ,   1       , &Task_atApp_CP        ,    0     );
  // xTaskCreatePinnedToCore(  atApp_Wifi_Task_Func      , "atApp_Wifi_Application"        ,  10000      ,     NULL    ,   1       , &Task_atApp_Wifi      ,    1     );
  // xTaskCreatePinnedToCore(  atApp_MB_RTU_SL_Task_Func , "atApp_MB_RTU_SL_Application"   ,  10000      ,     NULL    ,   1       , &Task_atApp_MB_RTU_SL ,    1     );
  // xTaskCreatePinnedToCore(  atApp_MB_TCP_MA_Task_Func , "atApp_MB_TCP_MA_Application"   ,  1024       ,     NULL    ,   1       , &Task_atApp_MB_TCP_MA ,    1     );
  // xTaskCreatePinnedToCore(  atApp_MB_TCP_SL_Task_Func , "atApp_MB_TCP_SL_Application"   ,  10000      ,     NULL    ,   1       , &Task_atApp_MB_TCP_SL ,    1     );
  // xTaskCreatePinnedToCore(  atApp_SNM_Task_Func       , "atApp_SNM_Module_Application"  ,  5000       ,     NULL    ,   1       , &Task_atApp_SNM       ,    1     );
  // xTaskCreatePinnedToCore(  atApp_DID_Task_Func       , "atApp_DID_Application"         ,  10000      ,     NULL    ,   1       , &Task_atApp_DID       ,    1     );
  // xTaskCreatePinnedToCore(  atApp_INVT_Task_Func      , "atApp_INVT_Application"        ,  10000      ,     NULL    ,   1       , &Task_atApp_CP        ,    0     );
  // xTaskCreatePinnedToCore(  atApp_ADE_Task_Func       , "atApp_ADE_Application"         ,  10000      ,     NULL    ,   1       , &Task_atApp_ADE       ,    0     );
  // xTaskCreatePinnedToCore(  atApp_CD_Task_Func        , "atApp_CD_Application"          ,  10000      ,     NULL    ,   1       , &Task_atApp_CD        ,    0     );
  // xTaskCreatePinnedToCore(  atApp_SGP30_Task_Func     , "atApp_SGP30_Application"       ,  10000      ,     NULL    ,   1       , &Task_atApp_SGP30     ,    0     );
  // xTaskCreatePinnedToCore(  atApp_SHT30_Task_Func     , "atApp_SHT30_Application"       ,  10000      ,     NULL    ,   1       , &Task_atApp_SHT30     ,    0     );
  // xTaskCreatePinnedToCore(  atApp_exHMI_Task_Func     , "atApp_exHMI_Application"       ,  10000      ,     NULL    ,   1       , &Task_atApp_exHMI     ,    0     );
  xTaskCreatePinnedToCore(  atApp_HMI_Task_Func       , "atApp_HMI_Application"         ,  10000      ,     NULL    ,   2       , &Task_atApp_HMI       ,    0     );
  // xTaskCreatePinnedToCore(  atApp_DS18B20_Task_Func   , "atApp_DS18B20_Application"     ,  10000      ,     NULL    ,   1       , &Task_atApp_DS18B20   ,    0     );
  // xTaskCreatePinnedToCore(  atApp_OTA_Task_Func       , "atApp_OTA_Application"         ,  10000      ,     NULL    ,   1       , &Task_atApp_OTA       ,    1     );

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//


// Some tasks will be suspended after initting 
  // vTaskSuspend(Task_atApp_OTA);
  // vTaskSuspend(Task_atApp_MB_TCP_MA);
  // vTaskSuspend(Task_atApp_DID);
  // vTaskSuspend(Task_atApp_SNM);
}
void loop() {}
