#include "ScreenController.h"

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
    disp.drawbitmap(0,0,image,128,64);
    disp.display();

}

void ScreenController :: looplines(char* messages[]){
    static long oldtime = millis();
    static int messagelinenumber = sizeof(messages)/sizeof(messages[0]);
    long currenttime = millis();
    static int startline = 0;
    if(currenttime - oldtime > SCROLLINTERVAL){
        disp.clear();
        for(int i = 0; i < 4; i++){
            if(i + startline > messagelinenumber){
                startline = 0:
            }
            int offset = getcenteroffset(msgs[startline+1])
            disp.drawstring(offset, i*2, msgs[startline+i]);
        }
        startline++;
        oldtime = millis();
        disp.display();
    }
}

void ScreenController :: loopimages(const uint8_t* images[]){
    static long oldtime = millis();
    static curindex = 0;
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
    offset = getcenteroffset(&word);
    disp.clear();
    disp.drawstring(offset, 4, word);
    disp.display();
}

int ScreenController :: getcenteroffset(char* text){
    characters = sizeof(text);
    sparespace = (16-characters)*8;
    return sparespace/2;
}

