#pragma once

#include "platform.h"

#include "GUI_Colours.h"

static const RGB WHITE(255, 255, 255);
static const RGB BLACK(0, 0, 0);
static const RGB RED(255, 0, 0);
static const RGB GREEN(0, 255, 0);
static const RGB BLUE(0, 0, 255);
static const RGB NAVY_BLUE(31, 58, 90);
static const RGB LIGHT_BLUE(144, 194, 250);

typedef enum
{
    ALIGN_CENTER,
    ALIGN_LEFT,
    ALIGN_RIGHT,
} TEXT_ALIGN;

typedef bool (*click_cb_fun)(void *user_data);
