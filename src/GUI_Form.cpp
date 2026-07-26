#include "GUI_Form.h"

GUI_Form::GUI_Form(PLATFORM_STRING label, form_value_update_fun value_cb) : GUI_Element(), label(label), value_update_cb(value_cb) {}

GUI_Form::~GUI_Form() {}

/**
 * @brief Draw form
 *
 * @param display Display to draw form on
 */
void GUI_Form::draw(display_driver *display)
{
    uint8_t t_size = get_font_size();
    RGB font_c = get_font_colour();
    if (parent)
    {
        if (!is_font_size_set())
        {
            t_size = parent->get_font_size();
        }
    }

    uint16_t text_y = display->center_text_vertical(label, get_height(), get_y(), t_size);
    RGB trim_color = get_trim_colour();
    RGB bg_color = get_background_colour();
    bool update_value = false;

    if (refresh)
    {
        update_value = true;
    }

    if (value_update_cb != NULL)
    {
        char *old_value[32];
        strncpy((char *)old_value, (char *)form_value, sizeof(form_value));
        value_update_cb((char *)form_value);

        if (strcmp((char *)old_value, (char *)form_value))
        {
            update_value = true;
        }
    }

    if (!is_hidden() && refresh)
    {
        display->draw_filled_round_rect(get_x(), get_y(), get_width(), get_height(), 10, trim_color);
        display->draw_filled_round_rect(get_x() + 1, get_y() + 1, get_width() - 2, get_height() - 2, 10, bg_color);
        display->draw_text(get_x() + 10, text_y, label, t_size, font_c);
    }

    if (!is_hidden())
    {
        if (update_value)
        {
            uint16_t text_width, text_height;
            display->get_text_bounds((char *)form_value, &text_width, &text_height);
            text_y = display->center_text_vertical((char *)form_value, get_height(), get_y(), t_size);
            uint16_t text_x = get_x() + get_width() - text_width - 10;
            // Draw a box over the old text to prevent needing to redraw the whole element.
            display->draw_filled_round_rect(text_x - 4, get_y() + 2, (get_x() + get_width()) - text_x, get_height() - 4, 10, bg_color);
            display->draw_text(text_x, text_y, (char *)form_value, t_size, font_c);
        }
    }

    refresh = false;
}

void GUI_Form::navigate(int16_t x_pos, int16_t y_pos) {}

void GUI_Form::navigate(INPUT_TYPE input, KEYBOARD_KEY key) {}

/**
 * @brief Set form refresh value
 *
 * @param r Value to decide if form should be redrawn
 * @param p Value to decide if need to update parents refresh
 */
void GUI_Form::set_refresh(bool r, bool p)
{
    refresh = r;

    if (p && parent != NULL)
    {
        parent->set_refresh(r, p);
    }
}

void GUI_Form::calculate_sizing(display_driver *display)
{
    // TODO
}
