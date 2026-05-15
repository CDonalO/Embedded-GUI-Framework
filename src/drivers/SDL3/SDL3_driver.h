#pragma once

#include "../display_driver.h"

#ifdef SDL3_DRIVER

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

class SDL3_driver : public display_driver
{
private:
    uint16_t width;
    uint16_t height;
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    bool setup_error;

public:
    SDL3_driver(uint16_t window_width, uint16_t window_height, uint16_t menu_bar_size, PLATFORM_STRING font_path);
    ~SDL3_driver();

    void get_text_bounds(PLATFORM_STRING text, uint16_t *width, uint16_t *height) override;

    int16_t get_display_width() override;
    int16_t get_display_height() override;

    uint16_t center_text_vertical(PLATFORM_STRING str, uint16_t container_h, uint16_t container_y) override;
    uint16_t center_text_horizontal(PLATFORM_STRING str, uint16_t container_w, uint16_t container_x) override;

    void draw_text(int16_t x, int16_t y, PLATFORM_STRING text, uint8_t size, RGB colour) override;
    void draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, RGB colour) override;
    void draw_filled_circle(int16_t x, int16_t y, int16_t r, RGB colour) override;
    void draw_filled_round_rect(int16_t x, int16_t y, int16_t width, int16_t height, int16_t border_radius, RGB colour) override;
    void draw_filled_rect(int16_t x, int16_t y, int16_t width, int16_t height, RGB colour) override;
    void draw_filled_triangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, RGB colour) override;

    void draw_bitmap(int16_t x, int16_t y, int16_t width, int16_t height, void *bitmap, BITMAP_TYPE bitmap_type, RGB colour) override;
    void draw_image(int16_t x, int16_t y, int16_t width, int16_t height, PLATFORM_STRING file_path) override;
};

#endif /* SDL3_DRIVER */