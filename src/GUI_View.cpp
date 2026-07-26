#include "GUI_View.h"

GUI_View::GUI_View(uint16_t menu_bar_size) : GUI_Element()
{
    this->menu_bar_size = menu_bar_size;
    update_sizing = true;
}

GUI_View::GUI_View(uint16_t menu_bar_size, uint16_t view_width, uint16_t view_height) : GUI_View(menu_bar_size)
{
    set_width(view_width);
    set_height(view_height);
}

GUI_View::GUI_View() : GUI_View(0) {}

GUI_View::~GUI_View()
{
    for (GUI_Menu *m : menu_objects)
    {
        delete m;
    }

    menu_objects.clear();
}

/**
 * @brief Main entry to draw everything added to view/menus
 *
 * @param display Display to draw button on
 */
void GUI_View::draw(display_driver *display)
{
    uint16_t text_y, text_x;

    calculate_sizing(display);

    ignore_refresh = !display->get_optimize_rendering();

    if (ignore_refresh)
    {
        set_refresh(true, false);
        refresh = true;
    }

    if (refresh)
    {
        display->draw_filled_rect(0, 0, get_width(), menu_bar_size, get_trim_colour());
        display->draw_filled_rect(0, 0, get_width(), menu_bar_size - 1, get_background_colour());
    }

    if (menu_stack.size() > 0)
    {
        menu_stack.top()->draw(display);

        if (refresh)
        {
            PLATFORM_STRING menu_name = menu_stack.top()->get_menu_name();

            uint8_t t_size = get_font_size();
            RGB font_c = get_font_colour();

            text_x = display->center_text_horizontal(menu_name, get_width(), 0, t_size);
            text_y = display->center_text_vertical(menu_name, menu_bar_size, 0, t_size);

            display->draw_text(text_x, text_y, menu_name, t_size, font_c);

            if (menu_stack.size() > 1)
            {
                // TODO Make this dynamically sized
                int arrow_x1 = 24;
                int arrow_y1 = 6;
                int arrow_height = menu_bar_size / 2;
                int arrow_width = 8;
                display->draw_filled_round_rect(8, 2, menu_bar_size - 4, 22, 5, back_button_bg_colour);
                set_min_width_px(max((uint16_t)22, get_min_width_px()));
                display->draw_filled_triangle(arrow_x1, arrow_y1, arrow_x1 - arrow_width, arrow_y1 + (arrow_height / 2), arrow_x1, arrow_y1 + arrow_height, back_button_arrow_colour);
                display->draw_filled_triangle(arrow_x1, arrow_y1 + 3, arrow_x1 - arrow_width + 3, arrow_y1 + (arrow_height / 2), arrow_x1, arrow_y1 + arrow_height - 3, back_button_bg_colour);
            }
            refresh = false;
        }
    }
}

void GUI_View::navigate(int16_t x_pos, int16_t y_pos)
{
    if (menu_stack.size() > 1 && y_pos >= 0 && y_pos <= menu_bar_size && x_pos >= 0 && x_pos <= get_width() / 2)
    {
        // TODO Make this dynamically sized
        reverse_menus();
        return;
    }

    menu_stack.top()->navigate(x_pos, y_pos);
}

void GUI_View::navigate(INPUT_TYPE input, KEYBOARD_KEY key)
{
    if (menu_stack.size() > 1 && key == KEYBOARD_ESC)
    {
        reverse_menus();
        return;
    }

    menu_stack.top()->navigate(input, key);
}

/**
 * @brief Set view refresh value
 *
 * @param r Value to decide if view should be redrawn
 * @param p Unused
 */
void GUI_View::set_refresh(bool r, bool p)
{
    refresh = r;

    if (ignore_refresh && !menu_stack.empty() && !p)
    {
        menu_stack.top()->set_refresh(true, false);
    }
}

void GUI_View::calculate_sizing(display_driver *display)
{
    if (menu_stack.size() > 0)
    {
        if (menu_stack.top()->get_width() != get_width())
        {
            update_sizing = true;
        }

        if (menu_stack.top()->get_height() != (get_height() - menu_bar_size))
        {
            update_sizing = true;
        }

        if (refresh)
        {
            update_sizing = true;
        }
    }

    if (update_sizing)
    {
        set_refresh(true, false);
    }

    if (menu_stack.size() > 0)
    {
        GUI_Menu *m = NULL;
        std::stack<GUI_Menu *> temp_stack;

        while (!menu_stack.empty())
        {
            m = menu_stack.top();
            m->set_x_offset(get_x());
            m->set_y_offset(menu_bar_size);
            m->set_width(get_width());
            m->set_height(get_height() - menu_bar_size);
            m->calculate_sizing(display);
            temp_stack.push(m);
            menu_stack.pop();
        }

        while (!temp_stack.empty())
        {
            m = temp_stack.top();
            menu_stack.push(m);
            temp_stack.pop();
        }

        m = menu_stack.top();
        uint16_t min_width = 0;
        uint16_t min_height = 0;

        min_width = m->get_min_width_px();
        if (get_max_width_px())
        {
            min_width = min(min_width, get_max_width_px());
        }

        min_height = menu_bar_size + m->get_min_height_px();
        if (get_max_height_px())
        {
            min_height = min(min_height, get_max_height_px());
        }

        set_min_width_px(min_width);
        set_min_height_px(min_height);
    }

    update_sizing = false;
}

/**
 * @brief Set view's menu
 *
 * @param menu Menu to be drawn
 */
void GUI_View::set_menu(GUI_Menu *menu)
{
    menu->set_x(0);
    menu->set_y(0);
    menu->set_width(get_width());
    menu->set_height(get_height() - menu_bar_size);
    menu->set_font_colour(get_font_colour());

    menu_objects.insert(menu);

    if (!menu->is_font_size_set() && is_font_size_set())
    {
        menu->set_font_size(get_font_size());
    }

    menu->parent = this;

    if (is_colour_scheme_set())
    {
        menu->set_colour_scheme(get_colour_scheme());
        menu->apply_colour_scheme();
    }

    if (menu_stack.size() > 0)
    {
        menu_stack.top()->set_refresh(true, false);
    }

    menu->set_refresh(true, false);
    menu->increase_ref();
    menu_stack.push(menu);

    refresh = true;
}

void GUI_View::set_global_colour_scheme(GUI_Colour_Scheme colour_scheme)
{
    set_colour_scheme(colour_scheme);

    if (menu_stack.size() > 0)
    {
        std::stack<GUI_Menu *> temp_stack;

        while (!menu_stack.empty())
        {
            GUI_Menu *m = menu_stack.top();
            menu_stack.pop();
            m->set_colour_scheme(colour_scheme);
            m->apply_colour_scheme();
            m->set_refresh(true, false);

            temp_stack.push(m);
        }

        while (!temp_stack.empty())
        {
            GUI_Menu *m = temp_stack.top();
            temp_stack.pop();

            menu_stack.push(m);
        }
    }
}

/**
 * @brief Returns to previous menu
 */
void GUI_View::reverse_menus(void)
{
    if (menu_stack.size() > 1)
    {
        menu_stack.top()->set_refresh(true, false);
        menu_stack.pop();
    }

    menu_stack.top()->set_refresh(true, false);
    refresh = true;
}

void GUI_View::set_menu_bar_colours(RGB return_bg_colour, RGB arrow_colour)
{
    back_button_bg_colour = return_bg_colour;
    back_button_arrow_colour = arrow_colour;
}