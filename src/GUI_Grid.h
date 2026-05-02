#ifndef _GUI_Grid_H_
#define _GUI_Grid_H_

#include "GUI.h"

typedef enum
{
    GRID_TYPE_NONE,
    GRID_TYPE_VERTICAL,
    GRID_TYPE_HORIZONTAL,
} GRID_TYPE;

#define GRID_ATTRIBUTE_NONE (1 << 0)
#define GRID_ATTRIBUTE_FLEX (1 << 1)
#define GRID_ATTRIBUTE_CENTER_FLEX (1 << 2)
class GUI_Grid : public GUI_Element
{
private:
    GRID_TYPE grid_type;
    uint16_t top_border_padding;
    uint16_t bottom_border_padding;
    uint16_t left_border_padding;
    uint16_t right_border_padding;
    uint16_t element_padding;
    uint8_t attributes;
    std::vector<GUI_Element *> elements;

public:
    GUI_Grid(GRID_TYPE type, uint16_t border_padding, uint16_t _element_padding, uint8_t grid_attributes = GRID_ATTRIBUTE_NONE);
    ~GUI_Grid();

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void set_refresh(bool r, bool p) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::GRID; }

    GUI_Element *clone() const { return new GUI_Grid(*this); }

    void add_element(GUI_Element *element);
    void adjust_elements();
    void set_top_border_padding(uint16_t border_padding);
    void set_bottom_border_padding(uint16_t border_padding);
    void set_left_border_padding(uint16_t border_padding);
    void set_right_border_padding(uint16_t border_padding);
};

#endif /* _GUI_Grid_H_ */