#ifndef _GUI_View_H_
#define _GUI_View_H_

#include "GUI.h"

class GUI_View : public GUI_Element
{
private:
    Adafruit_GFX *display;
    uint16_t text_colour;
    uint8_t text_size;
    std::stack<GUI_Menu *> menu_stack;

public:
    GUI_View(Adafruit_GFX *_display, uint8_t _text_size, uint16_t _text_colour);
    ~GUI_View();

    void draw(Adafruit_GFX *display) override;
    void draw();

    void set_menu(GUI_Menu *menu);
    void reverse_menus();
};

#endif /* _GUI_View_H_ */
