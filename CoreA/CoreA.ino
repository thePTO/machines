#include <Sodaq_SHT2x.h>

#define INTERVAL_SENSOR   2000             //定义传感器采样时间间隔
#define INTERVAL_NET      2000             //定义发送时间

#include <Wire.h>                                   
#include <ESP8266.h>
#include "I2Cdev.h"

#define SSID           "____"        
#define PASSWORD       "00000008"

#define IDLE_TIMEOUT_MS  10000      

// WEBSITE
#define HOST_NAME      "api.heclouds.com"
#define DEVICEID       "____"
#define HOST_PORT      (80)
String apiKey = "____";

char buf[10];

#define INTERVAL_sensor 2000

String mCottenData;
String postString; 
String jsonToSend;

float sensor_tem, sensor_hum, sensor_lux;                    
char sensor_tem_c[7], sensor_hum_c[7], sensor_lux_c[7] ;    

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); 
ESP8266 wifi(&mySerial);

unsigned long net_time = millis();                    
unsigned long sensor_time = millis();                       


void setup(void) {       
    Wire.begin();
    Serial.begin(9600);   
    while(!Serial);
    pinMode(A0, INPUT);

    Serial.println("loading setup");   
   Serial.print("Info:");
    Serial.println(wifi.getVersion().c_str());

    if (wifi.joinAP(SSID, PASSWORD)) {
      Serial.print("connected to relay");  
      Serial.print("IP: ");
      Serial.println(wifi.getLocalIP().c_str());
    } else {
      Serial.println("fail to connect relay");
    }
    Serial.println("setup accomplished");
}

void loop() {   
  if (sensor_time > millis()) { 
    sensor_time = millis();  
  }
    
  if(millis() - sensor_time > INTERVAL_SENSOR)               
  {  
    getSensorData();                                       
    sensor_time = millis();
  }  

  if (net_time > millis()) { 
    net_time = millis();
  }
  
  if (millis() - net_time > INTERVAL_NET) {                             
    uploadSensorData();                                    
    net_time = millis();
  }
}

void getSensorData() {  
    sensor_tem = SHT2x.GetTemperature() ;   
    sensor_hum = SHT2x.GetHumidity();   
    sensor_lux = analogRead(A0);    
    delay(2000);
    dtostrf(sensor_tem, 2, 1, sensor_tem_c);
    dtostrf(sensor_hum, 2, 1, sensor_hum_c);
    dtostrf(sensor_lux, 3, 1, sensor_lux_c);
}

void uploadSensorData() {
  if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
    Serial.print("opening channel...");

    jsonToSend="{\"Temperature\":";
    dtostrf(sensor_tem,1,2,buf);
    jsonToSend+="\""+String(buf)+"\"";
    jsonToSend+=",\"Humidity\":";
    dtostrf(sensor_hum,1,2,buf);
    jsonToSend+="\""+String(buf)+"\"";
    jsonToSend+=",\"Light\":";
    dtostrf(sensor_lux,1,2,buf);
    jsonToSend+="\""+String(buf)+"\"";
    jsonToSend+="}";

    postString="POST /devices/";
    postString+=DEVICEID;
    postString+="/datapoints?type=3 HTTP/1.1";
    postString+="\r\n";
    postString+="api-key:";
    postString+=apiKey;
    postString+="\r\n";
    postString+="Host:api.heclouds.com\r\n";
    postString+="Connection:close\r\n";
    postString+="Content-Length:";
    postString+=jsonToSend.length();
    postString+="\r\n";
    postString+="\r\n";
    postString+=jsonToSend;
    postString+="\r\n";
    postString+="\r\n";
    postString+="\r\n";

    const char *postArray = postString.c_str();                
    Serial.println(postArray);
    wifi.send((const uint8_t*)postArray, strlen(postArray)); 
    Serial.println("send success");   
     if (wifi.releaseTCP()) {                  
        Serial.println("connection closed");
     } else {
        Serial.println("fail to close connection");
     }
     postArray = NULL;                                       
  } else {
    Serial.println("fail to open channel");
  }
}
