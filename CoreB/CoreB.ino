#include <U8glib.h>//使用OLED需要包含这个头文件
#define INTERVAL_LCD 20 //定义OLED刷新时间间隔 
unsigned long lcd_time = millis(); //OLED刷新时间计时器
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE); //设置OLED型号 
//-------字体设置，大、中、小
#define setFont_L u8g.setFont(u8g_font_7x13)
#define setFont_M u8g.setFont(u8g_font_fixed_v0r)
#define setFont_S u8g.setFont(u8g_font_fixed_v0r)
#define setFont_SS u8g.setFont(u8g_font_fub25n)

#include "OurSpark.h"
ColorLEDController LEDController1(2, 6);

#include <IRremote.h>
IRrecv irrecv(10);  
decode_results results;
int light_switch=0;
int light_red=0;
int light_green=0;
int light_blue=0;
int scale=10;

void setup(){
  Serial.begin(9600); 
  irrecv.enableIRIn();
}

void loop(){
  if (irrecv.decode(&results)) {
    light_control(results.value);
    irrecv.resume(); 
  }
  if(light_switch){
    LEDController1.ShowColor(0,light_red,light_green,light_blue);
    delay(100);
  }else{
    LEDController1.ShowColor(0,0,0,0);
  }
  u8g.firstPage();
  do {
    setFont_L;
    u8g.setPrintPos(0, 10);
    u8g.print("Red:");
    u8g.setPrintPos(55, 10);
    u8g.print(light_red);
    u8g.setPrintPos(0, 30);
    u8g.print("Green:");
    u8g.setPrintPos(55, 30);
    u8g.print(light_green);
    u8g.setPrintPos(0,50);
    u8g.print("Blue:");
    u8g.setPrintPos(55,50);
    u8g.print(light_blue);
  }while(u8g.nextPage());
  delay(100);
}

void light_control(auto value){
  if(value==0X1FE48B7){ 
    if(!light_switch){
      light_switch=1;
    } else {
      light_switch=0;
    }
  }
  if(light_switch){
    switch(value){
      case 0X1FE807F:
        light_red+=scale;
        break;
      case 0X1FE20DF:
        light_red-=scale;
        break;
      case 0X1FE40BF:
        light_green+=scale;
        break;
      case 0X1FEA05F:
        light_green-=scale;
        break;
      case 0X1FEC03F:
        light_blue+=scale;
        break;
      case 0X1FE609F:
        light_blue-=scale;
        break;
      case 0X1FEE01F:
        scale-=1;
        break;
      case 0X1FE906F:
        scale+=1;
        break;
      case 0X1FE10EF:
        light_red=0;
        light_green=0;
        light_blue=0;
        scale=10;
        break;
      default:
        break;
    }
  }
