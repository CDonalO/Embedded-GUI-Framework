#pragma once

#include "GUI_Element.h"

#include <vector>
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
protected:
    int16_t selected_element;
    int16_t first_interactable_element_index;
    int16_t last_interactable_element_index;

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
    GUI_Grid(GRID_TYPE type, uint16_t border_padding, uint16_t element_padding, uint8_t grid_attributes = GRID_ATTRIBUTE_NONE);
    ~GUI_Grid();

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void navigate(INPUT_TYPE input) override;
    void set_refresh(bool r, bool p) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::GRID; }

    GUI_Element *clone() const override { return new GUI_Grid(*this); }

    void add_element(GUI_Element *element);
    void adjust_elements();
    void set_top_border_padding(uint16_t border_padding);
    void set_bottom_border_padding(uint16_t border_padding);
    void set_left_border_padding(uint16_t border_padding);
    void set_right_border_padding(uint16_t border_padding);

protected:
    void deselect_elements();
    void select_elements();
    bool end_of_interactable_elements();
    bool start_of_interactable_elements();

private:
    int16_t get_next_interactable_element();
    int16_t get_prev_interactable_element();
};
