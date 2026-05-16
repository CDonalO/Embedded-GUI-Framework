#pragma once

#include "GUI_Grid.h"

class GUI_Menu : public GUI_Grid
{
private:
    PLATFORM_STRING menu_name;

public:
    GUI_Menu(PLATFORM_STRING menu_name, GRID_TYPE menu_type, int16_t border_padding, uint16_t element_padding, uint8_t grid_attributes);
    GUI_Menu(PLATFORM_STRING menu_name);
    ~GUI_Menu();

    void draw(display_driver *display) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::MENU; }

    GUI_Element *clone() const override { return new GUI_Menu(*this); }

    PLATFORM_STRING get_menu_name();
    void set_menu_colour_scheme(GUI_Colour_Scheme colour_scheme);
};
