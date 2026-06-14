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
    uint16_t rows;
    uint8_t attributes;

    std::vector<int32_t> row_heights;
    std::vector<int32_t> col_widths;

    void resize_elements();

    uint16_t get_column_width(uint16_t col);
    uint16_t get_row_height(uint16_t row);

    class Grid_Element
    {
    private:
        GUI_Element *element;
        uint16_t column_span;
        uint16_t row_span;
        uint16_t curr_col;
        uint16_t curr_row;

    public:
        Grid_Element(GUI_Element *element, uint16_t column_span, uint16_t row_span) : element(element), column_span(column_span), row_span(row_span)
        {
            curr_col = 0;
            curr_row = 0;
        };

        ~Grid_Element()
        {
            if (element->get_ref_count() <= 1)
            {
                delete element;
            }
            else
            {
                element->decrease_ref();
            }
        };

        GUI_Element *get_element() { return element; };
        uint16_t get_row_span() { return row_span; };
        uint16_t get_col_span() { return column_span; };
        void set_row_span(uint16_t row_span) { this->row_span = row_span; };
        void set_col_span(uint16_t column_span) { this->column_span = column_span; };

        uint16_t get_current_row() { return curr_row; };
        uint16_t get_current_col() { return curr_col; };
        void set_current_row(uint16_t row) { curr_row = row; };
        void set_current_col(uint16_t col) { curr_col = col; };
    };

    bool can_grid_element_fit(uint16_t col, uint16_t row, uint16_t col_span, uint16_t row_span);
    Grid_Element *get_grid_element(uint16_t col, uint16_t row);
    void set_grid_element_col_row(Grid_Element *g);
    uint16_t get_col_x(uint16_t col);
    uint16_t get_row_y(uint16_t row);
    void adjust_x_y();

    std::vector<Grid_Element *> elements;

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

    void add_element(GUI_Element *element, uint16_t col_span, uint16_t row_span);
    void add_element(GUI_Element *element);
    void adjust_elements();
    void apply_colour_scheme();
    uint16_t get_rows();

protected:
    void deselect_elements();
    void select_elements();
    bool end_of_interactable_elements();
    bool start_of_interactable_elements();

private:
    int16_t get_next_interactable_element();
    int16_t get_prev_interactable_element();
};
