#include "GUI.h"

GUI_Button::GUI_Button(BUTTON_STYLE style, const char *button_str, click_cb_fun _click_cb, void *_user_data, TEXT_ALIGN _align) : GUI_Element()
{
    button_style = style;
    border_radius = 10;
    align_value = _align;
    user_data = _user_data;
    click_cb = _click_cb;

    strncpy((char *)text, button_str, sizeof(text));
}

GUI_Button::~GUI_Button()
{
}

void GUI_Button::draw(Adafruit_GFX *display)
{
    uint16_t bg_c = get_background_colour();
    uint16_t trim_c = get_trim_colour();
    uint16_t font_c = get_text_colour();
    uint16_t text_x, text_y;

    if (is_hidden())
        return;

    switch (button_style)
    {
    case BUTTON_ROUND_STYLE:
        display->fillRoundRect(get_x(), get_y(), get_width(), get_height(), border_radius, trim_c);
        display->fillRoundRect(get_x() + 2, get_y() + 2, get_width() - 4, get_height() - 4, border_radius, bg_c);
        break;
    case BUTTON_SQUARE_STYLE:
        display->fillRect(get_x(), get_y(), get_width(), get_height(), trim_c);
        display->fillRect(get_x() + 4, get_y() + 4, get_width() - 8, get_height() - 8, bg_c);
        break;
    }

    display->setTextSize(get_text_size());

    if (align_value == ALIGN_CENTER)
    {
        text_x = center_text_horizontal((char *)text, get_width(), get_x(), display);
    }
    else if (align_value == ALIGN_LEFT)
    {
        text_x = get_x() + 5;
    }
    else if (align_value == ALIGN_RIGHT)
    {
        int16_t x1, y1;
        uint16_t w, h;
        display->getTextBounds((char *)text, 0, 0, &x1, &y1, &w, &h);
        text_x = get_x() + get_width() - w - 5;
    }

    text_y = center_text_vertical((char *)text, get_height(), get_y(), display);

    display->setCursor(text_x, text_y);
    display->setTextColor(font_c);
    display->println((char *)text);
}

bool GUI_Button::navigate(int16_t x_pos, int16_t y_pos)
{
    if (click_cb != NULL)
    {
        return click_cb(user_data);
    }

    return false;
}