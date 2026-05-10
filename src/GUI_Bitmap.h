#pragma once

#include "GUI.h"

class GUI_Bitmap : public GUI_Element
{
private:
    void *bitmap_data;

    BITMAP_TYPE bitmap_type;

public:
    GUI_Bitmap(uint8_t *bitmap);
    GUI_Bitmap(uint16_t *bitmap);

    ~GUI_Bitmap();

    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::BITMAP; }

    GUI_Element *clone() const override { return new GUI_Bitmap(*this); }

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void set_refresh(bool r, bool p) override;
};
