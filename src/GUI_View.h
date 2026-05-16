#pragma once

#include "GUI_Menu.h"
#include "GUI_Button.h"

#include <stack>

class GUI_View : public GUI_Element
{
private:
    std::stack<GUI_Menu *> menu_stack;
    uint16_t menu_bar_size;
    RGB back_button_bg_colour;
    RGB back_button_arrow_colour;
    bool ignore_refresh;

public:
    GUI_View(uint16_t menu_bar_size);
    GUI_View();
    ~GUI_View();

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void navigate(INPUT_TYPE input, KEYBOARD_KEY key) override;
    void set_refresh(bool r, bool p) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::VIEW; }

    GUI_Element *clone() const override { return new GUI_View(*this); }

    void set_menu(GUI_Menu *menu);
    void set_global_colour_scheme(GUI_Colour_Scheme colour_scheme);
    void reverse_menus();
    void register_menu_change_button(GUI_Button *button, GUI_Menu *menu);
    void set_menu_bar_colours(RGB return_bg_colour, RGB arrow_colour);
};
