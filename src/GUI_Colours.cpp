#include "GUI_Colours.h"

RGB::RGB(uint8_t _r, uint8_t _g, uint8_t _b)
{
    r = _r;
    g = _g;
    b = _b;
}

RGB::RGB() : RGB(0, 0, 0) {}

RGB::RGB(const RGB &c)
{
    r = c.r;
    g = c.g;
    b = c.b;
}

RGB RGB::operator=(const RGB &c)
{
    r = c.r;
    g = c.g;
    b = c.b;
    return *this;
}

uint8_t RGB::get_red()
{
    return r;
}

uint8_t RGB::get_green()
{
    return g;
}

uint8_t RGB::get_blue()
{
    return b;
}