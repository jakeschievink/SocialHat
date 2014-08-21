#include "ST7565.h"
#include "thankyouBMP.h"
#include "glasses.h"

#define BACKLIGHT_LED 10

#define DEBUG 1
ST7565 glcd(23, 22, 21, 20, 19);

void setup(){
  Serial.begin(9600);
  glcd.begin(0x18); 
  
  glcd.setpixel(10, 10, BLACK);
  glcd.display();        // show the changes to the buffer
  delay(2000);
  glcd.clear();
  glcd.display();
  delay(2000);
  glcd.clear();
  
  glcd.drawbitmap(0,0,thankyou, 128,64, BLACK);
  glcd.display();
  delay(2000);
  glcd.clear();
  
  glcd.drawbitmap(0,0,glasses, 128,64, BLACK);
  glcd.display();
  delay(2000);
}
void loop(){
}
