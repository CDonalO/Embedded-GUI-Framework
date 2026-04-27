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

    void draw(Adafruit_GFX *display) override;
    bool navigate(int16_t x_pos, int16_t y_pos) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::MENU; }

    void add_element(GUI_Element *element);
    char *get_menu_name();
};

#endif /* _GUI_Menu_H_ */
