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
    INPUT_NONE,
    INPUT_UP,
    INPUT_DOWN,
    INPUT_LEFT,
    INPUT_RIGHT,
    INPUT_ENTER,
    INPUT_KEYBOARD,
} INPUT_TYPE;

typedef enum
{
    KEYBOARD_NONE,
    KEYBOARD_A,
    KEYBOARD_B,
    KEYBOARD_C,
    KEYBOARD_D,
    KEYBOARD_E,
    KEYBOARD_F,
    KEYBOARD_G,
    KEYBOARD_H,
    KEYBOARD_I,
    KEYBOARD_J,
    KEYBOARD_K,
    KEYBOARD_L,
    KEYBOARD_M,
    KEYBOARD_N,
    KEYBOARD_O,
    KEYBOARD_P,
    KEYBOARD_Q,
    KEYBOARD_R,
    KEYBOARD_S,
    KEYBOARD_T,
    KEYBOARD_U,
    KEYBOARD_V,
    KEYBOARD_W,
    KEYBOARD_X,
    KEYBOARD_Y,
    KEYBOARD_Z,
    KEYBOARD_0,
    KEYBOARD_1,
    KEYBOARD_2,
    KEYBOARD_3,
    KEYBOARD_4,
    KEYBOARD_5,
    KEYBOARD_6,
    KEYBOARD_7,
    KEYBOARD_8,
    KEYBOARD_9,
    KEYBOARD_ESC,
} KEYBOARD_KEY;

inline char keyboard_to_char(KEYBOARD_KEY key)
{
    switch (key)
    {
    case KEYBOARD_A:
        return 'a';
    case KEYBOARD_B:
        return 'b';
    case KEYBOARD_C:
        return 'c';
    case KEYBOARD_D:
        return 'd';
    case KEYBOARD_E:
        return 'e';
    case KEYBOARD_F:
        return 'f';
    case KEYBOARD_G:
        return 'g';
    case KEYBOARD_H:
        return 'h';
    case KEYBOARD_I:
        return 'i';
    case KEYBOARD_J:
        return 'j';
    case KEYBOARD_K:
        return 'k';
    case KEYBOARD_L:
        return 'l';
    case KEYBOARD_M:
        return 'm';
    case KEYBOARD_N:
        return 'n';
    case KEYBOARD_O:
        return 'o';
    case KEYBOARD_P:
        return 'p';
    case KEYBOARD_Q:
        return 'q';
    case KEYBOARD_R:
        return 'r';
    case KEYBOARD_S:
        return 's';
    case KEYBOARD_T:
        return 't';
    case KEYBOARD_U:
        return 'u';
    case KEYBOARD_V:
        return 'v';
    case KEYBOARD_W:
        return 'w';
    case KEYBOARD_X:
        return 'x';
    case KEYBOARD_Y:
        return 'y';
    case KEYBOARD_Z:
        return 'z';
    case KEYBOARD_0:
        return '0';
    case KEYBOARD_1:
        return '1';
    case KEYBOARD_2:
        return '2';
    case KEYBOARD_3:
        return '3';
    case KEYBOARD_4:
        return '4';
    case KEYBOARD_5:
        return '5';
    case KEYBOARD_6:
        return '6';
    case KEYBOARD_7:
        return '7';
    case KEYBOARD_8:
        return '8';
    case KEYBOARD_9:
        return '9';
    default:
        return '-';
    }
}

typedef enum
{
    ALIGN_CENTER,
    ALIGN_LEFT,
    ALIGN_RIGHT,
} TEXT_ALIGN;

typedef bool (*click_cb_fun)(void *user_data);
