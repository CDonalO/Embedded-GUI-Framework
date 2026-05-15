#pragma once

#ifdef GUI_IMAGE_SUPPORT

#include "GUI_Element.h"

class GUI_Image : public GUI_Element
{
private:
    PLATFORM_STRING file_path;

public:
    GUI_Image(PLATFORM_STRING file_path);
    ~GUI_Image();

    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::IMAGE; }

    GUI_Element *clone() const override { return new GUI_Image(*this); }

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void navigate(INPUT_TYPE input) override;
    void set_refresh(bool r, bool p) override;
};

#endif /* GUI_IMAGE_SUPPORT */