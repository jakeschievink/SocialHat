#include <ST7565.h>
#include "ScreenController.h"
#include "thankyouBMP.h"
#include "glasses.h"
#include "johntab.h"
#include "opensub.h"
#include "stretch.h"
#include "words.h"

#define BUTTON_PIN 14

#define BACKLIGHT_PIN 9

#define DEBUG 1

const uint8_t* images[] = {
    stretch,
    johntab,
    glasses,
    thankyou,
    opensub
};

const uint8_t* opensubimages[]={
    glasses,
    opensub
};

ScreenController screencontroller(8,7,6,5,4);

enum States {MESSAGELOOP, SLIDESHOW, OPENFORSUBMISSIONS, RANDOMWORD};

States currentstate = MESSAGELOOP;

long currenttime;

char* messages[] = {
    "Art",
    "Plants",
    "Open Source",
    "Anarchism",
    "Botany",
    "Communities",
    "Dystopia",
    "Drawing",
    "Stress",
    "Individualism",
    "Violence",
    "Communes"
};

void setup(){
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT);
    pinMode(BACKLIGHT_PIN, OUTPUT);
    attachInterrupt(BUTTON_PIN, press, RISING);
    screencontroller.init();
    analogWrite(BACKLIGHT_PIN, 100);
    delay(2000);
}

void loop(){
    currenttime = millis();
    switch(currentstate){
        case MESSAGELOOP:
            screencontroller.looplines(&messages);
            break;
        case SLIDESHOW:
            screencontroller.loopimages(images, sizeof(images)/sizeof(*images));
            break;
        case OPENFORSUBMISSIONS:
            screencontroller.loopimages(opensubimages, sizeof(opensubimages)/sizeof(*opensubimages));
            break;
        case RANDOMWORD:
            displayrandomwords();
            break;
    }
}  

void press(){
    static long oldtime = 0;
    if(currenttime - oldtime > 1000 && currentstate != RANDOMWORD){
        currentstate = States((int)currentstate + 1);
    }else if(currenttime - oldtime > 1000 && currentstate == RANDOMWORD){
        currentstate = MESSAGELOOP; 
    }
}

void displayrandomwords(){
    static long oldtime = 0;
    if(currenttime - oldtime > 5000){
        oldtime = millis();
        screencontroller.showword(getrandomword());
    }
}

char* getrandomword(){
    static int maxrand = sizeof(words)/sizeof(words[0]);
    int randomindex = random(maxrand);
    return words[randomindex];
}
