#pragma once

#include "GUI_Grid.h"
#include "GUI_Button.h"

#include <set>

class GUI_Menu : public GUI_Grid
{
private:
    GUI_Label menu_label;
    std::set<std::uintptr_t> menu_cb_objs;

public:
    GUI_Menu(PLATFORM_STRING menu_name, GRID_TYPE menu_type, int16_t border_padding, uint16_t element_padding, uint8_t grid_attributes, uint8_t columns = 1);
    GUI_Menu(PLATFORM_STRING menu_name);
    ~GUI_Menu();

    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::MENU; }
    GUI_Element *clone() const override { return new GUI_Menu(*this); }

    void draw(display_driver *display) override;
    uint32_t get_element_min_width_px() override;
    uint32_t get_element_min_height_px() override;

    PLATFORM_STRING get_menu_name();
    void set_menu_colour_scheme(GUI_Colour_Scheme colour_scheme);
    void register_menu_change_button(GUI_Button *button, GUI_Menu *menu);
};
