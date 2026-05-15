#include "GUI_Colours.h"

RGB::RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

RGB::RGB(uint8_t r, uint8_t g, uint8_t b) : RGB(r, g, b, 255) {}

RGB::RGB() : RGB(0, 0, 0) {}

RGB::RGB(const RGB &c)
{
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
}

RGB RGB::operator=(const RGB &c)
{
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
    return *this;
}

/**
 * @brief Get red value
 *
 * @return Red value
 */
uint8_t RGB::get_red()
{
    return r;
}

/**
 * @brief Get green value
 *
 * @return Green value
 */
uint8_t RGB::get_green()
{
    return g;
}

/**
 * @brief Get blue value
 *
 * @return Blue value
 */
uint8_t RGB::get_blue()
{
    return b;
}

/**
 * @brief Get alpha value
 *
 * @return Alpha value
 */
uint8_t RGB::get_alpha()
{
    return a;
}