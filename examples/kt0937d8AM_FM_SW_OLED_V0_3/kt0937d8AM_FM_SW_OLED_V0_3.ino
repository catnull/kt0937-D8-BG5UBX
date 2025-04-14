/*
* Written by BG5UBX . Zhang Yuandong . seighbang@126.com. @2024
*FM0.1   2024.11.27  FM stereo function succeed. and the key S1 as  VOL up, S2 as VOLdown.
*AM_FM   2024.11.29  FM AM two Band function enabled.
*AM_FM_SW_OLED 2024.12.02 FM AM SW all bands receiver. with OLED ssd1306 support.
*        2024.12.4  to enable the short wave mode , the programming guide ommited the function of sw_en register bit, then you should operate this bit as you changing the band between FM, AM, SW.
*AM_FM_SW_OLED 2024.12.08 improve oled showed routine.
*AM_FM_SW_OLEDV_0.2 2024.12.08 test esp32 slight sleep mode to avoid the noise signal emitting from mcu.
*
*/

#include <KT0937.h>
#include "OneButton.h"
#include <Wire.h>
#include <U8x8lib.h>

//GPIO 13 as PIN_INPUT_FUN , and the sleep wake up PIN.
#define BUTTON_GPIO_NUM_DEFAULT         13
/* "Boot" button is active low */
#define BUTTON_WAKEUP_LEVEL_DEFAULT     0

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#define FRAME_TIME 100   // 40 MS A SHOW FRAME


#define PIN_INPUT_FUN 13
#define PIN_INPUT_UP 15
#define PIN_INPUT_DOWN 2

//sw amplifier 9018 power supply by GPIO PIN 0
#define PIN_SW_ON 0

#define BAND_FM   0
#define BAND_AM   1
#define BAND_SW1  2
#define BAND_SW2  3
#define BAND_SW3  4
#define BAND_SW4  5
#define BAND_SW5  6
#define BAND_SW6  7
#define BAND_SW7  8
#define BAND_SW8  9
#define BAND_SW9  10
#define BAND_SW10 11
#define BAND_SW11 12
#define BAND_SW12 13
#define BAND_SW13 14
#define BAND_SW14 15
#define BAND_SW15 16
#define BAND_SW16 17
#define BAND_SW17 18
#define BAND_SW18 19
#define BAND_SW19 20
#define BAND_SW20 21
#define BAND_SW21 22
#define BAND_SW22 23
#define BAND_SW23 24
#define BAND_SW24 25
#define BAND_SW25 26
#define BAND_SW26 27
#define BAND_SW27 28
#define BAND_SW28 29
#define BAND_SW29 30
#define BAND_SW30 31  //17Mhz 18m
#define BAND_SW31 32  //9Mhz  32m

//device id
#define KT0937_DEV_ID 0x82

//oled flah elapsed time
#define OLED_REFLASH_ELAPSED_TIME 6000  // time to flash milliseconds 3000 ms = 3 second
#define WAKE_UP_ELAPSED_TIME 10000

typedef struct{
  uint16_t lowFreq;  //Low Frequency /1kHz , as 12MHz 12000kHz / 1kHz = 12000
  uint16_t highFreq; //High Frequency /1kHz, as 13 MHz 13000kHz /1kHz = 13000
  uint16_t chanNum;// channum =(highFreq - low Frequency ) / SW_STEP , as 1 kHz set as SW_STEP
}sw_band_record_t;

//OLED ssd1306 display
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); 



KT0937 radio;

OneButton buttonFun(PIN_INPUT_FUN, true);
OneButton buttonUp(PIN_INPUT_UP, true);
OneButton buttonDown(PIN_INPUT_DOWN, true);

//oled display buffer
char display_buffer[8]={};
long frame_duration_start_time = 0;


int8_t band = BAND_FM ;

bool isBandChanged = 0;

long oled_showed_time = 0;
bool oled_show_flag = false;
bool wake_up_flag = true;
long wake_up_time = 0;

sw_band_record_t swBandTable[31] = 
{
//{ low,high,channum } , 
{ 1750,3050,1300 } ,//sw 1 
{ 2950,4050,1100 } ,//sw 2 
{ 3950,5050,1100 } ,//sw 3 
{ 4950,6050,1100 } ,//sw 4 
{ 5950,7050,1100 } ,//sw 5 
{ 6950,8050,1100 } ,//sw 6 
{ 7950,9050,1100 } ,//sw 7 
{ 8950,10050,1100 } ,//sw 8 
{ 9950,11050,1100 } ,//sw 9 
{ 10950,12050,1100 } ,//sw 10 
{ 11950,13050,1100 } ,//sw 11 
{ 12950,14050,1100 } ,//sw 12 
{ 13950,15050,1100 } ,//sw 13 
{ 14950,16050,1100 } ,//sw 14 
{ 15950,17050,1100 } ,//sw 15 
{ 16950,18050,1100 } ,//sw 16 
{ 17950,19050,1100 } ,//sw 17 
{ 18950,20050,1100 } ,//sw 18 
{ 19950,21050,1100 } ,//sw 19 
{ 20950,22050,1100 } ,//sw 20 
{ 21950,23050,1100 } ,//sw 21 
{ 22950,24050,1100 } ,//sw 22 
{ 23950,25050,1100 } ,//sw 23 
{ 24950,26050,1100 } ,//sw 24 
{ 25950,27050,1100 } ,//sw 25 
{ 26950,28050,1100 } ,//sw 26 
{ 27950,29050,1100 } ,//sw 27 
{ 28950,30050,1100 } ,//sw 28 
{ 29950,31050,1100 } ,//sw 29
{ 16950,18050,1100 } ,//sw 16 band 30
{ 8950,10050,1100 } ,//sw 8  band 31



};





void clickFun()
{
  oled_showed_time = millis();
  oled_show_flag = true;
  u8x8.begin();
  u8x8.setFont(u8x8_font_px437wyse700b_2x2_r);
} 

void doubleClickFun()
{
  
}

void clickVolUp()
{
  radio.setVolume(radio.getVolume()+1);
}

void clickVolDown()
{
  radio.setVolume(radio.getVolume()-1);
}

//DouBle Click to change band
void doubleClickBandUp()
{
  band = band + 1;
  if(band > BAND_SW31)  
  {
    band = BAND_FM ;
  }
  isBandChanged = 1;
}

void doubleClickBandDown()
{
  band = band - 1;
  if(band <0 )
  {
    band = BAND_SW31 ;
  }
  isBandChanged = 1;
}

void checkBand()
{
  if(isBandChanged == 1)
  {  
    switch (band) {
      case BAND_FM :
        radio.enableSWAmp(0);
        radio.setFMBand();
        break;
      case BAND_AM :
        radio.enableSWAmp(0);
        radio.setAMBand();
        //Serial.println("AM Band");
        //dumpAll();
        break;
      default ://BAND SW1 -SW29
        //Serial.print("SW Band:");
        //Serial.println(band);
        
        radio.enableSWAmp(1);
        radio.setSWBand(swBandTable[band - 2].lowFreq, swBandTable[band - 2].highFreq, swBandTable[band - 2].chanNum);
        //dumpAll();
        break;
    }
    isBandChanged = 0;
  }
}







void setup() {
  Serial.begin(9600);
  while(!Serial);
  Wire.begin();
  //Wire.setClock(400000);
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.print("check chip id:");
  while(radio.getDeviceId()!= KT0937_DEV_ID){
    Serial.print("KT_device id error....");
  }
  Serial.println(radio.getDeviceId());
  digitalWrite(LED_BUILTIN , LOW);
  radio.setup();
  radio.setSWOnPin(PIN_SW_ON);

  Serial.println("setup...");
  
 
  
  
  //FM Band set 
  radio.disableFMSoftMute(1);
  radio.disableFMAFC(1);
  
  //MW Band set 
  radio.disableMWSoftMute(1);
  radio.disableMWAFC(1);
  radio.setAMIFBW(AM_IF_1_2KHZ); 
  
 //SW Band set 
  radio.disableSWSoftMute(1);
  radio.disableSWAFC(1); 

  
  radio.setFMBand();
  Serial.println("FMBand setted ...");


  
  //Volume set 0 - 31 .
  radio.setVolume(15);

  Serial.println("Volume setted......");


 // dumpAll();

  
  //Serial.print("Error:");Serial.println(radio.getErrorCode());
  /*
  dump(0x04);
  dump(0x1B);
  dump(0x51);
  dump(0x1A);
  dump(0x88);
  dump(REG_CHAN_NUM1);
  dump(REG_CHAN_NUM0);
  dump(REG_LOW_CHAN1);
  dump(REG_LOW_CHAN0);
  dump(REG_FMCHAN1);
  dump(REG_FMCHAN0);
  dump(REG_BANDCFG0);
  dump(REG_BANDCFG2);
  dump(REG_GUARD2);
  dump(REG_ADC4);
  dump(REG_ADC3);
  dump(REG_FMCHAN0);
  dump(REG_GPIOCFG2);
  dump(REG_ADC0);
  
  dumpAll();
*/
  

  //Button function atachment
  buttonFun.attachClick(clickFun);
  buttonUp.attachClick(clickVolUp);
  buttonDown.attachClick(clickVolDown);
  buttonUp.attachDoubleClick(doubleClickBandUp);
  buttonDown.attachDoubleClick(doubleClickBandDown);  

  //oled
  u8x8.begin();
  u8x8.setFont(u8x8_font_px437wyse700b_2x2_r);
  u8x8.setPowerSave(1);

  //ligth sleep gpio 13 function
  /*
  const int button_gpio_num = BUTTON_GPIO_NUM_DEFAULT;    //配置默认唤醒GPIO    
  const int wakeup_level = BUTTON_WAKEUP_LEVEL_DEFAULT;   //设置唤醒电平

  gpio_config_t config = {
          .pin_bit_mask = BIT64(button_gpio_num),         //M5Stack 不能配置GPIO1 作为串口引脚，影响串口输出
          .mode = GPIO_MODE_INPUT,                        //输入模式
          .pull_up_en = 1,                                //使能上拉
  };
  gpio_config(&config);                  //配置GPIO
  gpio_wakeup_enable(button_gpio_num,wakeup_level == 0 ? GPIO_INTR_LOW_LEVEL : GPIO_INTR_HIGH_LEVEL);//设置gpio唤醒
  esp_sleep_enable_gpio_wakeup();
*/
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_2,0);
}

//drawing band and frequency

void displayBuffer()
{
  sprintf(display_buffer,"band:%2d",band);  
  u8x8.drawString(0, 0, display_buffer);
  if(band == BAND_FM)
  {
    sprintf(display_buffer,"%s","        "); 
    sprintf(display_buffer,"%5.2f M",float(float(radio.getCurrentFrequency())/20.0)); 
  }
  else if(band == BAND_AM)
  {
    sprintf(display_buffer,"%s","        "); 
    sprintf(display_buffer,"%4d k  ",radio.getCurrentFrequency());
  }
  else 
  {
    sprintf(display_buffer,"%s","        "); 
    sprintf(display_buffer,"%0.3fM",float(float(radio.getCurrentFrequency())/1000.0));
  }
  u8x8.drawString(0,10, display_buffer);  
}

void loop() {
  /*
  //frequency
  if(band == BAND_FM)
  {
    Serial.println(radio.getCurrentFrequency()*50);
  }
  else
  {
    Serial.println(radio.getCurrentFrequency());
  }

//band
  Serial.print("band:");
  Serial.println(band);

  debug_err();
  */

  
  buttonFun.tick();
  buttonUp.tick();
  buttonDown.tick();
  checkBand();
  if((oled_show_flag == true )&&((millis()-oled_showed_time)> OLED_REFLASH_ELAPSED_TIME))
  {
    u8x8.setPowerSave(1);
    oled_show_flag = false;
    //change esp32 to light sleep mode
   // esp_light_sleep_start();
  } 
  if(oled_show_flag == true){
     displayBuffer();
  }
  
  if((wake_up_flag == false))
  {
    wake_up_flag = true;
    wake_up_time = millis();
  }  
  
  if((wake_up_flag == true)&&(millis()-wake_up_time)>WAKE_UP_ELAPSED_TIME)
  {
    wake_up_flag = false;
    u8x8.setPowerSave(1);
    esp_light_sleep_start();
  }  
}




void dump(int ADRESS){
  Serial.print(ADRESS,HEX);
  Serial.print(":");
  Serial.println(radio.getRegister(ADRESS),HEX);
}

void dumpAll(){
  uint8_t i;
  for(i = 0x00; i<0xf8; i++)
  {
    dump(i);
  }
}

void debug_err(){
  Serial.print("err(HEX):");
  Serial.println(radio.getErrorCode(),HEX);
}
