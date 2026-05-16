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
    RGB(PLATFORM_STRING hex_string);
    RGB();
    RGB(const RGB &c);

    ~RGB() {}

    RGB operator=(const RGB &c);

    uint8_t get_red();
    uint8_t get_green();
    uint8_t get_blue();
    uint8_t get_alpha();
};

class GUI_Colour_Scheme
{
private:
    RGB background_colour;
    RGB active_background_colour;
    RGB trim_colour;
    RGB active_trim_colour;
    RGB font_colour;
    RGB active_font_colour;

    bool background_colour_set;
    bool active_background_colour_set;
    bool trim_colour_set;
    bool active_trim_colour_set;
    bool font_colour_set;
    bool active_font_colour_set;

public:
    GUI_Colour_Scheme(RGB background_colour, RGB active_background_colour, RGB trim_colour, RGB active_trim_colour, RGB font_colour, RGB active_font_colour);
    GUI_Colour_Scheme(RGB background_colour, RGB active_background_colour, RGB trim_colour, RGB active_trim_colour, RGB font_colour);
    GUI_Colour_Scheme(RGB background_colour, RGB active_background_colour, RGB trim_colour, RGB active_trim_colour);
    GUI_Colour_Scheme(RGB background_colour, RGB active_background_colour, RGB trim_colour);
    GUI_Colour_Scheme(RGB background_colour, RGB active_background_colour);
    GUI_Colour_Scheme(RGB background_colour);
    GUI_Colour_Scheme();

    ~GUI_Colour_Scheme() {}

    RGB get_background_colour();
    RGB get_active_background_colour();
    RGB get_trim_colour();
    RGB get_active_trim_colour();
    RGB get_font_colour();
    RGB get_active_font_colour();

    bool is_background_colour_set();
    bool is_active_background_colour_set();
    bool is_trim_colour_set();
    bool is_active_trim_colour_set();
    bool is_font_colour_set();
    bool is_active_font_colour_set();
};
