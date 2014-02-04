#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include "EEPROMAnything.h"

#define OLED_DC    11
#define OLED_CS    12
#define OLED_CLK   10
#define OLED_MOSI   9
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
typedef enum {SIDEWAYS, UPWARDS} scroll_type;

typedef struct config_s
{
    scroll_type scrolling; 
    int text_size;
}configuration;

configuration cf= {UPWARDS, 4};

char message[200];

int  x, minX, y, minY;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC);
  display.setTextSize(cf.text_size);
  display.setTextColor(WHITE);
  EEPROM_readAnything(0, message);

  if(cf.scrolling == SIDEWAYS){
    display.setTextWrap(false);
  }else{
    display.setTextWrap(true);
    convert_comma_to_newline(message);
  }
  x = display.width();
  y = display.height();
  Serial.begin(9600);
  setMinX();
  setMinY();
}

void loop() {
  display.clearDisplay();
  if(cf.scrolling == SIDEWAYS){
    display.setCursor(x, 20);
    if(--x < minX) x = display.width();
  }
  if(cf.scrolling == UPWARDS){
      display.setCursor(0, y);
      if(--y < minY) y = display.height();
  }
  display.print(message);
  display.display();
  checkSerial();
  
}
void checkSerial(){
    bool firstRead = false;
    char option;
    if(Serial.available() > 0){
        if(!firstRead){
            option = Serial.read();
            firstRead = true;
            Serial.println(option);
        }
        recieveChars().toCharArray(message, 100);
        Serial.print(message);
        EEPROM_writeAnything(0, message);
        convert_comma_to_newline(message);
        setMinX();
        setMinY();

    }
}
void setMinX(void){
  minX = -(cf.text_size*6) * strlen(message);   // 12 = 6 pixels/character * text size 2
}
void setMinY(void){
    minY= -((get_newlines(message))*(cf.text_size*7))-display.height();
}
int get_newlines(char* msg){
    int length = strlen(msg);
    int newlines = 0;
    for(int i = 0; i<length; i++){
        if((byte)msg[i] == 10){
            Serial.print("newline");
            newlines++;
        }
    }
    return newlines;
}
void convert_comma_to_newline(char* msg){
    int length = strlen(msg);
    for(int i =0; i<length; i++){
        if((byte)msg[i] == 44){
            msg[i] = ' ';
            if(msg[i+1] == 44){
                msg[i] = '\n';
            }
            msg[i+1] = '\n';
            
        }
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
