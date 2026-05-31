#include "GUI_Slider.h"

#include <cmath>

GUI_Slider::GUI_Slider(int16_t min_val, int16_t max_val, int16_t default_val) : GUI_Element(), min_val(min_val), max_val(max_val), default_val(default_val)
{
    if (default_val < min_val || default_val > max_val)
    {
        val = min_val;
    }
    else
    {
        val = default_val;
    }

    range = max_val - min_val;

    set_interactable(true);
}

GUI_Slider::~GUI_Slider()
{
}

void GUI_Slider::normalize_value()
{
    norm_val = val - min_val;
}

void GUI_Slider::draw(display_driver *display)
{
    RGB slider_edge_colour = get_background_colour();
    uint16_t bar_y = get_center_y() - (bar_h / 2);
    uint16_t slider_h = bar_h * 4;

    min_bar_x = get_x() + 20;
    max_bar_x = get_x() + get_width() - 20;
    bar_w = max_bar_x - min_bar_x;
    x_per_val = bar_w;

    display->draw_filled_round_rect(min_bar_x, bar_y + (bar_h / 2), bar_w, bar_h, 2, get_background_colour());

    x_per_val /= range;

    uint16_t slider_x = min_bar_x + (x_per_val * norm_val);

    if (is_selected())
    {
        slider_edge_colour = get_active_background_colour();
    }

    display->draw_filled_circle(slider_x, get_center_y(), slider_h, slider_edge_colour);
    display->draw_filled_circle(slider_x, get_center_y(), slider_h - 3, get_background_colour());
}

void GUI_Slider::navigate(int16_t x_pos, int16_t y_pos)
{
    if (x_pos < min_bar_x || x_pos > max_bar_x)
    {
        return;
    }

    for (uint32_t x = 0; x <= range; x++)
    {
        uint16_t slider_x = (x_per_val * x) + min_bar_x;

        if (x_pos >= slider_x - (x_per_val / 2) && x_pos <= slider_x + (x_per_val / 2))
        {
            val = min_val + x;
            set_refresh(true, true);
            normalize_value();
            break;
        }
    }
}

void GUI_Slider::navigate(INPUT_TYPE input, KEYBOARD_KEY key)
{
    if (input != INPUT_LEFT && input != INPUT_RIGHT)
    {
        return;
    }

    if (input == INPUT_LEFT)
    {
        if (val > min_val)
        {
            val -= 1;
            set_refresh(true, true);
        }
    }
    else if (input == INPUT_RIGHT)
    {
        if (val < max_val)
        {
            val += 1;
            set_refresh(true, true);
        }
    }

    normalize_value();
}

void GUI_Slider::set_refresh(bool r, bool p)
{
    refresh = r;
}
