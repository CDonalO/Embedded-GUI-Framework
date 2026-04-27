#include "GUI.h"

GUI_View::GUI_View(Adafruit_GFX *_display) : GUI_Element()
{
    display = _display;
}

GUI_View::~GUI_View()
{
}

void GUI_View::draw(Adafruit_GFX *display)
{
}

void GUI_View::draw()
{
    uint16_t text_y, text_x;

    display->setTextColor(get_text_colour());
    display->setTextSize(get_text_size());

    if (menu_stack.size() > 0)
    {
        menu_stack.top()->draw(display);
    }

    display->setTextColor(get_text_colour());
    display->setTextSize(get_text_size());
}

void GUI_View::set_menu(GUI_Menu *menu)
{
    menu->set_x(0);
    menu->set_y(0);
    menu->set_width(get_width());
    menu->set_height(get_height());

    menu_stack.push(menu);
}

void GUI_View::reverse_menus(void)
{
    menu_stack.pop();
}
