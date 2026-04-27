#ifndef _GUI_Grid_H_
#define _GUI_Grid_H_

#include "GUI.h"

typedef enum
{
    GRID_TYPE_NONE,
    GRID_TYPE_VERTICAL,
    GRID_TYPE_HORIZONTAL,
} GRID_TYPE;

class GUI_Grid : public GUI_Element
{
private:
    GRID_TYPE grid_type;
    uint16_t top_border_padding;
    uint16_t bottom_border_padding;
    uint16_t left_border_padding;
    uint16_t right_border_padding;
    uint16_t element_padding;
    std::vector<GUI_Element *> elements;

    void adjust_elements();

public:
    GUI_Grid(GRID_TYPE type, uint16_t border_padding, uint16_t _element_padding);
    ~GUI_Grid();

    void draw(Adafruit_GFX *display) override;
    bool navigate(int16_t x_pos, int16_t y_pos) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::GRID; }

    void add_element(GUI_Element *element);
    void set_top_border_padding(uint16_t border_padding);
    void set_bottom_border_padding(uint16_t border_padding);
    void set_left_border_padding(uint16_t border_padding);
    void set_right_border_padding(uint16_t border_padding);
};

#endif /* _GUI_Grid_H_ */