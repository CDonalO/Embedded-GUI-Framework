#pragma once

#include "GUI_Colours.h"
#include "drivers/display_driver.h"
#include "GUI_Definitions.h"

class GUI_Element
{
private:
    int16_t x;
    int16_t y;
    uint16_t height;
    uint16_t width;
    uint16_t container_x_offset;
    uint16_t container_y_offset;
    uint16_t max_height_px;
    uint16_t max_width_px;
    GUI_Colour_Scheme colour_scheme;
    bool colour_scheme_set;
    RGB background_colour;
    bool background_colour_set;
    RGB trim_colour;
    bool trim_colour_set;
    RGB active_background_colour;
    bool active_background_colour_set;
    RGB active_trim_colour;
    bool active_trim_colour_set;
    RGB font_colour;
    bool font_colour_set;
    RGB active_font_colour;
    bool active_font_colour_set;
    uint8_t font_size;
    bool font_size_set;
    bool hidden;
    bool selected;
    bool width_auto_size;
    bool height_auto_size;
    bool interactable = false;

protected:
    bool refresh;

public:
    GUI_Element(int16_t x, int16_t y, uint16_t height, uint16_t width);
    GUI_Element(int16_t x, int16_t y);
    GUI_Element();
    GUI_Element *parent;

    enum class Element_Type
    {
        BUTTON,
        TOGGLE_BUTTON,
        MENU,
        VIEW,
        GRID,
        LABEL,
        FORM,
        BITMAP,
        IMAGE,
    };

    virtual ~GUI_Element() = default;

    virtual void draw(display_driver *display) = 0;
    virtual void navigate(int16_t x_pos, int16_t y_pos) = 0;
    virtual void navigate(INPUT_TYPE input, KEYBOARD_KEY key) = 0;
    virtual void set_refresh(bool r, bool p) = 0;
    virtual Element_Type get_type() = 0;
    virtual GUI_Element *clone() const = 0;

    bool operator==(const GUI_Element &element) const;

    int16_t get_x();
    int16_t get_y();
    uint16_t get_x_offset();
    uint16_t get_y_offset();
    uint16_t get_width();
    uint16_t get_height();
    uint16_t get_max_width_px();
    uint16_t get_max_height_px();
    bool get_width_auto_sizeable();
    bool get_height_auto_sizeable();
    GUI_Colour_Scheme get_colour_scheme();
    RGB get_background_colour();
    RGB get_trim_colour();
    RGB get_active_background_colour();
    RGB get_active_trim_colour();
    RGB get_font_colour();
    RGB get_active_font_colour();
    uint8_t get_font_size();
    void set_x(int16_t x);
    void set_y(int16_t y);
    void set_x_offset(uint16_t offset);
    void set_y_offset(uint16_t offset);
    void set_width(uint16_t width);
    void set_height(uint16_t height);
    void set_max_width_px(uint16_t max_width);
    void set_max_height_px(uint16_t max_height);
    void set_dimensions(int16_t _x, int16_t _y, uint16_t _w, uint16_t _h);
    void set_width_auto_sizeable(bool auto_sizeable);
    void set_height_auto_sizeable(bool auto_sizeable);
    void set_colour_scheme(GUI_Colour_Scheme scheme);
    void set_background_colour(RGB background_colour);
    void set_trim_colour(RGB trim_colour);
    void set_active_background_colour(RGB active_background_colour);
    void set_active_trim_colour(RGB active_trim_colour);
    void set_base_colours(RGB _background_colour, RGB _trim_colour);
    void set_active_colours(RGB _active_background_colour, RGB _active_trim_colour);
    void set_colours(RGB _background_colour, RGB _active_background_colour, RGB _trim_colour, RGB _active_trim_colour);
    void set_font_colour(RGB font_colour);
    void set_active_font_colour(RGB active_font_colour);
    void set_font_colours(RGB _font_colour, RGB _active_font_colour);
    void set_font_size(uint8_t font_size);
    void select();
    void deselect();
    void hide();
    void show();
    void set_interactable(bool value);
    bool is_selected();
    bool is_hidden();
    bool is_interactable();
    bool within_bounds(int16_t x_pos, int16_t y_pos);
    bool is_font_size_set();
    bool is_colour_scheme_set();

    void print_element();

private:
    void _set_background_colour(RGB background_colour);
    void _set_active_background_colour(RGB active_background_colour);
    void _set_trim_colour(RGB trim_colour);
    void _set_active_trim_colour(RGB active_trim_colour);
    void _set_font_colour(RGB font_colour);
    void _set_active_font_colour(RGB active_font_colour);
};
