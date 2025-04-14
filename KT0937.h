
/**
 * @mainpage PU2CLR KT0937 Arduino Library
 * @brief PU2CLR KT0937 Arduino Library implementation. <br>
 * @details This is an Arduino library for the KT0937, BROADCAST RECEIVER.<br>
 * @details It works with I2C protocol and can provide an easier interface for controlling the KT0937 device.<br>
 * @details This library was built based on KT0937 Datasheet from KTMicro (Monolithic Digital FM/MW/SW/LW Receiver Radio-on-a-Chip TM).
 * @details Others sources help the author to build this library. They are referenced in the documentation for this library on: https://github.com/pu2clr/KT0937
 * @details This library uses the I2C protocols to read and write KT0937 registers. In this context, registers are memory position into the device.
 * @details The KT0937 is a full band AM (LW, MW and SW) and FM DSP receiver that can provide you a easy way to build a high quality radio with low cost.
 * @details This device, will surprise hobbyists and experimenters with its simplicity.
 *
 * This library can be freely distributed using the MIT Free Software model.
 *
 * Copyright (c) 2024 Zhang Yuandong 
 * Copyright (c) 2020 Ricardo Lima Caratti.
 * Contact: pu2clr@gmail.com
 *
 */

 #ifndef _KT0937_H // Prevent this file from being compiled more than once
 #define _KT0937_H


#include <Arduino.h>
#include <Wire.h>

#define KT0937_I2C_ADDRESS 0x35  // It is needed to check it when the KT0937 device arrives.

#define MODE_FM     0
#define MODE_AM     1

#define TURN_ON      1
#define TURN_OFF     0
#define ENABLE_ON    1
#define ENABLE_OFF   0

#define DE_EMPHASIS_75 0
#define DE_EMPHASIS_50 1

#define OSCILLATOR_32KHZ    0      //  32.768KHz
#define OSCILLATOR_6_5MHZ   1      //  6.5MHz
#define OSCILLATOR_7_6MHZ   2      //  7.6MHz
#define OSCILLATOR_12MHZ    3      //  12MHz
#define OSCILLATOR_13MHZ    4      //  13MHz
#define OSCILLATOR_15_2MHZ  5      //  15.2MHz
#define OSCILLATOR_19_2MHZ  6      //  19.2MHz
#define OSCILLATOR_24MHZ    7      //  24MHz
#define OSCILLATOR_26MHZ    8      //  26MHz
#define OSCILLATOR_38KHz    9      //  38KHz

#define REF_CLOCK_ENABLE    1      // Reference Clock
#define REF_CLOCK_DISABLE   0      // Crystal Clock

#define DIAL_MODE_ON        1      // Mechanical tuning (Via 100K resistor)
#define DIAL_MODE_OFF       0      // MCU (Arduino) tuning

#define INT_MODE_RISING     1       //INT pin rising signal as interrupt out.
#define INT_MODE_FALLING    0

/**
* register address 
*/
#define REG_DEVICEID0       0x00
#define REG_DEVICEID1       0x01
#define REG_KTMARK0         0x02
#define REG_KTMARK1         0x03
#define REG_PLLCFG0         0x04
#define REG_PLLCFG1         0x05
#define REG_PLLCFG2         0x06
#define REG_PLLCFG3         0x07
#define REG_SYSCLK_CFG0     0x08
#define REG_SYSCLK_CFG1     0x09
#define REG_SYSCLK_CFG2     0x0A
#define REG_XTALCFG         0x0D
#define REG_RXCFG0          0x0E
#define REG_RXCFG1          0x0F
#define REG_PVTCALI0        0x10
#define REG_BANDCFG0        0x16
#define REG_BANDCFG2        0x18
#define REG_BANDCFG3        0x19
#define REG_MUTECFG0        0x1A
#define REG_G38KCFG0        0x1B
#define REG_G38KCFG1        0x1C
#define REG_SOFTMUTE0       0x1D
#define REG_SOFTMUTE1       0x1E
#define REG_SOFTMUTE2       0x1F
#define REG_SOFTMUTE3       0x20
#define REG_SOFTMUTE4       0x21
#define REG_SOFTMUTE5       0x22
#define REG_SOUNDCFG        0x28
#define REG_FLT_CFG         0x29
#define REG_DSPCFG0         0x2A
#define REG_DSPCFG1         0x2B
#define REG_DSPCFG2         0x2C
#define REG_DSPCFG5         0x2F
#define REG_DSPCFG6         0x30
#define REG_DSPCFG7         0x34
#define REG_DSPCFG8         0x35
#define REG_SW_CFG0         0x38
#define REG_SW_CFG1         0x39
#define REG_SW_CFG2         0x3A
#define REG_AFC2            0x3E
#define REG_AFC3            0x3F
#define REG_ANACFG0         0x4E
#define REG_ANACFG1         0x4F
#define REG_GPIOCFG2        0x51
#define REG_SW_CFG3         0x52
#define REG_AMCALI0         0x55
#define REG_AMCALI1         0x56
#define REG_AMCALI2         0x57
#define REG_AMDSP0          0x62
#define REG_AMDSP1          0x63
#define REG_AMDSP3          0x65
#define REG_AMDSP4          0x66
#define REG_AMDSP5          0x67
#define REG_AMDSP6          0x68
#define REG_AMDSP7          0x69
#define REG_ADC0            0x71
#define REG_ADC3            0x74
#define REG_ADC4            0x75
#define REG_ADC5            0x76
#define REG_STATUS10        0x79
#define REG_FMST_CFG        0x7E
#define REG_FMTUNE_VALID0   0x7F
#define REG_FMTUNE_VALID1   0x80
#define REG_MWTUNE_VALID0   0x81
#define REG_MWTUNE_VALID1   0x82
#define REG_MWTUNE_VALID2   0x83
#define REG_MWTUNE_VALID3   0x84
#define REG_SPARE2          0x87
#define REG_FMCHAN0         0x88
#define REG_FMCHAN1         0x89
#define REG_AMCHAN0         0x8C
#define REG_AMCHAN1         0x8D
#define REG_LOW_CHAN0       0x98
#define REG_LOW_CHAN1       0x99
#define REG_CHAN_NUM0       0x9A
#define REG_CHAN_NUM1       0x9B
#define REG_GUARD2          0xA0
#define REG_STATUS0         0xDE
#define REG_STATUS4         0xE2
#define REG_STATUS5         0xE3
#define REG_STATUS6         0xE4
#define REG_STATUS7         0xE5
#define REG_STATUS8         0xE6
#define REG_AFC_STATUS0     0xE8
#define REG_AFC_STATUS1     0xE9
#define REG_AMSTATUS0       0xEA
#define REG_AMSTATUS2       0xEC
#define REG_AMSTATUS3       0xED
#define REG_SWTUNE_VALID0   0xF0
#define REG_SWTUNE_VALID1   0xF1
#define REG_SWTUNE_VALID2   0xF2
#define REG_SWTUNE_VALID3   0xF3
#define REG_SW_SOFTMUTE0    0XF4
#define REG_SW_SOFTMUTE1    0XF5
#define REG_SW_SOFTMUTE2    0XF6
#define REG_SW_SOFTMUTE3    0xF7


/*
* error code 
*/
#define ERR_OK 0
#define ERR_POWER_ON 1
#define ERR_CLK 2
#define ERR_SW_PIN 3

/*
* MW IF BandWidth
*/

#define AM_IF_1_2KHZ 0
#define AM_IF_2_4KHZ 1
#define AM_IF_3_6KHZ 2
#define AM_IF_4_8KHZ 3
#define AM_IF_6_0KHZ 4










/**
 * @defgroup GA01 Union, Structure and Defined Data Types
 * @brief   KT0937 Defined Data Types
 * @details Defined Data Types is a way to represent the KT0937 registers information
 * @details Some information appears to be inaccurate due to translation problems from Chinese to English.
 * @details The information shown here was extracted from Datasheet:
 * @details KT0937 stereo FM / TV / MW / SW / LW digital tuning radio documentation.
 * @details Other information seems incomplete even in the original Chinese Datasheet.
 * @details For example: Reg 10 (0x0A). There is no information about it. The Reg11 and 12 seem wrong
 */

/**
 * @ingroup GA01
 * @brief 0.1 DEVICEID0 (Address 0x0000)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    uint8_t deviceid0;  //!< Default value:0x82 
} kt09xx_device_id_0;


/**
 * @ingroup GA01
 * @brief 0.1 DEVICEID1 (Address 0x0001)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    uint8_t deviceid1; //!<Default Value: 0x06
} kt09xx_device_id_1;

/**
 * @ingroup GA01
 * @brief 0.1 KTMARK0 (Address 0x0002)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    uint8_t ktmark0;  //!<Default Value: 0x4B  'K'
    char ktmask0_ascii;
} kt09xx_ktmask_0;

/**
 * @ingroup GA01
 * @brief 0.1 KTMARK1 (Address 0x0003)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    uint8_t ktmark1; //!Deault Value: 0x54 'T'
    char ktmask1_ascii;
} kt09xx_ktmask_1;



/**
 * @ingroup GA01
 * @brief 0.1 PLLCFG0 (Address 0x0004)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    struct
    {
        uint8_t DIVIDERP_10_8 : 3;   //!< Default Value: B(000)PLL divider P configuration.
        uint8_t RESERVED : 4;   //!< Default Value: B(000_0)Reserved.
        uint8_t SYS_CFGOK : 1;   //!< Default Value: B(0) Clock initialization completed.
        
    } refined;
    uint8_t raw;
} kt09xx_pllcfg_0;

/**
 * @ingroup GA01
 * @brief 0.1 PLLCFG1 (Address 0x0005)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    struct
    {
        uint8_t DIVIDERP_7_0 : 8;   //!< Default Value: 0x01 Clock PLL divider P configuration.
    } refined;
    uint8_t raw;
} kt09xx_pllcfg_1;

/**
 * @ingroup GA01
 * @brief 0.1 PLLCFG2 (Address 0x0006)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    struct
    {
        uint8_t DIVIDERN_10_8 : 3;   //!< Default Value B(010) PLL divider N configuration. .
        uint8_t RESERVED : 5;        //!< Default Value B(0000_0)
    } refined;
    uint8_t raw;
} kt09xx_pllcfg_2;

/**
 * @ingroup GA01
 * @brief 0.1 PLLCFG3 (Address 0x0007)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    struct
    {
        uint8_t DIVIDERN_7_0 : 8;   //!< Default Value 0x9c  PLL divider N configuration. .
    } refined;
    uint8_t raw;
} kt09xx_pllcfg_3;

/**
 * @ingroup GA01
 * @brief 0.1 SYSCLK_CFG0(Address 0x0008)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    struct
    {
        uint8_t FPFD_19_16: 4;   //!< Default Value B(1000)  Phase-detection Frequency. FPFD<19:0> = External Xtal clock or RCLK frequency / 
        uint8_t RESERVED : 4;    //!< Default Value B(0000) 
    } refined;
    uint8_t raw;
} kt09xx_sysclk_cfg_0;

/**
 * @ingroup GA01
 * @brief 0.1 SYSCLK_CFG1(Address 0x0009)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    struct
    {
        uint8_t FPFD_15_8: 8;   //!< Default Value 0x00  Phase-detection Frequency. FPFD<19:0> = External Xtal clock or RCLK frequency / 
    } refined;
    uint8_t raw;
} kt09xx_sysclk_cfg_1;

/**
 * @ingroup GA01
 * @brief 0.1 SYSCLK_CFG1(Address 0x000A)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    struct
    {
        uint8_t FPFD_7_0: 8;   //!< Default Value 0x00  Phase-detection Frequency. FPFD<19:0> = External Xtal clock or RCLK frequency / 
    } refined;
    uint8_t raw;
} kt09xx_sysclk_cfg_2;

/**
 * @ingroup GA01
 * @brief 0.1 XTALCFG (Address 0x000D)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    struct
    {
        uint8_t RESERVED0 : 4; //!<Default Value B(0011) 
        uint8_t RCLK_EN : 1;   //!< Default Value B(0)  Reference Clock Enable. 0 = Crystal. 1 = External reference clock. 
        uint8_t RESERVED1 : 3; //!< Default Value B(110) 
    } refined;
    uint8_t raw;
} kt09xx_xtalcfg; //XTALCFG

/**
 * @ingroup GA01
 * @brief 0.1 RXCFG0 (Address 0x000E)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    struct
    {
        uint8_t RESERVED1 : 4; //!<Default Value B(0000)  
        uint8_t DSP_RST : 1;   //!< Default Value B(0)  DSP Reset
        uint8_t STDBY : 1;   //!< Default Value B(0)  Standby Mode Control.0 = Normal operation. 1 = Standby mode.
        uint8_t RESERVED0 : 2; //!< Default Value B(00)
    } refined;
    uint8_t raw;
} kt09xx_rxcfg_0;

/**
 * @ingroup GA01
 * @brief 0.1 RXCFG1(Address 0x000F)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    struct
    {
        
        uint8_t VOLUME : 5;   //!< Default Value B(1_1111)  Volume Control Bits:\
                                    11111 = 0dB   \
                                    11110 = -2dB  \
                                    11101 = -4dB  \
                                    ......        \
                                    00010 = -58dB \
                                    00001 = -60dB \
                                    00000 = Mute 
        uint8_t RESERVED : 3; //!< Default Value B(000)
    } refined;
    uint8_t raw;    
} kt09xx_rxcfg_1;

/**
 * @ingroup GA01
 * @brief 0.1 PVTCALI0 (Address 0x0010)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    struct
    {
        uint8_t RESERVED1 :6; //!<Default Value B(00_000)  
        uint8_t STBYLDO_CALI_EN : 1; //!< Default Value B(0)  Standby LDO Calibration Enable.\
                                        0 = Disable.\
                                        1 = Enable.
        uint8_t RESERVED0 : 1; //!< Default Value B(0)
    } refined;
    uint8_t raw;
} kt09xx_pvtcali_0;

/**
 * @ingroup GA01
 * @brief 0.1 BANDCFG0 (Address 0x0016)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    struct
    {
        uint8_t RESERVED1 : 4; //!<Default Value B(1010)  
        uint8_t SW_EN : 1;   //!< Default Value B(0)  Short Wave Enable Control:0 = Disable 1 = Enable        
        uint8_t RESERVED0 : 3; //!< Default Value B(100)
    } refined;
    uint8_t raw;
} kt09xx_bandcfg_0;

/**
 * @ingroup GA01
 * @brief 0.1 BANDCFG2 (Address 0x0018)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 22.
 */
typedef union {
    struct
    {       
        uint8_t MW_SPACE : 2; //!<Default Value B(01) MW Band Space Selection.  00 = 1kHz\
                                                                                01 = 9kHz\
                                                                                10 = 10kHz\
                                                                                11 =10kHz
        uint8_t RESERVED1 : 2; //!<Default Value B(10)  
        uint8_t FM_SPACE : 2;   //!< Default Value B(01)  FM Band Space Selection.\
                                    00 = 200 kHz (USA, Europe)\
                                    01 = 100KHz (Europe, Japan)\
                                    10 = 50KHz\
                                    11 = 50KHz
        
        
        uint8_t RESERVED0 : 2; //!< Default Value B(01)
    } refined;
    uint8_t raw;
} kt09xx_bandcfg_2;

/**
 * @ingroup GA01
 * @brief 0.1 BANDCFG3 (Address 0x0019)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
        uint8_t SW_SPACE : 2; //!<Default Value B(01) MW Band Space Selection.  00 = 1kHz\
                                                                                01 = 5kHz\
                                                                                10 = 9kHz\
                                                                                11 =10kHz
        uint8_t FM_SMUTE_MIN_GAIN : 3;   //!< Default Value B(100)  The Total Attenuation of \
                                                Volume Can Be Configured:\
                                                000 = -9dB\
                                                001 = -12dB\
                                                010 = -15dB\
                                                011 = -18dB\
                                                100 = -21dB\
                                                101 = -24dB\
                                                110 = -27dB\
                                                111 = -30dB
        uint8_t MW_SMUTE_MIN_GAIN : 3; //!< Default Value B(001). The Total Attenuation of \
                                        Volume CanBe Configured:000 = -9dB\
                                                                001 = -12dB\
                                                                010 = -15dB\
                                                                011 = -18dB\
                                                                100 = -21dB\
                                                                101 = -24dB\
                                                                110 = -27dB\
                                                                111 = -30dB
        
    } refined;
    uint8_t raw;
} kt09xx_bandcfg_3;

/**
 * @ingroup GA01
 * @brief 0.1 MUTECFG0 (Address 0x001A)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
        uint8_t RESERVED : 6; //!<Default Value B(00_1000) 
        uint8_t MW_DSMUTE : 1;   //!< Default Value B(0)  MW Softmute Disable.0=MWsoftmuteenable.1=MWsoftmutedisable.
        uint8_t FM_DSMUTE : 1; //!< Default Value B(0). FM Softmute Disable. 0=FMsoftmuteenable.1=FMsoftmutedisable. 
    } refined;
    uint8_t raw;
} kt09xx_mutecfg_0;

/**
 * @ingroup GA01
 * @brief 0.1 G38KCFG0 (Address 0x001B)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
        uint8_t RESERVED1 : 2; //!<Default Value B(00)
        uint8_t POWERON_FINISH : 1;   //!< Default Value B(0)  Power On Flow Finish Flag.0=Initialization. 1 = Finish.
        uint8_t RESERVED0 : 5; //!< Default Value B(1000_0).  
    } refined;
    uint8_t raw;
} kt09xx_g38kcfg_0;

/**
 * @ingroup GA01
 * @brief 0.1 G38KCFG1 (Address 0x001C)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
        uint8_t ST_DEMOD : 8; //!< Default Value 0x00.  Stereo Demodulation Indicator.0x00 = Mono. Others = Stereo.
    } refined;
    uint8_t raw;
} kt09xx_g38kcfg_1;

/**
 * @ingroup GA01
 * @brief 0.1 SOFTMUTE0 (Address 0x001D)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
        uint8_t MW_SMUTE_START_RSSI: 7 ; //!< Default Value B(001_0111). The Starting Level of Attenuation According to RSSI inMWMode.
        uint8_t RESERVED : 1; //!< Default Value B(1). 
    } refined;
    uint8_t raw;
} kt09xx_softmute_0;

/**
 * @ingroup GA01
 * @brief 0.1 SOFTMUTE1 (Address 0x001E)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
       
        uint8_t MW_SMUTE_SLOPE_RSSI: 3 ; //!< Default Value B(100). The Slope of Attenuation According to RSSI in AM Mode.\
                                                000=4\
                                                001=3\
                                                010=2\
                                                011=1\
                                                100=1/2\
                                                101=1/3\
                                                110=1/4\
                                                111=0
         uint8_t RESERVED : 5; //!< Default Value B(0010_0).  
        
    } refined;
    uint8_t raw;
} kt09xx_softmute_1;

/**
 * @ingroup GA01
 * @brief 0.1 SOFTMUTE2 (Address 0x001F)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
        uint8_t FM_SMUTE_SLOPE_RSSI : 3; //!< Default Value B(011). The Slope of Attenuation According to RSSI in FM Mode:\
                                            000 = 4\
                                            001 = 3\
                                            010 = 2\
                                            011 = 1\
                                            100 = 1/2\
                                            101 = 1/3\
                                            110 = 1/4\
                                            111 = 0
        uint8_t RESERVED : 1; //!< Default Value B(0)
        uint8_t FM_SMUTE_START_RSSI: 3 ; //!< Default Value B(101). The Starting Level of \
                                            Attenuation According to RSSIinFMMode:\
                                            000 = 22 dBuVEMF\
                                            001 = 20 dBuVEMF\
                                            010 = 18 dBuVEMF\
                                            011 = 16 dBuVEMF\
                                            100 = 14 dBuVEMF\
                                            101 = 12 dBuVEMF\
                                            110 = 10 dBuVEMF\
                                            111 = 8 dBuVEMF
        uint8_t TUNE_INT_PL : 1; //!< Default Value B(0). Interrupt Polarity.0 = INT interrupt is active low.1 = INT interrupt is active high. 

    } refined;
    uint8_t raw;
} kt09xx_softmute_2;

/**
 * @ingroup GA01
 * @brief 0.1 SOFTMUTE3 (Address 0x0020)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 26.
 */
typedef union {
    struct
    {
        uint8_t MW_SMUTE_START_SNR: 7 ; //!< Default Value B(011_0000). The Starting Level of \
                                            Attenuation According to SNR inMWMode.\
                                            000_0000 = 0\
                                            000_0001 = 1\
                                            ...... \
                                            111_1110 = 126\
                                            111_1111 = 127
        uint8_t RESERVED : 1; //!< Default Value B(0).         
    } refined;
    uint8_t raw;
} kt09xx_softmute_3;

/**
 * @ingroup GA01
 * @brief 0.1 SOFTMUTE4 (Address 0x0021)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
        uint8_t FM_SMUTE_SLOPE_SNR : 3; //!< Default Value B(010). The Slope of Attenuation According to SNR in FM Mode:\
                                            000 = 4\
                                            001 = 3\
                                            010 = 2\
                                            011 = 1\
                                            100 = 1/2\
                                            101 = 1/3 \
                                            110 = 1/4 \
                                            111 = 0
        
        
        uint8_t RESERVED1 : 1; //!< Default Value B(0)
        uint8_t MW_SMUTE_SLOPE_SNR: 3 ; //!< Default Value B(000).The Slope of Attenuation According to SNR in MW Mode:\
                                        000 = 4\
                                        001 = 3\
                                        010 = 2\
                                        011 = 1\
                                        100 = 1/2\
                                        101 = 1/3\
                                        110 = 1/4\
                                        111 = 0
        
        
        uint8_t RESERVED0 : 1; //!< Default Value B(0).                                             
    } refined;
    uint8_t raw;
} kt09xx_softmute_4;

/**
 * @ingroup GA01
 * @brief 0.1 SOFTMUTE5 (Address 0x0022)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
        uint8_t FM_SMUTE_START_SNR : 6; //!< Default Value B(01_0101). The Starting Level of \
                                            Attenuation According to SNR inFMMode.\
                                            00_0000 = 0\
                                            00_0001 = 1\
                                            ......\
                                            11_1110 = 62\
                                            11_1111 = 63        
        uint8_t RESERVED : 1; //!< Default Value B(0)
        uint8_t TUNE_INT_MODE: 1 ; //!< Default Value B(0).Tune Interrupt Mode Selection.\
                                    This bit selects whether the configured INT interrupt will be edge or level sensitive.\
                                                        0 = INT is level triggered.\
                                                        1 = INT is edge triggered.            
        uint8_t TUNE_INT_EN : 1; //!< Default Value B(0). Tune Interrupt Output Enable Bit.\
                                                        0 = Disable.\
                                                        1 = Enable.                        
    } refined;
    uint8_t raw;
} kt09xx_softmute_5;

/**
 * @ingroup GA01
 * @brief 0.1 SOUNDCFG (Address 0x0028)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
        uint8_t RESERVED1 : 4; //!< Default Value B(1101) 
        uint8_t BASS: 2 ; //!< Default Value B(00).Bass Boost Effect Mode Selection:\
                                00 = Bypass\
                                01 = 9.4 dB@70Hz\
                                10 = 13.3dB@70Hz\
                                11 = 18.2dB@70Hz
                                         
        uint8_t RESERVED0 : 2; //!< Default Value B(00). 
    } refined;
    uint8_t raw;
} kt09xx_soundcfg;

/**
 * @ingroup GA01
 * @brief 0.1 FLTCFG (Address 0x0029)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
        uint8_t RESERVED1 : 4; //!< Default Value B(0000)
        uint8_t BLEND_MOD: 1 ; //!< Default Value B(0).Blend Mode Selection:    0=RSSImode  1=SNRmode        
        uint8_t RESERVED0 : 3; //!< Default Value B(000).                                   
    } refined;
    uint8_t raw;
} kt09xx_fltcfg;

/**
 * @ingroup GA01
 * @brief 0.1 DSPCFG0 (Address 0x002A)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
        uint8_t RESERVED1 : 4; //!< Default Value B(0000)
        uint8_t FM_GAIN: 3 ; //!< Default Value B(100).Audio Gain for FM Audio Processor:\
                                        000= 0dB\
                                        001 = 3.5dB\
                                        010 = 6dB\
                                        011 = 9.5dB\
                                        100 = -2.5dB\
                                        101 = -3.66dB\
                                        110 = -6dB\
                                        111 = -8.5dB
        
        uint8_t RESERVED0 : 1; //!< Default Value B(1).                                   
    } refined;
    uint8_t raw;
} kt09xx_dspcfg_0;

/**
 * @ingroup GA01
 * @brief 0.1 DSPCFG1 (Address 0x002B)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
        
        uint8_t DBLEND : 1;   //!<Default Value B(0) .Blend Disable:0 = Blend enable 1 = Blend disable
        uint8_t RESERVED1 : 2; //!<Default Value B(00)       
        uint8_t DE : 1; //!< Default Value B(1)  De-emphasis Time Constant Selection:\
                                    0 = 75us. Used in USA.\
                                    1 = 50us. Used in Europe,Australia, Japan 
        uint8_t RESERVED0 : 3; //!< Default Value B(010).       
        uint8_t MONO : 1; //!< Default Value B(1). Mono Selection:0 = Stereo 1 = Force mono                            
    } refined;
    uint8_t raw;
} kt09xx_dspcfg_1;

/**
 * @ingroup GA01
 * @brief 0.1 DSPCFG2 (Address 0x002C)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
        uint8_t BLEND_STOP_RSSI : 4; //!< Default Value B(1111).The Ending Value of Blend According to RSSI in FM Mode:\
                                            0000 = 8dbuVEMF\
                                            0001 = 10dbuVEMF\
                                            0010 = 12dbuVEMF \
                                            0011 = 14dbuVEMF \
                                            0100 = 16dbuVEMF \
                                            0101 = 18dbuVEMF \
                                            0110 = 20dbuVEMF \
                                            0111 = 22dbuVEMF \
                                            1000 = 24dbuVEMF \
                                            1001 = 26dbuVEMF \
                                            1010 = 28dbuVEMF \
                                            1011 = 30dbuVEMF \
                                            1100 = 32dbuVEMF \
                                            1101 = 34dbuVEMF \
                                            1110 = 36dbuVEMF \
                                            1111 = 38dbuVEMF
        uint8_t BLEND_START_RSSI : 4; //!< Default Value B(0101). The Starting Value of Blend According to RSSI in FM  Mode:\
                                            0000 = 8dbuVEMF\
                                            0001 = 10dbuVEMF\
                                            0010 = 12dbuVEMF\
                                            0011 = 14dbuVEMF\
                                            0100 = 16dbuVEMF\
                                            0101 = 18dbuVEMF\
                                            0110 = 20dbuVEMF\
                                            0111 = 22dbuVEMF\
                                            1000 = 24dbuVEMF\
                                            1001 = 26dbuVEMF\
                                            1010 = 28dbuVEMF\
                                            1011 = 30dbuVEMF\
                                            1100 = 32dbuVEMF\
                                            1101 = 34dbuVEMF\
                                            1110 = 36dbuVEMF\
                                            1111 = 38dbuVEMF
        
        
                                  
    } refined;
    uint8_t raw;
} kt09xx_dspcfg_2;

/**
 * @ingroup GA01
 * @brief 0.1 DSPCFG5 (Address 0x002F)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
        uint8_t AM_SEL_ENHANCE : 1;   //!<Default Value B(0) .AM Channel Selectivity Enhance.0 = Disable.1 = Enable.
        uint8_t SMUTE_FILTER_EN : 1;   //!<Default Value B(0) .Softmute Filter Enable.0 = Disable.1 = Enable. 
        uint8_t AM_SUP_ENHANCE : 1;   //!<Default Value B(0) .AM suppression Enhance.0 = Disable.1 = Enable. 
        uint8_t RESERVED1 : 1; //!<Default Value B(0) 
        uint8_t BLEND_COMBO_MODE : 1; //!< Default Value B(0).  Blend Combo Mode Enable Bit.\
                                            0 = Disable combo Mode.\
                                            1 = Enable combo Mode.
        uint8_t ANT_CALI_SWITCH_BAND : 1; //!< Default Value B(0).Antenna Calibrate When Switching Band.\
                                            0 = Disable.\
                                            1 = Enable. 
        uint8_t RESERVED0: 2; //!< Default Value B(00).                       
    } refined;
    uint8_t raw;
} kt09xx_dspcfg_5;

/**
 * @ingroup GA01
 * @brief 0.1 DSPCFG6 (Address 0x0030)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
        uint8_t FM_RSSI_BIAS : 5; //!< Default Value B(0_0000).FM RSSI Bias: \
                                    10000 = -16dB\
                                    10001 = -15dB\
                                    ......\
                                    11110 = -2dB \
                                    11111 = -1dB \
                                    00000 = 0dB\
                                    00001 = 1dB\
                                    ......\
                                    01111 = 15dB
        uint8_t RESERVED : 3; //!< Default Value B(00). 

    } refined;
    uint8_t raw;
} kt09xx_dspcfg_6;

/**
 * @ingroup GA01
 * @brief 0.1 DSPCFG7 (Address 0x0034)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 24.
 */
typedef union {
    struct
    {
        
        uint8_t BLEND_START_SNR : 6;//!<Default Value B(00_0000). The Stop Level of Blend According to SNR in FM Mode.\
                                        When the starting value meets \
                                        the ending value, it is separated immediately.
        uint8_t RESERVED : 2; //!< Default Value B(00). 

    } refined;
    uint8_t raw;
} kt09xx_dspcfg_7;

/**
 * @ingroup GA01
 * @brief 0.1 DSPCFG8 (Address 0x0035)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 30.
 */
typedef union {
    struct
    {
        
        uint8_t BLEND_STOP_SNR : 6;//!<Default Value B(00_0000). The Stop Level of Blend \
                                        According to SNR in FM \
                                        Mode.\
                                        When the starting value meets \
                                        the ending value, it is separated immediately.
        uint8_t RESERVED : 2; //!< Default Value B(00). 

    } refined;
    uint8_t raw;
} kt09xx_dspcfg_8;

/**
 * @ingroup GA01
 * @brief 0.1 SW_CFG0 (Address 0x0038)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 30.
 */
typedef union {
    struct
    {       
        uint8_t SW_GAIN : 4;   //!<Default Value B(0100).   Audio Gain for SW Audio Processor:\
                                            0000 = 6dB\
                                            0001 = 3dB\
                                            0010 = 0dB\
                                            0011 = -3dB\
                                            0100 = -6dB\
                                            0101 = -9dB\
                                            0110 = -12dB\
                                            0111 = -15dB\
                                            1000 = -18dB
        uint8_t BLEND_SSW_BBAGC_RATIO : 3;//!<Default Value B(101). SW Baseband AGC Ratio:000 = 1/inf.\
                                            001 = 1/16\
                                            010 = 1/8\
                                            011 = 1/4\
                                            100 = 1/3\
                                            101 = 1/2\
                                            110 = Reserved\
                                            111 = Reserved
        uint8_t SW_AFCD : 1; //!< Default Value B(0). AFC Disable Control Bit in SW Mode:0=AFCenable 1=AFCdisable

    } refined;
    uint8_t raw;
} kt09xx_swcfg_0;

/**
 * @ingroup GA01
 * @brief 0.1 SW_CFG1 (Address 0x0039)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 30.
 */
typedef union {
    struct
    {
        
        uint8_t SW_VOLUME : 4;//!<Default Value B(1010). SW Volume Control Bits:\
                                1111 = 0dB\
                                1110 = -0.5dB\
                                1101 =-1.0dB \
                                1100 = -1.5dB \
                                1011 = -2.0dB \
                                1010 = -2.5dB \
                                1001 = -3.0dB \
                                1000 = -3.5dB \
                                0111 = -4.0dB \
                                0110 = -4.5dB \
                                0101 = -5.0dB \
                                0100 = -5.5dB \
                                0011 = -6.0dB \
                                0010 = -6.5dB \
                                0001 = -7.0dB \
                                0000 = -7.5dB
        uint8_t RESERVED : 4; //!< Default Value B(0000). 

                                                                          
    } refined;
    uint8_t raw;
} kt09xx_swcfg_1;

/**
 * @ingroup GA01
 * @brief 0.1 SW_CFG2(Address 0x003A)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 30.
 */
typedef union {
    struct
    {
        
        uint8_t SW_BBAGC_HI_TH : 6;//!<Default Value B(01_1011). SW Baseband AGC High Threshold:\
                                    0 = 0dBm\
                                    1= -3dBm\
                                    2=--6dBm\
                                    ......\
                                    32= -96dBm \
                                    33= -99dBm  
        uint8_t RESERVED : 2; //!< Default Value B(00).                                                                         
    } refined;
    uint8_t raw;
} kt09xx_swcfg_2;

/**
 * @ingroup GA01
 * @brief 0.1 AFC2 (Address 0x003E)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 30.
 */
typedef union {
    struct
    {
        
        uint8_t FM_TH_AFC : 3;//!<Default Value B(011).Programmable threshold for FM AFC △F digital IF offset that can be adjusted in FM mode:\
                                000 = 5k\
                                001 = 15k\
                                010 = 25k\
                                011 = 35k\
                                100 = 50k\
                                101 = 100k\
                                110 = 150k\
                                111 = 200k
        uint8_t RESERVED1 : 3;//!<Default Value B(000). 
        uint8_t FM_AFCD  : 1;//!<Default Value B(0). AFC Disable Control Bit in FM Mode:0=AFCenable.1=AFCdisable. 
        uint8_t RESERVED0 : 1; //!< Default Value B(00). 
                                        

    } refined;
    uint8_t raw;
} kt09xx_afc_2;

/**
 * @ingroup GA01
 * @brief 0.1 AFC3(Address 0x003F)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 30.
 */
typedef union {
    struct
    {
        uint8_t MW_TH_AFC : 3;//!<Default Value B(000).MW AFC Threshold:\
                                    000 = 2944Hz\
                                    001 = 4992Hz\
                                    010 = 6016Hz\
                                    011 = 8064Hz\
                                    100 = 9984Hz\
                                    101 =12032 Hz\
                                    110 = 14976 Hz\
                                    111 = 16256 Hz 
        uint8_t RESERVED1 : 3;//!<Default Value B(000). 
        uint8_t MW_AFCD  : 1;//!<Default Value B(0). AFC Disable Control Bit in MW Mode:0=AFCenable.1=AFCdisable.                                        
        uint8_t RESERVED0 : 1; //!< Default Value B(00).
    } refined;
    uint8_t raw;
} kt09xx_afc_3;

/**
 * @ingroup GA01
 * @brief 0.1 ANACFG0 (Address 0x004E)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t AUDV_DCLVL : 3;//!<Default Value B(010).Audio Output Common Voltage:\
                                    000= 0.85v\
                                    001=0.91v\
                                    010= 1.05v\
                                    011= 1.15v\
                                    100= 1.20v\
                                    101= 1.35v\
                                    110= 1.50v\
                                    111=1.60v
        uint8_t RESERVED1 : 1;//!<Default Value B(0).
        uint8_t DEPOP_TC  : 2;//!<Default Value B(11). De-pop Time Constant:00 = 250ms\
                                01 = 500ms\
                                10 = 750ms\
                                11 = 1s
        uint8_t RESERVED0 : 2; //!< Default Value B(00).               
    } refined;
    uint8_t raw;
} kt09xx_anacfg_0;

/**
 * @ingroup GA01
 * @brief 0.1 ANACFG1 (Address 0x004F)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t INT_PIN  : 2;//!<Default Value B(10). INT pin function control:00 = Reserved.\
                                01 = Output high.\
                                10 = Output low.\
                                11 = Reserved.
        uint8_t RESERVED : 6; //!< Default Value B(1000_00).                          
    } refined;
    uint8_t raw;
} kt09xx_anacfg_1;

/**
 * @ingroup GA01
 * @brief 0.1 GPIOCFG2 (Address 0x0051)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t CH_PIN  : 2;//!<Default Value B(00). CH pin function control.\
                                00 = high Z.\
                                01 = Key controlled channel increase / decrease input.\
                                10 = Dial controlled channel increase / decrease input.\
                                11 = Reserved.
        uint8_t RESERVED : 6; //!< Default Value B(0000_00).                         
    } refined;
    uint8_t raw;
} kt09xx_gpiocfg_2;

/**
 * @ingroup GA01
 * @brief 0.1 SW_CFG3(Address 0x0052)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t SW_BBAGC_LOW_TH  : 6;//!<Default Value B(01_0110).SW Baseband AGC Low Threshold:\
                                            0 = 0dBm\
                                            1= -3dBm\
                                            2=--6dBm \
                                            ......\
                                            32= -96dBm \
                                            33= -99dBm 
        uint8_t RESERVED : 2; //!< Default Value B(00).                                            
    } refined;
    uint8_t raw;
} kt09xx_swcfg_3;

/**
 * @ingroup GA01
 * @brief 0.1 AMCALI0 (Address 0x0055)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t MW_Q : 3; //!<Default Value B(100)  MW Antenna Q Factor Control.\
                                000 = Minimum Q factor.\
                                ......\
                                111 = Maximum Q factor.
        uint8_t SW_TH_AFC  : 3;//!<Default Value B(00_0). SW AFC Threshold:000 = 2944Hz\
                                001 = 4992Hz\
                                010 = 6016Hz\
                                011 = 8064Hz\
                                100 = 9984Hz\
                                101 = 12032 Hz\
                                110 = 14976 Hz\
                                111 = 16256 Hz 
        uint8_t RESERVED : 2; //!< Default Value B(00).                                               
    } refined;
    uint8_t raw;
} kt09xx_amcali_0;

/**
 * @ingroup GA01
 * @brief 0.1 AMCALI1(Address 0x0056)   
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t CAP_13_8  : 6;//!<Default Value B(11_1111). High 6 Bits of Capacitor for LC Tank:\
                                    0x0000 = Minimum Capacitor.\
                                    ......\
                                    0x3FFF = Maximum Capacitor.
        uint8_t RESERVED : 2; //!< Default Value B(00).                             
    } refined;
    uint8_t raw;
} kt09xx_amcali_1;

/**
 * @ingroup GA01
 * @brief 0.1 AMCALI2(Address 0x0057)   
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t CAP_7_0  : 8;//!<Default Value B(1110_1111). Low 8 Bits of Capacitor for LC Tank:\
                                    0x0000 = Minimum Capacitor.\
                                    ......\
                                    0x3FFF = Maximum Capacitor.
    } refined;
    uint8_t raw;
} kt09xx_amcali_2;

/**
 * @ingroup GA01
 * @brief 0.1 AMDSP0 (Address 0x0062)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t FLT_SEL : 3; //!<Default Value B(001)  AM Channel Filter \
                                    Bandwidth Selection:000=1.2KHz\
                                    001=2.4KHz\
                                    010=3.6KHz\
                                    011=4.8KHz\
                                    100=6.0KHz
        uint8_t RESERVED  : 1;//!<Default Value B(0).
        uint8_t MW_GAIN : 4; //!< Default Value B(0100).Audio Gain for MW Audio Processor:\
                                0000 = 6dB\
                                0001 = 3dB\
                                0010 = 0dB\
                                0011 = -3dB\
                                0100 = -6dB\
                                0101 = -9dB\
                                0110 = -12dB\
                                0111 = -15dB \
                                1000 = -18dB                               
    } refined;
    uint8_t raw;
} kt09xx_amdsp_0;


/**
 * @ingroup GA01
 * @brief 0.1 AMDSP1 (Address 0x0063)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t AM_RSSI_BIAS  : 5;//!<Default Value B(00_0). AM RSSI Bias.\
                                    10000 = -16dB \
                                    10001 = -15dB\
                                    .....\
                                    11110 = -2dB \
                                    11111 = -1dB\
                                    00000 = 0dB\
                                    00001 = 1dB \
                                    ......\
                                    01111 = 15dB
        uint8_t RESERVED : 3; //!< Default Value B(000).                              
    } refined;
    uint8_t raw;
} kt09xx_amdsp_1;

/**
 * @ingroup GA01
 * @brief 0.1 AMDSP3 (Address 0x0065)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t AM_BBAGC_BW : 3; //!<Default Value B(000) AM Baseband AGC \
                                    Bandwidth Selection:\
                                    000 = Minimum Bandwidth\
                                    ......\
                                    111 = Maximum Bandwidth
        uint8_t RESERVED1 : 1; //!<Default Value B(0) 
        uint8_t MW_BBAGC_RATIO  : 3;//!<Default Value B(101). MW Baseband AGC Ratio:\
                                        000 = 1/inf.\
                                        001 = 1/16\
                                        010 = 1/8\
                                        011 = 1/4\
                                        100 = 1/3\
                                        101 = 1/2\
                                        110 = Reserved\
                                        111 = Reserved  
        uint8_t RESERVED0 : 1; //!< Default Value B(1).                                                           
    } refined;
    uint8_t raw;
} kt09xx_amdsp_3;

/**
 * @ingroup GA01
 * @brief 0.1 AMDSP4 (Address 0x0066)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t AM_SNR_MODE_SEL  : 3;//!<Default Value B(000). AM SNR Mode Selection:\
                                    000 = AM_SNR_MODE1 \
                                    001 = AM_SNR_MODE2 \
                                    010 = AM_SNR_MODE2\
                                    011 = AM_SNR_MODE2 \
                                    100 = Reserved\
                                    101 = Reserved\
                                    110 = Reserved\
                                    111 = Reserved
        uint8_t RESERVED : 5; //!< Default Value B(0001_1). 
                            
    } refined;
    uint8_t raw;
} kt09xx_amdsp_4;

/**
 * @ingroup GA01
 * @brief 0.1 AMDSP5(Address 0x0067)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t MW_BBAGC_HI_TH  : 6;//!<Default Value B(01_1011). MW Baseband AGC High Threshold:\
                                        0 = 0dBm\
                                        1 = -3dBm\
                                        2 = -6dBm \
                                        ......\
                                        32 = -96dBm\
                                        33 = -99dBm 
        uint8_t RESERVED : 2; //!< Default Value B(00).                                 
    } refined;
    uint8_t raw;
} kt09xx_amdsp5;

/**
 * @ingroup GA01
 * @brief 0.1 AMDSP6(Address 0x0068)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t MW_BBAGC_LOW_TH  : 6;//!<Default Value B(00_0). MW Baseband AGC High Threshold:\
                                        0 = 0dBm\
                                        1 = -3dBm\
                                        2 = -6dBm \
                                        ......\
                                        32 = -96dBm\
                                        33 = -99dBm 
        uint8_t RESERVED : 2; //!< Default Value B(00). 
    } refined;
    uint8_t raw;
} kt09xx_amdsp_6;

/**
 * @ingroup GA01
 * @brief 0.1 AMDSP7 (Address 0x0069)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t MW_VOLUME : 4;//!<Default Value B(1010). MW Volume Control Bits:1111 = 0dB\
                                1110 = -0.5dB\
                                1101 = -1.0dB\
                                1100 = -1.5dB\
                                1011 = -2.0dB\
                                1010 = -2.5dB\
                                1001 = -3.0dB\
                                1000 = -3.5dB\
                                0111 = -4.0dB\
                                0110 = -4.5dB\
                                0101 = -5.0dB\
                                0100 = -5.5dB\
                                0011 = -6.0dB\
                                0010 = -6.5dB\
                                0001 = -7.0dB\
                                0000 = -7.5dB
        uint8_t RESERVED : 4; //!< Default Value B(1000). 

    } refined;
    uint8_t raw;
} kt09xx_amdsp_7;

/**
 * @ingroup GA01
 * @brief 0.1 ADC0(Address 0x0071)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t RESERVED1 : 2; //!<Default Value B(00).
        uint8_t CH_ADC_START : 1; //!<Default Value B(0).Channel ADC Start:0 = None.1 = Start.\
                                        Note: CH_ADC_START\
                                        register will be automatically cleared, after one clock cycle when it be setto 1.
        uint8_t RESERVED0  : 4;//!<Default Value B(000_0).  
        uint8_t CH_ADC_DIS : 1; //!< Default Value B(0).Channel ADC Enable:0 = Enable ADC.1 = DisableADC.  
    } refined;
    uint8_t raw;
} kt09xx_adc_0;

/**
 * @ingroup GA01
 * @brief 0.1 ADC3(Address 0x0074)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t CH_ADC_WIN_12_8  : 5;//!<Default Value B(0_0001). Channel ADC Window Length.
        uint8_t RESERVED : 3; //!< Default Value B(111). 
    } refined;
    uint8_t raw;
} kt09xx_adc_3;

/**
 * @ingroup GA01
 * @brief 0.1 ADC4(Address 0x0075)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t CH_ADC_WIN_7_0 : 8; //!< Default Value B(0001_0100).  Channel ADC Window Length.   
    } refined;
    uint8_t raw;
} kt09xx_adc_4;

/**
 * @ingroup GA01
 * @brief 0.1 ADC5 (Address 0x0076)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t RESERVED1 : 1; //!<Default Value B(0) 
        uint8_t STBYLDO_PD  : 1;//!<Default Value B(1). Standby LDO Power Down Control:0 = Power on.1=Powerdown.
        uint8_t RESERVED0 : 6; //!< Default Value B(1010_01). 
    } refined;
    uint8_t raw;
} kt09xx_adc_5;

/**
 * @ingroup GA01
 * @brief 0.1 STATUS10 (Address 0x0079
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t AFC_AAF : 8; //!< Default Value 0x00 AFC Accumulative Adjust Frequency:\
                                    FM mode:\
                                            0x80 = -128*2048Hz\
                                            0x81 = -127*2048Hz \
                                            ......\
                                            0xFF = -1*2048Hz\
                                            0x00 = 0Hz\
                                            ......\
                                            0x01 = 1*2048Hz\
                                    AM mode:\
                                            0x80 = -128*128Hz\
                                            0x81 = -127*128Hz \
                                            ......\
                                            0xFF = -1*128Hz\
                                            0x00 = 0Hz\
                                            0x01 = 1*128Hz\
                                            ......\
                                            0x7E = 126*128Hz \
                                            0x7F = 127 *128Hz 

    } refined;
    uint8_t raw;
} kt09xx_status_10;

/**
 * @ingroup GA01
 * @brief 0.1 FMST_CFG (Address 0x007E)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t RESERVED1 : 4; //!<Default Value B(1100) 
        uint8_t BLEND_START_COMBO  : 3;//!<Default Value B(010). The Starting Value of Blend \
                                            According to RSSIandSNRin FM Mode.\
                                            000 = 17dBuVEMF\
                                            001 = 19dBuVEMF\
                                            010 = 21dBuVEMF\
                                            011 = 23dBuVEMF\
                                            100 = 25dBuVEMF\
                                            101 = 27dBuVEMF\
                                            110 = 29dBuVEMF\
                                            111 = 31dBuVEMF
        uint8_t RESERVED0 : 1; //!< Default Value B(00). 
    } refined;
    uint8_t raw;
} kt09xx_fmst_cfg;

/**
 * @ingroup GA01
 * @brief 0.1 FMTUNE_VALID0(Address 0x007F)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t FM_TUN_SNR_LOWTH : 3; //!<Default Value B(101). Set FM SNR Low Threshold for Valid Channel Indicator.\
                                        000 = 6\
                                        001 = 8\
                                        010 = 10\
                                        011 = 12\
                                        100 = 15\
                                        101 = 18\
                                        110 = 21\
                                        111 = 24 
        uint8_t RESERVED1 : 1; //!<Default Value B(0)
        uint8_t FM_TUN_SNR_HITH  : 3;//!<Default Value B(101). Set FM SNR High Threshold for Valid Channel Indicator.\
                                        000 = 8\
                                        001 = 10\
                                        010 = 12\
                                        011= 15\
                                        100 = 18\
                                        101 = 21\
                                        110 = 24\
                                        111 = 27
        uint8_t RESERVED0 : 1; //!< Default Value B(0).                                 

    } refined;
    uint8_t raw;
} kt09xx_fmtune_valid_0;

/**
 * @ingroup GA01
 * @brief 0.1 FMTUNE_VALID1(Address 0x0080)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
         
        
        
        uint8_t FM_TUN_RSSI_LOWTH : 3; //!<Default Value B(101). Set FM RSSI Low Threshold for Valid Channel Indicator.\
                                    000 = -110dBm\
                                    001 = -108dBm\
                                    010 = -106dBm\
                                    011 = -104dBm\
                                    100 = -102dBm\
                                    101 = -100dBm\
                                    110 = -98dBm\
                                    111 = -96dBm
        uint8_t RESERVED1 : 1; //!<Default Value B(0)
        uint8_t FM_TUN_RSSI_HITH  : 3;//!<Default Value B(101). Set FM RSSI High Threshold.\
                                    or Valid Channel Indicator.\
                                    001 = -108dBm\
                                    010 = -106dBm\
                                    011 = -104dBm\
                                    100 = -102dBm\
                                    101 = -100dBm\
                                    110 = -98dBm\
                                    111 = -96dBm\
                                    111 = -94dBm
        uint8_t RESERVED0 : 1; //!< Default Value B(0).                                                        
    } refined;
    uint8_t raw;
} kt09xx_fmtune_valid_1;

/**
 * @ingroup GA01
 * @brief 0.1 MWTUNE_VALID0(Address 0x0081)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t MW_TUN_SNR_HITH  : 7;//!<Default Value B(011_1010). Set MW SNR High Threshold for Valid Channel Indicator.\
                                                000_0000 = 0\
                                                000_0001 = 1\
                                                ......\
                                                111_1110 = 126 \
                                                111_1111 = 127
        uint8_t RESERVED : 1; //!< Default Value B(0).                                         
    } refined;
    uint8_t raw;
} kt09xx_mwtune_valid_0;

/**
 * @ingroup GA01
 * @brief 0.1 MWTUNE_VALID1(Address 0x0082)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t MW_TUN_SNR_LOWTH  : 7;//!<Default Value B(011_0101). Set MW SNR Low Threshold for Valid Channel Indicator.\
                                            000_0000 = -110dBm\
                                            000_0001 = -107dBm\
                                            ......\
                                            111_0111 = 9dBm\
                                            111_1000 = 10dBm
        uint8_t RESERVED : 1; //!< Default Value B(0). 
    } refined;
    uint8_t raw;
} kt09xx_mwtune_valid_1;

/**
 * @ingroup GA01
 * @brief 0.1 MWTUNE_VALID2(Address 0x0083)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t MW_TUN_RSSI_HITH  : 7;//!<Default Value B(010_0100). Set MW RSSI High Threshold for Valid Channel Indicator.\
                                        000_0000 = -110dBm\
                                        000_0001 = -107dBm \
                                        ......\
                                        111_0111 = 9dBm\
                                        111_1000 = 10dBm 
        uint8_t RESERVED : 1; //!< Default Value B(00). 
                                
    } refined;
    uint8_t raw;
} kt09xx_mwtune_valid_2;

/**
 * @ingroup GA01
 * @brief 0.1 MWTUNE_VALID3(Address 0x0084)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t MW_TUN_RSSI_LOWTH  : 7;//!<Default Value B(010_0100). Set MW RSSI High Threshold for Valid Channel Indicator.\
                                        000_0000 = -110dBm\
                                        000_0001 = -107dBm \
                                        ......\
                                        111_0111 = 9dBm\
                                        111_1000 = 10dBm
        uint8_t RESERVED : 1; //!< Default Value B(0). 
    } refined;
    uint8_t raw;
} kt09xx_mwtune_valid_3;

/**
 * @ingroup GA01
 * @brief 0.1 SPARE2 (Address 0x0087)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t RESERVED1 : 5; //!<Default Value B(0_0000) 
        
        uint8_t SMUTE_GAIN_CTRL_EN  : 1;//!<Default Value B(00_0). SoftmuteGain Control by SMUTE_GAIN<7:0>:\
                                                0 = Disable\
                                                1 = Enable
        uint8_t RESERVED0 : 2; //!< Default Value B(00). 
    } refined;
    uint8_t raw;
} kt09xx_spare_2;

/**
 * @ingroup GA01
 * @brief 0.1 FMCHAN0 (Address 0x0088)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t FM_HIGH_CHAN_11_8 : 4;//!<Default Value B(0110). High edge frequency of FM band with 50KHz per LSB.\
                                        Frequency(KHz)=FM_HIGH_C HAN<11:0>*50KHz
        uint8_t RESERVED : 2; //!<Default Value B(00) 
        uint8_t AM_FM  : 1;//!<Default Value B(1). AM/FM Mode Switching:0=FMmode.1=AMmode.
        uint8_t CHANGE_BAND : 1; //!< Default Value B(0). Change Band:\
                                        0 = Keep current band.\
                                        1 = Change band.\
                                        This bit willautomatically clear 0 after band switching process.                                

    } refined;
    uint8_t raw;
} kt09xx_fm_chan_0;

/**
 * @ingroup GA01
 * @brief 0.1 FMCHAN1(Address 0x0089)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t FM_HIGH_CHAN_7_0 : 8; //!< Default Value B(1011_1000). High edge frequency of FM band with 50KHz per LSB.\
                                    Frequency(KHz)=FM_HIGH_C HAN<11:0>*50KHz
    } refined;
    uint8_t raw;
} kt09xx_fm_chan_1;

/**
 * @ingroup GA01
 * @brief 0.1 AMCHAN0 (Address 0x008C)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t AM_HIGH_CHAN_14_8  : 7;//!<Default Value B(000_001). High edge frequency of AM band with 50KHz per LSB.\
                                            Frequency(KHz) = AM_CHAN<14:0>*1KHz
        uint8_t RESERVED : 1; //!< Default Value B(0). 
    } refined;
    uint8_t raw;
} kt09xx_am_chan_0;

/**
 * @ingroup GA01
 * @brief 0.1 AMCHAN1 (Address 0x008D)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t AM_HIGH_CHAN_7_0  : 8;//!<Default Value B(1111_1000). High edge frequency of AM band with 50KHz per LSB.\
                                            Frequency(KHz) = AM_CHAN<14:0>*1KHz     
    } refined;
    uint8_t raw;
} kt09xx_am_chan_1;

/**
 * @ingroup GA01
 * @brief 0.1 LOW_CHAN0(Address 0x0098)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t LOW_CHAN_14_8  : 7;//!<Default Value B(000_001). Low edge frequency of MW \
                                        band with 1KHz per LSB and default is 513KHz(0x0201). \
                                        Low edge frequency of FM \
                                        band with 50KHz per LSB.\
                                        Low edge frequency of SW \
                                        band with 1KHz per LSB.
        uint8_t RESERVED : 1; //!< Default Value B(0). 
    } refined;
    uint8_t raw;
} kt09xx_low_chan_0;

/**
 * @ingroup GA01
 * @brief 0.1 LOW_CHAN1 (Address 0x0099)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t LOW_CHAN_7_0  : 8;//!<Default Value B(0XF8). Low edge frequency of band \
                                        with 1KHz per LSB and default is 513KHz(0x0201). \
                                        Low edge frequency of FM \
                                        band with 50KHz per LSB.\
                                        Low edge frequency of SW \
                                        band with 1KHz per LSB.
    } refined;
    uint8_t raw;
} kt09xx_low_chan_1;

/**
 * @ingroup GA01
 * @brief 0.1 CHAN_NUM0(Address 0x009A)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t CHAN_NUM_11_8  : 4;//!<Default Value B(0000). Channel number of band and the channel number is \
                                        CHAN_NUM<11:0> + 1. If \
                                        CHAN_NUM<11:0> is set to 0, only one channel is defined.
        uint8_t RESERVED : 4; //!< Default Value B(0000). 
    } refined;
    uint8_t raw;
} kt09xx_chan_num_0;

/**
 * @ingroup GA01
 * @brief 0.1 CHAN_NUM1 (Address 0x009B)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t CHAN_NUM_7_0  : 8;//!<Default Value B(0000). Channel number of band and the channel number is \
                                        CHAN_NUM<11:0> + 1. If \
                                        CHAN_NUM<11:0> is set to 0, only one channel is defined.
    } refined;
    uint8_t raw;
} kt09xx_chan_num_1;

/**
 * @ingroup GA01
 * @brief 0.1 GUARD2 (Address 0x00A0)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t CH_GUARD : 8; //!< Default Value 0x17. Channel guard range in dial mode.
    } refined;
    uint8_t raw;
} kt09xx_guard_2;//GUARD2

/**
 * @ingroup GA01
 * @brief 0.1 STATUS0(Address 0x00DE)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {   
        uint8_t ST_TUNE : 1; //!<Default Value B(0). Stereo Signal Indicator:0 = Mono state, 1 = Stereo state
        uint8_t RESERVED1 : 1; //!<Default Value B(1).
        uint8_t VALID_TUNE  : 1;//!<Default Value B(0). Valid Channel Indicator: 0=Invalidchannel. 1 = Valid channel.
        uint8_t RESERVED0 : 5; //!< Default Value B(1101_0). 
    } refined;
    uint8_t raw;
} kt09xx_status_0; //STATUS0

/**
 * @ingroup GA01
 * @brief 0.1 STATUS4(Address 0x00E2)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t FM_SNR  : 6;//!<Default Value B(00_0000). ChannelSNRValueinFM Mode:000000 = Minimum SNR , 111111 = Maximum SNR 
        uint8_t RESERVED : 2; //!< Default Value B(00). 
    } refined;
    uint8_t raw;
} kt09xx_status_4; //STATUS 4

/**
 * @ingroup GA01
 * @brief 0.1 STATUS5(Address 0x00E3)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t SMUTE_GAIN : 8; //!< Default Value 0x00. Softmute Gain.0x00 = Mute.0x01~0x80 = 20log(smute_gain<7:0>/128) .0x81~0xFF = Reserved.  
    } refined;
    uint8_t raw;
} kt09xx_status_5; //STATUS5

/**
 * @ingroup GA01
 * @brief 0.1 STATUS6(Address 0x00E4)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t RDCHAN_14_8  : 7;//!<Default Value B(000_0110). CurrentChannelIndicator:FM mode:\
                                        Frequency(KHz) = RDCHAN<14:0>*50KHz  \
                                        AM mode:\
                                        Frequency(KHz) = \
                                        RDCHAN<14:0>*1KHz
        uint8_t RESERVED : 1; //!< Default Value B(0). 
    } refined;
    uint8_t raw;
} kt09xx_status_6; //STATUS_6

/**
 * @ingroup GA01
 * @brief 0.1 STATUS7(Address 0x00E5)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t RDCHAN_7_0  : 8;//!<Default Value 0xB8.  CurrentChannelIndicator:FM mode:\
                                        Frequency(KHz) = RDCHAN<14:0>*50KHz  \
                                        AM mode:\
                                        Frequency(KHz) = \
                                        RDCHAN<14:0>*1KHz
    } refined;
    uint8_t raw;
} kt09xx_status_7; //STATUS_7

/**
 * @ingroup GA01
 * @brief 0.1 STATUS8(Address 0x00E6)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t FM_RSSI  : 7;//!<Default Value B(000_0000).FMRSSIValueIndicator.FM RSSI(dBm) = -110 + FM_RSSI<6:0> * 1dB
        uint8_t RESERVED : 1; //!< Default Value B(0).  
    } refined;
    uint8_t raw;
} kt09xx_status_8; //STATUS_8

/**
 * @ingroup GA01
 * @brief 0.1 AFC_STATUS0(Address 0x00E8)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t AM_CARRIER_OFST : 8; //!< Default Value 0x00.AM Carrier Frequency Offset:\
                                        0x80 = -128*128Hz\
                                        0x81 = -127*128Hz\
                                        ......\
                                        0xFF = -1*128Hz\
                                        0x00 = 0\
                                        0x01 = 1*128Hz\
                                        .....\
                                        0x7E = 126 * 128 Hz\
                                        0x7F = 127 *128Hz
    } refined;
    uint8_t raw;
} kt09xx_afc_status_0;//AFC_STATUS_0

/**
 * @ingroup GA01
 * @brief 0.1 AFC_STATUS1(Address 0x00E9)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t FM_CARRIER_OFST : 8; //!< Default Value 0x00. FM Carrier Frequency Offset:\
                                            0x80 = -128*1024Hz\
                                            0x81 = -127*1024Hz\
                                            0xFF = -1*1024Hz\
                                            0x00 = 0Hz\
                                            0x01 = 1*1024Hz\
                                            0x7E=126*1024Hz\
                                            0x7F = 127 *1024Hz  
    } refined;
    uint8_t raw;
} kt09xx_afc_status_1;//AFC_STATUS1

/**
 * @ingroup GA01
 * @brief 0.1 AMSTATUS0(Address 0x00EA)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t AM_RSSI  : 7;//!<Default Value B(00_0). AMRSSIValueIndicator.AM RSSI(dBm) = -110 + AM_RSSI<6:0> * 1dB
        uint8_t RESERVED : 1; //!< Default Value B(00). 
    } refined;
    uint8_t raw;
} kt09xx_am_status_0;//SMSTATUS0

/**
 * @ingroup GA01
 * @brief 0.1 AMSTATUS2(Address 0x00EC)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t AM_SNR_MODE1  : 7;//!<Default Value B(000_0000). AM Channel SNR Value (Mode 1):\
                                    000000 = Minimum SNR ...... 111111 = Maximum SNR
        uint8_t RESERVED : 1; //!< Default Value B(00). 
    } refined;
    uint8_t raw;
} kt09xx_am_status_2;//AMSTATUS2

/**
 * @ingroup GA01
 * @brief 0.1 AMSTATUS3(Address 0x00ED)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t AM_SNR_MODE2  : 7;//!<Default Value B(000_0000). AM Channel SNR value (Mode 2):000000 = Minimum SNR......111111 = Maximum SNR\
                                     When AM_SNR_MODE_SEL=1/2/3,         AM_SNR_MODE2 is valid. 
         uint8_t AM_CARRY_LOCK : 1; //!< Default Value B(0). AM Carry Frequency Lock Flag:0 = Lock loses.1 = Lock.
    } refined;
    uint8_t raw;
} kt09xx_am_status_3;//AMSTATUS3

/**
 * @ingroup GA01
 * @brief 0.1 SWTUNE_VALID0(Address 0x00F0)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t SW_TUN_SNR_HITH  : 7;//!<Default Value B(011_1010). Set SW SNR High Threshold for Valid Channel Indicator.\
                                        000_0000 = 0\
                                        000_0001 = 1 \
                                        …… \
                                        111_1110 = 126\
                                        111_1111= 127
        uint8_t RESERVED : 1; //!< Default Value B(0). 
    } refined;
    uint8_t raw;
} kt09xx_sw_tune_valid_0;//SWTUNE_VALID0

/**
 * @ingroup GA01
 * @brief 0.1 SWTUNE_VALID1(Address 0x00F1)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t SW_TUN_SNR_LOWTH  : 7;//!<Default Value B(011_0101). Set SW SNR Low Threshold for Valid Channel Indicator.\
                                        000_0000 = 0\
                                        000_0001 = 1\
                                        ......\
                                        111_1110 = 126\
                                        111_1111 = 127 
        uint8_t RESERVED : 1; //!< Default Value B(0). 
    } refined;
    uint8_t raw;
} kt09xx_sw_tune_valid_1 ;//SWTUNE_VALID1

/**
 * @ingroup GA01
 * @brief 0.1 SWTUNE_VALID2(Address 0x00F2)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t SW_TUN_RSSI_HITH  : 7;//!<Default Value B(011_1010). Set SW RSSI High Threshold for Valid Channel Indicator.\
                                        000_0000 = -110dBm\
                                        000_0001 = -107dBm \
                                        ......\
                                        111_0111 = 9dBm\
                                        111_1000 = 10dBm 
        uint8_t RESERVED : 1; //!< Default Value B(0). 
    } refined;
    uint8_t raw;
} kt09xx_sw_tune_valid_2; //SWTUNE_VALID2

/**
 * @ingroup GA01
 * @brief 0.1 SWTUNE_VALID3(Address 0x00F3)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t SW_TUN_RSSI_LOWTH  : 7;//!<Default Value B(001_1111). Set SW RSSI Low Threshold for Valid Channel Indicator.\
                                                    000_0000 = -110dBm \
                                                    000_0001 = -107dBm\
                                                    ...... \
                                                    111_0111 = 9dBm\
                                                    111_1000 = 10dBm
        uint8_t RESERVED : 1; //!< Default Value B(0). 
    } refined;
    uint8_t raw;
} kt09xx_swtune_valid_3; //SWTUNE_VALID3

/**
 * @ingroup GA01
 * @brief 0.1 SW_SOFTMUTE0 (Address 0X00F4)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t SW_SMUTE_START_SNR  : 7;//!<Default Value B(011_0000). The Starting Level of \
                                                Attenuation According to SNR inSWMode.\
                                                000_0000 = 0\
                                                000_0001 = 1 \
                                                ......\
                                                111_1110 = 126 \
                                                111_1111 = 127
        uint8_t SW_DSMUTE : 1; //!< Default Value B(0). SW Softmute Disable:0=SWsoftmuteenable 1=SWsoftmutedisable
    } refined;
    uint8_t raw;
} kt09xx_sw_softmute_0;//SW_SOFTMUTE0

/**
 * @ingroup GA01
 * @brief 0.1 SW_SOFTMUTE1(Address 0X00F5)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 44.
 */
typedef union {
    struct
    {
        uint8_t SW_SMUTE_START_RSSI  : 7;//!<Default Value B(001_0111). The Starting Level of \
                                            Attenuation According to RSSIinSWMode.\
                                            000_0000 = -110dBm\
                                            000_0001 = -107dBm \
                                            …… \
                                            111_0111 = 9dBm\
                                            111_1000 = 10dBm 
        uint8_t RESERVED : 1; //!< Default Value B(0). 
    } refined;
    uint8_t raw;
} kt09xx_sw_softmute_1;//SW_SOFTMUTE1

/**
 * @ingroup GA01
 * @brief 0.1 SW_SOFTMUTE2 (Address 0X00F6)
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        
        uint8_t SW_SMUTE_SLOPE_RSSI : 3; //!<Default Value B(100). TheSlope of Attenuation According to RSSI in SW Mode:\
                                        000 = 4\
                                        001 = 3\
                                        010 = 2\
                                        011 = 1\
                                        100 = 1/2\
                                        101 = 1/3\
                                        110 = 1/4 \
                                        111 = 0
        uint8_t SW_SMUTE_SLOPE_SNR  : 3;//!<Default Value B(00_0). he Slope of Attenuation According to SNR in SW Mode:\
                                        000 = 4\
                                        001 = 3\
                                        010 = 2\
                                        011 = 1\
                                        100 = 1/2\
                                        101 = 1/3\
                                        110 = 1/4\
                                        111 = 0
        uint8_t RESERVED : 2; //!< Default Value B(01). 
    } refined;
    uint8_t raw;
} kt09xx_sw_softmute_2; //SW_SOFTMUTE2

/**
 * @ingroup GA01
 * @brief 0.1 SW_SOFTMUTE3 (Address 0x00F7
 * @see KT0937; kt0937-d8 Monolithic Digital FM/MW/SW Receiver Radio-on-a-Chip; page 32.
 */
typedef union {
    struct
    {
        uint8_t RESERVED1 : 3; //!< Default Value B(011).
        uint8_t SW_SMUTE_MIN_GAIN  : 3;//!<Default Value B(00_1). The Total Attenuation of \
                                            Volume Can Be Configured:\
                                            000 = -9dB\
                                            001 = -12dB\
                                            010 = -15dB\
                                            011 = -18dB\
                                            100 = -21dB\
                                            101 = -24dB\
                                            110 = -27dB\
                                            111 = -30dB 
        uint8_t RESERVED0 : 2; //!< Default Value B(00). 
    } refined;
    uint8_t raw;
} kt09xx_sw_softmute_3; //SW_SOFTMUTE3



/**
 * @ingroup GA01
 * @brief Converts 16 bits word to two bytes
 */
typedef union {
    struct {
        uint8_t lowByte;
        uint8_t highByte;
    } refined;
    uint16_t raw;
} word16_to_bytes;

/**
 * @ingroup GA01
 * @brief KT0937 Class
 * @details This class implements all functions that will help you to control the KT0937 devices.
 *
 * @author BG5UBX - Zhang Yuandong . PU2CLR - Ricardo Lima Caratti
 */

class KT0937 {

protected:

    int deviceAddress = KT0937_I2C_ADDRESS;
    int swOnPin = -1; 

    uint8_t currentAmSpace = 0;
    uint8_t currentFmSpace = 2;

    uint16_t currentStep;                                   //!< Stores the current step
    uint32_t currentFrequency;                              //!< Stores the current frequency
    uint32_t minimumFrequency;                              //!< Stores the minimum frequency for the current band
    uint32_t maximumFrequency;                              //!< Stores the maximum frequency for the current band
    uint8_t currentMode;                                    //!< Stores the current mode
    uint8_t currentRefClockType = OSCILLATOR_32KHZ;         //!< Stores the crystal type
    uint8_t currentRefClockEnabled = REF_CLOCK_DISABLE;     //!< Strores 0 = Crystal; 1 = Reference clock
    uint8_t currentDialMode = DIAL_MODE_OFF;                //!< Stores the default Dial Mode (OFF)
    uint16_t deviceId;

    uint8_t currentVolume = 15;

    uint8_t errorCode = ERR_OK;
    

public:
    void setRegister(int reg, uint8_t parameter);  // reg ADDRESS , parameter to write to the register
    uint8_t getRegister(int reg);
    uint16_t getDeviceId();
    void setI2CBusAddress(int deviceAddress);

    void enableSWAmp(uint8_t on_off); //9018 RF Amplifier
    void setSystemClock(); // set SystemClock to 32.768 crystal
    void setup();//init KT0937
    void setup(uint8_t swOnPin);
    void setVolume(int8_t volume);
    uint8_t getVolume();
    void enableStandbyMode();
    void wakeUp();
    void resetDSP();
    uint8_t getErrorCode();
    void setSWOnPin(int sw_on_pin);

    void shutDownADCCH();
    void turnOnADCCH();
    void setADCCHWin();
    void setFMBand(uint16_t lowFrequency, uint16_t highFrequency);
    void setFMBand(uint16_t singleFrequency);
    void setFMBand();
    void setAMBand(uint16_t lowFrequency, uint16_t highFrequency);
    void setAMBand();
    void setSWBand(uint16_t lowFrequency, uint16_t highFrequency, uint16_t chanNumber );
    void setSWBand();
    void enableSW(uint8_t enable_sw);

    void enableDialMode();
    void disableFMSoftMute(bool disable);
    void disableMWSoftMute(bool disable);
    void disableSWSoftMute(bool disable);
    void disableMWAFC(bool disable);
    void disableFMAFC(bool disable);
    void disableSWAFC(bool disable);
    void setAMIFBW(uint8_t mwIFBW);
    
    
    uint16_t getCurrentFrequency();
    void setIntMode(bool isRising);
    


};

#endif

