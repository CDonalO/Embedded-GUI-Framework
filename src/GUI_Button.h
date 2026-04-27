#ifndef _GUI_Button_H_
#define _GUI_Button_H_

#include "GUI.h"

typedef enum
{
    BUTTON_NO_STYLE,
    BUTTON_ROUND_STYLE,
    BUTTON_SQUARE_STYLE,
} BUTTON_STYLE;

class GUI_Button : public GUI_Element
{
private:
    char *text[32];
    BUTTON_STYLE button_style;
    uint8_t border_radius;
    TEXT_ALIGN align_value;
    click_cb_fun click_cb;
    void *user_data;

public:
    GUI_Button(BUTTON_STYLE style, const char *button_str, click_cb_fun _click_cb = NULL, void *_user_data = NULL, TEXT_ALIGN _align = ALIGN_CENTER);
    ~GUI_Button();

    void draw(Adafruit_GFX *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void set_refresh(bool r) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::BUTTON; }
};

#endif /* _GUI_Button_H_ */
