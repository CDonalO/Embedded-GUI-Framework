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

public:
    GUI_Button(BUTTON_STYLE style, const char *button_str, TEXT_ALIGN _align = ALIGN_CENTER);
    ~GUI_Button();

    void draw(Adafruit_GFX *display) override;
};

#endif /* _GUI_Button_H_ */
