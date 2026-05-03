#include "GUI.h"

GUI_Label::GUI_Label(char *label, TEXT_ALIGN _align, uint8_t text_size, RGB text_colour) : GUI_Element()
{
    set_text_colour(text_colour);
    set_text_size(text_size);
    align_value = _align;
    strncpy((char *)text, label, sizeof(text));
}

GUI_Label::~GUI_Label()
{
}

/**
 * @brief Draw label
 *
 * @param display Display to draw label on
 */
void GUI_Label::draw(display_driver *display)
{
    int text_x, text_y;

    if (!refresh)
        return;

    if (is_hidden())
        return;

    display->set_text_size(get_text_size());
    display->set_text_colour(get_text_colour());

    if (align_value == ALIGN_CENTER)
    {
        text_x = display->center_text_horizontal((char *)text, get_width(), get_x());
    }
    else if (align_value == ALIGN_LEFT)
    {
        text_x = get_x() + 5;
    }
    else if (align_value == ALIGN_RIGHT)
    {
        int16_t x1, y1;
        uint16_t w, h;
        display->get_text_bounds((char *)text, 0, 0, &x1, &y1, &w, &h);
        text_x = get_x() + get_width() - w - 5;
    }

    text_y = display->center_text_vertical((char *)text, get_height(), get_y());

    display->draw_text(text_x, text_y, (char *)text);

#ifdef VISUAL_ELEMENT_DEBUG
    display->draw_line(get_x(), get_y() + (get_height() / 2), get_x() + get_width(), get_y() + (get_height() / 2), RED);
    display->draw_line(get_x() + (get_width() / 2), get_y(), get_x() + (get_width() / 2), get_y() + get_height(), RED);
#endif /* VISUAL_ELEMENT_DEBUG */
}

void GUI_Label::navigate(int16_t x_pos, int16_t y_pos)
{
}

/**
 * @brief Set label refresh value
 *
 * @param r Value to decide if label should be redrawn
 * @param p Value to decide if need to update parents refresh
 */
void GUI_Label::set_refresh(bool r, bool p)
{
    refresh = r;

    if (p && parent != NULL)
    {
        parent->set_refresh(r, p);
    }
}