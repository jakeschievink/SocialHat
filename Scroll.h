#include <Arduino.h>

class Scroll{
public:
    Scroll();
    void init();
    void startScroll();
    void setMessage(char* msg);
    
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
    
