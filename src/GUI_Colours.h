#pragma once

#include "platform.h"

class RGB
{
private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

public:
    RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    RGB(uint8_t r, uint8_t g, uint8_t b);
    RGB();
    RGB(const RGB &c);

    ~RGB() {}

    RGB operator=(const RGB &c);

    uint8_t get_red();
    uint8_t get_green();
    uint8_t get_blue();
    uint8_t get_alpha();
};
