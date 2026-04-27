#ifndef _GUI_H_
#define _GUI_H_

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <vector>
#include <stack>

typedef enum
{
    ALIGN_CENTER,
    ALIGN_LEFT,
    ALIGN_RIGHT,
} TEXT_ALIGN;

inline uint16_t center_text_vertical(char *str, uint16_t container_h, uint16_t container_y, Adafruit_GFX *display)
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

inline uint16_t center_text_horizontal(char *str, uint16_t container_w, uint16_t container_x, Adafruit_GFX *display)
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

inline uint16_t RGB(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

static const uint16_t WHITE = RGB(255, 255, 255);
static const uint16_t BLACK = RGB(0, 0, 0);
static const uint16_t RED = RGB(255, 0, 0);
static const uint16_t GREEN = RGB(0, 255, 0);
static const uint16_t BLUE = RGB(0, 0, 255);

#include "GUI_Element.h"
#include "GUI_Menu.h"
#include "GUI_View.h"
#include "GUI_Button.h"

#endif /* _GUI_H_ */