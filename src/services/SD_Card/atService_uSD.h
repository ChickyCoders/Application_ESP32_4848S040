/**
@file
*/
/*
  Service_atService_uSD.h

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/
#ifndef _Service_atService_uSD_
#define _Service_atService_uSD_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "../Service.h"
#include"Arduino.h"
#include "SD.h"
#include "FS.h"
#include "SPI.h"
#include "../PCF8575/atService_PCF8575.h"
#include "../SPI/atService_VSPI.h"
/* _____DEFINETIONS__________________________________________________________ */
#define CS_PIN 0
#ifndef YES 
#define YES 0
#define NO  1
#endif
/* _____GLOBAL VARIABLES_____________________________________________________ */

/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the 
 */
class Service_uSD : public Service
{
public:
  Service_uSD();
  ~Service_uSD();
  
  bool uSD_plugging = NO;

  void listDir(const char * dirname, uint8_t levels);
  void createDir(const char * path);
  void removeDir(const char * path);
  void readFile(const char * path);
  void writeFile(const char * path, const char * message);
  void appendFile( const char * path, const char * message);
  void renameFile( const char * path1, const char * path2);
  void deleteFile( const char * path);

protected:
     
private:
  static void  Service_uSD_Start();
  static void  Service_uSD_Execute();    
  static void  Service_uSD_End();
} atService_uSD ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_uSD::Service_uSD(/* args */)
{
    _Start_User      = *Service_uSD_Start;
    _Execute_User    = *Service_uSD_Execute;
    _End_User        = *Service_uSD_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char*)"uSD Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_uSD::~Service_uSD()
{
    
}
/**
 * This start function will init some critical function 
 */
void  Service_uSD::Service_uSD_Start()
{
  //initialize Services
  // atService_PCF8575.Debug();
  atService_PCF8575.Run_Service();
  atService_VSPI.Run_Service();

  //setup uSD input pin
  atService_PCF8575.Pin_Modes[PCF8575_PIN_P0] = MODE_PCF8575_Input;

  //int SD
  atService_VSPI.check_In();
  if(!SD.begin(CS_PIN)){
    if(atService_uSD.User_Mode == SER_USER_MODE_DEBUG)
      Serial.println("Card Mount Failed");
  }
  atService_VSPI.check_Out();
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE){
    if(atService_uSD.User_Mode == SER_USER_MODE_DEBUG)
      Serial.println("No SD card attached");
  }
  
  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
    if(atService_uSD.User_Mode == SER_USER_MODE_DEBUG)
      Serial.println("MMC");
  } else if(cardType == CARD_SD){
    if(atService_uSD.User_Mode == SER_USER_MODE_DEBUG)
      Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
    if(atService_uSD.User_Mode == SER_USER_MODE_DEBUG)
      Serial.println("SDHC");
  } else {
    if(atService_uSD.User_Mode == SER_USER_MODE_DEBUG)
      Serial.println("UNKNOWN");
  }

  // atService_uSD.writeFile("/abc.txt", "Hello ");
  atService_uSD.appendFile("/abc.txt", "World!\n");
  atService_uSD.appendFile("/abc.txt", "12321321321312\n");
  atService_uSD.readFile("/abc.txt");
}  

/**
 * Execute fuction of SNM app
 */
void  Service_uSD::Service_uSD_Execute()
{   
  atService_PCF8575.Run_Service();
  if(atService_uSD.User_Mode == SER_USER_MODE_DEBUG)
  {
    //check uSD plugging
    atService_uSD.uSD_plugging = atService_PCF8575.Pin_Vals[PCF8575_PIN_P0];
    if (atService_uSD.uSD_plugging == YES)
    {
      //show space of uSD
      Serial.printf("Total space uSD: %lluMB\n", SD.totalBytes() / (1024 * 1024));
      Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
    }
    else Serial.printf("No SD Card attached  \n");
  }   
}    
void  Service_uSD::Service_uSD_End(){}

//list folder and file in uSD
void Service_uSD::listDir(const char * dirname, uint8_t levels){
  Serial.printf("Listing directory: %s\n", dirname);

  File root = SD.open(dirname);
  if(!root){
    Serial.println("Failed to open directory");
    return;
  }
  if(!root.isDirectory()){
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while(file){
    if(file.isDirectory()){
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if(levels){
        listDir(file.name(), levels -1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}
//create folder
void Service_uSD::createDir(const char * path){
  Serial.printf("Creating Dir: %s\n", path);
  if(SD.mkdir(path)){
    Serial.println("Dir created");
  } else {
    Serial.println("mkdir failed");
  }
}
// erase folder
void Service_uSD::removeDir( const char * path){
  Serial.printf("Removing Dir: %s\n", path);
  if(SD.rmdir(path)){
    Serial.println("Dir removed");
  } else {
    Serial.println("rmdir failed");
  }
}

void Service_uSD::readFile( const char * path){
  Serial.printf("Reading file: %s\n", path);

  File file = SD.open(path);
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}
//erase old data and write message to file
void Service_uSD::writeFile( const char * path, const char * message){
  Serial.printf("Writing file: %s\n", path);

  File file = SD.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}
//keep old data and write more message to file
void Service_uSD::appendFile(const char * path, const char * message){
  Serial.printf("Appending to file: %s\n", path);

  File file = SD.open(path, FILE_APPEND);
  if(!file){
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)){
      Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void Service_uSD::renameFile(const char * path1, const char * path2){
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (SD.rename(path1, path2)) {
    Serial.println("File renamed");
  } else {
    Serial.println("Rename failed");
  }
}

void Service_uSD::deleteFile(const char * path){
  Serial.printf("Deleting file: %s\n", path);
  if(SD.remove(path)){
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}

#endif


