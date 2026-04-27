#include "GUI.h"

GUI_Element::GUI_Element(int16_t _x, int16_t _y, uint16_t _h, uint16_t _w) : x(_x), y(_y), height(_h), width(_w)
{
    hidden = false;
    selected = false;
    text_size = 1;
    text_colour = BLACK;
    background_colour = WHITE;
    trim_colour = BLACK;
}

GUI_Element::GUI_Element(int16_t _x, int16_t _y) : GUI_Element(_x, _y, 0, 0) {}

GUI_Element::GUI_Element() : GUI_Element(0, 0) {}

int16_t GUI_Element::get_x()
{
    return x;
}

int16_t GUI_Element::get_y()
{
    return y;
}

uint16_t GUI_Element::get_width()
{
    return width;
}

uint16_t GUI_Element::get_height()
{
    return height;
}

uint16_t GUI_Element::get_background_colour()
{
    return background_colour;
}

uint16_t GUI_Element::get_trim_colour()
{
    return trim_colour;
}

uint16_t GUI_Element::get_text_colour()
{
    return text_colour;
}

uint8_t GUI_Element::get_text_size()
{
    return text_size;
}

void GUI_Element::set_x(int16_t _x)
{
    x = _x;
}

void GUI_Element::set_y(int16_t _y)
{
    y = _y;
}

void GUI_Element::set_width(uint16_t _width)
{
    width = _width;
}

void GUI_Element::set_height(uint16_t _height)
{
    height = _height;
}

void GUI_Element::set_dimensions(int16_t _x, int16_t _y, uint16_t _width, uint16_t _height)
{
    set_x(_x);
    set_y(_y);
    set_width(_width);
    set_height(_height);
}

void GUI_Element::set_background_colour(uint16_t _background_colour)
{
    background_colour = _background_colour;
}

void GUI_Element::set_trim_colour(uint16_t _trim_colour)
{
    trim_colour = _trim_colour;
}

void GUI_Element::set_text_colour(uint16_t _text_colour)
{
    text_colour = _text_colour;
}

void GUI_Element::set_text_size(uint8_t _text_size)
{
    text_size = _text_size;
}

void GUI_Element::select()
{
    selected = true;
}

void GUI_Element::deselect()
{
    selected = false;
}

void GUI_Element::hide()
{
    hidden = true;
}

void GUI_Element::show()
{
    hidden = false;
}

bool GUI_Element::is_selected()
{
    return selected;
}

bool GUI_Element::is_hidden()
{
    return hidden;
}

bool GUI_Element::within_bounds(int16_t x_pos, int16_t y_pos)
{
    bool ret = false;

    if (x_pos >= get_x() && x_pos <= get_x() + width && y_pos >= get_y() && y_pos <= get_y() + height)
        ret = true;

    return ret;
}
