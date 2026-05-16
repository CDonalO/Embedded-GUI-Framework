#include "GUI_Button.h"

GUI_Button::GUI_Button(BUTTON_STYLE style, PLATFORM_STRING button_str, BUTTON_ATTRIBUTE button_attribute, click_cb_fun click_cb, void *user_data, TEXT_ALIGN align) : GUI_Element(), button_style(style), click_cb(click_cb), user_data(user_data), align_value(align), button_attribute(button_attribute), text(button_str)
{
    border_radius = 10;
    disabled = false;
    disabled_bg_colour = BLACK;
    disabled_trim_colour = BLACK;
    disabled_font_colour = WHITE;
    set_interactable(true);
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
    RGB font_c = get_font_colour();
    uint16_t text_x, text_y;

    if (!refresh)
        return;

    if (is_hidden())
        return;

    if (is_selected())
    {
        bg_c = get_active_background_colour();
        trim_c = get_active_trim_colour();
        font_c = get_active_font_colour();
    }

    if (is_disabled())
    {
        bg_c = disabled_bg_colour;
        trim_c = disabled_trim_colour;
        font_c = disabled_font_colour;
    }

    if (button_attribute == BUTTON_ATTRIBUTE_ROUNDED)
    {
        display->draw_filled_round_rect(get_x(), get_y(), get_width(), get_height(), border_radius, trim_c);
        display->draw_filled_round_rect(get_x() + 1, get_y() + 1, get_width() - 2, get_height() - 2, border_radius, bg_c);
    }
    else if (button_attribute == BUTTON_ATTRIBUTE_SQUARED)
    {
        display->draw_filled_rect(get_x(), get_y(), get_width(), get_height(), trim_c);
        display->draw_filled_rect(get_x() + 1, get_y() + 1, get_width() - 2, get_height() - 2, bg_c);
    }

    switch (button_style)
    {
    case BUTTON_STYLE_UP_ARROW:
    case BUTTON_STYLE_DOWN_ARROW:
    case BUTTON_STYLE_LEFT_ARROW:
    case BUTTON_STYLE_RIGHT_ARROW:

        if (button_style == BUTTON_STYLE_UP_ARROW || button_style == BUTTON_STYLE_DOWN_ARROW)
        {
            // TODO make this dynamically sized
            bool arrow_up_dir = true;
            if (button_style == BUTTON_STYLE_DOWN_ARROW)
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
        else if (button_style == BUTTON_STYLE_LEFT_ARROW || button_style == BUTTON_STYLE_RIGHT_ARROW)
        {
            // TODO make this dynamically sized
            bool arrow_left_dir = true;
            if (button_style == BUTTON_STYLE_RIGHT_ARROW)
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
    case BUTTON_STYLE_PLUS:
    case BUTTON_STYLE_MINUS:
        int bar_width = get_height() / 4;

        if (get_height() > get_width())
        {
            bar_width = get_width() / 4;
        }

        int bar_height = bar_width / 6;

        int bar_x = get_x() + (get_width() / 2) - (bar_width / 2);
        int bar_y = get_y() + (get_height() / 2) - (bar_height / 2);

        display->draw_filled_rect(bar_x, bar_y, bar_width, bar_height, font_c);

        if (button_style == BUTTON_STYLE_PLUS)
        {
            bar_x = get_x() + (get_width() / 2) - (bar_height / 2);
            bar_y = get_y() + (get_height() / 2) - (bar_width / 2);

            display->draw_filled_rect(bar_x, bar_y, bar_height, bar_width, font_c);
        }
        break;
    }

    if (align_value == ALIGN_CENTER)
    {
        text_x = display->center_text_horizontal(text, get_width(), get_x());
    }
    else if (align_value == ALIGN_LEFT)
    {
        text_x = get_x() + 5;
    }
    else if (align_value == ALIGN_RIGHT)
    {
        uint16_t w, h;
        display->get_text_bounds((char *)text.c_str(), &w, &h);
        text_x = get_x() + get_width() - w - 5;
    }

    text_y = display->center_text_vertical(text, get_height(), get_y());

    if (button_style == BUTTON_NO_STYLE)
    {
        uint8_t t_size = get_font_size();
        if (parent)
        {
            if (!is_font_size_set())
            {
                t_size = parent->get_font_size();
            }
        }
        display->draw_text(text_x, text_y, text, t_size, font_c);
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

void GUI_Button::navigate(INPUT_TYPE input, KEYBOARD_KEY key)
{
    if (input != INPUT_ENTER)
        return;

    navigate(0, 0);
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
void GUI_Button::set_button_str(PLATFORM_STRING button_str)
{
    text = button_str;
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
 * @param disabled_font_colour Font colour when disabled
 */
void GUI_Button::set_disabled_colours(RGB disabled_bg_colour, RGB disabled_trim_colour, RGB disabled_font_colour)
{
    this->disabled_bg_colour = disabled_bg_colour;
    this->disabled_trim_colour = disabled_trim_colour;
    this->disabled_font_colour = disabled_font_colour;
}

/**
 * @brief Set the buttons attribute
 *
 * @param attribute Button attribute
 */
void GUI_Button::set_button_attributes(BUTTON_ATTRIBUTE attribute)
{
    button_attribute = attribute;
}

GUI_Toggle_Button::GUI_Toggle_Button(TOGGLE_BUTTON_STYLE style, PLATFORM_STRING button_str, click_cb_fun click_cb, bool default_value, TEXT_ALIGN align) : GUI_Button(BUTTON_NO_STYLE, button_str, BUTTON_ATTRIBUTE_ROUNDED, click_cb, NULL, align)
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
        RGB container_colour = toggled_colour;
        int container_padding = 2;
        int container_h = get_height() - (container_padding * 2);

        if (container_h > 35)
        {
            container_h = 35;
        }

        int container_w = get_width() / 12;

        if (container_w > 55)
        {
            container_w = 55;
        }
        else if (container_w < 50)
        {
            container_w = 50;
        }

        int circle_r = (container_h / 2) - (container_padding * 2);
        int circle_y = get_y() + get_height() / 2;
        int circle_x = get_x() + get_width() - container_w - container_padding;

        int container_r = circle_r + (container_padding * 2);
        int container_y = circle_y;
        int container1_x = circle_x;
        int container2_x = container1_x + container_w - container_r - container_padding;

        if (value)
        {
            circle_x = container2_x;
        }
        else
        {
            container_colour = non_toggled_colour;
        }

        display->draw_filled_circle(container1_x, container_y, container_r, container_colour);
        display->draw_filled_circle(container2_x, container_y, container_r, container_colour);
        display->draw_filled_rect(container1_x, container_y - container_r, container_w - (container_r), container_r * 2, container_colour);
        display->draw_filled_circle(circle_x, circle_y, circle_r, toggle_element_colour);
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

void GUI_Toggle_Button::navigate(INPUT_TYPE input, KEYBOARD_KEY key)
{
    if (input != INPUT_ENTER)
        return;

    navigate(0, 0);
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
