#include "GUI_Image.h"

#ifdef GUI_IMAGE_SUPPORT

GUI_Image::GUI_Image(PLATFORM_STRING file_path) : GUI_Element(), file_path(file_path)
{
}

GUI_Image::~GUI_Image()
{
}

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

void GUI_Image::navigate(INPUT_TYPE input) {}

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

#endif /* GUI_IMAGE_SUPPORT */
