#include <Arduino.h>
#include "ST7565.h"

#define SCROLLINTERVAL 5000

class ScreenController{
public:
    ScreenController(int8_t SID, int8_t SCLK, int8_t A0, int8_t RST, int8_t CS) :disp(SID, SCLK, AO, RST, CS) {};
    void init(char* msgs[]);
    void startScroll();
    void showimage();
    void looplines();
    void showword();
    ST7565 disp;
private:
    int getcenteroffset(int characters)
};
    
