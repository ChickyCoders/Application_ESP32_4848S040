#ifndef _IDM_MB_Register_
#define _IDM_MB_Register_

/* _____DEFINETIONS__________________________________________________________ */


enum IDM_REGISTER_INDEX
{
/*
    Control Inverter
*/

// Name Of Inverter Used
IDM_REGISTER_R_INVERTER_TYPE = 5001,     
IDM_REGISTER_RW_DIRECTION_RUN,     
// Communication setting frequency  
IDM_REGISTER_RW_SET_FREQUENCY,      

/*
    Data of Inverter 
*/
IDM_REGISTER_R_OPERATION_FREQUENCY,  
IDM_REGISTER_R_INPUT_VOLTAGE,     
IDM_REGISTER_R_INPUT_CURRENT,    
IDM_REGISTER_R_OUTPUT_VOLTAGE,      
IDM_REGISTER_R_OUTPUT_CURRENT,             
IDM_REGISTER_R_FAULT_CODE        
};

#endif