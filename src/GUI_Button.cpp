#include "GUI.h"

GUI_Button::GUI_Button(BUTTON_STYLE style, const char *button_str, click_cb_fun _click_cb, void *_user_data, TEXT_ALIGN _align) : GUI_Element()
{
    button_style = style;
    border_radius = 10;
    align_value = _align;
    user_data = _user_data;
    click_cb = _click_cb;
    disabled = false;
    icon_bitmap = NULL;
    icon_width = 0;
    icon_height = 0;

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

    if (!refresh)
        return;

    if (is_hidden())
        return;

    if (is_selected())
    {
        bg_c = get_active_background_colour();
        trim_c = get_active_trim_colour();
        font_c = get_active_text_colour();
    }

    switch (button_style)
    {
    case BUTTON_ROUND_STYLE:
    case BUTTON_ROUND_STYLE_UP_ARROW:
    case BUTTON_ROUND_STYLE_DOWN_ARROW:
    case BUTTON_ROUND_STYLE_LEFT_ARROW:
    case BUTTON_ROUND_STYLE_RIGHT_ARROW:
        display->fillRoundRect(get_x(), get_y(), get_width(), get_height(), border_radius, trim_c);
        display->fillRoundRect(get_x() + 1, get_y() + 1, get_width() - 2, get_height() - 2, border_radius, bg_c);

        if (button_style == BUTTON_ROUND_STYLE_UP_ARROW || button_style == BUTTON_ROUND_STYLE_DOWN_ARROW)
        {
            // TODO make this dynamically sized
            bool arrow_up_dir = true;
            if (button_style == BUTTON_ROUND_STYLE_DOWN_ARROW)
            {
                arrow_up_dir = false;
            }

            int arrow_width = 15;
            int arrow_height = 15;
            int arrow_x1 = get_x() + (get_width() / 2) - (arrow_width / 2);
            int arrow_y1 = get_y() + (get_height() / 2);

            if (arrow_up_dir)
            {
                arrow_y1 += (arrow_height / 2);
            }
            else
            {
                arrow_y1 -= (arrow_height / 2);
            }

            int arrow_x2 = arrow_x1 + (arrow_width / 2);
            int arrow_y2 = arrow_y1;

            if (arrow_up_dir)
            {
                arrow_y2 -= arrow_height;
            }
            else
            {
                arrow_y2 += arrow_height;
            }

            int arrow_x3 = arrow_x1 + arrow_width;
            int arrow_y3 = arrow_y1;

            display->fillTriangle(arrow_x1, arrow_y1, arrow_x2, arrow_y2, arrow_x3, arrow_y3, font_c);
        }
        else if (button_style == BUTTON_ROUND_STYLE_LEFT_ARROW || button_style == BUTTON_ROUND_STYLE_RIGHT_ARROW)
        {
            // TODO make this dynamically sized
            bool arrow_left_dir = true;
            if (button_style == BUTTON_ROUND_STYLE_RIGHT_ARROW)
            {
                arrow_left_dir = false;
            }

            int arrow_width = 15;
            int arrow_height = 15;

            int arrow_x1 = get_x() + (get_width() / 2);

            if (arrow_left_dir)
            {
                arrow_x1 += (arrow_width / 2);
            }
            else
            {
                arrow_x1 -= (arrow_width / 2);
            }

            int arrow_y1 = get_y() + (get_height() / 2) - (arrow_height / 2);
            int arrow_x2 = arrow_x1;

            if (arrow_left_dir)
            {
                arrow_x2 -= arrow_width;
            }
            else
            {
                arrow_x2 += arrow_width;
            }

            int arrow_y2 = arrow_y1 + (arrow_height / 2);
            int arrow_x3 = arrow_x1;
            int arrow_y3 = arrow_y1 + arrow_height;

            display->fillTriangle(arrow_x1, arrow_y1, arrow_x2, arrow_y2, arrow_x3, arrow_y3, font_c);
        }

        break;
    case BUTTON_SQUARE_STYLE:
    case BUTTON_ICON_STYLE:
        display->fillRect(get_x(), get_y(), get_width(), get_height(), trim_c);
        display->fillRect(get_x() + 1, get_y() + 1, get_width() - 2, get_height() - 2, bg_c);

        if (button_style == BUTTON_ICON_STYLE && icon_bitmap != NULL)
        {
            int bitmap_x = get_x() + (get_width() / 2) - icon_width / 2;
            int bitmap_y = get_y() + (get_height() / 2) - icon_height / 2;
            display->drawBitmap(bitmap_x, bitmap_y, icon_bitmap, icon_width, icon_height, icon_bg_colour);
        }
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

    // TODO Make this better
    if (button_style != BUTTON_ROUND_STYLE_DOWN_ARROW && button_style != BUTTON_ROUND_STYLE_UP_ARROW && button_style != BUTTON_ICON_STYLE && button_style != BUTTON_ROUND_STYLE_LEFT_ARROW && button_style != BUTTON_ROUND_STYLE_RIGHT_ARROW)
    {
        display->println((char *)text);
    }

#ifdef VISUAL_ELEMENT_DEBUG
    display->drawLine(get_x(), get_y() + (get_height() / 2), get_x() + get_width(), get_y() + (get_height() / 2), RED);
    display->drawLine(get_x() + (get_width() / 2), get_y(), get_x() + (get_width() / 2), get_y() + get_height(), RED);
#endif /* VISUAL_ELEMENT_DEBUG */
}

void GUI_Button::navigate(int16_t x_pos, int16_t y_pos)
{
    if (is_disabled())
        return;

    if (click_cb != NULL)
    {
        refresh = click_cb(user_data);
    }
}

void GUI_Button::set_refresh(bool r)
{
    refresh = r;
}

void GUI_Button::set_button_style(BUTTON_STYLE style)
{
    button_style = style;
}

void GUI_Button::set_button_str(const char *button_str)
{
    strncpy((char *)text, button_str, sizeof(text));
}

void GUI_Button::set_icon_bitmap(uint8_t *_bitmap, uint8_t _width, uint8_t _height, uint16_t _icon_bg_colour)
{
    icon_bitmap = _bitmap;
    icon_width = _width;
    icon_height = _height;
    icon_bg_colour = _icon_bg_colour;
}

void GUI_Button::set_click_user_cb(click_cb_fun _click_cb, void *_user_data)
{
    click_cb = _click_cb;
    user_data = _user_data;
}

void GUI_Button::set_disabled(bool disable)
{
    disabled = disable;
}

bool GUI_Button::is_disabled()
{
    return disabled;
}

GUI_Toggle_Button::GUI_Toggle_Button(TOGGLE_BUTTON_STYLE style, const char *button_str, click_cb_fun _click_cb, bool default_value, TEXT_ALIGN _align) : GUI_Button(BUTTON_ROUND_STYLE, button_str, _click_cb, NULL, _align)
{
    button_style = style;
    value = default_value;
    toggled_colour = GREEN;
    non_toggled_colour = BLACK;
    toggle_element_colour = WHITE;
}

void GUI_Toggle_Button::draw(Adafruit_GFX *display)
{
    if (!refresh)
        return;

    if (is_hidden())
        return;

    if (button_style == TOGGLE_BUTTON_NO_STYLE)
    {
        if (value)
        {
            GUI_Button::select();
        }
        else
        {
            GUI_Button::deselect();
        }
    }

    GUI_Button::draw(display);

    switch (button_style)
    {
    case TOGGLE_BUTTON_ROUND_STYLE:
    {
        // TODO Make this scale nicely, currently looks bad when button is tall
        int container_radius = 50;
        int container_w = 70;
        int container_h = get_height() - 12;
        int container_x = get_x() + get_width() - container_w - 6;
        int container_y = get_y() + 6;

        int circle_padding = 3;
        int circle_r = container_h - (circle_padding * 2);
        int circle_y = container_y + (circle_r / 2) + circle_padding;
        int circle_x = container_x;

        if (value)
        {
            circle_x += container_w - (circle_r / 2) - circle_padding;
        }
        else
        {
            circle_x += circle_padding + (circle_r / 2);
        }

        display->fillRoundRect(container_x, container_y, container_w, container_h, container_radius, value ? toggled_colour : non_toggled_colour);
        display->fillCircle(circle_x, circle_y, circle_r / 2, toggle_element_colour);
    }
    break;
    }
}

void GUI_Toggle_Button::navigate(int16_t x_pos, int16_t y_pos)
{
    if (is_disabled())
        return;

    toggle();

    if (click_cb != NULL)
    {
        if (user_data)
        {
            refresh = click_cb(user_data);
        }
        else
        {
            refresh = click_cb(&value);
        }
    }
}

void GUI_Toggle_Button::set_toggle_button_style(TOGGLE_BUTTON_STYLE style)
{
    button_style = style;
}

void GUI_Toggle_Button::toggle()
{
    value = !value;
    refresh = true;
}

bool GUI_Toggle_Button::get_toggled()
{
    return value;
}

void GUI_Toggle_Button::set_toggled_colours(uint16_t _toggled_colour, uint16_t _non_toggled_colour, uint16_t _toggle_element_colour)
{
    toggled_colour = _toggled_colour;
    non_toggled_colour = _non_toggled_colour;
    toggle_element_colour = _toggle_element_colour;
}
