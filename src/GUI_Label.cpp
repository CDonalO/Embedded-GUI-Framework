#include "GUI.h"

GUI_Label::GUI_Label(char *label, TEXT_ALIGN _align, uint8_t text_size, uint16_t text_colour) : GUI_Element()
{
    set_text_colour(text_colour);
    set_text_size(text_size);
    align_value = _align;
    strncpy((char *)text, label, sizeof(text));
}

GUI_Label::~GUI_Label()
{
    free(text);
}

void GUI_Label::draw(Adafruit_GFX *display)
{
    int text_x, text_y;

    if (!refresh)
        return;

    if (is_hidden())
        return;

    display->setTextSize(get_text_size());
    display->setTextColor(get_text_colour());

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
    display->println((char *)text);

#ifdef ELEMENT_DEBUG
    display->drawLine(get_x(), get_y() + (get_height() / 2), get_x() + get_width(), get_y() + (get_height() / 2), RED);
    display->drawLine(get_x() + (get_width() / 2), get_y(), get_x() + (get_width() / 2), get_y() + get_height(), RED);
#endif /* ELEMENT_DEBUG */
}

void GUI_Label::navigate(int16_t x_pos, int16_t y_pos)
{
}

void GUI_Label::set_refresh(bool r)
{
}