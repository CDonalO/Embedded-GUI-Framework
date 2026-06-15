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
#ifdef ADAFRUIT_DRIVER
    PLATFORM_PRINTF("Image element type not supported on adafruit gfx\n");
#endif /* ADAFRUIT_DRIVER */

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
}

uint32_t GUI_Image::get_element_min_width_px()
{
    return get_min_width_px();
}

uint32_t GUI_Image::get_element_min_height_px()
{
    return get_min_height_px();
}

#endif /* GUI_IMAGE_SUPPORT */
