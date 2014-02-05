
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Scroll.h"

#define OLED_DC    11
#define OLED_CS    12
#define OLED_CLK   10
#define OLED_MOSI   9
#define OLED_RESET 13



Adafruit_SSD1306 disp(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
Scroll :: Scroll(){
}
void Scroll :: init(){
    configuration  = {UPWARDS,2};
    disp.begin(SSD1306_SWITCHCAPVCC);
    disp.setTextSize(configuration.text_size);
    disp.setTextColor(WHITE);
    _x = disp.width();
    _y = disp.height();
    if(configuration.scrolling == SIDEWAYS){
        disp.setTextWrap(false);
    }else{
        disp.setTextWrap(true);
    }
    setMinX();
    setMinY();
}

void Scroll :: startScroll(){
    disp.clearDisplay();
    if(configuration.scrolling == SIDEWAYS){
        disp.setCursor(_x, 20);
        if(--_x < _minX) _x = disp.width();
    }
    if(configuration.scrolling == UPWARDS){
        disp.setCursor(0, _y);
        if(--_y < _minY) _y = disp.height();
    }
    disp.print(_message);
    disp.display();
}
void Scroll :: setMessage(char* msg){
    int length = strlen(msg);
    strncpy(_message, msg, 200);
    if(configuration.scrolling == UPWARDS){
        convert_comma_to_newline(_message);
    }
    setMinX();
    setMinY();

}
void Scroll :: convert_comma_to_newline(char* msg){
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
int Scroll :: get_newlines(char* msg){
    int length = strlen(msg);
    int newlines = 0;
    for(int i = 0; i<length; i++){
        if((byte)msg[i] == 10){
            newlines++;
        }
    }
    return newlines;
}

void Scroll :: setMinX(void){
    _minX = -(configuration.text_size*6) * strlen(_message);   // 12 = 6 pixels/character * text size 2
}
void Scroll :: setMinY(void){
    _minY= -((get_newlines(_message))*(configuration.text_size*7))-disp.height();
}
