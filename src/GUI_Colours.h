#pragma once

#include <Arduino.h>

class RGB
{
private:
    uint8_t r;
    uint8_t g;
    uint8_t b;

public:
    RGB();
    RGB(uint8_t r, uint8_t g, uint8_t b);
    RGB(const RGB &c);

    ~RGB() {}

    RGB operator=(const RGB &c);

    uint8_t get_red();
    uint8_t get_green();
    uint8_t get_blue();
};
