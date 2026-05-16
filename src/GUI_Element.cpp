#include "GUI_Element.h"

GUI_Element::GUI_Element(int16_t x, int16_t y, uint16_t height, uint16_t width) : x(x), y(y), height(height), width(width)
{
    hidden = false;
    selected = false;
    font_size = 1;
    font_colour = BLACK;
    active_font_colour = WHITE;
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
    colour_scheme_set = false;
    background_colour_set = false;
    active_background_colour_set = false;
    trim_colour_set = false;
    active_trim_colour_set = false;
    font_colour_set = false;
    active_font_colour_set = false;
    font_size_set = false;
    alignment = ALIGN_CENTER_HORIZONTAL | ALIGN_CENTER_VERTICAL;
}

GUI_Element::GUI_Element(int16_t x, int16_t y) : GUI_Element(x, y, 0, 0) {}

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
 * @brief Get Element alignment
 *
 * @return Alignment of element
 */
uint8_t GUI_Element::get_element_alignment()
{
    return alignment;
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
 * @brief Get colour scheme of element
 *
 * @return colour scheme of element
 */
GUI_Colour_Scheme GUI_Element::get_colour_scheme()
{
    return colour_scheme;
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
 * @brief Get RGB font colour of element
 *
 * @return RGB font colour of element
 */
RGB GUI_Element::get_font_colour()
{
    return font_colour;
}

/**
 * @brief Get RGB active font colour of element
 *
 * @return RGB active font colour of element
 */
RGB GUI_Element::get_active_font_colour()
{
    return active_font_colour;
}

/**
 * @brief Get font size of element
 *
 * @return Font size of element
 */
uint8_t GUI_Element::get_font_size()
{
    return font_size;
}

/**
 * @brief Set x position of element
 *
 * @param x The new x position
 */
void GUI_Element::set_x(int16_t x)
{
    this->x = x;
}

/**
 * @brief Set y position of element
 *
 * @param y The new y position
 */
void GUI_Element::set_y(int16_t y)
{
    this->y = y;
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
 * @brief Set element alignment
 *
 * @param alignment Element alignment
 */
void GUI_Element::set_element_alignment(uint8_t alignment)
{
    this->alignment = alignment;
}

/**
 * @brief Set width of element
 *
 * @param width The new width
 */
void GUI_Element::set_width(uint16_t width)
{
    this->width = width;
}

/**
 * @brief Set height of element
 *
 * @param height The new height
 */
void GUI_Element::set_height(uint16_t height)
{
    this->height = height;
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
 * @brief Set colour scheme of element
 *
 * @param scheme Colour scheme of element
 */
void GUI_Element::set_colour_scheme(GUI_Colour_Scheme scheme)
{
    if (!colour_scheme_set)
    {
        colour_scheme = scheme;
        colour_scheme_set = true;

        if (colour_scheme.is_background_colour_set())
        {
            _set_background_colour(colour_scheme.get_background_colour());
        }

        if (colour_scheme.is_active_background_colour_set())
        {
            _set_active_background_colour(colour_scheme.get_active_background_colour());
        }

        if (colour_scheme.is_trim_colour_set())
        {
            _set_trim_colour(colour_scheme.get_trim_colour());
        }

        if (colour_scheme.is_active_trim_colour_set())
        {
            _set_active_trim_colour(colour_scheme.get_active_trim_colour());
        }

        if (colour_scheme.is_font_colour_set())
        {
            _set_font_colour(colour_scheme.get_font_colour());
        }

        if (colour_scheme.is_active_font_colour_set())
        {
            _set_active_font_colour(colour_scheme.get_active_font_colour());
        }
    }
}

/**
 * @brief Set background colour of element
 *
 * @param background_colour Colour of background
 */
void GUI_Element::set_background_colour(RGB background_colour)
{
    background_colour_set = true;
    this->background_colour = background_colour;
}

/**
 * @brief Set trim colour of element
 *
 * @param trim_colour Colour of background
 */
void GUI_Element::set_trim_colour(RGB trim_colour)
{
    trim_colour_set = true;
    this->trim_colour = trim_colour;
}

/**
 * @brief Set active background colour of element
 *
 * @param active_background_colour Colour of active background
 */
void GUI_Element::set_active_background_colour(RGB active_background_colour)
{
    active_background_colour_set = true;
    this->active_background_colour = active_background_colour;
}

/**
 * @brief Set active trim colour of element
 *
 * @param active_trim_colour Colour of active trim
 */
void GUI_Element::set_active_trim_colour(RGB active_trim_colour)
{
    active_trim_colour_set = true;
    this->active_trim_colour = active_trim_colour;
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
 * @brief Set font colour of element
 *
 * @param font_colour Colour of font
 */
void GUI_Element::set_font_colour(RGB font_colour)
{
    font_colour_set = true;
    this->font_colour = font_colour;
}

/**
 * @brief Set active font colour of element
 *
 * @param active_font_colour Colour of active font
 */
void GUI_Element::set_active_font_colour(RGB active_font_colour)
{
    active_font_colour_set = true;
    this->active_font_colour = active_font_colour;
}

/**
 * @brief Set font colours of element
 *
 * @param _font_colour Colour of font
 * @param _active_font_colour Colour of active font
 */
void GUI_Element::set_font_colours(RGB _font_colour, RGB _active_font_colour)
{
    set_font_colour(_font_colour);
    set_active_font_colour(_active_font_colour);
}

/**
 * @brief Set font size of element
 *
 * @param font_size Size of font.
 */
void GUI_Element::set_font_size(uint8_t font_size)
{
    font_size_set = true;
    this->font_size = font_size;
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
 * @brief Set element interactable
 *
 * @param value New interactable value
 */
void GUI_Element::set_interactable(bool value)
{
    interactable = value;
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
 * @brief Check if element is interactable
 *
 * @return True if interactable otherwise false
 */
bool GUI_Element::is_interactable()
{
    return interactable;
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

/**
 * @brief Check if font size has been manually set
 *
 * @return True if font size has been manually set otherwise false
 */
bool GUI_Element::is_font_size_set()
{
    return font_size_set;
}

/**
 * @brief Check if colour scheme has been manually set
 *
 * @return True if colour scheme has been manually set otherwise false
 */
bool GUI_Element::is_colour_scheme_set()
{
    return colour_scheme_set;
}

#ifdef VERBOSE_ELEMENT_DEBUG
void GUI_Element::print_element()
{
    PLATFORM_PRINTF("Element\n");
    PLATFORM_PRINTF("X: %d, X offset: %d\n", x, container_x_offset);
    PLATFORM_PRINTF("Y: %d, Y offset: %d\n", y, container_y_offset);
    PLATFORM_PRINTF("Width: %d, Height: %d\n", width, height);
}
#else
void GUI_Element::print_element() {}
#endif

void GUI_Element::_set_background_colour(RGB background_colour)
{
    if (background_colour_set)
    {
        return;
    }

    this->background_colour = background_colour;
}

void GUI_Element::_set_active_background_colour(RGB active_background_colour)
{
    if (active_background_colour_set)
    {
        return;
    }

    this->active_background_colour = active_background_colour;
}

void GUI_Element::_set_trim_colour(RGB trim_colour)
{
    if (trim_colour_set)
    {
        return;
    }

    this->trim_colour = trim_colour;
}

void GUI_Element::_set_active_trim_colour(RGB active_trim_colour)
{
    if (active_trim_colour_set)
    {
        return;
    }

    this->active_trim_colour = active_trim_colour;
}

void GUI_Element::_set_font_colour(RGB font_colour)
{
    if (font_colour_set)
    {
        return;
    }

    this->font_colour = font_colour;
}

void GUI_Element::_set_active_font_colour(RGB active_font_colour)
{
    if (active_font_colour_set)
    {
        return;
    }

    this->active_font_colour = active_font_colour;
}