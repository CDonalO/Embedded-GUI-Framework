#include "GUI.h"

GUI_Button::GUI_Button(BUTTON_STYLE style, const char *button_str) : GUI_Element()
{
    button_style = style;
    border_radius = 10;

    strncpy((char *)text, button_str, sizeof(text));
}

GUI_Button::~GUI_Button()
{
}

void GUI_Button::draw(Adafruit_GFX *display)
{
    uint16_t bg_c = get_background_colour();
    uint16_t font_c = get_text_colour();
    uint16_t text_x, text_y;

    if (is_hidden())
        return;

    switch (button_style)
    {
    case BUTTON_ROUND_STYLE:
        display->fillRoundRect(get_x(), get_y(), get_width(), get_height(), border_radius, bg_c);
        break;
    case BUTTON_SQUARE_STYLE:
        display->fillRect(get_x(), get_y(), get_width(), get_height(), bg_c);
        break;
    }

    display->setTextSize(get_text_size());

    text_x = center_text_horizontal((char *)text, get_width(), get_x(), display);
    text_y = center_text_vertical((char *)text, get_height(), get_y(), display);

    display->setCursor(text_x, text_y);
    display->setTextColor(font_c);
    display->println((char *)text);
}
