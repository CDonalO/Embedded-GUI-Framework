#include "GUI_Menu.h"
#include "GUI_View.h"

GUI_Menu::GUI_Menu(PLATFORM_STRING menu_name, GRID_TYPE menu_type, int16_t border_padding, uint16_t element_padding, uint8_t grid_attributes) : GUI_Grid(menu_type, border_padding, element_padding, grid_attributes), menu_name(menu_name)
{
}

GUI_Menu::GUI_Menu(PLATFORM_STRING menu_name) : GUI_Menu(menu_name, GRID_TYPE_NONE, 0, 0, 0)
{
}

GUI_Menu::~GUI_Menu()
{
}

typedef struct menu_change_event
{
    GUI_Menu *parent_menu;
    GUI_Menu *sub_menu;
} _menu_change_event;

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

void GUI_Menu::set_menu_colour_scheme(GUI_Colour_Scheme colour_scheme)
{
    set_colour_scheme(colour_scheme);

    GUI_Grid::apply_colour_scheme();

    GUI_Grid::set_refresh(true, false);
}

bool set_menu_cb(void *user_data)
{
    menu_change_event *event = (menu_change_event *)user_data;

    GUI_Menu *parent_menu = event->parent_menu;

    if (parent_menu->parent != NULL && parent_menu->parent->get_type() == GUI_Element::Element_Type::VIEW)
    {
        GUI_View *view = static_cast<GUI_View *>(parent_menu->parent);
        view->set_menu(event->sub_menu);
    }

    return false;
}

/**
 * @brief Set menu change button
 *
 * @param button Button to change menu
 * @param menu Menu to change to
 */
void GUI_Menu::register_menu_change_button(GUI_Button *button, GUI_Menu *menu)
{
    menu_change_event *user_data = (menu_change_event *)malloc(sizeof(menu_change_event));

    memset(user_data, 0, sizeof(menu_change_event));

    user_data->parent_menu = this;
    user_data->sub_menu = menu;
    button->set_click_user_cb(set_menu_cb, user_data);
}
