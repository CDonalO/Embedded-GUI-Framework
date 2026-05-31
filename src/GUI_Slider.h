#pragma once

#include "GUI_Element.h"

class GUI_Slider : public GUI_Element
{
private:
    int16_t default_val;
    int16_t max_val;
    int16_t min_val;
    int16_t val;

    uint16_t min_bar_x;
    uint16_t max_bar_x;
    uint16_t bar_w;
    uint16_t bar_h = 2;
    uint32_t range;
    uint32_t norm_val;
    float x_per_val;
    void normalize_value();

public:
    GUI_Slider(int16_t min_val, int16_t max_val, int16_t default_val);
    ~GUI_Slider();

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void navigate(INPUT_TYPE input, KEYBOARD_KEY key) override;
    void set_refresh(bool r, bool p) override;

    GUI_Element *clone() const override { return new GUI_Slider(*this); }
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::SLIDER; }
};
