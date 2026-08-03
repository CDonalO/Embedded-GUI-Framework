#pragma once

#include <format>
#include "GUI_Label.h"
#include "Form_Data.h"

class GUI_Slider : public GUI_Element, public Form_Data_Number
{
private:
    int16_t default_val;
    int16_t max_val;
    int16_t min_val;
    int16_t val;

    uint16_t min_bar_x;
    uint16_t max_bar_x;
    uint16_t bar_w;
    uint16_t bar_h;
    uint16_t bar_y;
    uint16_t slider_h;
    uint16_t bar_padding;
    uint32_t range;
    uint32_t norm_val;
    float x_per_val;
    GUI_Label value_label;
    GUI_Label min_value_label;
    GUI_Label max_value_label;

    void normalize_value();

public:
    GUI_Slider(int16_t min_val, int16_t max_val, int16_t default_val);
    ~GUI_Slider();

    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::SLIDER; }
    GUI_Element *clone() const override { return new GUI_Slider(*this); }

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void navigate(INPUT_TYPE input, KEYBOARD_KEY key) override;
    void set_refresh(bool r, bool p) override;
    void calculate_sizing(display_driver *display) override;
};
