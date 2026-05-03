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

/**
 * @brief Get X position of element
 *
 * @return Absolute x position of element
 */
int16_t GUI_Element::get_x()
{
    return x + container_x_offset;
}

/**
 * @brief Get Y position of element
 *
 * @return Absolute y position of element
 */
int16_t GUI_Element::get_y()
{
    return y + container_y_offset;
}

/**
 * @brief Get X offset of element
 *
 * @return X offset of element
 */
uint16_t GUI_Element::get_x_offset()
{
    return container_x_offset;
}

/**
 * @brief Get Y offset of element
 *
 * @return Y offset of element
 */
uint16_t GUI_Element::get_y_offset()
{
    return container_y_offset;
}

/**
 * @brief Get width of element
 *
 * @return Width of element
 */
uint16_t GUI_Element::get_width()
{
    return width;
}

/**
 * @brief Get height of element
 *
 * @return Height of element
 */
uint16_t GUI_Element::get_height()
{
    return height;
}

/**
 * @brief Get max width of element
 *
 * @return Max width in px of element
 */
uint16_t GUI_Element::get_max_width_px()
{
    return max_width_px;
}

/**
 * @brief Get max height of element
 *
 * @return Max height in px of element
 */
uint16_t GUI_Element::get_max_height_px()
{
    return max_height_px;
}

/**
 * @brief Get element width auto sizeable
 *
 * @return True if width is auto sizeable
 */
bool GUI_Element::get_width_auto_sizeable()
{
    return width_auto_size;
}

/**
 * @brief Get element height auto sizeable
 *
 * @return True if height is auto sizeable
 */
bool GUI_Element::get_height_auto_sizeable()
{
    return height_auto_size;
}

/**
 * @brief Get RGB background colour of element
 *
 * @return RGB background colour of element
 */
RGB GUI_Element::get_background_colour()
{
    return background_colour;
}

/**
 * @brief Get RGB trim colour of element
 *
 * @return RGB trim colour of element
 */
RGB GUI_Element::get_trim_colour()
{
    return trim_colour;
}

/**
 * @brief Get RGB active background colour of element
 *
 * @return RGB active background colour of element
 */
RGB GUI_Element::get_active_background_colour()
{
    return active_background_colour;
}

/**
 * @brief Get RGB active trim colour of element
 *
 * @return RGB active trim colour of element
 */
RGB GUI_Element::get_active_trim_colour()
{
    return active_trim_colour;
}

/**
 * @brief Get RGB text colour of element
 *
 * @return RGB text colour of element
 */
RGB GUI_Element::get_text_colour()
{
    return text_colour;
}

/**
 * @brief Get RGB active text colour of element
 *
 * @return RGB active text colour of element
 */
RGB GUI_Element::get_active_text_colour()
{
    return active_text_colour;
}

/**
 * @brief Get text size of element
 *
 * @return Text size of element
 */
uint8_t GUI_Element::get_text_size()
{
    return text_size;
}

/**
 * @brief Set x position of element
 *
 * @param _x The new x position
 */
void GUI_Element::set_x(int16_t _x)
{
    x = _x;
}

/**
 * @brief Set y position of element
 *
 * @param _y The new y position
 */
void GUI_Element::set_y(int16_t _y)
{
    y = _y;
}

/**
 * @brief Set x offset of element
 *
 * @param offset The new x offset
 */
void GUI_Element::set_x_offset(uint16_t offset)
{
    container_x_offset = offset;
}

/**
 * @brief Set y offset of element
 *
 * @param offset The new y offset
 */
void GUI_Element::set_y_offset(uint16_t offset)
{
    container_y_offset = offset;
}

/**
 * @brief Set width of element
 *
 * @param _width The new width
 */
void GUI_Element::set_width(uint16_t _width)
{
    width = _width;
}

/**
 * @brief Set height of element
 *
 * @param _height The new height
 */
void GUI_Element::set_height(uint16_t _height)
{
    height = _height;
}

/**
 * @brief Set max width of element in px
 *
 * @param max_width The new max width px
 */
void GUI_Element::set_max_width_px(uint16_t max_width)
{
    max_width_px = max_width;
}

/**
 * @brief Set max height of element in px
 *
 * @param max_height The new max height px
 */
void GUI_Element::set_max_height_px(uint16_t max_height)
{
    max_height_px = max_height;
}

/**
 * @brief Set x,y, width, height of element
 *
 * @param _x The new x
 * @param _y The new y
 * @param _width The new width
 * @param _height The new height
 */
void GUI_Element::set_dimensions(int16_t _x, int16_t _y, uint16_t _width, uint16_t _height)
{
    set_x(_x);
    set_y(_y);
    set_width(_width);
    set_height(_height);
}

/**
 * @brief Set element width auto sizeable
 *
 * @param auto_sizeable True if element can resize width dynamically
 */
void GUI_Element::set_width_auto_sizeable(bool auto_sizeable)
{
    width_auto_size = auto_sizeable;
}

/**
 * @brief Set element height auto sizeable
 *
 * @param auto_sizeable True if element can resize height dynamically
 */
void GUI_Element::set_height_auto_sizeable(bool auto_sizeable)
{
    height_auto_size = auto_sizeable;
}

/**
 * @brief Set background colour of element
 *
 * @param _background_colour Colour of background
 */
void GUI_Element::set_background_colour(RGB _background_colour)
{
    background_colour = _background_colour;
}

/**
 * @brief Set trim colour of element
 *
 * @param _trim_colour Colour of background
 */
void GUI_Element::set_trim_colour(RGB _trim_colour)
{
    trim_colour = _trim_colour;
}

/**
 * @brief Set active background colour of element
 *
 * @param _background_colour Colour of active background
 */
void GUI_Element::set_active_background_colour(RGB _background_colour)
{
    active_background_colour = _background_colour;
}

/**
 * @brief Set active trim colour of element
 *
 * @param _trim_colour Colour of active trim
 */
void GUI_Element::set_active_trim_colour(RGB _trim_colour)
{
    active_trim_colour = _trim_colour;
}

/**
 * @brief Set (active) background/trim colours of element
 *
 * @param _background_colour Colour of background
 * @param _active_background_colour Colour of active background
 * @param _trim_colour Colour of trim
 * @param _active_trim_colour Colour of active trim
 */
void GUI_Element::set_colours(RGB _background_colour, RGB _active_background_colour, RGB _trim_colour, RGB _active_trim_colour)
{
    set_background_colour(_background_colour);
    set_active_background_colour(_active_background_colour);
    set_trim_colour(_trim_colour);
    set_active_trim_colour(_active_trim_colour);
}

/**
 * @brief Set base colours of element
 *
 * @param _background_colour Colour of background
 * @param _trim_colour Colour of trim
 */
void GUI_Element::set_base_colours(RGB _background_colour, RGB _trim_colour)
{
    set_background_colour(_background_colour);
    set_trim_colour(_trim_colour);
}

/**
 * @brief Set active colours of element
 *
 * @param _active_background_colour Colour of background
 * @param _active_trim_colour Colour of trim
 */
void GUI_Element::set_active_colours(RGB _active_background_colour, RGB _active_trim_colour)
{
    set_active_background_colour(_active_background_colour);
    set_active_trim_colour(_active_trim_colour);
}

/**
 * @brief Set text colour of element
 *
 * @param _text_colour Colour of text
 */
void GUI_Element::set_text_colour(RGB _text_colour)
{
    text_colour = _text_colour;
}

/**
 * @brief Set active text colour of element
 *
 * @param _active_text_colour Colour of active text
 */
void GUI_Element::set_active_text_colour(RGB _active_text_colour)
{
    active_text_colour = _active_text_colour;
}

/**
 * @brief Set text colours of element
 *
 * @param _text_colour Colour of text
 * @param _active_text_colour Colour of active text
 */
void GUI_Element::set_text_colours(RGB _text_colour, RGB _active_text_colour)
{
    set_text_colour(_text_colour);
    set_active_text_colour(_active_text_colour);
}

/**
 * @brief Set text size of element
 *
 * @param _text_size Size of text.
 */
void GUI_Element::set_text_size(uint8_t _text_size)
{
    text_size = _text_size;
}

/**
 * @brief Select element
 */
void GUI_Element::select()
{
    selected = true;
}

/**
 * @brief Deselect element
 */
void GUI_Element::deselect()
{
    selected = false;
}

/**
 * @brief Hide element
 */
void GUI_Element::hide()
{
    hidden = true;
}

/**
 * @brief Show element
 */
void GUI_Element::show()
{
    hidden = false;
}

/**
 * @brief Check if element is selected
 *
 * @return True if selected otherwise false
 */
bool GUI_Element::is_selected()
{
    return selected;
}

/**
 * @brief Check if element is hidden
 *
 * @return True if hidden otherwise false
 */
bool GUI_Element::is_hidden()
{
    return hidden;
}

/**
 * @brief Check if x,y coordinates within element
 *
 * @return True if within elemenet otherwise false
 */
bool GUI_Element::within_bounds(int16_t x_pos, int16_t y_pos)
{
    bool ret = false;

    if (x_pos >= get_x() && x_pos <= get_x() + width && y_pos >= get_y() && y_pos <= get_y() + height)
        ret = true;

    return ret;
}
