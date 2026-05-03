#ifndef _GUI_View_H_
#define _GUI_View_H_

#include "GUI.h"

class GUI_View : public GUI_Element
{
private:
    display_driver *display;
    std::stack<GUI_Menu *> menu_stack;
    uint16_t menu_bar_size;
    RGB back_button_bg_colour;
    RGB back_button_arrow_colour;

public:
    GUI_View(display_driver *display, uint16_t menu_bar_size);
    ~GUI_View();

    void draw();
    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void set_refresh(bool r, bool p) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::VIEW; }

    GUI_Element *clone() const override { return new GUI_View(*this); }

    void set_menu(GUI_Menu *menu);
    void reverse_menus();
    void register_menu_change_button(GUI_Button *button, GUI_Menu *menu);
    void set_menu_bar_colours(RGB return_bg_colour, RGB arrow_colour);
};

#endif /* _GUI_View_H_ */
