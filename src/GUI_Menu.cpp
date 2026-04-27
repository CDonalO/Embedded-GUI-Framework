#include "GUI.h"

GUI_Menu::GUI_Menu(const char *_menu_name) : GUI_Element()
{
    strncpy((char *)menu_name, _menu_name, sizeof(menu_name));
}

GUI_Menu::~GUI_Menu()
{
}

void GUI_Menu::draw(Adafruit_GFX *display)
{
    if (refresh)
        display->fillRect(get_x(), get_y(), get_width(), get_height(), get_background_colour());

    for (int x = 0; x < elements.size(); x++)
    {
        if (elements[x]->get_refresh())
        {
            display->setTextColor(get_text_colour());
            display->setTextSize(get_text_size());
            elements[x]->set_x_offset(get_x());
            elements[x]->set_y_offset(get_y());
            elements[x]->draw(display);
            elements[x]->set_refresh(false);
        }
    }

    refresh = false;
}

void GUI_Menu::navigate(int16_t x_pos, int16_t y_pos)
{
    for (int x = 0; x < elements.size(); x++)
    {
        if (elements[x]->within_bounds(x_pos, y_pos))
        {
            elements[x]->navigate(x_pos, y_pos);
        }
    }
}

void GUI_Menu::set_refresh(bool r)
{
    refresh = r;

    for (int x = 0; x < elements.size(); x++)
    {
        elements[x]->set_refresh(r);
    }
}

void GUI_Menu::add_element(GUI_Element *element)
{
    if (element->get_type() == GUI_Element::Element_Type::GRID)
    {
        if (element->get_width() == 0)
        {
            element->set_width(get_width());
        }

        if (element->get_height() == 0)
        {
            element->set_height(get_height());
        }
        GUI_Grid *grid_element = static_cast<GUI_Grid *>(element);
        grid_element->adjust_elements();
    }
    elements.push_back(element);
}

const char *GUI_Menu::get_menu_name()
{
    return (char *)menu_name;
}
