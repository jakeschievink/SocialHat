#include <ST7565.h>
#include "ScreenController.h"
#include "thankyouBMP.h"
#include "glasses.h"
#include "stretch.h"

#include "words.h"

#define BACKLIGHT_LED 10

#define DEBUG 1

const uint8_t* images[] = {
    thankyou,
    glasses,
    stretch
};

/* ST7565 glcd(23, 22, 21, 20, 19); */
ScreenController screencontroller(23,22,21,20,19);
enum States {MESSAGELOOP, SLIDESHOW, RANDOMWORD};

States currentstate = RANDOMWORD;
char* messages[] = {
    "Open Source",
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
    "Communes"
};

void setup(){
  Serial.begin(9600);
  screencontroller.init();
  delay(2000);
}

void loop(){
    switch(currentstate){
        case MESSAGELOOP:
            screencontroller.looplines(&messages);
            break;
        case SLIDESHOW:
            screencontroller.loopimages(images);
            break;
        case RANDOMWORD:
            screencontroller.showword(getrandomword());
            delay(5000);
            break;
    }
}  

char* getrandomword(){
    static int maxrand = sizeof(words)/sizeof(words[0]);
    int randomindex = random(maxrand);
    Serial.println(randomindex);
    return words[randomindex];
}
