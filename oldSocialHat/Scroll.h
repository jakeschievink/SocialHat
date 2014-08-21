#include <Arduino.h>


class Scroll{
public:
    Scroll(int oled_dc, int oled_cs, int oled_clk, int oled_mosi, int oled_reset);
    void init();
    void startScroll();
    void setMessage(char* msg);
    Adafruit_SSD1306 disp;
private: 
    typedef enum {SIDEWAYS, UPWARDS} scroll_type;
    struct 
    {
        scroll_type scrolling; 
        int text_size;
    }configuration;

    char _message[200];
    int _x, _minX, _y, _minY;
    void convert_comma_to_newline(char* msg);
    int get_newlines(char* msg);
    void setMinX();
    void setMinY();
};
    
