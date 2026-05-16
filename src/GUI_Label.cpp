#include "GUI_Label.h"

GUI_Label::GUI_Label(PLATFORM_STRING label) : GUI_Element()
{
    this->label = label;
}

GUI_Label::GUI_Label() : GUI_Label("")
{
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
    int16_t text_x = get_x();
    int16_t text_y = get_y();
    uint8_t text_align = get_element_alignment();

    if (!refresh)
        return;

    if (is_hidden())
        return;

    uint8_t t_size = get_font_size();
    RGB font_c = get_font_colour();
    if (parent)
    {
        if (!is_font_size_set())
        {
            t_size = parent->get_font_size();
        }
    }

    if (text_align & ALIGN_CENTER_HORIZONTAL)
    {
        text_x = display->center_text_horizontal(label, get_width(), get_x(), t_size);
    }
    else
    {
        if (text_align & ALIGN_LEFT)
        {
            text_x = get_x() + 5;
        }
        else if (text_align & ALIGN_RIGHT)
        {
            uint16_t w, h;
            display->get_text_bounds((char *)label.c_str(), &w, &h);
            text_x = get_x() + get_width() - w - 5;
        }
    }

    if (text_align & ALIGN_CENTER_VERTICAL)
    {
        text_y = display->center_text_vertical(label, get_height(), get_y(), t_size);
    }
    else
    {
        if (text_align & ALIGN_TOP)
        {
            text_y = get_y() + 5;
        }
        else if (text_align & ALIGN_BOTTOM)
        {
            uint16_t w, h;
            display->get_text_bounds((char *)label.c_str(), &w, &h);
            text_y = get_y() + get_height() - h - 5;
        }
    }

    display->draw_text(text_x, text_y, label, t_size, font_c);

#ifdef VISUAL_ELEMENT_DEBUG
    display->draw_line(get_x(), get_y() + (get_height() / 2), get_x() + get_width(), get_y() + (get_height() / 2), RED);
    display->draw_line(get_x() + (get_width() / 2), get_y(), get_x() + (get_width() / 2), get_y() + get_height(), RED);
#endif /* VISUAL_ELEMENT_DEBUG */
}

void GUI_Label::navigate(int16_t x_pos, int16_t y_pos) {}

void GUI_Label::navigate(INPUT_TYPE input, KEYBOARD_KEY key)
{
    if (input == INPUT_KEYBOARD)
    {
        if (key == KEYBOARD_BACKSPACE)
        {
            if (label.length() > 0)
            {
                PLATFORM_STRING_POP_BACK(label);
            }
        }
        else
        {
            char c = keyboard_to_char(key);
            PLATFORM_STRING_PUSH_BACK(label, c);
        }
    }
}

/**
 * @brief Get label value
 *
 * @return Label value
 */
PLATFORM_STRING GUI_Label::get_label()
{
    return label;
}

/**
 * @brief Set label value
 *
 * @param new_label New label value
 */
void GUI_Label::set_label(PLATFORM_STRING new_label)
{
    label = new_label;
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