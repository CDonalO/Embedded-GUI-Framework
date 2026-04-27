#include "GUI.h"

GUI_Menu::GUI_Menu(const char *_menu_name) : GUI_Element()
{
    strcpy((char *)menu_name, _menu_name);
    background_colour = WHITE;
}

GUI_Menu::~GUI_Menu()
{
}

void GUI_Menu::add_element(GUI_Element *element)
{
    elements.push_back(element);
}

void GUI_Menu::draw(Adafruit_GFX *display)
{
    display->fillRect(get_x(), get_y(), get_width(), get_height(), background_colour);

    for (int x = 0; x < elements.size(); x++)
    {
        if (elements[x] != NULL)
        {
            elements[x]->draw(display);
        }
    }
}

char *GUI_Menu::get_menu_name()
{
    return (char *)menu_name;
}
