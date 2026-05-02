#ifndef _GUI_H_
#define _GUI_H_

#include <Arduino.h>
#include <vector>
#include <stack>

typedef enum
{
    ALIGN_CENTER,
    ALIGN_LEFT,
    ALIGN_RIGHT,
} TEXT_ALIGN;

typedef bool (*click_cb_fun)(void *user_data);

#include "display_driver.h"
#if __has_include(<Adafruit_GFX.h>)
#include "drivers/Adafruit_GFX_driver.h"
#endif

static const RGB WHITE(255, 255, 255);
static const RGB BLACK(0, 0, 0);
static const RGB RED(255, 0, 0);
static const RGB GREEN(0, 255, 0);
static const RGB BLUE(0, 0, 255);
static const RGB NAVY_BLUE(31, 58, 90);
static const RGB LIGHT_BLUE(144, 194, 250);

#include "GUI_Element.h"
#include "GUI_Button.h"
#include "GUI_Menu.h"
#include "GUI_View.h"
#include "GUI_Grid.h"
#include "GUI_Label.h"
#include "GUI_Form.h"

#endif /* _GUI_H_ */