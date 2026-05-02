#ifndef _GUI_Element_H_
#define _GUI_Element_H_

#include "GUI.h"

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
    RGB background_colour;
    RGB trim_colour;
    RGB active_background_colour;
    RGB active_trim_colour;
    RGB text_colour;
    RGB active_text_colour;
    uint8_t text_size;
    bool hidden;
    bool selected;
    bool width_auto_size;
    bool height_auto_size;

protected:
    bool refresh;

public:
    GUI_Element(int16_t _x, int16_t _y, uint16_t _h, uint16_t _w);
    GUI_Element(int16_t _x, int16_t _y);
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
    };

    virtual ~GUI_Element() = default;

    virtual void draw(display_driver *display) = 0;
    virtual void navigate(int16_t x_pos, int16_t y_pos) = 0;
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
    RGB get_background_colour();
    RGB get_trim_colour();
    RGB get_active_background_colour();
    RGB get_active_trim_colour();
    RGB get_text_colour();
    RGB get_active_text_colour();
    uint8_t get_text_size();
    void set_x(int16_t _x);
    void set_y(int16_t _y);
    void set_x_offset(uint16_t offset);
    void set_y_offset(uint16_t offset);
    void set_width(uint16_t _width);
    void set_height(uint16_t _height);
    void set_max_width_px(uint16_t max_width);
    void set_max_height_px(uint16_t max_height);
    void set_dimensions(int16_t _x, int16_t _y, uint16_t _w, uint16_t _h);
    void set_width_auto_sizeable(bool auto_sizeable);
    void set_height_auto_sizeable(bool auto_sizeable);
    void set_background_colour(RGB _background_colour);
    void set_trim_colour(RGB _trim_colour);
    void set_active_background_colour(RGB _background_colour);
    void set_active_trim_colour(RGB _trim_colour);
    void set_base_colours(RGB _background_colour, RGB _trim_colour);
    void set_active_colours(RGB _active_background_colour, RGB _active_trim_colour);
    void set_colours(RGB _background_colour, RGB _active_background_colour, RGB _trim_colour, RGB _active_trim_colour);
    void set_text_colour(RGB _text_colour);
    void set_active_text_colour(RGB _active_text_colour);
    void set_text_colours(RGB _text_colour, RGB _active_text_colour);
    void set_text_size(uint8_t _text_size);
    void select();
    void deselect();
    void hide();
    void show();
    bool is_selected();
    bool is_hidden();
    bool within_bounds(int16_t x_pos, int16_t y_pos);
};

#endif /* _GUI_Element_H_ */
