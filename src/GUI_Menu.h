#ifndef _GUI_Menu_H_
#define _GUI_Menu_H_

#include "GUI.h"

class GUI_Menu : public GUI_Element
{
private:
    uint16_t background_colour;
    char *menu_name[32];
    std::vector<GUI_Element *> elements;

public:
    GUI_Menu(const char *_menu_name);
    ~GUI_Menu();

    void add_element(GUI_Element *element);
    void draw(Adafruit_GFX *display) override;

    char *get_menu_name();
};

#endif /* _GUI_Menu_H_ */
