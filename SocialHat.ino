#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include "EEPROMAnything.h"
#include "Scroll.h"
Scroll scrollscreen(9, 10, 11, 13, 12) ;
char message[200];

typedef enum {SCROLL, IMAGE} mode;
void setup() {
    Serial.begin(9600);
    scrollscreen.init();
    EEPROM_readAnything(1, message);
    scrollscreen.setMessage(message);
    mode currentmode = SCROLL;
    Serial.println(message);
    while(currentmode == SCROLL){
        scrollscreen.startScroll();
        checkSerial();
    }

}

void loop() {
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
