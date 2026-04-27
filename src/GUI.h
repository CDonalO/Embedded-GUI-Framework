#ifndef _GUI_H_
#define _GUI_H_

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <vector>
#include <stack>

inline uint16_t RGB(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

static const uint16_t WHITE = RGB(255, 255, 255);

#include "GUI_Element.h"
#include "GUI_Menu.h"
#include "GUI_View.h"

#endif /* _GUI_H_ */