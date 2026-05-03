#include "GUI.h"

GUI_Button::GUI_Button(BUTTON_STYLE style, const char *button_str, click_cb_fun click_cb, void *user_data, TEXT_ALIGN align) : GUI_Element(), button_style(style), click_cb(click_cb), user_data(user_data), align_value(align)
{
    border_radius = 10;
    disabled = false;
    icon_bitmap = NULL;
    icon_width = 0;
    icon_height = 0;
    disabled_bg_colour = BLACK;
    disabled_trim_colour = BLACK;
    disabled_text_colour = WHITE;

    strncpy((char *)text, button_str, sizeof(text));
}

GUI_Button::~GUI_Button()
{
}

/**
 * @brief Draw button
 *
 * @param display Display to draw button on
 */
void GUI_Button::draw(display_driver *display)
{
    RGB bg_c = get_background_colour();
    RGB trim_c = get_trim_colour();
    RGB font_c = get_text_colour();
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

    if (is_disabled())
    {
        bg_c = disabled_bg_colour;
        trim_c = disabled_trim_colour;
        font_c = disabled_text_colour;
    }

    switch (button_style)
    {
    case BUTTON_ROUND_STYLE:
    case BUTTON_ROUND_STYLE_UP_ARROW:
    case BUTTON_ROUND_STYLE_DOWN_ARROW:
    case BUTTON_ROUND_STYLE_LEFT_ARROW:
    case BUTTON_ROUND_STYLE_RIGHT_ARROW:
        display->draw_filled_round_rect(get_x(), get_y(), get_width(), get_height(), border_radius, trim_c);
        display->draw_filled_round_rect(get_x() + 1, get_y() + 1, get_width() - 2, get_height() - 2, border_radius, bg_c);

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

            display->draw_filled_triangle(arrow_x1, arrow_y1, arrow_x2, arrow_y2, arrow_x3, arrow_y3, font_c);
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

            display->draw_filled_triangle(arrow_x1, arrow_y1, arrow_x2, arrow_y2, arrow_x3, arrow_y3, font_c);
        }

        break;
    case BUTTON_SQUARE_STYLE:
    case BUTTON_ICON_STYLE:
        display->draw_filled_rect(get_x(), get_y(), get_width(), get_height(), trim_c);
        display->draw_filled_rect(get_x() + 1, get_y() + 1, get_width() - 2, get_height() - 2, bg_c);

        if (button_style == BUTTON_ICON_STYLE && icon_bitmap != NULL)
        {
            int bitmap_x = get_x() + (get_width() / 2) - icon_width / 2;
            int bitmap_y = get_y() + (get_height() / 2) - icon_height / 2;
            display->draw_bitmap(bitmap_x, bitmap_y, icon_bitmap, icon_width, icon_height, icon_bg_colour);
        }
        break;
    }

    display->set_text_size(get_text_size());

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

    display->set_text_colour(font_c);

    // TODO Make this better
    if (button_style != BUTTON_ROUND_STYLE_DOWN_ARROW && button_style != BUTTON_ROUND_STYLE_UP_ARROW && button_style != BUTTON_ICON_STYLE && button_style != BUTTON_ROUND_STYLE_LEFT_ARROW && button_style != BUTTON_ROUND_STYLE_RIGHT_ARROW)
    {
        display->draw_text(text_x, text_y, (char *)text);
    }

#ifdef VISUAL_ELEMENT_DEBUG
    display->draw_line(get_x(), get_y() + (get_height() / 2), get_x() + get_width(), get_y() + (get_height() / 2), RED);
    display->draw_line(get_x() + (get_width() / 2), get_y(), get_x() + (get_width() / 2), get_y() + get_height(), RED);
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

/**
 * @brief Set buttons refresh value
 *
 * @param r Value to decide if button should be redrawn
 * @param p Value to decide if need to update parents refresh
 */
void GUI_Button::set_refresh(bool r, bool p)
{
    refresh = r;

    if (p && parent != NULL)
    {
        parent->set_refresh(r, true);
    }
}

/**
 * @brief Set button style
 *
 * @param style Button style
 */
void GUI_Button::set_button_style(BUTTON_STYLE style)
{
    button_style = style;
}

/**
 * @brief Set button string
 *
 * @param button_str Button string
 */
void GUI_Button::set_button_str(const char *button_str)
{
    strncpy((char *)text, button_str, sizeof(text));
}

/**
 * @brief Set button icon bitmap
 *
 * @param bitmap Pointer to bitmap
 * @param width Width of bitmap
 * @param height Height of bitmap
 * @param icon_bg_colour Icon background colour
 */
void GUI_Button::set_icon_bitmap(uint8_t *bitmap, uint8_t width, uint8_t height, RGB icon_bg_colour)
{
    icon_bitmap = bitmap;
    icon_width = width;
    icon_height = height;
    this->icon_bg_colour = icon_bg_colour;
}

/**
 * @brief Set button click callback function
 *
 * @param click_cb Function called when button is pressed
 * @param user_data Data passed to the callback function
 */
void GUI_Button::set_click_user_cb(click_cb_fun click_cb, void *user_data)
{
    this->click_cb = click_cb;
    this->user_data = user_data;
}

/**
 * @brief Disable the button
 *
 * @param disable Set disabled state of button
 */
void GUI_Button::set_disabled(bool disable)
{
    disabled = disable;
}

/**
 * @brief Disable the button
 *
 * @return True if button is disabled otherwise false
 */
bool GUI_Button::is_disabled()
{
    return disabled;
}

/**
 * @brief Set the buttons colours when disabled
 *
 * @param disabled_bg_colour Background colour when disabled
 * @param disabled_trim_colour Trim colour when disabled
 * @param disabled_text_colour Text colour when disabled
 */
void GUI_Button::set_disabled_colours(RGB disabled_bg_colour, RGB disabled_trim_colour, RGB disabled_text_colour)
{
    this->disabled_bg_colour = disabled_bg_colour;
    this->disabled_trim_colour = disabled_trim_colour;
    this->disabled_text_colour = disabled_text_colour;
}

GUI_Toggle_Button::GUI_Toggle_Button(TOGGLE_BUTTON_STYLE style, const char *button_str, click_cb_fun click_cb, bool default_value, TEXT_ALIGN align) : GUI_Button(BUTTON_ROUND_STYLE, button_str, click_cb, NULL, align)
{
    button_style = style;
    value = default_value;
    toggled_colour = GREEN;
    non_toggled_colour = BLACK;
    toggle_element_colour = WHITE;
}

/**
 * @brief Draw toggle button
 *
 * @param display Display to draw toggle button on
 */
void GUI_Toggle_Button::draw(display_driver *display)
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

        display->draw_filled_round_rect(container_x, container_y, container_w, container_h, container_radius, value ? toggled_colour : non_toggled_colour);
        display->draw_filled_circle(circle_x, circle_y, circle_r / 2, toggle_element_colour);
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

/**
 * @brief Link elements to toggle button state change
 *
 * @param element Element to be altered upon button being toggled
 * @param linked_function Function to alter linked element
 */
void GUI_Toggle_Button::link_button_state(GUI_Element *element, linked_button_update_fun linked_function)
{
    if (element->get_type() == GUI_Element::Element_Type::VIEW || element->get_type() == GUI_Element::Element_Type::MENU)
    {
        return;
    }

    links.add_button_link(element, linked_function);
    linked_function(element, value);
    element->set_refresh(true, true);
}

/**
 * @brief Set toggle button style
 *
 * @param style Toggle button style
 */
void GUI_Toggle_Button::set_toggle_button_style(TOGGLE_BUTTON_STYLE style)
{
    button_style = style;
}

/**
 * @brief Toggle button
 */
void GUI_Toggle_Button::toggle()
{
    value = !value;
    links.trigger_links(value);
    refresh = true;
}

/**
 * @brief Get toggle button value
 *
 * @return True if toggled otherwise false
 */
bool GUI_Toggle_Button::get_toggled()
{
    return value;
}

/**
 * @brief Set the round buttons toggle slider colours
 *
 * @param toggled_colour Background colour of round slider when toggled
 * @param non_toggled_colour Background colour of round slider when not toggled
 * @param toggle_element_colour Toggle slider circle
 */
void GUI_Toggle_Button::set_toggled_colours(RGB toggled_colour, RGB non_toggled_colour, RGB toggle_element_colour)
{
    this->toggled_colour = toggled_colour;
    this->non_toggled_colour = non_toggled_colour;
    this->toggle_element_colour = toggle_element_colour;
}
