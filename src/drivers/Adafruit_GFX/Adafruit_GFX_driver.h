#ifndef _Adafruit_GFX_driver_H_
#define _Adafruit_GFX_driver_H_

#include <Adafruit_GFX.h>

#include "../display_driver.h"

class Adafruit_GFX_driver : public display_driver
{
private:
    Adafruit_GFX *display;

public:
    Adafruit_GFX_driver(Adafruit_GFX *display);
    ~Adafruit_GFX_driver();

    void get_text_bounds(const char *text, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *width, uint16_t *height) override;

    int16_t get_display_width() override;
    int16_t get_display_height() override;

    uint16_t center_text_vertical(char *str, uint16_t container_h, uint16_t container_y) override;
    uint16_t center_text_horizontal(char *str, uint16_t container_w, uint16_t container_x) override;

    void set_text_size(uint8_t size) override;
    void set_text_colour(RGB colour) override;

    void draw_text(int16_t x, int16_t y, const char *text) override;
    void draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, RGB colour) override;
    void draw_filled_circle(int16_t x, int16_t y, int16_t r, RGB colour) override;
    void draw_filled_round_rect(int16_t x, int16_t y, int16_t width, int16_t height, int16_t border_radius, RGB colour) override;
    void draw_filled_rect(int16_t x, int16_t y, int16_t width, int16_t height, RGB colour) override;
    void draw_filled_triangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, RGB colour) override;

    void draw_bitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t width, int16_t height, RGB colour) override;
};

#endif /* _Adafruit_GFX_driver_H_ */