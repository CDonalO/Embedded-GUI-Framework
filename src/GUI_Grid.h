#pragma once

#include "GUI_Element.h"

#include <vector>
typedef enum
{
    GRID_TYPE_NONE,
    GRID_TYPE_VERTICAL,
    GRID_TYPE_HORIZONTAL,
    MENU_TYPE_NONE = GRID_TYPE_NONE,
    MENU_TYPE_VERTICAL = GRID_TYPE_VERTICAL,
    MENU_TYPE_HORIZONTAL = GRID_TYPE_HORIZONTAL,
} GRID_TYPE;

#define GRID_ATTRIBUTE_NONE (1 << 0)
#define GRID_ATTRIBUTE_FLEX (1 << 1)
class GUI_Grid : public GUI_Element
{
protected:
    int16_t selected_element;
    int16_t first_interactable_element_index;
    int16_t last_interactable_element_index;

private:
    GRID_TYPE grid_type;
    uint32_t min_col_width;
    uint32_t min_row_height;
    uint16_t element_padding;
    uint16_t columns;
    uint8_t attributes;

    std::vector<int32_t> row_heights;
    std::vector<int32_t> col_widths;

    void resize_elements();

    uint16_t get_column_width(uint16_t col);
    uint16_t get_row_height(uint16_t row);

    uint16_t get_rows();
    void adjust_sub_grids();
    void adjust_x_y();

    std::vector<GUI_Element *> elements;

public:
    GUI_Grid(GRID_TYPE type, uint16_t border_padding, uint16_t element_padding, uint8_t grid_attributes = GRID_ATTRIBUTE_NONE, uint16_t columns = 1);

    ~GUI_Grid();

    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::GRID; }
    GUI_Element *clone() const override { return new GUI_Grid(*this); }

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void navigate(INPUT_TYPE input, KEYBOARD_KEY key) override;
    void set_refresh(bool r, bool p) override;
    uint32_t get_element_min_width_px() override;
    uint32_t get_element_min_height_px() override;

    void add_element(GUI_Element *element);
    void adjust_elements();
    void apply_colour_scheme();

protected:
    void deselect_elements();
    void select_elements();
    bool end_of_interactable_elements();
    bool start_of_interactable_elements();

private:
    int16_t get_next_interactable_element();
    int16_t get_prev_interactable_element();
};
