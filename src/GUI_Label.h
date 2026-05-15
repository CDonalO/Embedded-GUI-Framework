#pragma once

#include "GUI_Element.h"

class GUI_Label : public GUI_Element
{
private:
    PLATFORM_STRING label;
    TEXT_ALIGN align_value;

public:
    GUI_Label(PLATFORM_STRING label, TEXT_ALIGN align, uint8_t text_size, RGB text_colour);
    ~GUI_Label();

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void navigate(INPUT_TYPE input, KEYBOARD_KEY key) override;
    void set_refresh(bool r, bool p) override;

    GUI_Element *clone() const override { return new GUI_Label(*this); }

    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::LABEL; }
};
