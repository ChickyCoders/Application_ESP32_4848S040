#ifndef _General_MB_Register_
#define _General_MB_Register_

/* _____DEFINETIONS__________________________________________________________ */

#define Initial_value   0

enum GENERAL_REGISTER_INDEX
{

/*
 Modbus
*/
GENERAL_REGISTER_RW_MODBUS_RTU_ID   =  1,                    
GENERAL_REGISTER_RW_MODBUS_RTU_BAUDRATE,                
GENERAL_REGISTER_RW_MODBUS_RTU_CHECK_NUMBER,            
//Time interval returns  for data to be after received command
GENERAL_REGISTER_RW_MODBUS_RTU_TIME_DELAY_FOR_RETURN_DA,  
// MODBUS TCP/IP: A.B.C.D
GENERAL_REGISTER_R_MODBUS_TCP_IP_A,                     
GENERAL_REGISTER_R_MODBUS_TCP_IP_B,                     
GENERAL_REGISTER_R_MODBUS_TCP_IP_C,                     
GENERAL_REGISTER_R_MODBUS_TCP_IP_D,                     
// eg: 502 for modbus
GENERAL_REGISTER_R_MODBUS_TCP_IP_PORT,                              
                                       

/*
 Device identification
*/

GENERAL_REGISTER_R_DEVICE_TYPE,          
//ID of device in it's LCM          
GENERAL_REGISTER_RW_DEVICE_ID,                         
//The level of this devide           
GENERAL_REGISTER_R_DEVICE_LEVEL,       

/*
 Control
*/

GENERAL_REGISTER_RW_LAST_LEVEL_CONTROL,
GENERAL_REGISTER_RW_CONTROL_COMMAND_CCA,                               
GENERAL_REGISTER_R_FAULT_CODE,   
                                     
/*
 Condition operating
*/
 GENERAL_REGISTER_R_TEMPERATURE,                                       
 GENERAL_REGISTER_R_HUMIDITY,                                          
};

#endif