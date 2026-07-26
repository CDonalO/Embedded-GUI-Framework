#pragma once

#include "GUI_Element.h"

#ifdef GUI_IMAGE_SUPPORT

class GUI_Image : public GUI_Element
{
private:
    PLATFORM_STRING file_path;

public:
    GUI_Image(PLATFORM_STRING file_path, uint16_t width, uint16_t height);
    GUI_Image(PLATFORM_STRING file_path);
    ~GUI_Image();

    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::IMAGE; }
    GUI_Element *clone() const override { return new GUI_Image(*this); }

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void navigate(INPUT_TYPE input, KEYBOARD_KEY key) override;
    void set_refresh(bool r, bool p) override;
    void calculate_sizing(display_driver *display) override;
};

#endif /* GUI_IMAGE_SUPPORT */

class GUI_Bitmap : public GUI_Element
{
private:
    void *bitmap_data;

    BITMAP_TYPE bitmap_type;

public:
    GUI_Bitmap(uint8_t *bitmap, uint16_t width, uint16_t height);
    GUI_Bitmap(uint16_t *bitmap, uint16_t width, uint16_t height);

    ~GUI_Bitmap();

    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::BITMAP; }
    GUI_Element *clone() const override { return new GUI_Bitmap(*this); }

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void navigate(INPUT_TYPE input, KEYBOARD_KEY key) override;
    void set_refresh(bool r, bool p) override;
    void calculate_sizing(display_driver *display) override;
};