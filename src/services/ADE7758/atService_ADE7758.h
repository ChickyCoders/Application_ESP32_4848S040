/**
@file
Service for communicating with ADE7758 by SPI
*/
/*
  Service_atService_ADE7758.h - 
  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Service_atService_ADE7758_
#define _Service_atService_ADE7758_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "../Service.h"
#include "SPI.h"
/* _____DEFINETIONS__________________________________________________________ */
#define SPI_FREQUENCY_ADE7758       1000000
#define SCK_Pin         14
#define MISO_Pin        12
#define MOSI_Pin        13
#define CS_Pin          15
#define Interupt_Pin    25

#define ADC_Full_Scale 16777216

enum phase_index_enum{
    PHASE_A = 0,
    PHASE_B,
    PHASE_C,
    PHASE_NUMBER,
};
/*
Watt-Hour Accumulation Register for Phase A. Active power is
accumulated over time in this read-only register. The AWATTHR register
can hold a maximum of 0.52 seconds of active energy information with
full-scale analog inputs before it overflows (see the Active Energy
Calculation section). Bit 0 and Bit 1 of the COMPMODE register determine
how the active energy is processed from the six analog inputs.
*/
#define AWATTHR     0x01  //        16bit   
#define BWATTHR     0x02  //        16bit   
#define CWATTHR     0x03  //        16bit   
/*
VAR-Hour Accumulation Register for Phase A. Reactive power is
accumulated over time in this read-only register. The AVARHR register
can hold a maximum of 0.52 seconds of reactive energy information
with full-scale analog inputs before it overflows (see the Reactive Energy
Calculation section). Bit 0 and Bit 1 of the COMPMODE register
determine how the reactive energy is processed from the six analog inputs
*/
#define AVARHR      0x04  //        signed 16bit   
#define BVARHR      0x05  //        signed 16bit   
#define CVARHR      0x06  //        signed 16bit   

/*
VA-Hour Accumulation Register for Phase A. Apparent power is
accumulated over time in this read-only register. The AVAHR register can
hold a maximum of 1.15 seconds of apparent energy information with
full-scale analog inputs before it overflows (see the Apparent Energy
Calculation section). Bit 0 and Bit 1 of the COMPMODE register determine
how the apparent energy is processed from the six analog inputs
*/
#define AVAHR       0x07  //        signed 16bit
#define BVAHR       0x08  //        signed 16bit
#define CVAHR       0x09  //        signed 16bit

/*
Phase A Current Channel RMS Register. The register contains the rms
component of the Phase A input of the current channel. The source is
selected by data bits in the mode register
*/
#define AIRMS       0x0A //---------signed 24bit
#define BIRMS		0x0B //---------signed 24bit
#define CIRMS		0x0C //---------signed 24bit

/*
Phase A Voltage Channel RMS Register.
*/
#define AVRMS		0x0D //---------signed 24bit
#define BVRMS		0x0E //---------signed 24bit
#define CVRMS		0x0F //---------signed 24bit

/*
Frequency of the Line Input Estimated by the Zero-Crossing Processing.
It can also display the period of the line input. Bit 7 of the LCYCMODE
register determines if the reading is frequency or period. Default is
frequency. Data Bit 0 and Bit 1 of the MMODE register determine the
voltage channel used for the frequency or period calculation
*/
#define FREQ 0x10   // -------------unsigned 12bit

/*
Temperature Register. This register contains the result of the latest
temperature conversion. Refer to the Temperature Measurement
section for details on how to interpret the content of this register.
*/
#define TEMP 0x11 // ---------------signed 8 bit

/*
Waveform Register. This register contains the digitized waveform of one
of the six analog inputs or the digitized power waveform. The source is
selected by Data Bit 0 to Bit 4 in the WAVEMODE register.
*/
#define WFORM 0x12 // signed 24bit

/*
Operational Mode Register. This register defines the general
configuration of the ADE7758 (see Table 18).
*/
#define OPMODE 0x13 //unsigned 8 bit defaut is 0x04

/*
Measurement Mode Register. This register defines the channel used for
period and peak detection measurements (see Table 19).
*/
#define MMODE 0x14// unsigned 8 bit default is 0xFC

/*
Waveform Mode Register. This register defines the channel and sampling
frequency used in the waveform sampling mode (see Table 20). 
*/
#define WAVEMODE 0x15// unsigned 8 bit default is 0

/*
Computation Mode Register. This register configures the formula
applied for the energy and line active energy measurements (see Table 22).
*/
#define COMPMODE 0x16 // unsigned 8 bit default is 0x1C

/*
Line Cycle Mode Register. This register configures the line cycle
accumulation mode for WATT-HR, VAR-HR, and VA-Hr (see Table 23).
*/
#define LCYCMODE 0x17 // unsigned 8 bit default is 0x78

/*
IRQ Mask Register. It determines if an interrupt event generates an
active-low output at the IRQ pin (see the Interrupts section).
*/
#define Mask 0x18 // unsigned 24 bit 

/*
IRQ Status Register. This register contains information regarding the
source of the ADE7758 interrupts (see the Interrupts section). 
*/
#define Status 0x19 // unsigned 24bit 

/*
IRQ Reset Status Register. Same as the STATUS register, except that its
contents are reset to 0 (all flags cleared) after a read operation.
*/
#define RSTATUS 0x1A // unsigned 24 bit

/*
Zero-Cross Timeout Register. If no zero crossing is detected within the
time period specified by this register, the interrupt request line (IRQ)
goes active low for the corresponding line voltage. The maximum
timeout period is 2.3 seconds (see the Zero-Crossing Detection section).
*/
#define ZXTOUT 0x1B // unsigned 16 bit default is 0xFFFF

/*
Line Cycle Register. The content of this register sets the number of
half-line cycles that the active, reactive, and apparent energies are
accumulated for in the line accumulation mode. 
*/
#define LINECYC 0x1C // unsigned 16 bit default is 0xFFFF

/*
SAG Line Cycle Register. This register specifies the number of consecutive
half-line cycles where voltage channel input may fall below a threshold
level. This register is common to the three line voltage SAG detection.
The detection threshold is specified by the SAGLVL register (see the Line
Voltage SAG Detection section). 
*/
#define SAGCYC 0x1D // unsigned 8 bit default is 0xFF

/*
SAG Voltage Level. This register specifies the detection threshold for the
SAG event. This register is common to all three phases’ line voltage SAG
detections. See the description of the SAGCYC register for details.
*/
#define SAGLVL 0x1E // unsigned 8 bit 

/*
Voltage Peak Level Interrupt Threshold Register. This register sets the
level of the voltage peak detection. Bit 5 to Bit 7 of the MMODE register
determine which phases are to be monitored. If the selected voltage
phase exceeds this level, the PKV flag in the IRQ status register is set. 
*/
#define VPINTLVL 0x1F // unsigned 8 bit default is 0xff

/*
Current Peak Level Interrupt Threshold Register. This register sets the
level of the current peak detection. Bit 5 to Bit 7 of the MMODE register
determine which phases are to be monitored. If the selected current
phase exceeds this level, the PKI flag in the IRQ status register is set.
*/
#define IPINTLVL 0x20 // unsigned 8 bit default is 0xFF

/*
Voltage Peak Register. This register contains the value of the peak
voltage waveform that has occurred within a fixed number of half-line
cycles. The number of half-line cycles is set by the LINECYC register
*/
#define VPEAK 0x21 // unsigned 8 bit 

/*
Current Peak Register. This register holds the value of the peak current
waveform that has occurred within a fixed number of half-line cycles. The
number of half-line cycles is set by the LINECYC register.
*/
#define IPEAK 0x22 // unsigned 8 bit

/*
PGA Gain Register. This register is used to adjust the gain selection for the
PGA in the current and voltage channels (see the Analog Inputs section). 
*/
#define Gain 0x23 // unsigned 8 bit

/*
Phase A VRMS Gain Register. The range of the voltage rms calculation can
be adjusted by writing to this register. It has an adjustment range of ±50%
with a resolution of 0.0244%/LSB. 
*/
#define AVRMSGAIN 0x24 // signed 12 bit
#define BVRMSGAIN 0x25 // signed 12 bit
#define CVRMSGAIN 0x26 // signed 12 bit

/*
Phase A Current Gain Register. This register is not recommended to be
used and it should be kept at 0, its default value
*/
#define AIGAIN 0x27 // signed 12 bit
#define BIGAIN 0x28 // signed 12 bit
#define CIGAIN 0x29 // signed 12 bit

/*
Phase A Watt Gain Register. The range of the watt calculation can be
adjusted by writing to this register. It has an adjustment range of ±50%
with a resolution of 0.0244%/LSB. 
*/
#define AWG 0x2A // signed 12 bit
#define BWG 0x2B // signed 12 bit
#define CWG 0x2C // signed 12 bit

/*
Phase A VAR Gain Register. The range of the VAR calculation can be
adjusted by writing to this register. It has an adjustment range of ±50%
with a resolution of 0.0244%/LSB.
*/
#define AVARG 0x2D // signed 12 bit
#define BVARG 0x2E // signed 12 bit
#define CVARG 0x2F // signed 12 bit

/*
Phase A VA Gain Register. The range of the VA calculation can be adjusted
by writing to this register. It has an adjustment range of ±50% with a
resolution of 0.0244%/LSB.
*/
#define AVAG 0x30 // signed 12 bit
#define BVAG 0x31 // signed 12 bit
#define CVAG 0x32 // signed 12 bit

/*
Phase A Voltage RMS Offset Correction Register
*/
#define AVRMSOS 0x33 // signed 12 bit
#define BVRMSOS 0x34 // signed 12 bit
#define CVRMSOS 0x35 // signed 12 bit

/*
Phase A Current RMS Offset Correction Register
*/
#define AIRMSOS 0x36 // signed 12 bit
#define BIRMSOS 0x37 // signed 12 bit
#define CIRMSOS 0x38 // signed 12 bit

/*
Phase A Watt Offset Calibration Register.
*/
#define AWATTOS 0x39 // signed 12 bit
#define BWATTOS 0x3A // signed 12 bit
#define CWATTOS 0x3B // signed 12 bit

/*
Phase A VAR Offset Calibration Register.
*/
#define AVAROS 0x3C
#define BVAROS 0x3D
#define CVAROS 0x3E

/*
Phase A Phase Calibration Register. The phase relationship between the
current and voltage channel can be adjusted by writing to this signed
7-bit register (see the Phase Compensation section). 
*/
#define APHCAL 0x3F // signed 7 bits
#define BPHCAL 0x40 // signed 7 bits
#define CPHCAL 0x41 // signed 7 bits

/*
Active Energy Register Divider.
*/ 
#define WDIV 0x42 // unsigned 8 bits

/*
Reactive Energy Register Divider.
*/
#define VARDIV 0x43 // unsigned 8 bits

/*
Apparent Energy Register Divider.
*/
#define VADIV 0x44 // unsigned 8 bits

/*
Active Power CF Scaling Numerator Register. The content of thisregister is
used in the numerator of the APCF output scaling calculation. Bits [15:13]
indicate reverse polarity active power measurement for Phase A, Phase B,
and Phase C in order; that is, Bit 15 is Phase A, Bit 14 is Phase B, and so on.
*/
#define APCFNUM 0x45 // unsigned 16 bit

/*
Active Power CF Scaling Denominator Register. The content of this
register is used in the denominator of the APCF output scaling.
*/
#define APCFDEN 0x46 // unsigned 12 bit default is 0x3F

/*
Reactive Power CF Scaling Numerator Register. The content of this register
is used in the numerator of the VARCF output scaling. Bits [15:13] indicate
reverse polarity reactive power measurement for Phase A, Phase B, and
Phase C in order; that is, Bit 15 is Phase A, Bit 14 is Phase B, and so on.
*/
#define VARCFNUM 0x47 // unsigned 16 bit

/*
Reactive Power CF Scaling Denominator Register. The content of this
register is used in the denominator of the VARCF output scaling. 
*/
#define VARCFDEN 0x48

/*
Checksum Register. The content of this register represents the sum of all
the ones in the last register read from the SPI port. 
*/
#define CHKSUM 0x7E // unsigned 8 bit 

//version if the die
#define VERS 0x7F

/* _____GLOBAL VARIABLES_____________________________________________________ */
SPIClass adeSPI(HSPI);
SPISettings Settings_For_ADE7758(SPI_FREQUENCY_ADE7758, MSBFIRST, SPI_MODE1);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the 
 */
class Service_ADE7758 : public Service
{
public:
    Service_ADE7758();
    ~Service_ADE7758();
    float get_RMS_Voltage(phase_index_enum phase_index);
    float get_RMS_Current(phase_index_enum phase_index);
    float get_Active_Power(phase_index_enum phase_index);
    float get_Reactive_Power(phase_index_enum phase_index);
    float get_Apparent_Power(phase_index_enum phase_index);
    float get_Frequency();
    float get_Temperature();
    uint8_t get_Version();

protected:
    uint32_t read24bit(uint8_t reg);
    int16_t read16bit(uint8_t reg);
    uint16_t read12bit(uint8_t reg);
    uint8_t  read8bit(uint8_t reg);
private:
    static void  Service_ADE7758_Start();
    static void  Service_ADE7758_Execute();    
    static void  Service_ADE7758_End();
} atService_ADE7758 ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_ADE7758::Service_ADE7758(/* args */)
{
    _Start_User      = *Service_ADE7758_Start;
    _Execute_User    = *Service_ADE7758_Execute;
    _End_User        = *Service_ADE7758_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char*)"ADE7758 Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_ADE7758::~Service_ADE7758()
{
    
}
/**
 * This start function will init some critical function 
 */
void  Service_ADE7758::Service_ADE7758_Start()
{
    adeSPI.begin(14,12,13,15);
    pinMode (CS_Pin, OUTPUT);
}  

/**
 * Execute fuction of SNM app
 */
void  Service_ADE7758::Service_ADE7758_Execute()
{   
    if(atService_ADE7758.User_Mode == SER_USER_MODE_DEBUG)
    {
        
    }   
}    
void  Service_ADE7758::Service_ADE7758_End(){}

/**
 * @brief Read 24 bit data form register and return in 32bit data
 * @param reg register to read data
 */
uint32_t Service_ADE7758::read24bit(uint8_t reg)
{
    uint8_t Byte2,Byte1,Byte0;

    adeSPI.beginTransaction(Settings_For_ADE7758);
    digitalWrite (CS_Pin, LOW);
    adeSPI.transfer(reg); 
    delayMicroseconds(5);
    Byte2 = adeSPI.transfer(0x00);
    delayMicroseconds(5);
    Byte1 = adeSPI.transfer(0x00);
    delayMicroseconds(5);
    Byte0 = adeSPI.transfer(0x00);
    delayMicroseconds(5);
    digitalWrite (CS_Pin, HIGH);
    adeSPI.endTransaction();

    uint32_t val = (unsigned long)Byte2<<16 | (unsigned long)Byte1<<8 | (unsigned long)Byte0;
    return val;
}
/**
 * @brief Read 16 bit data form register and return in 16 bit data
 * @param reg register to read data
 */
int16_t Service_ADE7758::read16bit(uint8_t reg)
{
    uint8_t Byte1,Byte0;

    adeSPI.beginTransaction(Settings_For_ADE7758);
    digitalWrite (CS_Pin, LOW);
    adeSPI.transfer(reg); 
    delayMicroseconds(5);
    Byte1 = adeSPI.transfer(0x00);
    delayMicroseconds(5);
    Byte0 = adeSPI.transfer(0x00);
    delayMicroseconds(5);
    digitalWrite (CS_Pin, HIGH);
    adeSPI.endTransaction();

    int16_t val = (unsigned long)Byte1<<8 | (unsigned long)Byte0;
    return val;
}
/**
 * @brief Read 12 bit data form register and return in 16 bit data
 * @param reg register to read data
 */
uint16_t Service_ADE7758::read12bit(uint8_t reg)
{
    uint8_t Byte1,Byte0;

    adeSPI.beginTransaction(Settings_For_ADE7758);
    digitalWrite (CS_Pin, LOW);
    adeSPI.transfer(reg); 
    delayMicroseconds(5);
    Byte1 = adeSPI.transfer(0x00);
    delayMicroseconds(5);
    Byte0 = adeSPI.transfer(0x00);
    delayMicroseconds(5);
    digitalWrite (CS_Pin, HIGH);
    adeSPI.endTransaction();

    uint16_t val = ((unsigned long)Byte1<<8 | (unsigned long)Byte0 ) &0x0FFF;
    return val;
}
/**
 * @brief Read 8 bit data form register and return in 8 bit data
 * @param reg register to read data
 */
uint8_t Service_ADE7758::read8bit(uint8_t reg)
{
    uint8_t Byte0;

    adeSPI.beginTransaction(Settings_For_ADE7758);
    digitalWrite (CS_Pin, LOW);
    adeSPI.transfer(reg); 
    delayMicroseconds(5);
    Byte0 = adeSPI.transfer(0x00);
    delayMicroseconds(5);
    digitalWrite (CS_Pin, HIGH);
    adeSPI.endTransaction();

    return Byte0;
}

float Service_ADE7758::get_RMS_Voltage(phase_index_enum phase_index)
{
    float RMS_Voltage = 0;
    switch (phase_index)
    {
    case PHASE_A:
        RMS_Voltage = (float)read24bit(AVRMS);
        break;
    case PHASE_B:
        RMS_Voltage = (float)read24bit(BVRMS);
        break;
    case PHASE_C:
        RMS_Voltage = (float)read24bit(CVRMS);
        break;
    
    default:
        break;
    }

    return 0.5*RMS_Voltage/ADC_Full_Scale;
}

float Service_ADE7758::get_RMS_Current(phase_index_enum phase_index)
{
    float RMS_Current = 0;
    switch (phase_index)
    {
    case PHASE_A:
        RMS_Current = (float)read24bit(AIRMS);
        break;
    case PHASE_B:
        RMS_Current = (float)read24bit(BIRMS);
        break;
    case PHASE_C:
        RMS_Current = (float)read24bit(CIRMS);
        break;
    
    default:
        break;
    }

    return 0.5*RMS_Current/ADC_Full_Scale; 
}

float Service_ADE7758::get_Active_Power(phase_index_enum phase_index)
{
    float Active_Power = 0;
    switch (phase_index)
    {
    case PHASE_A:
        Active_Power = (float)read16bit(AWATTHR);
        break;
    case PHASE_B:
        Active_Power = (float)read16bit(BWATTHR);
        break;
    case PHASE_C:
        Active_Power = (float)read16bit(CWATTHR);
        break;
    
    default:
        break;
    }

    return Active_Power/65535;
}

float Service_ADE7758::get_Reactive_Power(phase_index_enum phase_index)
{
    float Reactive_Power = 0;
    switch (phase_index)
    {
    case PHASE_A:
        Reactive_Power = (float)read16bit(AVARHR);
        break;
    case PHASE_B:
        Reactive_Power = (float)read16bit(BVARHR);
        break;
    case PHASE_C:
        Reactive_Power = (float)read16bit(CVARHR);
        break;
    
    default:
        break;
    }

    return Reactive_Power/65535;
}

float Service_ADE7758::get_Apparent_Power(phase_index_enum phase_index)
{
    float Apparent_Power = 0;
    switch (phase_index)
    {
    case PHASE_A:
        Apparent_Power = (float)read16bit(AVAHR);
        break;
    case PHASE_B:
        Apparent_Power = (float)read16bit(BVAHR);
        break;
    case PHASE_C:
        Apparent_Power = (float)read16bit(CVAHR);
        break;
    
    default:
        break;
    }

    return Apparent_Power/65535;
}

float Service_ADE7758::get_Frequency()
{
    float frequency = 0;
    frequency = read12bit(FREQ);
    return frequency;
}

float Service_ADE7758::get_Temperature()
{
    int8_t temperature = 0;
    temperature = read8bit(TEMP);
    return (float)temperature;
}

uint8_t Service_ADE7758::get_Version()
{
    uint8_t version = 0;
    version = read8bit(VERS);
    return version;
}

#endif


