#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include "EEPROMAnything.h"
#include "Scroll.h"

Scroll scrollscreen;
char message[200];
void setup() {
    Serial.begin(9600);
    scrollscreen.init();
    EEPROM_readAnything(0, message);
    scrollscreen.setMessage(message);
    Serial.println(message);
}

void loop() {
    scrollscreen.startScroll();
    checkSerial();
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
        EEPROM_writeAnything(0, tmpMsg);
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
