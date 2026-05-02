#include "GUI.h"

GUI_Menu::GUI_Menu(const char *_menu_name) : GUI_Element()
{
    strncpy((char *)menu_name, _menu_name, sizeof(menu_name));
}

GUI_Menu::~GUI_Menu()
{
}

void GUI_Menu::draw(display_driver *display)
{
    if (refresh)
        display->draw_filled_rect(get_x(), get_y(), get_width(), get_height(), get_background_colour());

    for (int x = 0; x < elements.size(); x++)
    {
        display->set_text_colour(get_text_colour());
        display->set_text_size(get_text_size());
        elements[x]->set_x_offset(get_x());
        elements[x]->set_y_offset(get_y());
        elements[x]->draw(display);
        elements[x]->set_refresh(false, false);
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

void GUI_Menu::set_refresh(bool r, bool p)
{
    refresh = r;

    if (!p)
    {
        for (int x = 0; x < elements.size(); x++)
        {
            elements[x]->set_refresh(r, false);
        }
    }
}

void GUI_Menu::add_element(GUI_Element *element)
{
    // TODO Improve this
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
    element->parent = this;
    elements.push_back(element);
}

void GUI_Menu::adjust_grids()
{
    for (int x = 0; x < elements.size(); x++)
    {
        // TODO Improve this
        if (elements[x]->get_type() == GUI_Element::Element_Type::GRID)
        {
            GUI_Grid *grid_element = static_cast<GUI_Grid *>(elements[x]);
            if (grid_element->get_width() == 0)
            {
                grid_element->set_width(get_width());
            }

            if (grid_element->get_height() == 0)
            {
                grid_element->set_height(get_height());
            }

            grid_element->adjust_elements();
        }
    }
}

const char *GUI_Menu::get_menu_name()
{
    return (char *)menu_name;
}
