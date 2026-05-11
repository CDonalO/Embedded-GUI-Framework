#include "GUI_Bitmap.h"

GUI_Bitmap::GUI_Bitmap(uint8_t *bitmap) : GUI_Element(), bitmap_data(bitmap), bitmap_type(BITMAP_ALPHA_MAP) {}

GUI_Bitmap::GUI_Bitmap(uint16_t *bitmap) : GUI_Element(), bitmap_data(bitmap), bitmap_type(BITMAP_RGB565) {}

GUI_Bitmap::~GUI_Bitmap() {}

/**
 * @brief Draw bitmap
 *
 * @param display Display to draw button on
 */
void GUI_Bitmap::draw(display_driver *display)
{
    display->draw_bitmap(get_x(), get_y(), get_width(), get_height(), bitmap_data, bitmap_type, get_background_colour());
}

void GUI_Bitmap::navigate(int16_t x_pos, int16_t y_pos)
{
}

void GUI_Bitmap::set_refresh(bool r, bool p)
{
    refresh = r;
}