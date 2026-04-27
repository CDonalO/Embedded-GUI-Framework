#include "GUI.h"

typedef struct menu_change_event
{
    GUI_View *v;
    GUI_Menu *m;
} _menu_change_event;

GUI_View::GUI_View(Adafruit_GFX *_display, uint16_t _menu_bar_size) : GUI_Element()
{
    display = _display;
    menu_bar_size = _menu_bar_size;
}

GUI_View::~GUI_View()
{
}

void GUI_View::draw()
{
    uint16_t text_y, text_x;

    if (refresh)
    {
        display->fillRect(0, 0, get_width(), menu_bar_size, get_trim_colour());
        display->fillRect(0, 0, get_width(), menu_bar_size - 1, get_background_colour());
    }

    if (menu_stack.size() > 0)
    {
        menu_stack.top()->set_x_offset(get_x());
        menu_stack.top()->set_y_offset(menu_bar_size);
        menu_stack.top()->draw(display);

        if (refresh)
        {
            const char *menu_name = menu_stack.top()->get_menu_name();

            display->setTextColor(get_text_colour());
            display->setTextSize(get_text_size());

            text_x = center_text_horizontal((char *)menu_name, get_width(), 0, display);
            text_y = center_text_vertical((char *)menu_name, menu_bar_size, 0, display);

            display->setCursor(text_x, text_y);
            display->println(menu_name);

            if (menu_stack.size() > 1)
            {
                // TODO Make this dynamically sized
                int arrow_x1 = 24;
                int arrow_y1 = 6;
                int arrow_height = menu_bar_size / 2;
                int arrow_width = 8;
                display->fillRoundRect(8, 2, menu_bar_size - 4, 22, 5, back_button_bg_colour);
                display->fillTriangle(arrow_x1, arrow_y1, arrow_x1 - arrow_width, arrow_y1 + (arrow_height / 2), arrow_x1, arrow_y1 + arrow_height, back_button_arrow_colour);
                display->fillTriangle(arrow_x1, arrow_y1 + 3, arrow_x1 - arrow_width + 3, arrow_y1 + (arrow_height / 2), arrow_x1, arrow_y1 + arrow_height - 3, back_button_bg_colour);
            }
            refresh = false;
        }
    }

    display->setTextColor(get_text_colour());
    display->setTextSize(get_text_size());
}

void GUI_View::draw(Adafruit_GFX *display)
{
}

void GUI_View::navigate(int16_t x_pos, int16_t y_pos)
{
    if (menu_stack.size() > 1 && y_pos >= 0 && y_pos <= menu_bar_size)
    {
        // TODO Make this dynamically sized
        reverse_menus();
        return;
    }

    menu_stack.top()->navigate(x_pos, y_pos);
}

void GUI_View::set_refresh(bool r)
{
    refresh = r;
}

void GUI_View::set_menu(GUI_Menu *menu)
{
    menu->set_x(0);
    menu->set_y(0);
    menu->set_width(get_width());
    menu->set_height(get_height() - menu_bar_size);

    if (menu_stack.size() > 0)
    {
        menu_stack.top()->set_refresh(true);
    }

    menu->set_refresh(true);
    menu_stack.push(menu);

    refresh = true;
}

void GUI_View::reverse_menus(void)
{
    if (menu_stack.size() > 1)
    {
        menu_stack.top()->set_refresh(true);
        menu_stack.pop();
    }

    menu_stack.top()->set_refresh(true);
    refresh = true;
}

bool set_menu_cb(void *user_data)
{
    menu_change_event *event = (menu_change_event *)user_data;

    event->v->set_menu(event->m);

    return false;
}

void GUI_View::register_menu_change_button(GUI_Button *button, GUI_Menu *menu)
{
    menu_change_event *user_data = (menu_change_event *)malloc(sizeof(menu_change_event));

    memset(user_data, 0, sizeof(menu_change_event));

    user_data->v = this;
    user_data->m = menu;
    button->set_click_user_cb(set_menu_cb, user_data);
}

void GUI_View::set_menu_bar_colours(uint16_t return_bg_colour, uint16_t arrow_colour)
{
    back_button_bg_colour = return_bg_colour;
    back_button_arrow_colour = arrow_colour;
}