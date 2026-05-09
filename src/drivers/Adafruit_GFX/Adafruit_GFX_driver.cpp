#include "Adafruit_GFX_driver.h"

static uint16_t get_rgb_colour(RGB c)
{
    uint8_t r = c.get_red();
    uint8_t g = c.get_green();
    uint8_t b = c.get_blue();
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

Adafruit_GFX_driver::Adafruit_GFX_driver(Adafruit_GFX *_display)
{
    display = _display;
}

Adafruit_GFX_driver::~Adafruit_GFX_driver()
{
}

void Adafruit_GFX_driver::get_text_bounds(const char *text, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *width, uint16_t *height)
{
    display->getTextBounds(text, x, y, x1, y1, width, height);
}

uint16_t Adafruit_GFX_driver::center_text_vertical(char *str, uint16_t container_h, uint16_t container_y)
{
    int16_t x_bound, y_bound;
    uint16_t text_w, text_h;

    if (str == NULL)
    {
        return 0;
    }

    display->getTextBounds(str, 0, container_y, &x_bound, &y_bound, &text_w, &text_h);

    return container_y + (container_h / 2) + (text_h / 2);
}

uint16_t Adafruit_GFX_driver::center_text_horizontal(char *str, uint16_t container_w, uint16_t container_x)
{
    int16_t x_bound, y_bound;
    uint16_t text_w, text_h;

    if (str == NULL)
    {
        return 0;
    }

    display->getTextBounds(str, container_x, 0, &x_bound, &y_bound, &text_w, &text_h);

    return container_x + (container_w / 2) - (text_w / 2);
}

int16_t Adafruit_GFX_driver::get_display_width()
{
    return display->width();
}

int16_t Adafruit_GFX_driver::get_display_height()
{
    return display->height();
}

void Adafruit_GFX_driver::set_text_size(uint8_t size)
{
    display->setTextSize(size);
}

void Adafruit_GFX_driver::set_text_colour(RGB colour)
{
    uint16_t c = get_rgb_colour(colour);
    display->setTextColor(c);
}

void Adafruit_GFX_driver::draw_text(int16_t x, int16_t y, const char *text)
{
    display->setCursor(x, y);
    display->println(text);
}

void Adafruit_GFX_driver::draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, RGB colour)
{
    uint16_t c = get_rgb_colour(colour);
    display->drawLine(x1, y1, x2, y2, c);
}

void Adafruit_GFX_driver::draw_filled_circle(int16_t x, int16_t y, int16_t r, RGB colour)
{
    uint16_t c = get_rgb_colour(colour);
    display->fillCircle(x, y, r, c);
}

void Adafruit_GFX_driver::draw_filled_round_rect(int16_t x, int16_t y, int16_t width, int16_t height, int16_t border_radius, RGB colour)
{
    uint16_t c = get_rgb_colour(colour);
    display->fillRoundRect(x, y, width, height, border_radius, c);
}

void Adafruit_GFX_driver::draw_filled_rect(int16_t x, int16_t y, int16_t width, int16_t height, RGB colour)
{
    uint16_t c = get_rgb_colour(colour);
    display->fillRect(x, y, width, height, c);
}

void Adafruit_GFX_driver::draw_filled_triangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, RGB colour)
{
    uint16_t c = get_rgb_colour(colour);
    display->fillTriangle(x1, y1, x2, y2, x3, y3, c);
}

void Adafruit_GFX_driver::draw_bitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t width, int16_t height, RGB colour)
{
    uint16_t c = get_rgb_colour(colour);
    display->drawBitmap(x, y, bitmap, width, height, c);
}