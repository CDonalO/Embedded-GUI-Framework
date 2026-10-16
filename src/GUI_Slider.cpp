#include "GUI_Slider.h"

#include <cmath>
#ifndef ARDUINO
#include <format>
#endif

GUI_Slider::GUI_Slider(int16_t min_val, int16_t max_val, int16_t default_val) : GUI_Element(), min_val(min_val), max_val(max_val), default_val(default_val), Form_Data_Number()
{
    if (default_val < min_val || default_val > max_val)
    {
        val = min_val;
    }
    else
    {
        val = default_val;
    }

    normalize_value();

    range = max_val - min_val;

    bar_h = 2;
    bar_padding = 20;
    slider_h = bar_h * 4;

#ifdef ARDUINO
    String value_string = String(min_val);
    min_value_label.set_label(value_string);
    value_string = String(max_val);
    max_value_label.set_label(value_string);
#else
    string value_string = format("{}", min_val);
    min_value_label.set_label(value_string);
    value_string = format("{}", max_val);
    max_value_label.set_label(value_string);
#endif

    set_interactable(true);
}

GUI_Slider::~GUI_Slider()
{
}

void GUI_Slider::normalize_value()
{
#ifdef ARDUINO
    String value_string = String(val);
#else
    string value_string = format("{}", val);
#endif

    norm_val = val - min_val;
    Form_Data_Number::set_data(val);
    value_label.set_label(value_string);
}

void GUI_Slider::draw(display_driver *display)
{
    if (!refresh)
    {
        return;
    }

    RGB slider_edge_colour = get_background_colour();

    display->draw_filled_round_rect(min_bar_x, bar_y, bar_w, bar_h, 2, get_background_colour());

    uint16_t slider_x = min_bar_x + (x_per_val * norm_val);

    if (is_selected())
    {
        slider_edge_colour = get_active_background_colour();
    }

    display->draw_filled_circle(slider_x, bar_y + (bar_h / 2), slider_h, slider_edge_colour);
    display->draw_filled_circle(slider_x, bar_y + (bar_h / 2), slider_h - 3, get_background_colour());
    value_label.draw(display);
    min_value_label.draw(display);
    max_value_label.draw(display);
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

    if (p && parent != NULL)
    {
        parent->set_refresh(r, p);
    }
}

void GUI_Slider::calculate_sizing(display_driver *display)
{
    uint16_t min_width = 0;
    bar_y = get_center_y() - (bar_h / 2);
    min_bar_x = get_x() + bar_padding;
    max_bar_x = get_x() + get_width() - bar_padding;
    bar_w = max_bar_x - min_bar_x;
    x_per_val = bar_w;
    x_per_val /= range;
    value_label.set_y(bar_y + (bar_h * 15));
    value_label.set_font_size(parent->get_font_size());
    value_label.set_font_colour(parent->get_font_colour());
    value_label.calculate_sizing(display);
    value_label.set_x(min_bar_x + (bar_w / 2));

    min_value_label.set_font_colour(parent->get_font_colour());
    min_value_label.set_font_size(parent->get_font_size());
    min_value_label.set_y(bar_y + (bar_h * 15));
    min_value_label.calculate_sizing(display);
    min_value_label.set_x(min_bar_x + (min_value_label.get_min_width_px() / 2));

    max_value_label.set_font_colour(parent->get_font_colour());
    max_value_label.set_font_size(parent->get_font_size());
    max_value_label.set_y(bar_y + (bar_h * 15));
    max_value_label.calculate_sizing(display);
    max_value_label.set_x(min_bar_x + bar_w - (max_value_label.get_min_width_px() / 2));

    min_width = value_label.get_min_width_px() + min_value_label.get_min_width_px() + max_value_label.get_min_width_px() + 15;

    min_width = max(min_width, (uint16_t)(bar_padding * 2 + 8));

    set_min_height_px(slider_h + 8 + value_label.get_min_height_px() + (bar_h * 15));
    set_min_width_px(min_width);
}
