#include "Adafruit_GFX_driver.h"
#include "../../GUI_View.h"

#ifdef ADAFRUIT_DRIVER
static uint16_t get_rgb_colour(RGB c)
{
    uint8_t r = c.get_red();
    uint8_t g = c.get_green();
    uint8_t b = c.get_blue();
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

Adafruit_GFX_driver::Adafruit_GFX_driver(Adafruit_GFX *_display, uint16_t menu_bar_size) : display_driver(menu_bar_size)
{
    display = _display;
    view = new GUI_View(menu_bar_size);
}

Adafruit_GFX_driver::~Adafruit_GFX_driver() {}
{
}

void Adafruit_GFX_driver::get_text_bounds(PLATFORM_STRING text, uint16_t *width, uint16_t *height)
{
    int16_t temp;

    if (text.length() == 0)
    {
        *width = 0;
        *height = 0;
        return;
    }

    display->getTextBounds(text.c_str(), 0, 0, &temp, &temp, width, height);
}

uint16_t Adafruit_GFX_driver::center_text_vertical(PLATFORM_STRING str, uint16_t container_h, uint16_t container_y)
{
    uint16_t text_w, text_h;

    if (str.length() == 0)
    {
        return 0;
    }

    get_text_bounds(str, &text_w, &text_h);

    return container_y + (container_h / 2) + (text_h / 2);
}

uint16_t Adafruit_GFX_driver::center_text_horizontal(PLATFORM_STRING str, uint16_t container_w, uint16_t container_x)
{
    uint16_t text_w, text_h;

    if (str.length() == 0)
    {
        return 0;
    }

    get_text_bounds(str, &text_w, &text_h);

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

void Adafruit_GFX_driver::draw_text(int16_t x, int16_t y, PLATFORM_STRING text, uint8_t size, RGB colour)
{
    if (text.length() == 0)
    {
        return;
    }

    uint16_t c = get_rgb_colour(colour);
    display->setTextColor(c);
    display->setTextSize(size);
    display->setCursor(x, y);
    display->println(text.c_str());
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

void Adafruit_GFX_driver::draw_bitmap(int16_t x, int16_t y, int16_t width, int16_t height, void *bitmap, BITMAP_TYPE bitmap_type, RGB colour)
{
    uint16_t c = get_rgb_colour(colour);

    if (bitmap_type == BITMAP_ALPHA_MAP)
    {
        uint8_t *data = (uint8_t *)bitmap;
        display->drawBitmap(x, y, data, width, height, c);
    }
}

void Adafruit_GFX_driver::draw_image(int16_t x, int16_t y, int16_t width, int16_t height, PLATFORM_STRING file_path)
{
}

#endif /* ADAFRUIT_DRIVER */
