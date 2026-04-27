#ifndef _GUI_H_
#define _GUI_H_

#include <Arduino.h>
#include <Adafruit_GFX.h>

inline uint16_t RGB(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

#include "GUI_Element.h"

#endif /* _GUI_H_ */