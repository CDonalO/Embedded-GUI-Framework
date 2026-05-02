#ifndef _display_driver_H_
#define _display_driver_H_

#include "GUI_Colours.h"

class display_driver
{
public:
    display_driver() {}
    virtual ~display_driver() {}

    virtual void get_text_bounds(const char *text, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *width, uint16_t *height) = 0;

    virtual int16_t get_display_width() = 0;
    virtual int16_t get_display_height() = 0;

    virtual uint16_t center_text_vertical(char *str, uint16_t container_h, uint16_t container_y) = 0;
    virtual uint16_t center_text_horizontal(char *str, uint16_t container_w, uint16_t container_x) = 0;

    virtual void set_text_size(uint8_t size) = 0;
    virtual void set_text_colour(RGB colour) = 0;

    virtual void draw_text(int16_t x, int16_t y, const char *text) = 0;
    virtual void draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, RGB colour) = 0;
    virtual void draw_filled_circle(int16_t x, int16_t y, int16_t r, RGB colour) = 0;
    virtual void draw_filled_round_rect(int16_t x, int16_t y, int16_t width, int16_t height, int16_t border_radius, RGB colour) = 0;
    virtual void draw_filled_rect(int16_t x, int16_t y, int16_t width, int16_t height, RGB colour) = 0;
    virtual void draw_filled_triangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, RGB colour) = 0;

    virtual void draw_bitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t width, int16_t height, RGB colour) = 0;
};

#endif /* _display_driver_H_ */