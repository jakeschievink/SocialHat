#include <ST7565.h>
#include "Timer.h"
#include "ScreenController.h"
#include "thankyouBMP.h"
#include "glasses.h"
#include "stretch.h"
#include "words.h"

#define BUTTON_PIN 14

#define BACKLIGHT_PIN 9

#define DEBUG 1

const uint8_t* images[] = {
    thankyou,
    glasses,
    stretch
};

ScreenController screencontroller(8,7,6,5,4);

Timer t;

enum States {MESSAGELOOP, SLIDESHOW, RANDOMWORD};

States currentstate = MESSAGELOOP;

char* messages[] = {
    "Art",
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
    screencontroller.init();
    analogWrite(BACKLIGHT_PIN, 100);
    delay(2000);
}

void loop(){
    long currenttime = millis();
    if(pressed() == HIGH && currentstate != RANDOMWORD){
        currentstate = States((int)currentstate + 1);
        delay(1000);
    }else if( pressed() == HIGH && currentstate == RANDOMWORD){
        currentstate = MESSAGELOOP; 
        delay(1000);
    }

    switch(currentstate){
        case MESSAGELOOP:
            screencontroller.looplines(&messages);
            break;
        case SLIDESHOW:
            screencontroller.loopimages(images);
            break;
        case RANDOMWORD:
            displayrandomwords();
            break;
    }
}  

int pressed(){
    static long oldtime = 0;
    if(currenttime - oldtime > 1000){
        starttime = millis();
        return digitalRead(BUTTON_PIN);
    }else{
        return 0; 
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
