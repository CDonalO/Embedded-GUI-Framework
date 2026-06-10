#pragma once

#include "GUI_Button.h"
#include "GUI_Label.h"

class GUI_Form : public GUI_Element
{
public:
    typedef bool (*form_value_update_fun)(char *form_value);

private:
    form_value_update_fun value_update_cb;
    PLATFORM_STRING label;
    char *form_value[32];

public:
    GUI_Form(PLATFORM_STRING label, form_value_update_fun value_cb);
    ~GUI_Form();

    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::FORM; }
    GUI_Element *clone() const override { return new GUI_Form(*this); }

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void navigate(INPUT_TYPE input, KEYBOARD_KEY key) override;
    void set_refresh(bool r, bool p) override;
    uint32_t get_element_min_width_px() override;
    uint32_t get_element_min_height_px() override;
};
