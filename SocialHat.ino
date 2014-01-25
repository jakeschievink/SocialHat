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

configuration cf= {UPWARDS, 2};

char message[] = "Plants, Computer Programming, Cycling";
int  x, minX, y, minY;
String inputString;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC);
  display.setTextSize(cf.text_size);
  display.setTextColor(WHITE);
  EEPROM_readAnything(0, message);
  if(cf.scrolling == SIDEWAYS){
    display.setTextWrap(false);
  }else{
    display.setTextWrap(true);
    number_of_newlines(message);
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
  if(Serial.available() > 0){
    recieveChars().toCharArray(message, 100);
    Serial.print(message);
    EEPROM_writeAnything(0, message);
    number_of_newlines(message);
    setMinX();
    setMinY();

  }
}

void setMinX(void){
  minX = -(cf.text_size*6) * strlen(message);   // 12 = 6 pixels/character * text size 2
}
void setMinY(void){
    minY= -((((cf.text_size*6) * strlen(message))/128)*(cf.text_size*7))-display.height();
}

int number_of_newlines(char* msg){
    int length = strlen(msg);
    int newlines = 0; 
    for(int i =0; i<length; i++){
        if((byte)msg[i] == 44){
            msg[i] = ' ';
            msg[i+1] = '\n';
            
        }
    }
    return newlines;
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
