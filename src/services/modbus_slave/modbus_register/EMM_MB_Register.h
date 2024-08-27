#ifndef _EMM_MB_Register_
#define _EMM_MB_Register_

/* _____DEFINETIONS__________________________________________________________ */

enum EMM_REGISTER_INDEX
{

EMM_REGISTER_RW_ALERT = 4001,                

/*
 Voltage Parameter
*/

//Voltage Parameter of Phase A
EMM_REGISTER_R_VOLTAGE_PHASE_A,              
//Voltage Parameter of Phase B
EMM_REGISTER_R_VOLTAGE_PHASE_B,              
//Voltage Parameter of Phase C
EMM_REGISTER_R_VOLTAGE_PHASE_C,              

/*
 Current Parameter
*/

//Current Parameter of Phase A
EMM_REGISTER_R_CURRENT_PHASE_A,              
//Current Parameter of Phase B
EMM_REGISTER_R_CURRENT_PHASE_B,              
//Current Parameter of Phase C
EMM_REGISTER_R_CURRENT_PHASE_C,              

/*
 Power Parameter
*/

//Active Power(P)
EMM_REGISTER_R_ACTIVE_POWER,                 
//Reactive Power (Q)
EMM_REGISTER_R_REACTIVE_POWER,               
//Apparent Power (S)
EMM_REGISTER_R_APPARENT_POWER,               

/*
 Other Parameter
*/

//Cosphi
EMM_REGISTER_R_COSPHI,                       
//Frequency
EMM_REGISTER_R_FREQUENCY,

/*
 Control
*/

EMM_REGISTER_RW_CONTROL_RELAY,

/*
 Feedback state
*/
EMM_REGISTER_R_APTOMAT_FEEDBACK,
EMM_REGISTER_R_CONTACTOR_FEEDBACK,
EMM_REGISTER_R_RELAY_FEEDBACK
};

#endif