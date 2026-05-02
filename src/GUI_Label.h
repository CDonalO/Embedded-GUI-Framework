#ifndef _GUI_Label_H_
#define _GUI_Label_H_

#include "GUI.h"

class GUI_Label : public GUI_Element
{
private:
    char *text[32];
    TEXT_ALIGN align_value;

public:
    GUI_Label(char *label, TEXT_ALIGN _align, uint8_t text_size, RGB text_colour);
    ~GUI_Label();

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void set_refresh(bool r, bool p) override;

    GUI_Element *clone() const { return new GUI_Label(*this); }

    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::LABEL; }
};

#endif /* _GUI_Label_H_ */