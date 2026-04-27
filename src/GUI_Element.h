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
    uint16_t background_colour;
    uint16_t trim_colour;
    uint16_t text_colour;
    uint8_t text_size;
    bool hidden;
    bool selected;

public:
    GUI_Element(int16_t _x, int16_t _y, uint16_t _h, uint16_t _w);
    GUI_Element(int16_t _x, int16_t _y);
    GUI_Element();

    virtual ~GUI_Element() = default;

    virtual void draw(Adafruit_GFX *display) = 0;
    virtual bool navigate(int16_t x_pos, int16_t y_pos) = 0;

    int16_t get_x();
    int16_t get_y();
    uint16_t get_width();
    uint16_t get_height();
    uint16_t get_background_colour();
    uint16_t get_trim_colour();
    uint16_t get_text_colour();
    uint8_t get_text_size();
    void set_x(int16_t _x);
    void set_y(int16_t _y);
    void set_width(uint16_t _width);
    void set_height(uint16_t _height);
    void set_dimensions(int16_t _x, int16_t _y, uint16_t _w, uint16_t _h);
    void set_background_colour(uint16_t _background_colour);
    void set_trim_colour(uint16_t _trim_colour);
    void set_text_colour(uint16_t _text_colour);
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
