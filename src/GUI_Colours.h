#ifndef _GUI_Colours_H_
#define _GUI_Colours_H_

#include <Arduino.h>

class RGB
{
private:
    uint8_t r;
    uint8_t g;
    uint8_t b;

public:
    RGB();
    RGB(uint8_t _r, uint8_t _g, uint8_t _b);
    RGB(const RGB &c);

    ~RGB() {}

    RGB operator=(const RGB &c);

    uint8_t get_red();
    uint8_t get_green();
    uint8_t get_blue();
};

#endif /* _GUI_Colours_H_ */