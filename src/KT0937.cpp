/**
 * @brief  PU2CLR KT0937 Arduino Library
 * @details KT0937 Arduino Library implementation. This is an Arduino library for the KT0937, BROADCAST RECEIVER.  
 * @details It works with I2C protocol and can provide an easier interface to control the KT0937 device.<br>
 * @details This library was built based on KT0937 Datasheet from KTMicro (Monolithic Digital FM/MW/SW/LW Receiver Radio-on-a-Chip TM). 
 * @details This library can be freely distributed using the MIT Free Software model.
 * @copyright Copyright (c) 2020 Ricardo Lima Caratti. 
 * @author Ricardo LIma Caratti (pu2clr@gmail.com)
 */

#include <KT0937.h>

/** 
 * @defgroup GA03 Basic Methods 
 * @section  GA03 Basic 
 * @details  Low level functions used to operate with the KT09XX registers
 */



/**
 * @ingroup GA03
 * @brief Sets the a value to a given KT09XX register
 * 
 * @param reg        register number to be written (0x00 ~ 0xF7) - See #define REG_ in KT0937.h 
 * @param parameter  content you want to store 
 */
void KT0937::setRegister(int reg, uint8_t parameter)
{
    Wire.begin();
    Wire.beginTransmission(this->deviceAddress);
    Wire.write(reg);    
    Wire.write(parameter);
    Wire.endTransmission();
    delayMicroseconds(6000);
}



/**
 * @ingroup GA03
 * @brief Gets a given KT09XX register content 
 * @details It is a basic function to get a value from a given KT0937 device register
 * @param reg  register number to be read (0x1 ~ 0x3C) - See #define REG_ in KT0937.h 
 * @return the register content
 */
uint8_t KT0937::getRegister(int reg)
{

    uint8_t result;
    Wire.begin(); 
    Wire.beginTransmission(this->deviceAddress);
    Wire.write(reg);
    Wire.endTransmission(false);
    delayMicroseconds(6000);
    Wire.requestFrom(this->deviceAddress,1);
    result= Wire.read();
    Wire.endTransmission(true);
    delayMicroseconds(6000);

    return result;
}

/**
 * @ingroup GA03
 * @brief Gets the Device Id 
 * @return uint16_t 16 bits word with the device id number
 */
uint16_t KT0937::getDeviceId()
{
    uint8_t id_0 ;
    //uint8_t id_1 ;
    id_0 = getRegister(REG_DEVICEID0);
    //id_1 = getRegister(REG_KTMARK1);
    //this->deviceId = ((id_0 <<8)|(id_1)); 
    this->deviceId = id_0;
    return this->deviceId;
}

/**
 * @ingroup GA03
 * @brief Set I2C bus address 
 * 
 * @param deviceAddress  I2C address
 */
void KT0937::setI2CBusAddress(int deviceAddress)
{
    this->deviceAddress = deviceAddress;
}

/**
 * @ingroup GA03
 * @brief get errorCode 
 * 
 * @param 
 */

uint8_t KT0937::getErrorCode()
{
    return this->errorCode;
}

/**
 * @ingroup GA03
 * @brief Sets the sw_on_pin (9) to set the KT0937 SW_ON to enable 9018 RF Amplifier.
 *     
 * @see setup
 * 
 * @param on_off  1 = enable; 0 = disable
 */
void KT0937::enableSWAmp(uint8_t on_off)
{
    if (this->swOnPin < 0)
        return;
        
    pinMode(this->swOnPin, OUTPUT);
    digitalWrite(this->swOnPin, on_off);
}

/**
 * @ingroup GA03
 * @brief set the KT0937 System Clock .
 *     
 * @see setup
 * 
 * @param on_off  1 = enable; 0 = disable
 */
void KT0937::setSystemClock()
{
    //set DIVIDERP<10:0>
    kt09xx_pllcfg_0 reg0;
    reg0.raw = getRegister(REG_PLLCFG0); //get the current value of REG
    reg0.refined.DIVIDERP_10_8 = 0; //set dividerp <10:8> to 0
    setRegister(REG_PLLCFG0, reg0.raw); // write back to chip kt0937

    //set DIVIDERP<7:0>
    kt09xx_pllcfg_1 reg1;
    reg1.raw = getRegister(REG_PLLCFG1); //get the current value of REG
    reg1.refined.DIVIDERP_7_0 = 1; //set dividerp <7:0> to 1
    setRegister(REG_PLLCFG1, reg1.raw); // write back to chip kt0937

    //set DIVIDERN<10:8>
    kt09xx_pllcfg_2 reg2;
    reg2.raw = getRegister(REG_PLLCFG2); //get the current value of REG
    reg2.refined.DIVIDERN_10_8 = 2; //set dividerB <10:8> to 2
    setRegister(REG_PLLCFG2, reg2.raw); // write back to chip kt0937

    //set DIVIDERN<7:0>
    kt09xx_pllcfg_3 reg3;
    reg3.raw = getRegister(REG_PLLCFG3); //get the current value of REG
    reg3.refined.DIVIDERN_7_0 = 0x9C; //set dividern <7:0> to 0X9C
    setRegister(REG_PLLCFG3, reg3.raw); // write back to chip kt0937

    //set FPFD <19:16> to 8
    kt09xx_sysclk_cfg_0 reg4;
    reg4.raw = getRegister(REG_SYSCLK_CFG0); //get the current value of REG
    reg4.refined.FPFD_19_16 = 8; //set 
    setRegister(REG_SYSCLK_CFG0, reg4.raw); // write back to chip kt0937

    //set FPFD <15:8> to 0
    kt09xx_sysclk_cfg_1 reg5;
    reg5.raw = getRegister(REG_SYSCLK_CFG1); //get the current value of REG
    reg5.refined.FPFD_15_8 = 0; //set 
    setRegister(REG_SYSCLK_CFG1, reg5.raw); // write back to chip kt0937

    //set FPFD <7:0> to 0
    kt09xx_sysclk_cfg_2 reg6;
    reg6.raw = getRegister(REG_SYSCLK_CFG2); //get the current value of REG
    reg6.refined.FPFD_7_0 = 0; //set 
    setRegister(REG_SYSCLK_CFG2, reg6.raw); // write back to chip kt0937

    //setting xtalcfg;
    kt09xx_xtalcfg reg7;
    reg7.raw = getRegister(REG_XTALCFG); //get the current value of REG
    reg7.refined.RCLK_EN = 0; //set the bit to 0: crystal; 1: external Clock
    setRegister(REG_XTALCFG, reg7.raw); // write back to chip kt0937

 
 //set SYS_CFGOK<7>
    kt09xx_pllcfg_0 reg8;
    reg8.raw = getRegister(REG_PLLCFG0); //get the current value of REG
    reg8.refined.SYS_CFGOK = 1; //set SYS_CFGOK to 1
    setRegister(REG_PLLCFG0, reg8.raw); // write back to chip kt0937    
}

/**
 * @ingroup GA03
 * @brief nitialize KT0937.
 *     
 * @see setup
 * 
 * @param 
 */

void KT0937::setup()
{
//standby
enableStandbyMode();

//wake up
wakeUp();

//set DEPOP_TC<2:0> to 3
 kt09xx_anacfg_0 reg0;
 reg0.raw = getRegister(REG_ANACFG0);
 reg0.refined.DEPOP_TC = 3;
 setRegister(REG_ANACFG0,reg0.raw);

 //set AUDV_DCLVL<2:0> 2
 
 kt09xx_anacfg_0 reg1;
 reg1.raw = getRegister(REG_ANACFG0);
 reg1.refined.AUDV_DCLVL= 2;
 setRegister(REG_ANACFG0,reg1.raw);

 setSystemClock();

//check power on
kt09xx_g38kcfg_0 reg2;

while(1)
{
    reg2.raw = getRegister(REG_G38KCFG0);
    if(reg2.refined.POWERON_FINISH == 1)
    {
        break;
    }else{
        this->errorCode = ERR_CLK ;
    }
delay(5);
}

/*
//set FLT_SEL<2:0> to 1
kt09xx_amdsp_0 reg3;
reg3.raw = getRegister(REG_AMDSP0);
reg3.refined.FLT_SEL = 0;
setRegister(REG_AMDSP0, reg3.raw);

//setFM_AFC
disableFMAFC(1);
//setAM_AFC
disableMWAFC(1);
//setSW_AFC
disableSWAFC(1);
//setFM softmute
disableFMSoftMute(1);
//setAM softmute
disableMWSoftMute(1);


*/
//set ANT_CALI_SWITCH_BAND to 1

kt09xx_dspcfg_5 reg4;
reg4.raw = getRegister(REG_DSPCFG5);
reg4.refined.ANT_CALI_SWITCH_BAND = 1;
reg4.refined.AM_SUP_ENHANCE = 1; //AM_SUP_ENHANCE 1 
reg4.refined.AM_SEL_ENHANCE = 1; //AM_SEL_ENHANCE 1
setRegister(REG_DSPCFG5, reg4.raw);

//set INT mode


//enable DialMode
enableDialMode(); 

}

void KT0937::setup(uint8_t sw_on_pin)
{
    this->swOnPin = sw_on_pin;

    //debug
    this->errorCode = ERR_SW_PIN ;
    setup(); 
       
}

/**
 * @ingroup GA03
 * @brief set KT0937 to Deep Sleep. Should wake it UP by reboot.
 *     
 * @see setup
 * 
 * @param 
 */


void KT0937::enableStandbyMode()
{
    //set STBYLDO_CALI_EN to 1
    kt09xx_pvtcali_0 reg0;
    reg0.raw = getRegister(REG_PVTCALI0);
    reg0.refined.STBYLDO_CALI_EN = 1;
    setRegister(REG_PVTCALI0, reg0.raw);
    this->errorCode = getRegister(REG_PVTCALI0);
    

    //set STBYLDO_PD to 0
    kt09xx_adc_5 reg1;
    reg1.raw = getRegister(REG_ADC5);
    reg1.refined.STBYLDO_PD = 0;
    setRegister(REG_ADC5, reg1.raw);

     //set STDBY to 1
    kt09xx_rxcfg_0 reg2;
    reg2.raw = getRegister(REG_RXCFG0);
    reg2.refined.STDBY = 1;
    setRegister(REG_RXCFG0, reg2.raw);
}

/**
 * @ingroup GA03
 * @brief set KT0937 to wake up.
 *     
 * @see setup
 * 
 * @param 
 */
void KT0937::wakeUp()
{
   //set STDBY to 0
    kt09xx_rxcfg_0 reg2;
    reg2.raw = getRegister(REG_RXCFG0);
    reg2.refined.STDBY = 0;
    setRegister(REG_RXCFG0, reg2.raw);
    delay(1);
    //set STBYLDO_PD to 1
    kt09xx_adc_5 reg1;
    reg1.raw = getRegister(REG_ADC5);
    reg1.refined.STBYLDO_PD = 1;
    setRegister(REG_ADC5, reg1.raw);
}

void KT0937::resetDSP()
{
    //set DSP_RST to 1
    kt09xx_rxcfg_0 reg;
    reg.raw = getRegister(REG_RXCFG0);
    reg.refined.DSP_RST = 1;
    setRegister(REG_RXCFG0, reg.raw);
}

void KT0937::enableSW(uint8_t enable_sw)
{
    //enable short wave
    kt09xx_bandcfg_0 reg;
    reg.raw = getRegister(REG_BANDCFG0);
    reg.refined.SW_EN = enable_sw;
    setRegister(REG_BANDCFG0, reg.raw);

}

/**
 * @ingroup GA03
 * @brief set the volumn of KT0937
 *     
 * @see setup
 * 
 * @param 
 */
void KT0937::setVolume(int8_t volume)
{
    
    if(volume > 31) {
        volume = 31; // max 31 , min 0
    }else if(volume < 0 ){
        volume = 0;
    }
    
    this->currentVolume = volume;    
    //set VOLUMN<4:0> to volumn
    
    kt09xx_rxcfg_1 reg;
    reg.raw = getRegister(REG_RXCFG1);
    reg.refined.VOLUME = volume;
    setRegister(REG_RXCFG1,reg.raw);
}

uint8_t KT0937::getVolume()
{
    return this->currentVolume;
}

/**
 * @ingroup GA03
 * @brief disable ADC Chan PIN
 *     
 * @see setup
 * 
 * @param 
 */

void KT0937::shutDownADCCH()
{
    kt09xx_adc_0 reg ;
    reg.raw = getRegister(REG_ADC0);
    reg.refined.CH_ADC_DIS =1;
    //reg.refined.CH_ADC_START = 0;
    setRegister(REG_ADC0,reg.raw);
}

/**
 * @ingroup GA03
 * @brief disable ADC Chan PIN
 *     
 * @see setup
 * 
 * @param 
 */

void KT0937::turnOnADCCH()
{
    kt09xx_adc_0 reg ;
    reg.raw = getRegister(REG_ADC0);
    reg.refined.CH_ADC_DIS =0;
    reg.refined.CH_ADC_START = 1;
    setRegister(REG_ADC0,reg.raw);
}

/**
 * @ingroup GA03
 * @brief set FM Band from 87.5 MHz to 108.0MHz  and frequency step 100kHz
 * 1) 87500 / 50 kHz = 1750 , as 0x06D6 in Hex,  write 0xD6 into LOW_CHAN<7:0> while 
 * write 0x06 into LOW_CHAN<14:8>.
 * 2) 108MHz / 50KHz = 2160, which is 0x870 in Hex, write 0x70 into FM_HIGH_CHAN<7:0> and
 *write 0x08 into FM_HIGH_CHAN<11:8>. 
 * 3) (108MHz -87.5MHz) / 100KHz = 205, which is 0xCD in Hex, write 0xCD into 
 * CHAN_NUM<7:0> then write 0 into CHAN_NUM<11:8>.
 *     
 * @see setup
 * 
 * @param 
 */

 void KT0937::setFMBand(uint16_t frequency)
 {
    this->currentMode = MODE_FM;
    enableSW(0);
    shutDownADCCH();
    uint8_t freqH = ((frequency /50) >> 8);
    uint8_t freqL = ((frequency/50) & 0x00FF);
    //set band range . LOW_CHAN<14:8> set to 0X06
    kt09xx_low_chan_0 reg0 ;
    reg0.raw = getRegister(REG_LOW_CHAN0);
    reg0.refined.LOW_CHAN_14_8 =freqH;
    setRegister(REG_LOW_CHAN0,reg0.raw);

    //set band range. LOW_CHAN<7:0> set to 0xD6
    kt09xx_low_chan_1 reg1 ;
    reg1.raw = getRegister(REG_LOW_CHAN1);
    reg1.refined.LOW_CHAN_7_0 =freqL;
    setRegister(REG_LOW_CHAN1,reg1.raw);

    //set band range. write 0x08 into FM_HIGH_CHAN<11:8>
    kt09xx_fm_chan_0 reg2 ;
    reg2.raw = getRegister(REG_FMCHAN0);
    reg2.refined.FM_HIGH_CHAN_11_8 =freqH;
    setRegister(REG_FMCHAN0,reg2.raw);

    //set band range. write 0x70 into FM_HIGH_CHAN<7:0>
    kt09xx_fm_chan_1 reg3 ;
    reg3.raw = getRegister(REG_FMCHAN1);
    reg3.refined.FM_HIGH_CHAN_7_0 =freqL;
    setRegister(REG_FMCHAN1,reg3.raw);

    //set band range. write 0 into CHAN_NUM<11:8>.
    kt09xx_chan_num_0 reg4 ;
    reg4.raw = getRegister(REG_CHAN_NUM0);
    reg4.refined.CHAN_NUM_11_8 =0;
    setRegister(REG_CHAN_NUM0,reg4.raw);

    //set band range. write 0xCD into  CHAN_NUM<7:0>
    kt09xx_chan_num_1 reg5 ;
    reg5.raw = getRegister(REG_CHAN_NUM1);
    reg5.refined.CHAN_NUM_7_0 =0;
    setRegister(REG_CHAN_NUM1,reg5.raw);

    //set FM SPACE. write 0x01 into  FM_SPACE ,set to 100kHz
    kt09xx_bandcfg_2 reg6 ;
    reg6.raw = getRegister(REG_BANDCFG2);
    reg6.refined.FM_SPACE =1;
    setRegister(REG_BANDCFG2,reg6.raw);

    //set CHAN GUARD. write 0x17 (23) to CH_GUARD
    kt09xx_guard_2 reg7 ;
    reg7.raw = getRegister(REG_GUARD2);
    reg7.refined.CH_GUARD =0x10;
    setRegister(REG_GUARD2,reg7.raw);

    //set CH_ADC_WIN. CH_ADC_WIN<12:0> =  (CHAN_NUM<11:0> + CH_GUARD<7:0>)  * 2   (205(chan)+17(guard))*2 = 456 as 0x 1C8
    //set 0x 00 to <CH_ADC_WIN<12:8>, set 0xFB to <CH_ADC_WIN(7:)    
    kt09xx_adc_3 reg8 ;
    reg8.raw = getRegister(REG_ADC3);
    reg8.refined.CH_ADC_WIN_12_8 = 1;
    setRegister(REG_ADC3,reg8.raw);

    kt09xx_adc_4 reg9 ;
    reg9.raw = getRegister(REG_ADC4);
    reg9.refined.CH_ADC_WIN_7_0 = 0xC8;
    setRegister(REG_ADC4,reg9.raw);

    //set AM_FM = 0 register CHANGE_BAND=1, KT0937 can be working in FM channel mode.
    kt09xx_fm_chan_0 reg10 ;
    reg10.raw = getRegister(REG_FMCHAN0);
    reg10.refined.AM_FM =0;
    reg10.refined.CHANGE_BAND = 1;
    setRegister(REG_FMCHAN0,reg10.raw);

    //turn on ADCCH 
    turnOnADCCH();

 }

/**
 * @ingroup GA03
 * @brief set FM Band from 87.5 MHz to 108.0MHz  and frequency step 100kHz
 * 1) 87500 / 50 kHz = 1750 , as 0x06D6 in Hex,  write 0xD6 into LOW_CHAN<7:0> while 
 * write 0x06 into LOW_CHAN<14:8>.
 * 2) 108MHz / 50KHz = 2160, which is 0x870 in Hex, write 0x70 into FM_HIGH_CHAN<7:0> and
 *write 0x08 into FM_HIGH_CHAN<11:8>. 
 * 3) (108MHz -87.5MHz) / 100KHz = 205, which is 0xCD in Hex, write 0xCD into 
 * CHAN_NUM<7:0> then write 0 into CHAN_NUM<11:8>.
 *     
 * @see setup
 * 
 * @param 
 */
 void KT0937::setFMBand()
 {
    this->currentMode = MODE_FM;
    enableSW(0);
    shutDownADCCH();
    //uint8_t freqH = ((frequency /50) >> 8);
    //uint8_t freqL = ((frequency/50) & 0x00ff);
    //set band range . LOW_CHAN<14:8> set to 0X06
    kt09xx_low_chan_0 reg0 ;
    reg0.raw = getRegister(REG_LOW_CHAN0);
    reg0.refined.LOW_CHAN_14_8 =0x06;
    setRegister(REG_LOW_CHAN0,reg0.raw);

    //set band range. LOW_CHAN<7:0> set to 0xD6
    kt09xx_low_chan_1 reg1 ;
    reg1.raw = getRegister(REG_LOW_CHAN1);
    reg1.refined.LOW_CHAN_7_0 =0xA4;
    setRegister(REG_LOW_CHAN1,reg1.raw);

    //set band range. write 0x08 into FM_HIGH_CHAN<11:8>
    kt09xx_fm_chan_0 reg2 ;
    reg2.raw = getRegister(REG_FMCHAN0);
    reg2.refined.FM_HIGH_CHAN_11_8 =0x08;
    setRegister(REG_FMCHAN0,reg2.raw);

    //set band range. write 0x70 into FM_HIGH_CHAN<7:0>
    kt09xx_fm_chan_1 reg3 ;
    reg3.raw = getRegister(REG_FMCHAN1);
    reg3.refined.FM_HIGH_CHAN_7_0 =0x70;
    setRegister(REG_FMCHAN1,reg3.raw);

    //set band range. write 0 into CHAN_NUM<11:8>.
    kt09xx_chan_num_0 reg4 ;
    reg4.raw = getRegister(REG_CHAN_NUM0);
    reg4.refined.CHAN_NUM_11_8 =0x00;
    setRegister(REG_CHAN_NUM0,reg4.raw);

    //set band range. write 0xCD into  CHAN_NUM<7:0>
    kt09xx_chan_num_1 reg5 ;
    reg5.raw = getRegister(REG_CHAN_NUM1);
    reg5.refined.CHAN_NUM_7_0 =0xE6;
    setRegister(REG_CHAN_NUM1,reg5.raw);

    //set FM SPACE. write 0x01 into  FM_SPACE ,set to 100kHz
    kt09xx_bandcfg_2 reg6 ;
    reg6.raw = getRegister(REG_BANDCFG2);
    reg6.refined.FM_SPACE =0x01;
    setRegister(REG_BANDCFG2,reg6.raw);

    //set CHAN GUARD. write 0x17 (23) to CH_GUARD
    kt09xx_guard_2 reg7 ;
    reg7.raw = getRegister(REG_GUARD2);
    reg7.refined.CH_GUARD =0x17;
    setRegister(REG_GUARD2,reg7.raw);

    //set CH_ADC_WIN. CH_ADC_WIN<12:0> =  (CHAN_NUM<11:0> + CH_GUARD<7:0>)  * 2   (205(chan)+17(guard))*2 = 456 as 0x 1C8
    //set 0x 00 to <CH_ADC_WIN<12:8>, set 0xFB to <CH_ADC_WIN(7:)    
    kt09xx_adc_3 reg8 ;
    reg8.raw = getRegister(REG_ADC3);
    reg8.refined.CH_ADC_WIN_12_8 = 1;
    setRegister(REG_ADC3,reg8.raw);

    kt09xx_adc_4 reg9 ;
    reg9.raw = getRegister(REG_ADC4);
    reg9.refined.CH_ADC_WIN_7_0 = 0xFA;
    setRegister(REG_ADC4,reg9.raw);

    //set AM_FM = 0 register CHANGE_BAND=1, KT0937 can be working in FM channel mode.
    kt09xx_fm_chan_0 reg10 ;
    reg10.raw = getRegister(REG_FMCHAN0);
    reg10.refined.AM_FM =0;
    setRegister(REG_FMCHAN0,reg10.raw);

    reg10.raw = getRegister(REG_FMCHAN0);
    reg10.refined.CHANGE_BAND = 1;
    setRegister(REG_FMCHAN0,reg10.raw);

    reg10.raw = getRegister(REG_FMCHAN0);
    this->errorCode = reg10.raw;

    //turn on ADCCH 
    turnOnADCCH();

 }

 void KT0937::setAMBand(uint16_t lowFrequency, uint16_t highFrequency)
 {
    this->currentMode = MODE_AM;
    //
 }

 void KT0937::setAMBand()
 {
    this->currentMode = MODE_AM;
    enableSW(0);
    shutDownADCCH();
    
    //low :522 kHz , hex 522kHz / 1kHz = 522 , 0x020A;
    //High:1602 kHz, hex 1602kHz / 1kHz = 1602, 0x0654
    kt09xx_low_chan_0 reg0 ;
    reg0.raw = getRegister(REG_LOW_CHAN0);
    reg0.refined.LOW_CHAN_14_8 =0x02;
    setRegister(REG_LOW_CHAN0,reg0.raw);

    //set band range. LOW_CHAN<7:0> set to 0x0A
    kt09xx_low_chan_1 reg1 ;
    reg1.raw = getRegister(REG_LOW_CHAN1);
    reg1.refined.LOW_CHAN_7_0 =0x0A;
    setRegister(REG_LOW_CHAN1,reg1.raw);

    //set band range. write 0x06 into AM_HIGH_CHAN<11:8>
    kt09xx_am_chan_0 reg2 ;
    reg2.raw = getRegister(REG_AMCHAN0);
    reg2.refined.AM_HIGH_CHAN_14_8 =0x06;
    setRegister(REG_AMCHAN0,reg2.raw);

    //set band range. write 0x54 into AM_HIGH_CHAN<7:0>
    kt09xx_am_chan_1 reg3 ;
    reg3.raw = getRegister(REG_AMCHAN1);
    reg3.refined.AM_HIGH_CHAN_7_0 =0x54;
    setRegister(REG_AMCHAN1,reg3.raw);

    //set band range. write 0 into CHAN_NUM<11:8>.
    kt09xx_chan_num_0 reg4 ;
    reg4.raw = getRegister(REG_CHAN_NUM0);
    reg4.refined.CHAN_NUM_11_8 =0x00;
    setRegister(REG_CHAN_NUM0,reg4.raw);

    //set band range. write 0xCD into  CHAN_NUM<7:0>
    kt09xx_chan_num_1 reg5 ;
    reg5.raw = getRegister(REG_CHAN_NUM1);
    reg5.refined.CHAN_NUM_7_0 =0x7A;
    setRegister(REG_CHAN_NUM1,reg5.raw);

    //set AM SPACE. write 0x00 into  AM_SPACE ,set to 1kHz
    kt09xx_bandcfg_2 reg6 ;
    reg6.raw = getRegister(REG_BANDCFG2);
    reg6.refined.MW_SPACE =0x01;
    setRegister(REG_BANDCFG2,reg6.raw);

    //set CHAN GUARD. write 0x17 (23) to CH_GUARD
    kt09xx_guard_2 reg7 ;
    reg7.raw = getRegister(REG_GUARD2);
    reg7.refined.CH_GUARD =0x17;
    setRegister(REG_GUARD2,reg7.raw);

    //set CH_ADC_WIN. CH_ADC_WIN<12:0> =  (CHAN_NUM<11:0> + CH_GUARD<7:0>)  * 2   (205(chan)+17(guard))*2 = 456 as 0x 1C8
    //set 0x 00 to <CH_ADC_WIN<12:8>, set 0xFB to <CH_ADC_WIN(7:)    
    kt09xx_adc_3 reg8 ;
    reg8.raw = getRegister(REG_ADC3);
    reg8.refined.CH_ADC_WIN_12_8 = 0x08;
    setRegister(REG_ADC3,reg8.raw);

    kt09xx_adc_4 reg9 ;
    reg9.raw = getRegister(REG_ADC4);
    reg9.refined.CH_ADC_WIN_7_0 = 0xC6;
    setRegister(REG_ADC4,reg9.raw);

    //set AM_FM = 1 register CHANGE_BAND=1, KT0937 can be working in AM channel mode.
    kt09xx_fm_chan_0 reg10 ;
    reg10.raw = getRegister(REG_FMCHAN0);
    reg10.refined.AM_FM =1;
    setRegister(REG_FMCHAN0,reg10.raw);

    reg10.raw = getRegister(REG_FMCHAN0);
    reg10.refined.CHANGE_BAND = 1;
    setRegister(REG_FMCHAN0,reg10.raw);

    reg10.raw = getRegister(REG_FMCHAN0);
    this->errorCode = reg10.raw;
  
    //turn on ADCCH 
    turnOnADCCH();
 }

 void KT0937::setSWBand()
 {
    this->currentMode = MODE_AM;
    enableSW(1);
    shutDownADCCH();
    
    //low :522 kHz , hex 522kHz / 1kHz = 522 , 0x020A;
    //High:1602 kHz, hex 1602kHz / 1kHz = 1602, 0x0654
    kt09xx_low_chan_0 reg0 ;
    reg0.raw = getRegister(REG_LOW_CHAN0);
    reg0.refined.LOW_CHAN_14_8 =0x23;
    setRegister(REG_LOW_CHAN0,reg0.raw);

    //set band range. LOW_CHAN<7:0> set to 0x0A
    kt09xx_low_chan_1 reg1 ;
    reg1.raw = getRegister(REG_LOW_CHAN1);
    reg1.refined.LOW_CHAN_7_0 =0x28;
    setRegister(REG_LOW_CHAN1,reg1.raw);

    //set band range. write 0x06 into AM_HIGH_CHAN<11:8>
    kt09xx_am_chan_0 reg2 ;
    reg2.raw = getRegister(REG_AMCHAN0);
    reg2.refined.AM_HIGH_CHAN_14_8 =0x27;
    setRegister(REG_AMCHAN0,reg2.raw);

    //set band range. write 0x54 into AM_HIGH_CHAN<7:0>
    kt09xx_am_chan_1 reg3 ;
    reg3.raw = getRegister(REG_AMCHAN1);
    reg3.refined.AM_HIGH_CHAN_7_0 =0x10;
    setRegister(REG_AMCHAN1,reg3.raw);

    //set band range. write 0 into CHAN_NUM<11:8>.
    kt09xx_chan_num_0 reg4 ;
    reg4.raw = getRegister(REG_CHAN_NUM0);
    reg4.refined.CHAN_NUM_11_8 =0x00;
    setRegister(REG_CHAN_NUM0,reg4.raw);

    //set band range. write 0xCD into  CHAN_NUM<7:0>
    kt09xx_chan_num_1 reg5 ;
    reg5.raw = getRegister(REG_CHAN_NUM1);
    reg5.refined.CHAN_NUM_7_0 =0xC8;
    setRegister(REG_CHAN_NUM1,reg5.raw);

    //set AM SPACE. write 0x00 into  AM_SPACE ,set to 1kHz
    kt09xx_bandcfg_3 reg6 ;
    reg6.raw = getRegister(REG_BANDCFG3);
    reg6.refined.SW_SPACE = 1;
    setRegister(REG_BANDCFG3,reg6.raw);

    //set CHAN GUARD. write 0x17 (23) to CH_GUARD
    kt09xx_guard_2 reg7 ;
    reg7.raw = getRegister(REG_GUARD2);
    reg7.refined.CH_GUARD =0x17;
    setRegister(REG_GUARD2,reg7.raw);

    //set CH_ADC_WIN. CH_ADC_WIN<12:0> =  (CHAN_NUM<11:0> + CH_GUARD<7:0>)  * 2   (205(chan)+17(guard))*2 = 456 as 0x 1C8
    //set 0x 00 to <CH_ADC_WIN<12:8>, set 0xFB to <CH_ADC_WIN(7:)    
    kt09xx_adc_3 reg8 ;
    reg8.raw = getRegister(REG_ADC3);
    reg8.refined.CH_ADC_WIN_12_8 = 0x01;
    setRegister(REG_ADC3,reg8.raw);

    kt09xx_adc_4 reg9 ;
    reg9.raw = getRegister(REG_ADC4);
    reg9.refined.CH_ADC_WIN_7_0 = 0xBE;
    setRegister(REG_ADC4,reg9.raw);

    //set AM_FM = 1 register CHANGE_BAND=1, KT0937 can be working in AM channel mode.
    kt09xx_fm_chan_0 reg10 ;
    reg10.raw = getRegister(REG_FMCHAN0);
    reg10.refined.AM_FM =1;
    setRegister(REG_FMCHAN0,reg10.raw);

    reg10.raw = getRegister(REG_FMCHAN0);
    reg10.refined.CHANGE_BAND = 1;
    setRegister(REG_FMCHAN0,reg10.raw);

    reg10.raw = getRegister(REG_FMCHAN0);
    this->errorCode = reg10.raw;  
    //turn on ADCCH 
    turnOnADCCH();
 }


 void KT0937::setSWBand(uint16_t lowFrequency, uint16_t highFrequency, uint16_t chanNumber )
  {
    this->currentMode = MODE_AM;
    enableSW(1);
    shutDownADCCH();
    //calc the lowFrequency
    uint8_t byteHigh = uint8_t((lowFrequency>> 8)& 0x007F);
    uint8_t byteLow = uint8_t((lowFrequency) & 0x00FF);
    
        //low :522 kHz , hex 522kHz / 1kHz = 522 , 0x020A;
    //High:1602 kHz, hex 1602kHz / 1kHz = 1602, 0x0654
    kt09xx_low_chan_0 reg0 ;
    reg0.raw = getRegister(REG_LOW_CHAN0);
    reg0.refined.LOW_CHAN_14_8 =byteHigh;
    setRegister(REG_LOW_CHAN0,reg0.raw);

    //set band range. LOW_CHAN<7:0> set to 0x0A
    kt09xx_low_chan_1 reg1 ;
    reg1.raw = getRegister(REG_LOW_CHAN1);
    reg1.refined.LOW_CHAN_7_0 =byteLow;
    setRegister(REG_LOW_CHAN1,reg1.raw);

    //calc the HighFrequency
    byteHigh = uint8_t((highFrequency >> 8)&0x007F);
    byteLow =uint8_t ((highFrequency) & 0x00FF);
    

    //set band range. write 0x06 into AM_HIGH_CHAN<11:8>
    kt09xx_am_chan_0 reg2 ;
    reg2.raw = getRegister(REG_AMCHAN0);
    reg2.refined.AM_HIGH_CHAN_14_8 =byteHigh;
    setRegister(REG_AMCHAN0,reg2.raw);

    //set band range. write 0x54 into AM_HIGH_CHAN<7:0>
    kt09xx_am_chan_1 reg3 ;
    reg3.raw = getRegister(REG_AMCHAN1);
    reg3.refined.AM_HIGH_CHAN_7_0 =byteLow;
    setRegister(REG_AMCHAN1,reg3.raw);

    //set SW SPACE. write 0x01 into  SW_SPACE ,set to 5kHz
    kt09xx_bandcfg_3 reg6 ;
    reg6.raw = getRegister(REG_BANDCFG3);
    reg6.refined.SW_SPACE = 0;
    setRegister(REG_BANDCFG3,reg6.raw);

    //calc the Channel Number , with sw_space as  step
    byteHigh = uint8_t((chanNumber >> 8)&0x000F);
    byteLow = uint8_t((chanNumber) & 0x00FF);


    //set band range. write 0 into CHAN_NUM<11:8>.
    kt09xx_chan_num_0 reg4 ;
    reg4.raw = getRegister(REG_CHAN_NUM0);
    reg4.refined.CHAN_NUM_11_8 =byteHigh;
    setRegister(REG_CHAN_NUM0,reg4.raw);

    //set band range. write 0xCD into  CHAN_NUM<7:0>
    kt09xx_chan_num_1 reg5 ;
    reg5.raw = getRegister(REG_CHAN_NUM1);
    reg5.refined.CHAN_NUM_7_0 =byteLow;
    setRegister(REG_CHAN_NUM1,reg5.raw);
    
    //set CHAN GUARD. write 0x17 (23) to CH_GUARD
    kt09xx_guard_2 reg7 ;
    reg7.raw = getRegister(REG_GUARD2);
    reg7.refined.CH_GUARD =0x17;
    setRegister(REG_GUARD2,reg7.raw);



    //calc the CH_ADC_WIN
    uint16_t ch_adc_win =0;
    ch_adc_win = (chanNumber + 23) * 2;  // ( channel number  + CH_GUARD ) * 2  
    byteHigh = uint8_t((ch_adc_win >> 8)& 0x001F);
    byteLow = uint8_t((ch_adc_win) & 0x00FF);

    //set CH_ADC_WIN. CH_ADC_WIN<12:0> =  (CHAN_NUM<11:0> + CH_GUARD<7:0>)  * 2   (205(chan)+17(guard))*2 = 456 as 0x 1C8
    //set 0x 00 to <CH_ADC_WIN<12:8>, set 0xFB to <CH_ADC_WIN(7:)    
    kt09xx_adc_3 reg8 ;
    reg8.raw = getRegister(REG_ADC3);
    reg8.refined.CH_ADC_WIN_12_8 = byteHigh;
    setRegister(REG_ADC3,reg8.raw);

    kt09xx_adc_4 reg9 ;
    reg9.raw = getRegister(REG_ADC4);
    reg9.refined.CH_ADC_WIN_7_0 = byteLow;
    setRegister(REG_ADC4,reg9.raw);

  
    //set AM_FM = 1 register CHANGE_BAND=1, KT0937 can be working in AM channel mode.
    kt09xx_fm_chan_0 reg10 ;
    reg10.raw = getRegister(REG_FMCHAN0);
    reg10.refined.AM_FM =1;
    reg10.refined.CHANGE_BAND = 1;
    setRegister(REG_FMCHAN0,reg10.raw);
    delay(5);
    reg10.raw = getRegister(REG_FMCHAN0);
    this->errorCode = reg10.raw;

   //turn on ADCCH 
    turnOnADCCH();

    


 }




 void KT0937::enableDialMode()
 {
    //set CH_PIN<1:0> to  10
    kt09xx_gpiocfg_2 reg ;
    reg.raw = getRegister(REG_GPIOCFG2);
    reg.refined.CH_PIN = 2;
    setRegister(REG_GPIOCFG2,reg.raw);
 }

 void KT0937::disableFMSoftMute(bool disable)
 {
    kt09xx_mutecfg_0 reg;
    reg.raw = getRegister(REG_MUTECFG0);
    reg.refined.FM_DSMUTE = disable;
    setRegister(REG_MUTECFG0,reg.raw);
 }

 void KT0937::disableMWSoftMute(bool disable)
 {
    kt09xx_mutecfg_0 reg;
    reg.raw = getRegister(REG_MUTECFG0);
    reg.refined.MW_DSMUTE = disable;
    setRegister(REG_MUTECFG0,reg.raw);
 }

 void KT0937::disableSWSoftMute(bool disable)
 {
    kt09xx_sw_softmute_0 reg;
    reg.raw = getRegister(REG_SW_SOFTMUTE0);
    reg.refined.SW_DSMUTE = disable;
    setRegister(REG_SW_SOFTMUTE0,reg.raw);
 }

 void KT0937::disableMWAFC(bool disable)
 {
    kt09xx_afc_3 reg;
    reg.raw = getRegister(REG_AFC3);
    reg.refined.MW_AFCD = disable;
    setRegister(REG_AFC3,reg.raw);
 }

 

//disable FM AFC
void KT0937::disableFMAFC(bool disable)
 {
    kt09xx_afc_2 reg;
    reg.raw = getRegister(REG_AFC2);
    reg.refined.FM_AFCD = disable;
    setRegister(REG_AFC2,reg.raw);
 }

 //disable SW AFC
void KT0937::disableSWAFC(bool disable)
 {
    kt09xx_swcfg_0 reg;
    reg.raw = getRegister(REG_SW_CFG0);
    reg.refined.SW_AFCD = disable;
    setRegister(REG_SW_CFG0,reg.raw);
 }


 /* 
 * mwIFBW   000 : 1.2kHz
 *          001 : 2.4kHz
 *          010 : 3.6kHz
 *          011 : 4.8KHz
            100 : 6.0KHz
 *
 */
 
 void KT0937::setAMIFBW(uint8_t mwIFBW)
 {
    kt09xx_amdsp_0 reg;
    reg.raw = getRegister(REG_AMDSP0);
    reg.refined.FLT_SEL = mwIFBW;
    setRegister(REG_AMDSP0,reg.raw);
 }

 uint16_t KT0937::getCurrentFrequency()
 {
    kt09xx_status_6 regH;
    regH.raw = getRegister(REG_STATUS6);
    kt09xx_status_7 regL;
    regL.raw = getRegister(REG_STATUS7);
    this->currentFrequency = ((regH.raw << 8)|regL.raw);
    return this->currentFrequency;

 }


 uint8_t KT0937::getAMRSSI()
{   
    kt09xx_am_status_0 reg;
    reg.raw = getRegister(REG_AMSTATUS0);
    this->currentAMRSSI = reg.refined.AM_RSSI + 3;  //dBm = RSSI -110 ; dBuV = RSSI - 3; dBuVEMF = RSSI + 3; 
    return this->currentAMRSSI;
}

uint8_t KT0937::getAMSNR()
{   
    kt09xx_am_status_2 reg;
    reg.raw = getRegister(REG_AMSTATUS2);
    this->currentAMSNR = reg.refined.AM_SNR_MODE1;  // 0 minimum , 63 maximum
    return this->currentAMSNR;
}

uint8_t KT0937::getFMRSSI()
{   
    kt09xx_status_8 reg;
    reg.raw = getRegister(REG_STATUS8);
    this->currentFMRSSI = reg.refined.FM_RSSI + 3;  //dBm = RSSI -110 ; dBuV = RSSI - 3; dBuVEMF = RSSI + 3; 
    return this->currentFMRSSI;
}

uint8_t KT0937::getFMSNR()
{   
    kt09xx_status_4 reg;
    reg.raw = getRegister(REG_STATUS4);
    this->currentFMSNR = reg.refined.FM_SNR;  // 0 minimum , 63 maximum
    return this->currentFMSNR;
}

uint8_t KT0937::getRSSI()
{
    if(this->currentMode == MODE_AM)
    {
        this->currentRSSI = this->getAMRSSI();
    }else if( this->currentMode == MODE_FM)
    {
        this->currentRSSI = this->getFMRSSI();
    }
    return(this->currentRSSI);
}

uint8_t KT0937::getSNR()
{
    if(this->currentMode == MODE_AM)
    {
        this->currentSNR = this->getAMSNR();
    }else if( this->currentMode == MODE_FM)
    {
        this->currentSNR = this->getFMSNR();
    }
    return(this->currentSNR);

}

/**
 * @ingroup GA03
 * @brief 
 *    Register TUNE_INT_EN is used to enable the interrupt. When TUNE_INT_EN=1, the change of CH pin 
 *voltage will lead to the interrupt signal of INT pin. When TUNE_INT_EN=0, whether CH pin voltage 
 *changes or not, the INT pin will not output the interrupt signal. 
 *
 *   Register TUNE_INT_MODE is used to select the mode of interrupt. When TUNE_INT_MODE=1, 
 *KT0937 will output the pulse interrupt signal. When TUNE_INT_MODE=0, KT0937 will output the level 
 *interrupt signal.
 *  Register TUNE_INT_PL is used to set the polarity of the interrupt signal while tuning. When 
 *TUNE_INT_PL=0, the output of interrupt is low level or negative pulse signal. When TUNE_INT_PL=1, 
 *the output of interrupt is high level or positive pulse signal.
 *   There is no need to clear the interrupt in MCU when it shows the pulse signal, KT0937 can do it 
 *automatically. But if there is a low level signal showed, just set INT_PIN<1:0> in 2b’01 to clear the 
 *interrupt output. And as the case of high level signal, INT_PIN<1:0> should be set in 2b’10 to clear the 
 *interrupt output.
 * 
 * @see enable INT mode
 * 
 * @param 
 * 
 */

void KT0937::setIntMode(bool isRising)
{
    kt09xx_softmute_5 reg0;
    kt09xx_softmute_2 reg1;
    
   
    // set Pulse mode :  positive Pulse (RISING): TUNE_INT_MODE : 0x22<6> = 1, TUNE_INT_PL:0x1F<7> = 1 
    //                   negtive Pulse (FALLING): TUNE_INT_MODE : 0x22<6> = 1, TUNE_INT_PL:0x1F<7> = 0

    if(isRising == INT_MODE_RISING)
    {        
        reg0.raw = getRegister(REG_SOFTMUTE5);
        reg0.refined.TUNE_INT_MODE= 1;        
        setRegister(REG_SOFTMUTE5,reg0.raw);

        reg1.raw = getRegister(REG_SOFTMUTE2);
        reg1.refined.TUNE_INT_PL= 1;
        setRegister(REG_SOFTMUTE2,reg1.raw);

    }else if(isRising == INT_MODE_FALLING)
    {
        reg0.raw = getRegister(REG_SOFTMUTE5);
        reg0.refined.TUNE_INT_MODE= 1;
        setRegister(REG_SOFTMUTE5,reg0.raw);

        reg1.raw = getRegister(REG_SOFTMUTE2);
        reg1.refined.TUNE_INT_PL= 0;
        setRegister(REG_SOFTMUTE2,reg1.raw);
    }

     //set INT Mode TUNE_INT_EN  0x22<7>  to 1
     reg0.raw = getRegister(REG_SOFTMUTE5);
     reg0.refined.TUNE_INT_EN= 1;
     setRegister(REG_SOFTMUTE5,reg0.raw);

    //set INT_PIN to b(00) as auto cleard interrupt signal.
    kt09xx_anacfg_1 reg2;
    reg2.raw = getRegister(REG_ANACFG1);
    reg2.refined.INT_PIN= 0;
    setRegister(REG_ANACFG1,reg2.raw);

}

void KT0937::enableINT()
{
    kt09xx_softmute_5 reg;
    //set INT Mode TUNE_INT_EN  0x22<7>  to 1
    reg.raw = getRegister(REG_SOFTMUTE5);
    reg.refined.TUNE_INT_EN= 1;
    setRegister(REG_SOFTMUTE5,reg.raw);

    //set INT_PIN to b(00) as auto cleard interrupt signal.
    kt09xx_anacfg_1 reg2;
    reg2.raw = getRegister(REG_ANACFG1);
    reg2.refined.INT_PIN= 0;
    setRegister(REG_ANACFG1,reg2.raw);
}

void KT0937::setSWOnPin(int sw_on_pin_temp)
{
    this->swOnPin = sw_on_pin_temp;
}





