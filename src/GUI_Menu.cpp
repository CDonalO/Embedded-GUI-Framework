#include "GUI_Menu.h"

GUI_Menu::GUI_Menu(PLATFORM_STRING menu_name, GRID_TYPE menu_type, int16_t border_padding, uint16_t element_padding, uint8_t grid_attributes) : GUI_Grid(menu_type, border_padding, element_padding, grid_attributes), menu_name(menu_name)
{
}

GUI_Menu::GUI_Menu(PLATFORM_STRING menu_name) : GUI_Menu(menu_name, GRID_TYPE_NONE, 0, 0, 0)
{
}

GUI_Menu::~GUI_Menu()
{
}

/**
 * @brief Draw menu
 *
 * @param display Display to draw menu on
 */
void GUI_Menu::draw(display_driver *display)
{
    if (refresh)
        display->draw_filled_rect(get_x(), get_y(), get_width(), get_height(), get_background_colour());

    GUI_Grid::draw(display);

    refresh = false;
}

PLATFORM_STRING GUI_Menu::get_menu_name()
{
    return menu_name;
}
