#ifndef _GUI_View_H_
#define _GUI_View_H_

#include "GUI.h"

class GUI_View : public GUI_Element
{
private:
    Adafruit_GFX *display;
    std::stack<GUI_Menu *> menu_stack;
    uint16_t menu_bar_size;
    uint16_t back_button_bg_colour;
    uint16_t back_button_arrow_colour;

public:
    GUI_View(Adafruit_GFX *_display, uint16_t _menu_bar_size);
    ~GUI_View();

    void draw();
    void draw(Adafruit_GFX *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void set_refresh(bool r) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::VIEW; }

    void set_menu(GUI_Menu *menu);
    void reverse_menus();
    void set_menu_bar_colours(uint16_t bg_colour, uint16_t arrow_colour);
};

#endif /* _GUI_View_H_ */
