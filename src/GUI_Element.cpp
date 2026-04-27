#include "GUI_Element.h"

GUI_Element::GUI_Element(int16_t _x, int16_t _y, uint16_t _h, uint16_t _w) : x(_x), y(_y), height(_h), width(_w)
{
    hidden = false;
    selected = false;
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
