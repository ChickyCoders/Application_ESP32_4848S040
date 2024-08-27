/**
@file
Arduino library for communicating with GD200 Inverter over RS/485 (via RTU protocol).
*/
/*

  INVT_GD200A_V1.h - Arduino library for communicating with OP320A&S HMI
  over RS232/485 (via RTU protocol).

  Library:: INVT_GD200A_V1

  This version sofware driver is dev for GD200 series of INVT inverter. Prequisites is
  P00.01 = 2;
  P00.06 = 8;
  P00.17 = 1 ;// if the load is low
  p02.01 = 5.5;// Load Power
  p06.04 = 5 ;
  P14.00 = 3; //MODBUS_INVT_ADDRESS 
  P14.01 = 3;
  P14.02 = 1;
  P14.03 = 0;
  _RW_ characteristics means the function is with read and write characteristics
  _R_ characteristic can only read other than write 
  _W_ characteristic can only write other than read
  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef INVT_GD200A_DEFINES_h
#define INVT_GD200A_DEFINES_h



/* _____DEFINETIONS__________________________________________________________ */
// time delay between 2 command
#if !defined(Time_Delay)
#define Time_Delay
#define Time_Delay_5ms 5 // >= P14.03
#define Time_Delay_50ms 50
#define Time_Delay_100ms 100
#define Time_Delay_500ms 500
#endif // Time_Delay

// the fault type instruction
enum Fault_Type_Instruction
{
  
  #define	FAULT1	1 
  #define	FAULT2	2
  #define	FAULT3	3
  #define	FAULT4	4
  #define	FAULT5	5
  #define	FAULT6	6
  #define	FAULT7	7
  #define	FAULT8	8
  #define	FAULT9	9
  #define	FAULT10	10
  #define	FAULT11	11
  #define	FAULT12	12
  #define	FAULT13	13
  #define	FAULT14	14
  #define	FAULT15	15
  #define	FAULT16	16
  #define	FAULT17	17
  #define	FAULT18	18
  #define	FAULT19	19
  #define	FAULT20	20
  #define	FAULT21	21
  #define	FAULT22	22
  #define	FAULT23	23
  #define	FAULT24	24
  #define	FAULT25	25
  #define	FAULT26	26
  #define	FAULT27	27
  #define	FAULT28	28
  #define	FAULT29	29
  #define	FAULT30	30
  #define	FAULT31	31
  #define	FAULT32	32
  #define	FAULT33	33
  #define	FAULT34	34
  #define	FAULT35	35
  #define	FAULT36	36
};

/**
 * the fault type instruction
 * These defines are fault instruction in char* and used
 */ 
enum Fault_Type_Instruction_Code
{
  #define FAULT0_Char  (char*)"NOFAULT\n"
  #define FAULT1_Char  (char*)"[Error] - IGBT U phase protection (OUt1)\n"
  #define FAULT2_Char  (char*)"[Error] - IGBT V phase protection (OUt2)\n"
  #define FAULT3_Char  (char*)"[Error] - IGBT W phase protection (OUt3)\n"
  #define FAULT4_Char  (char*)"[Error] - Over current phase 1 (OC1)\n"
  #define FAULT5_Char  (char*)"[Error] - Over current phase 2 (OC2)\n"
  #define FAULT6_Char  (char*)"[Error] - Over current phase 3 (OC3)\n"
  #define FAULT7_Char  (char*)"[Error] - Over voltage phase 1 (OV1)\n"
  #define FAULT8_Char  (char*)"[Error] - Over voltage phase 2 (OV2)\n"
  #define FAULT9_Char  (char*)"[Error] - Over voltage phase 3 (OV3)\n"
  #define FAULT10_Char (char*)"[Error] - Under voltage (UV)\n"
  #define FAULT11_Char (char*)"[Error] - Motor overload (OL1)\n"
  #define FAULT12_Char (char*)"[Error] - The inverter overload (OL2)\n"
  #define FAULT13_Char (char*)"[Error] - Input side phase loss (SPI)\n"
  #define FAULT14_Char (char*)"[Error] - Output side phase loss (SPO)\n"
  #define FAULT15_Char (char*)"[Error] - Overheat of the rectifier module (OH1)\n"
  #define FAULT16_Char (char*)"[Error] - Overheat fault of the inverter module (OH2)\n"
  #define FAULT17_Char (char*)"[Error] - External fault (EF)\n"
  #define FAULT18_Char (char*)"[Error] - 485 communication fault (CE)\n"
  #define FAULT19_Char (char*)"[Error] - Current detection fault (ItE)\n"
  #define FAULT20_Char (char*)"[Error] - Motor autotune fault (tE)\n"
  #define FAULT21_Char (char*)"[Error] - EEPROM operation fault (EEP)\n"
  #define FAULT22_Char (char*)"[Error] - PID response offline fault (PIDE)\n"
  #define FAULT23_Char (char*)"[Error] - Braking unit fault (bCE)\n"
  #define FAULT24_Char (char*)"[Error] - Running time arrival (END)\n"
  #define FAULT25_Char (char*)"[Error] - Electrical overload (OL3)\n"
  #define FAULT26_Char (char*)"[Error] - Panel communication fault (PCE)\n"
  #define FAULT27_Char (char*)"[Error] - Parameter uploading fault (UPE)\n"
  #define FAULT28_Char (char*)"[Error] - Parameter downloading fault (DNE)\n"
  #define FAULT32_Char (char*)"[Error] - Grounding short circuit fault 1(ETH1)\n"
  #define FAULT33_Char (char*)"[Error] - Grounding short circuit fault 2(ETH2)\n"
  #define FAULT36_Char (char*)"[Error] - Undervoltage fault (LL)\n"
};

// direction of fan that is driven by inverter
#define FORWARD 1
#define REVERSE 0
// the INVT modbus register
// Communication control command
#define INVT_REGISTER_RW_CONTROL_COMMAND                0x2000
    #define INVT_VALUE_FORWARD_RUNNING    0x0001
    #define INVT_VALUE_REVERSE_RUNNING    0x0002
    #define INVT_VALUE_FORWARD_JOGGING    0x0003
    #define INVT_VALUE_REVERSE_JOGGING    0x0004
    #define INVT_VALUE_STOP               0x0005
    #define INVT_VALUE_COAST_TO_STOP      0x0006 // emergency stop
    #define INVT_VALUE_FAULT_RESET        0x0007
    #define INVT_VALUE_JOGGING_STOP       0x0008
// Communication setting frequency(0~Fmax(unit: 0.01Hz)) 
#define INVT_REGISTER_RW_SETTING_FREQUENCY              0x2001 // 0~Fmax(unit: 0.01Hz)
// PID reference, range(0~1000, 1000 corresponds to100.0% )
#define INVT_REGISTER_RW_PID_REFERENCE                  0x2002 
// PID feedback, range(0~1000, 1000 corresponds to100.0% )
#define INVT_REGISTER_RW_PID_FEEDBACK                   0x2003 
// Torque setting value (-3000~3000, 1000 corresponds to the 100.0% of the rated current of the motor)
#define INVT_REGISTER_RW_TORQUE_SETTING_VALUE           0x2004 
/**
 * The upper limit frequency setting during forward rotation(0~Fmax(unit: 0.01Hz))
 * #define MAX_FORWARD_ROTATION_LIMIT_FREQ                 5000
 */
#define INVT_REGISTER_RW_FORWARD_ROTATION_LIMIT_FREQ    0x2005 
/**
 * The upper limit frequency setting during reverse rotation(0~Fmax(unit: 0.01Hz))
 * // #define MAX_RESERVE_ROTATION_LIMIT_FREQ                 5000
 */  
#define INVT_REGISTER_RW_REVERSE_ROTATION_LIMIT_FREQ    0x2006 
// The upper limit torque of electromotion torque (0~3000, 1000 corresponds to the 100.0% of the rated current of the motor)
#define INVT_REGISTER_RW_LIMIT_TORQUE_ELECTROMOTION     0x2007 
// The upper limit torque of braking torque (0~3000, 1000 corresponds to the 100.0% of the rated current of the motor)
#define INVT_REGISTER_RW_LIMIT_TORQUE_BRAKING           0x2008 
/**
 * Special control command word
 * Bit0~1:
 * =00:motor 1 
 * =01:motor 2
 * =10:motor 3 
 * =11:motor 4
 * Bit2:
 * =1 torque control 
 * =0:speed control
 */
#define INVT_REGISTER_RW_SPECIAL_CONTROL_COMMAND_WORD   0x2009
// Virtual input terminal command , range: 0x000~0x1FF
#define INVT_REGISTER_RW_VIRTUAL_INPUT_TERMINAL_COMMAND 0x200A
// Virtual input terminal command , range: 0x000~0x0F
#define INVT_REGISTER_RW_VIRTUAL_INPUT_TERMINAL_COMMAND_ 0x200B
// Voltage setting value(special for V/F separation) (0~1000, 1000 corresponds to the 100.0% of the rated voltage of the motor)
#define INVT_REGISTER_RW_VOLTAGE_SETTING_VALUE          0x200C
// AO output setting 1(-1000~1000, 1000 corresponds to 100.0%)
#define INVT_REGISTER_RW_AO_OUTPUT_SETTING_1            0x200D
// AO output setting 2(-1000~1000, 1000 corresponds to 100.0%)
#define INVT_REGISTER_RW_AO_OUTPUT_SETTING_2            0x200E

/**
 * Switch 1 of the inverter
 * 0001H: forward running
 * 0002H: reverse running
 * 0003H: stop
 * 0004H: fault
 * 0005H: Power off state
 */ 
#define INVT_REGISTER_R_SW1                             0x2100
/**
 * Switch 2 of the inverter
 * Bit0: 
 * =0:bus voltage is not established
 * =1:bus voltage is established
 * Bi1~2:
 * =00:motor 1 
 * =01:motor 2
 * =10:motor 3 
 * =11:motor 4
 * Bit3: 
 * =0:asynchronous motor
 * =1:synchronous motor
 * Bit4:
 * =0:pre-alarm without overload
 * =1:overload pre-alarm
 * Bit5~ Bit6:
 * =00:keypad control
 * =01:terminal control
 * =10:communication control
 */
#define INVT_REGISTER_R_SW2                             0x2101
// Fault code of the inverter, See the fault type instruction
#define INVT_REGISTER_R_FAULT_CODE                      0x2102
/**
 * Identifying code of the inverter ( GD200A-----0x010C )
 * The code is consisted of 16 bit which is high 8 bits and low 8 bits. High 8 bits mean
the motor type series and low 8 bits mean the derived motor types of the series. For
example, 0110H means Goodrive200A vector inverters.
* Code high 8 bit: 01 GD
* Code low 8 bit:
* = 0x08 : GD35 vector inverters
* = 0x09 : GD35-H1 vector inverters 
* = 0x0A : GD300 vector inverters
* = 0x0B : GD100 simple vector invert
* = 0x0C : GD200A general inverter
* = 0x0D : GD10 mini inverters
*/ 
#define INVT_REGISTER_R_ID_CODE_OF_INVERTER             0x2103
// Operation frequency Range: 0.00Hz~P00.03
#define INVT_REGISTER_R_OPERATION_FREQUENCY             0x3000  
// Setting frequency. Range: 0.00Hz~P00.03
#define INVT_REGISTER_R_SETTING_FREQUENCY               0x3001
// Bus voltage. Range: 0~12000V. Unit 0.1V
#define INVT_REGISTER_R_BUS_VOLTAGE                     0x3002
// Output voltage. Range: 0~1200V. Unit V
#define INVT_REGISTER_R_OUTPUT_VOLTAGE                  0x3003
// Output current. Range: 0.0~5000.0A
#define INVT_REGISTER_R_OUTPUT_CURRENT                  0x3004
// Operation speed. Range: 0~65535RPM
#define INVT_REGISTER_R_OPERATION_SPEED                 0x3005
// Output power. Range: -300.0~300.0%
#define INVT_REGISTER_R_OUTPUT_POWER                    0x3006
// Output torque. Range: -32768 - 32768 Unit 0.1Nm
#define INVT_REGISTER_R_OUTPUT_TORQUE                   0x3007
// Close loop setting. Range: -100.0%~100.0%
#define INVT_REGISTER_R_CLOSE_LOOP_SETTING              0x3008
// Close loop feedback. Range: -100.0%~100.0%
#define INVT_REGISTER_R_CLOSE_LOOP_FEEDBACK             0x3009
// Input IO state. Range: 0000~00FF
#define INVT_REGISTER_R_INPUT_IO_STATE                  0x300A
// Output IO state. Range: 0000~00FF
#define INVT_REGISTER_R_OUTPUT_IO_STATE                 0x300B
// AI 1. Range: 0.00~10.00V
#define INVT_REGISTER_R_AI_1                            0x300C
// AI 2. Range: 0.00~10.00V
#define INVT_REGISTER_R_AI_2                            0x300D
// AI 3. Range: 0.00~10.00V
#define INVT_REGISTER_R_AI_3                            0x300E
// AI 4. Reserved
#define INVT_REGISTER_R_AI_4                            0x300F
// Read high speed pulse 1 input. Range: 0.00~50.00kHz
#define INVT_REGISTER_R_HIGH_SPEED_PULSE_1              0x3010
// Read high speed pulse 1 input. Reserved
#define INVT_REGISTER_R_HIGH_SPEED_PULSE_2              0x3011
// Read current step of the multi-step speed. Range: 0~15
#define INVT_REGISTER_R_CURRENT_STEP_MULTI_STEP_SPEED   0x3012
// External length. Range: 0~65535
#define INVT_REGISTER_R_EXTERNAL_LENGTH                 0x3013
// External counting value. Range: 0~65535
#define INVT_REGISTER_R_EXTERNAL_COUNTING_VALUE         0x3014
// Torque setting. Range: -32767~32768 x 0.1Nm
#define INVT_REGISTER_R_TORQUE_SETTING                  0x3015
// Inverter code
#define INVT_REGISTER_R_INVERTER_CODE                   0x3016
// Fault code
// #define INVT_REGISTER_R_FAULT_CODE                      0x5000
/**
 * inverter buffer for register uint16_t INVT_Buffer_RW_Registers[16];
 */
enum INVT_Buffer_RW_Index
{
#define INVT_Buffer_RW_Index_Control_Command                  0
#define INVT_Buffer_RW_Index_Setting_Frequency                1
#define INVT_Buffer_RW_Index_PID_REFERENCE                    2
#define INVT_Buffer_RW_Index_PID_FEEDBACK                     3
#define INVT_Buffer_RW_Index_PID_TORQUE_SETTING_VALUE         4
#define INVT_Buffer_RW_Index_FORWARD_ROTATION_LIMIT_FREQ      5
#define INVT_Buffer_RW_Index_REVERSE_ROTATION_LIMIT_FREQ      6
#define INVT_Buffer_RW_Index_LIMIT_TORQUE_ELECTROMOTION       7
#define INVT_Buffer_RW_Index_LIMIT_TORQUE_BRAKING             8
#define INVT_Buffer_RW_Index_SPECIAL_CONTROL_COMMAND_WORD     9
#define INVT_Buffer_RW_Index_VIRTUAL_INPUT_TERMINAL_COMMAND   10
#define INVT_Buffer_RW_Index_VIRTUAL_INPUT_TERMINAL_COMMAND_  11
#define INVT_Buffer_RW_Index_VOLTAGE_SETTING_VALUE            12
#define INVT_Buffer_RW_Index_AO_OUTPUT_SETTING_1              13
#define INVT_Buffer_RW_Index_AO_OUTPUT_SETTING_2              14
};


/**
 * inverter buffer for register uint16_t INVT_Buffer_R_Registers_1[4];
 */
enum INVT_Buffer_R_Index_Registers_1
{
#define INVT_Buffer_R_Index_SW1                               0
#define INVT_Buffer_R_Index_SW2                               1
#define INVT_Buffer_R_Index_FAULT_CODE                        2
#define INVT_Buffer_R_Index_ID_CODE_OF_INVERTER               3
};
// uint16_t INVT_Buffer_R_Registers_2[23];
enum INVT_Buffer_R_Index_Registers_2
{
#define INVT_Buffer_R_Index_OPERATION_FREQUENCY               00  
#define INVT_Buffer_R_Index_SETTING_FREQUENCY                 01
#define INVT_Buffer_R_Index_BUS_VOLTAGE                       02
#define INVT_Buffer_R_Index_OUTPUT_VOLTAGE                    03
#define INVT_Buffer_R_Index_OUTPUT_CURRENT                    04
#define INVT_Buffer_R_Index_OPERATION_SPEED                   05
#define INVT_Buffer_R_Index_OUTPUT_POWER                      06
#define INVT_Buffer_R_Index_OUTPUT_TORQUE                     07
#define INVT_Buffer_R_Index_CLOSE_LOOP_SETTING                08
#define INVT_Buffer_R_Index_CLOSE_LOOP_FEEDBACK               09
#define INVT_Buffer_R_Index_INPUT_IO_STATE                    10
#define INVT_Buffer_R_Index_OUTPUT_IO_STATE                   11
#define INVT_Buffer_R_Index_AI_1                              12
#define INVT_Buffer_R_Index_AI_2                              13
#define INVT_Buffer_R_Index_AI_3                              14
#define INVT_Buffer_R_Index_AI_4                              15
#define INVT_Buffer_R_Index_HIGH_SPEED_PULSE_1                16
#define INVT_Buffer_R_Index_HIGH_SPEED_PULSE_2                17
#define INVT_Buffer_R_Index_CURRENT_STEP_MULTI_STEP_SPEED     18
#define INVT_Buffer_R_Index_EXTERNAL_LENGTH                   19
#define INVT_Buffer_R_Index_EXTERNAL_COUNTING_VALUE           20
#define INVT_Buffer_R_Index_TORQUE_SETTING                    21
#define INVT_Buffer_R_Index_INVERTER_CODE                     22
};
#endif