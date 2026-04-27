#ifndef _GUI_View_H_
#define _GUI_View_H_

#include "GUI.h"

class GUI_View : public GUI_Element
{
private:
    Adafruit_GFX *display;
    std::stack<GUI_Menu *> menu_stack;

public:
    GUI_View(Adafruit_GFX *_display);
    ~GUI_View();

    void draw();
    void draw(Adafruit_GFX *display) override;
    bool navigate(int16_t x_pos, int16_t y_pos) override;

    void set_menu(GUI_Menu *menu);
    void reverse_menus();
};

#endif /* _GUI_View_H_ */
