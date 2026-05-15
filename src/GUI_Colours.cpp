#include "GUI_Colours.h"

RGB::RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

RGB::RGB(uint8_t r, uint8_t g, uint8_t b) : RGB(r, g, b, 255) {}

RGB::RGB(PLATFORM_STRING hex_string) : RGB(0, 0, 0)
{
    PLATFORM_STRING hex_string_escaped = hex_string;

    if (hex_string.size() == 0)
    {
        return;
    }

    if (PLATFORM_STRING_AT(hex_string, 0) == '#')
    {
        hex_string_escaped = PLATFORM_STRING_POP_FRONT(hex_string);
    }

    if (hex_string_escaped.size() != 6)
    {
        return;
    }

    uint32_t hex_value = strtol(hex_string_escaped.c_str(), nullptr, 16);
    uint32_t red = hex_value & (0xFF << 16);
    uint32_t green = hex_value & (0xFF << 8);
    uint32_t blue = hex_value & 0xFF;

    r = red >> 16;
    g = green >> 8;
    b = blue;
}

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