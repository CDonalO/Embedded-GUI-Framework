#include "GUI_Colours.h"

RGB::RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

RGB::RGB(uint8_t r, uint8_t g, uint8_t b) : RGB(r, g, b, 255) {}

RGB::RGB(PLATFORM_STRING hex_string) : RGB(0, 0, 0)
{
    PLATFORM_STRING hex_string_escaped = hex_string;

    if (hex_string.length() == 0)
    {
        return;
    }

    if (PLATFORM_STRING_AT(hex_string, 0) == '#')
    {
        hex_string_escaped = PLATFORM_STRING_POP_FRONT(hex_string);
    }

    if (hex_string_escaped.length() != 6)
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

GUI_Colour_Scheme::GUI_Colour_Scheme(RGB background_colour)
{
    this->background_colour = background_colour;
    background_colour_set = true;
}

GUI_Colour_Scheme::GUI_Colour_Scheme(RGB background_colour, RGB active_background_colour) : GUI_Colour_Scheme(background_colour)
{
    this->active_background_colour = active_background_colour;
    active_background_colour_set = true;
}

GUI_Colour_Scheme::GUI_Colour_Scheme(RGB background_colour, RGB active_background_colour, RGB trim_colour) : GUI_Colour_Scheme(background_colour, active_background_colour)
{
    this->trim_colour = trim_colour;
    trim_colour_set = true;
}

GUI_Colour_Scheme::GUI_Colour_Scheme(RGB background_colour, RGB active_background_colour, RGB trim_colour, RGB active_trim_colour) : GUI_Colour_Scheme(background_colour, active_background_colour, trim_colour)
{
    this->active_trim_colour = active_trim_colour;
    active_trim_colour_set = true;
}

GUI_Colour_Scheme::GUI_Colour_Scheme(RGB background_colour, RGB active_background_colour, RGB trim_colour, RGB active_trim_colour, RGB font_colour) : GUI_Colour_Scheme(background_colour, active_background_colour, trim_colour, active_trim_colour)
{
    this->font_colour = font_colour;
    font_colour_set = true;
}

GUI_Colour_Scheme::GUI_Colour_Scheme(RGB background_colour, RGB active_background_colour, RGB trim_colour, RGB active_trim_colour, RGB font_colour, RGB active_font_colour) : GUI_Colour_Scheme(background_colour, active_background_colour, trim_colour, active_trim_colour, font_colour)
{
    this->active_font_colour = active_font_colour;
    active_font_colour_set = true;
}

GUI_Colour_Scheme::GUI_Colour_Scheme()
{
    background_colour_set = false;
    active_background_colour_set = false;
    trim_colour_set = false;
    active_trim_colour_set = false;
    font_colour_set = false;
    active_font_colour_set = false;
}

RGB GUI_Colour_Scheme::get_background_colour()
{
    return background_colour;
}

RGB GUI_Colour_Scheme::get_active_background_colour()
{
    return active_background_colour;
}

RGB GUI_Colour_Scheme::get_trim_colour()
{
    return trim_colour;
}

RGB GUI_Colour_Scheme::get_active_trim_colour()
{
    return active_trim_colour;
}

RGB GUI_Colour_Scheme::get_font_colour()
{
    return font_colour;
}

RGB GUI_Colour_Scheme::get_active_font_colour()
{
    return active_font_colour;
}

bool GUI_Colour_Scheme::is_background_colour_set()
{
    return background_colour_set;
}

bool GUI_Colour_Scheme::is_active_background_colour_set()
{
    return active_background_colour_set;
}

bool GUI_Colour_Scheme::is_trim_colour_set()
{
    return trim_colour_set;
}

bool GUI_Colour_Scheme::is_active_trim_colour_set()
{
    return active_trim_colour_set;
}

bool GUI_Colour_Scheme::is_font_colour_set()
{
    return font_colour_set;
}

bool GUI_Colour_Scheme::is_active_font_colour_set()
{
    return active_font_colour_set;
}