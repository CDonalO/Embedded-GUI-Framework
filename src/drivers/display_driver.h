#pragma once

#include "../GUI_Definitions.h"

typedef enum
{
    BITMAP_ALPHA_MAP,
    BITMAP_RGB565,
} BITMAP_TYPE;

class GUI_View;
class display_driver
{
protected:
    bool optimize_rendering = true;

public:
    GUI_View *view;
    uint16_t menu_bar_size;

    display_driver(uint16_t menu_bar_size) : menu_bar_size(menu_bar_size) {}
    virtual ~display_driver() {}

    bool get_optimize_rendering() { return optimize_rendering; }

    virtual void get_text_bounds(const char *text, uint16_t *width, uint16_t *height) = 0;

    virtual int16_t get_display_width() = 0;
    virtual int16_t get_display_height() = 0;

    virtual uint16_t center_text_vertical(char *str, uint16_t container_h, uint16_t container_y) = 0;
    virtual uint16_t center_text_horizontal(char *str, uint16_t container_w, uint16_t container_x) = 0;

    virtual void draw_text(int16_t x, int16_t y, const char *text, uint8_t size, RGB colour) = 0;
    virtual void draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, RGB colour) = 0;
    virtual void draw_filled_circle(int16_t x, int16_t y, int16_t r, RGB colour) = 0;
    virtual void draw_filled_round_rect(int16_t x, int16_t y, int16_t width, int16_t height, int16_t border_radius, RGB colour) = 0;
    virtual void draw_filled_rect(int16_t x, int16_t y, int16_t width, int16_t height, RGB colour) = 0;
    virtual void draw_filled_triangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, RGB colour) = 0;

    virtual void draw_bitmap(int16_t x, int16_t y, int16_t width, int16_t height, void *bitmap, BITMAP_TYPE bitmap_type, RGB colour) = 0;
    virtual void draw_image(int16_t x, int16_t y, int16_t width, int16_t height, PLATFORM_STRING file_path) = 0;
};
