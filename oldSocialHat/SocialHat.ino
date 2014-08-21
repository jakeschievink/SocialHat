#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include "EEPROMAnything.h"
#include "Scroll.h"
#include "Pictures.cpp"
Scroll scrollscreen(9, 10, 11, 13, 12);
char message[200];
bool imagedisplayed = false;
bool interTrigger = false;
typedef enum {SCROLL, IMAGE} mode;
const int buttonPin = 8;
const unsigned char* pictures[] = {oledtest, Google, CopyLeft};
uint pictureCounter = 0;
mode currentmode = SCROLL;
void setup() {
    Serial.begin(9600);
    pinMode(buttonPin, INPUT);
    attachInterrupt(buttonPin, stateChange, HIGH);
    scrollscreen.init();
    EEPROM_readAnything(1, message);
    scrollscreen.setMessage(message);
    Serial.println(message);
    

}

void loop() {
    if(currentmode == SCROLL){
        scrollscreen.startScroll();
        checkSerial();
    }
    if(currentmode == IMAGE && !imagedisplayed){
        displayImage();
        imagedisplayed = true;
    }
    if(interTrigger == true){
        delay(10);
        interTrigger = false;
        imagedisplayed = false;
        if(currentmode == IMAGE){
            currentmode = SCROLL;
        }else{
            currentmode = IMAGE;
        }
    }
}
void displayImage(){
    scrollscreen.disp.clearDisplay();
    scrollscreen.disp.drawBitmap(0,0, pictures[pictureCounter], 128, 64, 1);
    if(pictureCounter < (sizeof(pictures)/ sizeof(pictures[0]))-1){
        pictureCounter++;
    }else{
        pictureCounter=0;
    }
    scrollscreen.disp.display();
}
void stateChange(){
   interTrigger = true; 
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
