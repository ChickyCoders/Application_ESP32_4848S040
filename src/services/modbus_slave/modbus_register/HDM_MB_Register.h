#ifndef _HDM_MB_Register_
#define _HDM_MB_Register_

/* _____DEFINETIONS__________________________________________________________ */


enum HDM_REGISTER_INDEX
{
// Mode Operation
HDM_REGISTER_RW_MODE_OPERATION = 7001,              

/*
    Setting HDM 
*/
//Object temperature               
HDM_REGISTER_RW_LOW_LIMIT_TEMPERATURE,     
HDM_REGISTER_RW_HIGH_LIMIT_TEMPERATURE,     
//Power operating
HDM_REGISTER_RW_POWER,            
HDM_REGISTER_RW_LOW_LIMIT_POWER,            
HDM_REGISTER_RW_HIGH_LIMIT_POWER,            

/*
    Feedback parameter 
*/
HDM_REGISTER_R_TEMPERATURE 

};

#endif