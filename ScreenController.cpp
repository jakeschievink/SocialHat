#include <ST7565.h>
#include "ScreenController.h"

ScreenController :: ScreenController(int8_t SID, int8_t SCLK, int8_t AO, int8_t RST, int8_t CS) : disp(SID, SCLK, AO, RST, CS) {};

void ScreenController :: init(){
    disp.begin(0x18);
    disp.setpixel(10, 10, BLACK);
    disp.display();
    delay(2000);
    disp.clear();
    disp.display();
    delay(2000);
}

void ScreenController :: showimage(const uint8_t* image){
    disp.clear();
    disp.drawbitmap(0, 0, image, 128, 64, 0);
    disp.display();

}

void ScreenController :: looplines(char** messages){
    static long oldtime = millis();
    static int messagelinenumber = sizeof(messages)/sizeof(messages[0]);
    long currenttime = millis();
    static int startline = 0;
    if(currenttime - oldtime > SCROLLINTERVAL){
        disp.clear();
        for(int i = 0; i < 4; i++){
            if(i + startline > messagelinenumber){
                startline = 0;
            }
            int offset = getcenteroffset(sizeof(messages[startline+1]));
            disp.drawstring(offset, i*2, messages[startline+i]);
        }
        startline++;
        oldtime = millis();
        disp.display();
    }
}

void ScreenController :: loopimages(const uint8_t* images[]){
    static long oldtime = millis();
    static int curindex = 0;
    long currenttime = millis();
    int maxindex = sizeof(images)/sizeof(images[0])-1;
    if(currenttime - oldtime > SCROLLINTERVAL){
        showimage(images[curindex]);
        if(++curindex > maxindex)
            curindex = 0;
        oldtime = millis();
    }
}

void ScreenController :: showword(char* word){
    int offset = getcenteroffset(sizeof(word));
    disp.clear();
    disp.drawstring(offset, 4, word);
    disp.display();
}

int ScreenController :: getcenteroffset(int chars){
    int sparespace = (16-chars)*8;
    return sparespace/2;
}

