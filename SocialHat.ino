#include <ST7565.h>
#include <EEPROM.h>
#include "EEPROMAnything.h"
#include "ScreenController.h"
#include "SendReceive.h"
#include "thankyouBMP.h"
#include "glasses.h"
#include "johntab.h"
#include "opensub.h"
#include "stretch.h"
#include "wouda.h"
#include "words.h"

#define BUTTON_PIN 11

#define BACKLIGHT_PIN 3

#define DEBUG 1

const uint8_t* images[] = {
    stretch,
    wouda,
    johntab,
    glasses,
    thankyou,
    opensub
};

const uint8_t* opensubimages[]={
    wouda,
    opensub
};

ScreenController screencontroller(10,9,8,7,6);
SendReceive sendrecieve;

enum States {SHOWRECIEVED, MESSAGELOOP, SLIDESHOW, OPENFORSUBMISSIONS, RANDOMWORD, RECIEVENEW};

States currentstate = SHOWRECIEVED;

long currenttime;

char* recievedmessage;
char messagebuffer[200];

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
    EEPROM_readAnything(0, messagebuffer);
    screencontroller.init();
    analogWrite(BACKLIGHT_PIN, 100);
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

        case RECIEVENEW:
            screencontroller.showword("RECIEVING");
            recieve();
            break;

        case SHOWRECIEVED:
            screencontroller.showword(messagebuffer);
            break;
          }
}  

void recieve(){
    sendrecieve.recieve();
    if(sendrecieve.ismessageready()){
        for(int i = 0; i<200; i++){
            messagebuffer[i] = sendrecieve.messageholder[i];
        }
        EEPROM_writeAnything(0, messagebuffer);
    }
}

void press(){
    static long oldtime = 0;
    if(currenttime - oldtime > 1000 && currentstate != RECIEVENEW){
        currentstate = States((int)currentstate + 1);
    }else if(currenttime - oldtime > 1000 && currentstate == RECIEVENEW){
        currentstate = SHOWRECIEVED;
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

