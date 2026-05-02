#ifndef _GUI_Menu_H_
#define _GUI_Menu_H_

#include "GUI.h"

class GUI_Menu : public GUI_Element
{
private:
    char *menu_name[32];
    std::vector<GUI_Element *> elements;

public:
    GUI_Menu(const char *_menu_name);
    ~GUI_Menu();

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void set_refresh(bool r, bool p) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::MENU; }

    GUI_Element *clone() const { return new GUI_Menu(*this); }

    void add_element(GUI_Element *element);
    void adjust_grids();
    const char *get_menu_name();
};

#endif /* _GUI_Menu_H_ */
