#include "ST7565.h"
#include "ScreenController.h"
#include "thankyouBMP.h"
#include "glasses.h"

#include "words.h"

#define BACKLIGHT_LED 10

#define DEBUG 1

const uint8_t* images[] = {
    thankyou,
    glasses
}

/* ST7565 glcd(23, 22, 21, 20, 19); */
ScreenController screencontroller(23,22,21,20,19);
enum States {MESSAGELOOP, SLIDESHOW, RANDOMWORD};

States currentstate = MESSAGELOOP;
char* listOfMessages[] = {
    "Botany",
    "Communities",
    "Dystopia",
    "Creation",
    "Cyber Technology",
    "Drawing",
    "Anarchism",
    "Stress",
    "Individualism",
    "Violence",
    "Communes", 
    "Autonomy"
};

void setup(){
  Serial.begin(9600);
  screencontroller.init();
}

void loop(){
    switch(currentstate){
        case MESSAGELOOP:
            screencontroller.looplines(&messages);
            break;
        case SLIDESHOW:
            screencontroller.loopimages(&images);
            break;
        case RANDOMWORD:
            screencontroller.showword(getrandomword());
            break;
    }
}

char* getrandomword(){
    static int maxrand = sizeof(words)/sizeof(words[0])
    srandom(600);
    randomindex = random() % maxrand;
}
