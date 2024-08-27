/**
@file
*/
/*
  Service_atService_EEPROM.h

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Service_atService_EEPROM_
#define _Service_atService_EEPROM_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "../Service.h"
#include <EEPROM.h>
/* _____DEFINETIONS__________________________________________________________ */
#define EEPROM_SIZE	2150
/* _____GLOBAL VARIABLES_____________________________________________________ */

/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Service class is the Service to manage the 
 */

class Service_EEPROM : public Service
{
public:
    Service_EEPROM();
    ~Service_EEPROM();

    uint8_t Read(int address);
    void Write(int address, uint8_t val);

    uint32_t ReadInt(int address);
    size_t WriteInt(int address, uint32_t value);

    String readString (int address);
    size_t WriteString(int address, const char* value);

    bool Commit();
protected:
     
private:
    static void  Service_EEPROM_Start();
    static void  Service_EEPROM_Execute();    
    static void  Service_EEPROM_End();
} atService_EEPROM ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_EEPROM::Service_EEPROM(/* args */)
{
    _Start_User      = *Service_EEPROM_Start;
    _Execute_User    = *Service_EEPROM_Execute;
    _End_User        = *Service_EEPROM_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char*)"EP Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_EEPROM::~Service_EEPROM()
{
    
}
/**
 * This start function will init some critical function 
 */
void  Service_EEPROM::Service_EEPROM_Start()
{
    EEPROM.begin(EEPROM_SIZE);
}  

/**
 * Execute fuction of SNM app
 */
void  Service_EEPROM::Service_EEPROM_Execute()
{   
    if(atService_EEPROM.User_Mode == SER_USER_MODE_DEBUG)
    {
        
    }   
}    
void  Service_EEPROM::Service_EEPROM_End(){}
uint8_t Service_EEPROM::Read(int address)
{
    return EEPROM.read(address);
}
void Service_EEPROM::Write(int address, uint8_t val)
{
    EEPROM.write(address,val);
}

uint32_t Service_EEPROM::ReadInt(int address)
{
    return EEPROM.readInt(address);
}
size_t Service_EEPROM::WriteInt(int address, uint32_t value)
{
    return EEPROM.writeUInt(address,value);
}
bool Service_EEPROM::Commit()
{
    return EEPROM.commit();
}
size_t Service_EEPROM::WriteString(int address, const char* value)
{
    return EEPROM.writeString(address,value);
}
String Service_EEPROM::readString (int address)
{
    return EEPROM.readString(address);
}
#endif


