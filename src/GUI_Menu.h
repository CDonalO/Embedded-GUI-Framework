#pragma once

#include "GUI_Grid.h"

class GUI_Menu : public GUI_Grid
{
private:
    char *menu_name[32];

public:
    GUI_Menu(const char *_menu_name, GRID_TYPE menu_type, int16_t border_padding, uint16_t element_padding, uint8_t grid_attributes);
    GUI_Menu(const char *_menu_name);
    ~GUI_Menu();

    void draw(display_driver *display) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::MENU; }

    GUI_Element *clone() const override { return new GUI_Menu(*this); }

    const char *get_menu_name();
};
