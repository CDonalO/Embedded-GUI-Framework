#include "GUI.h"

GUI_Element::GUI_Element(int16_t _x, int16_t _y, uint16_t _h, uint16_t _w) : x(_x), y(_y), height(_h), width(_w)
{
    hidden = false;
    selected = false;
    text_size = 1;
    text_colour = BLACK;
    active_text_colour = WHITE;
    background_colour = WHITE;
    trim_colour = BLACK;
    active_trim_colour = BLACK;
    active_background_colour = WHITE;
    container_x_offset = 0;
    container_y_offset = 0;
    max_width_px = 0;
    max_height_px = 0;
    refresh = true;
    width_auto_size = false;
    height_auto_size = false;
    parent = NULL;
}

GUI_Element::GUI_Element(int16_t _x, int16_t _y) : GUI_Element(_x, _y, 0, 0) {}

GUI_Element::GUI_Element() : GUI_Element(0, 0) {}

// Compare visible element properties
bool GUI_Element::operator==(const GUI_Element &element) const
{
    if (this->x != element.x)
    {
        return false;
    }

    if (this->y != element.y)
    {
        return false;
    }

    if (this->height != element.height)
    {
        return false;
    }

    if (this->width != element.width)
    {
        return false;
    }

    if (this->max_height_px != element.max_height_px)
    {
        return false;
    }

    if (this->max_width_px != element.max_width_px)
    {
        return false;
    }

    if (this->hidden != element.hidden)
    {
        return false;
    }

    return true;
}

int16_t GUI_Element::get_x()
{
    return x + container_x_offset;
}

int16_t GUI_Element::get_y()
{
    return y + container_y_offset;
}

uint16_t GUI_Element::get_x_offset()
{
    return container_x_offset;
}

uint16_t GUI_Element::get_y_offset()
{
    return container_y_offset;
}

uint16_t GUI_Element::get_width()
{
    return width;
}

uint16_t GUI_Element::get_height()
{
    return height;
}

uint16_t GUI_Element::get_max_width_px()
{
    return max_width_px;
}

uint16_t GUI_Element::get_max_height_px()
{
    return max_height_px;
}

bool GUI_Element::get_width_auto_sizeable()
{
    return width_auto_size;
}

bool GUI_Element::get_height_auto_sizeable()
{
    return height_auto_size;
}

RGB GUI_Element::get_background_colour()
{
    return background_colour;
}

RGB GUI_Element::get_trim_colour()
{
    return trim_colour;
}

RGB GUI_Element::get_active_background_colour()
{
    return active_background_colour;
}

RGB GUI_Element::get_active_trim_colour()
{
    return active_trim_colour;
}

RGB GUI_Element::get_text_colour()
{
    return text_colour;
}

RGB GUI_Element::get_active_text_colour()
{
    return active_text_colour;
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

void GUI_Element::set_x_offset(uint16_t offset)
{
    container_x_offset = offset;
}

void GUI_Element::set_y_offset(uint16_t offset)
{
    container_y_offset = offset;
}

void GUI_Element::set_width(uint16_t _width)
{
    width = _width;
}

void GUI_Element::set_height(uint16_t _height)
{
    height = _height;
}

void GUI_Element::set_max_width_px(uint16_t max_width)
{
    max_width_px = max_width;
}

void GUI_Element::set_max_height_px(uint16_t max_height)
{
    max_height_px = max_height;
}

void GUI_Element::set_dimensions(int16_t _x, int16_t _y, uint16_t _width, uint16_t _height)
{
    set_x(_x);
    set_y(_y);
    set_width(_width);
    set_height(_height);
}

void GUI_Element::set_width_auto_sizeable(bool auto_sizeable)
{
    width_auto_size = auto_sizeable;
}

void GUI_Element::set_height_auto_sizeable(bool auto_sizeable)
{
    height_auto_size = auto_sizeable;
}

void GUI_Element::set_background_colour(RGB _background_colour)
{
    background_colour = _background_colour;
}

void GUI_Element::set_trim_colour(RGB _trim_colour)
{
    trim_colour = _trim_colour;
}

void GUI_Element::set_active_background_colour(RGB _background_colour)
{
    active_background_colour = _background_colour;
}

void GUI_Element::set_active_trim_colour(RGB _trim_colour)
{
    active_trim_colour = _trim_colour;
}

void GUI_Element::set_colours(RGB _background_colour, RGB _active_background_colour, RGB _trim_colour, RGB _active_trim_colour)
{
    set_background_colour(_background_colour);
    set_active_background_colour(_active_background_colour);
    set_trim_colour(_trim_colour);
    set_active_trim_colour(_active_trim_colour);
}

void GUI_Element::set_base_colours(RGB _background_colour, RGB _trim_colour)
{
    set_background_colour(_background_colour);
    set_trim_colour(_trim_colour);
}

void GUI_Element::set_active_colours(RGB _active_background_colour, RGB _active_trim_colour)
{
    set_active_background_colour(_active_background_colour);
    set_active_trim_colour(_active_trim_colour);
}

void GUI_Element::set_text_colour(RGB _text_colour)
{
    text_colour = _text_colour;
}

void GUI_Element::set_active_text_colour(RGB _active_text_colour)
{
    active_text_colour = _active_text_colour;
}

void GUI_Element::set_text_colours(RGB _text_colour, RGB _active_text_colour)
{
    set_text_colour(_text_colour);
    set_active_text_colour(_active_text_colour);
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
