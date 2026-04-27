#ifndef _GUI_Button_H_
#define _GUI_Button_H_

#include "GUI.h"

typedef enum
{
    BUTTON_NO_STYLE,
    BUTTON_ROUND_STYLE,
    BUTTON_ROUND_STYLE_UP_ARROW,
    BUTTON_ROUND_STYLE_DOWN_ARROW,
    BUTTON_ROUND_STYLE_LEFT_ARROW,
    BUTTON_ROUND_STYLE_RIGHT_ARROW,
    BUTTON_ICON_STYLE,
    BUTTON_SQUARE_STYLE,
} BUTTON_STYLE;

typedef enum
{
    TOGGLE_BUTTON_NO_STYLE,
    TOGGLE_BUTTON_ROUND_STYLE,
} TOGGLE_BUTTON_STYLE;

class GUI_Button : public GUI_Element
{
private:
    char *text[32];
    BUTTON_STYLE button_style;
    uint8_t border_radius;
    TEXT_ALIGN align_value;
    uint8_t *icon_bitmap;
    uint8_t icon_width;
    uint8_t icon_height;
    uint16_t icon_bg_colour;

protected:
    click_cb_fun click_cb;
    void *user_data;
    bool disabled;

public:
    GUI_Button(BUTTON_STYLE style, const char *button_str, click_cb_fun _click_cb = NULL, void *_user_data = NULL, TEXT_ALIGN _align = ALIGN_CENTER);
    ~GUI_Button();

    void draw(Adafruit_GFX *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void set_refresh(bool r) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::BUTTON; }

    void set_icon_bitmap(uint8_t *_bitmap, uint8_t _width, uint8_t _height, uint16_t _icon_bg_colour);
    void set_click_user_cb(click_cb_fun _click_cb, void *_user_data);
    void set_disabled(bool disable);
    bool is_disabled();
};

class GUI_Toggle_Button : public GUI_Button
{
private:
    TOGGLE_BUTTON_STYLE button_style;
    bool value;
    uint16_t toggled_colour;
    uint16_t non_toggled_colour;
    uint16_t toggle_element_colour;

public:
    GUI_Toggle_Button(TOGGLE_BUTTON_STYLE style, const char *button_str, click_cb_fun _click_cb = NULL, bool default_value = false, TEXT_ALIGN _align = ALIGN_CENTER);

    void draw(Adafruit_GFX *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void toggle();
    bool get_toggled();
    void set_toggled_colours(uint16_t _toggled_colour, uint16_t _non_toggled_colour, uint16_t _toggle_element_colour);
};

#endif /* _GUI_Button_H_ */
