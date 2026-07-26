#include "GUI_Image.h"

#ifdef GUI_IMAGE_SUPPORT

GUI_Image::GUI_Image(PLATFORM_STRING file_path, uint16_t width, uint16_t height) : GUI_Element(width, height), file_path(file_path) {}

GUI_Image::GUI_Image(PLATFORM_STRING file_path) : GUI_Image(file_path, 0, 0) {}

GUI_Image::~GUI_Image() {}

/**
 * @brief Draw image
 *
 * @param display Display to draw image on
 */
void GUI_Image::draw(display_driver *display)
{
    if (!refresh)
    {
        return;
    }

    display->draw_image(get_x(), get_y(), get_width(), get_height(), file_path);
}

void GUI_Image::navigate(int16_t x_pos, int16_t y_pos) {}

void GUI_Image::navigate(INPUT_TYPE input, KEYBOARD_KEY key) {}

/**
 * @brief Set image refresh value
 *
 * @param r Value to decide if image should be redrawn
 * @param p Value to decide if need to update parents refresh
 */
void GUI_Image::set_refresh(bool r, bool p)
{
    refresh = r;

    if (p && parent != NULL)
    {
        parent->set_refresh(r, p);
    }
}

void GUI_Image::calculate_sizing(display_driver *display)
{
    if (!refresh)
    {
        return;
    }

    uint16_t min_width = 0;
    uint16_t min_height = 0;

    if (get_width_auto_sizeable())
    {
        min_width = 1;
        min_height = 1;
    }
    else
    {
        min_width = get_width();
        min_height = get_height();
    }

    set_min_width_px(min_width);
    set_min_height_px(min_height);
}

#endif /* GUI_IMAGE_SUPPORT */

GUI_Bitmap::GUI_Bitmap(uint8_t *bitmap, uint16_t width, uint16_t height) : GUI_Element(width, height), bitmap_data(bitmap), bitmap_type(BITMAP_ALPHA_MAP) {}

GUI_Bitmap::GUI_Bitmap(uint16_t *bitmap, uint16_t width, uint16_t height) : GUI_Element(width, height), bitmap_data(bitmap), bitmap_type(BITMAP_RGB565) {}

GUI_Bitmap::~GUI_Bitmap() {}

/**
 * @brief Draw bitmap
 *
 * @param display Display to draw button on
 */
void GUI_Bitmap::draw(display_driver *display)
{
    if (!refresh)
    {
        return;
    }

    display->draw_bitmap(get_x(), get_y(), get_width(), get_height(), bitmap_data, bitmap_type, get_background_colour());
}

void GUI_Bitmap::navigate(int16_t x_pos, int16_t y_pos) {}

void GUI_Bitmap::navigate(INPUT_TYPE input, KEYBOARD_KEY key) {}

void GUI_Bitmap::set_refresh(bool r, bool p)
{
    refresh = r;

    if (p && parent != NULL)
    {
        parent->set_refresh(r, p);
    }
}

void GUI_Bitmap::calculate_sizing(display_driver *display)
{
    if (!refresh)
    {
        return;
    }

    set_min_width_px(get_width());
    set_min_height_px(get_height());
}
