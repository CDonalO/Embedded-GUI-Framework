#include "GUI.h"

typedef struct menu_change_event
{
    GUI_View *v;
    GUI_Menu *m;
} _menu_change_event;

GUI_View::GUI_View(display_driver *display, uint16_t menu_bar_size) : GUI_Element()
{
    this->display = display;
    this->menu_bar_size = menu_bar_size;
}

GUI_View::~GUI_View()
{
}

/**
 * @brief Main entry to draw everything added to view/menus
 */
void GUI_View::draw()
{
    uint16_t text_y, text_x;

    if (refresh)
    {
        display->draw_filled_rect(0, 0, get_width(), menu_bar_size, get_trim_colour());
        display->draw_filled_rect(0, 0, get_width(), menu_bar_size - 1, get_background_colour());
    }

    if (menu_stack.size() > 0)
    {
        menu_stack.top()->set_x_offset(get_x());
        menu_stack.top()->set_y_offset(menu_bar_size);
        menu_stack.top()->draw(display);

        if (refresh)
        {
            const char *menu_name = menu_stack.top()->get_menu_name();

            display->set_text_colour(get_text_colour());
            display->set_text_size(get_text_size());

            text_x = display->center_text_horizontal((char *)menu_name, get_width(), 0);
            text_y = display->center_text_vertical((char *)menu_name, menu_bar_size, 0);

            display->draw_text(text_x, text_y, menu_name);

            if (menu_stack.size() > 1)
            {
                // TODO Make this dynamically sized
                int arrow_x1 = 24;
                int arrow_y1 = 6;
                int arrow_height = menu_bar_size / 2;
                int arrow_width = 8;
                display->draw_filled_round_rect(8, 2, menu_bar_size - 4, 22, 5, back_button_bg_colour);
                display->draw_filled_triangle(arrow_x1, arrow_y1, arrow_x1 - arrow_width, arrow_y1 + (arrow_height / 2), arrow_x1, arrow_y1 + arrow_height, back_button_arrow_colour);
                display->draw_filled_triangle(arrow_x1, arrow_y1 + 3, arrow_x1 - arrow_width + 3, arrow_y1 + (arrow_height / 2), arrow_x1, arrow_y1 + arrow_height - 3, back_button_bg_colour);
            }
            refresh = false;
        }
    }

    display->set_text_colour(get_text_colour());
    display->set_text_size(get_text_size());
}

/**
 * @brief Draw view (not used)
 *
 * @param display Display to draw button on
 */
void GUI_View::draw(display_driver *display)
{
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

/**
 * @brief Set view refresh value
 *
 * @param r Value to decide if view should be redrawn
 * @param p Unused
 */
void GUI_View::set_refresh(bool r, bool p)
{
    refresh = r;
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

    if (menu_stack.size() > 0)
    {
        menu_stack.top()->set_refresh(true, false);
    }

    menu->set_refresh(true, false);
    menu->adjust_grids();
    menu_stack.push(menu);

    refresh = true;
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

bool set_menu_cb(void *user_data)
{
    menu_change_event *event = (menu_change_event *)user_data;

    event->v->set_menu(event->m);

    return false;
}

/**
 * @brief Set menu change button
 *
 * @param button Button to change menu
 * @param menu Menu to change to
 */
void GUI_View::register_menu_change_button(GUI_Button *button, GUI_Menu *menu)
{
    menu_change_event *user_data = (menu_change_event *)malloc(sizeof(menu_change_event));

    memset(user_data, 0, sizeof(menu_change_event));

    user_data->v = this;
    user_data->m = menu;
    button->set_click_user_cb(set_menu_cb, user_data);
}

void GUI_View::set_menu_bar_colours(RGB return_bg_colour, RGB arrow_colour)
{
    back_button_bg_colour = return_bg_colour;
    back_button_arrow_colour = arrow_colour;
}