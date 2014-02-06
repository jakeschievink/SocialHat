#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include "EEPROMAnything.h"
#include "Scroll.h"
#include "Pictures.cpp"
Scroll scrollscreen(9, 10, 11, 13, 12) ;
char message[200];
bool imagedisplayed = false;
typedef enum {SCROLL, IMAGE} mode;

mode currentmode = SCROLL;
void setup() {
    Serial.begin(9600);
    scrollscreen.init();
    EEPROM_readAnything(1, message);
    scrollscreen.setMessage(message);
    Serial.println(message);
    

}

void loop() {
    while(currentmode == SCROLL){
        scrollscreen.startScroll();
        checkSerial();
    }
    while(currentmode == IMAGE && !imagedisplayed){
        displayImage();
        imagedisplayed = true;
        
    }
}
void displayImage(){
    scrollscreen.disp.clearDisplay();
    scrollscreen.disp.drawBitmap(0, 0,  oledtest, 128, 64, 1);
    scrollscreen.disp.display();
}
void checkSerial(){
    bool firstRead = false;
    char option;
    char tmpMsg[200];
    if(Serial.available() > 0){
        if(!firstRead){
            option = Serial.read();
            firstRead = true;
            Serial.println(option);
        }
        recieveChars().toCharArray(tmpMsg, 100);
        Serial.print(tmpMsg);
        scrollscreen.setMessage(tmpMsg);
        Serial.println(EEPROM_writeAnything(1, tmpMsg));
    }
}

String recieveChars(){
  String content = "";
  char character;
  while(Serial.available()) {
      character = Serial.read();
      content.concat(character);
      Serial.println((byte)character);
  }
  if(content != ""){
    return content;
  }
}
