#include "GUI_Grid.h"

#include <cmath>

GUI_Grid::GUI_Grid(GRID_TYPE type, uint16_t border_padding, uint16_t element_padding, uint8_t grid_attributes, uint16_t columns) : GUI_Element(), columns(columns), grid_type(type), attributes(grid_attributes)
{
    this->element_padding = element_padding;
    top_border_padding = border_padding;
    bottom_border_padding = border_padding;
    right_border_padding = border_padding;
    left_border_padding = border_padding;
    selected_element = -1;
    first_interactable_element_index = -1;
    last_interactable_element_index = -1;
    set_interactable(true);
}

GUI_Grid::~GUI_Grid()
{
}

/**
 * @brief Draw grid
 *
 * @param display Display to draw grid on
 */
void GUI_Grid::draw(display_driver *display)
{
    if (parent && !is_font_size_set() && parent->is_font_size_set())
    {
        set_font_size(parent->get_font_size());
    }

    for (uint16_t x = 0; x < elements.size(); x++)
    {
        if (!elements[x]->is_font_size_set() && is_font_size_set())
        {
            elements[x]->set_font_size(get_font_size());
        }

        elements[x]->set_x_offset(get_x());
        elements[x]->set_y_offset(get_y());
        elements[x]->draw(display);
        elements[x]->set_refresh(false, false);
    }

#ifdef VISUAL_ELEMENT_DEBUG
    display->draw_line(get_x(), get_center_y(), get_x() + get_width(), get_center_y(), RED);
    display->draw_line(get_center_x(), get_y(), get_center_x(), get_y() + get_height(), RED);
#endif /* VISUAL_ELEMENT_DEBUG */
}

void GUI_Grid::navigate(int16_t x_pos, int16_t y_pos)
{
    for (uint16_t x = 0; x < elements.size(); x++)
    {
        if (elements[x]->within_bounds(x_pos, y_pos))
        {
            elements[x]->navigate(x_pos, y_pos);
        }
    }
}

void GUI_Grid::navigate(INPUT_TYPE input, KEYBOARD_KEY key)
{
    bool in_grid = true;

    if (input == INPUT_KEYBOARD || input == INPUT_LEFT || input == INPUT_RIGHT)
    {
        if (selected_element != -1)
        {
            elements[selected_element]->navigate(input, key);
        }
        return;
    }

    int16_t new_selected_element = -1;
    if (selected_element != -1 && elements[selected_element]->is_interactable())
    {
        if (elements[selected_element]->get_type() == GUI_Element::Element_Type::GRID)
        {
            GUI_Grid *grid_element = static_cast<GUI_Grid *>(elements[selected_element]);

            if (grid_element->first_interactable_element_index != -1)
            {
                if (input == INPUT_UP && !grid_element->start_of_interactable_elements())
                {
                    elements[selected_element]->navigate(input, key);
                    in_grid = false;
                }
                else if (input == INPUT_DOWN && !grid_element->end_of_interactable_elements())
                {
                    elements[selected_element]->navigate(input, key);
                    in_grid = false;
                }
            }
            if (in_grid)
            {
                grid_element->deselect_elements();
            }
        }
        else
        {
            if (elements.size() > 1)
            {
                elements[selected_element]->deselect();
            }
        }
    }

    if (in_grid)
    {
        if (input == INPUT_DOWN)
        {
            new_selected_element = get_next_interactable_element();
        }
        else if (input == INPUT_UP)
        {
            new_selected_element = get_prev_interactable_element();
        }
    }

    if (new_selected_element != -1)
    {
        selected_element = new_selected_element;

        if (elements[selected_element]->get_type() == GUI_Element::Element_Type::GRID)
        {
            GUI_Grid *grid_element = static_cast<GUI_Grid *>(elements[selected_element]);

            if (input == INPUT_UP)
            {
                if (grid_element->selected_element != grid_element->last_interactable_element_index)
                {
                    elements[selected_element]->navigate(input, key);
                }
                else
                {
                    grid_element->select_elements();
                }
            }
            else if (input == INPUT_DOWN)
            {
                if (grid_element->selected_element != grid_element->first_interactable_element_index)
                {
                    elements[selected_element]->navigate(input, key);
                }
                else
                {
                    grid_element->select_elements();
                }
            }
        }
        else
        {
            elements[selected_element]->select();
        }
    }
}

/**
 * @brief Set grid refresh value
 *
 * @param r Value to decide if grid should be redrawn
 * @param p Value to decide if need to update parents refresh
 */
void GUI_Grid::set_refresh(bool r, bool p)
{
    refresh = true;

    if (p && parent != NULL)
    {
        adjust_elements();
        parent->set_refresh(r, p);
    }

    if (!p)
    {
        for (uint16_t x = 0; x < elements.size(); x++)
        {
            elements[x]->set_refresh(r, false);
        }
    }
}

uint16_t GUI_Grid::get_column_width(uint16_t col)
{
    uint16_t cols = columns;
    uint16_t col_width = get_width() - left_border_padding - right_border_padding;

    if (elements.size() == 1)
    {
        return col_width;
    }

    if (col < col_widths.size())
    {
        return col_widths[col];
    }

    col_width -= (cols - 1) * element_padding;
    uint16_t standard_col_width = col_width / cols;
    uint16_t rows = get_rows();
    uint16_t ret_col_width = standard_col_width;
    uint16_t auto_sizeable_cols = cols;

    for (uint16_t x = 0; x < cols; x++)
    {
        col_widths.push_back(-1);
    }

    for (uint16_t x = 0; x < cols; x++)
    {
        bool uniform_col = true;
        bool hidden_col = true;
        uint16_t max_col_width = standard_col_width;

        for (uint16_t y = 0; y < rows; y++)
        {
            uint16_t element_index = y * cols + x;
            if (element_index < elements.size())
            {
                if (hidden_col && !elements[element_index]->is_hidden())
                {
                    hidden_col = false;
                }

                if (!elements[element_index]->get_width_auto_sizeable())
                {
                    uniform_col = false;
                    max_col_width = min(max_col_width, elements[element_index]->get_width());
                }
                else if (elements[element_index]->get_max_width_px() != 0 && max_col_width > elements[element_index]->get_max_width_px())
                {
                    uniform_col = false;
                    max_col_width = elements[element_index]->get_max_width_px();
                }
            }
        }

        if (hidden_col)
        {
            max_col_width = 0;
            col_width += element_padding;
            uniform_col = false;
        }

        if (!uniform_col)
        {
            col_width -= max_col_width;
            col_widths[x] = max_col_width;

            auto_sizeable_cols--;

            if (auto_sizeable_cols > 0)
            {
                standard_col_width = col_width / auto_sizeable_cols;
            }
        }
    }

    for (uint16_t x = 0; x < cols; x++)
    {
        if (col_widths[x] == -1)
        {
            col_widths[x] = standard_col_width;
        }
    }

    return col_widths[col];
}

uint16_t GUI_Grid::get_row_height(uint16_t row)
{
    uint16_t rows = get_rows();
    uint16_t row_height = get_height() - top_border_padding - bottom_border_padding;

    if (elements.size() == 1)
    {
        return row_height;
    }

    if (row < row_heights.size())
    {
        return row_heights[row];
    }

    row_height -= (rows - 1) * element_padding;
    uint16_t standard_row_height = row_height / rows;
    uint16_t ret_row_height = standard_row_height;
    uint16_t auto_sizeable_rows = rows;

    for (uint16_t x = 0; x < rows; x++)
    {
        row_heights.push_back(-1);
    }

    for (uint16_t x = 0; x < rows; x++)
    {
        bool uniform_row = true;
        bool hidden_row = true;
        uint16_t max_row_height = standard_row_height;

        for (uint16_t y = 0; y < columns; y++)
        {
            uint16_t element_index = (x * columns) + y;
            if (element_index < elements.size())
            {
                if (hidden_row && !elements[element_index]->is_hidden())
                {
                    hidden_row = false;
                }

                if (!elements[element_index]->get_height_auto_sizeable())
                {
                    uniform_row = false;
                    max_row_height = min(max_row_height, elements[element_index]->get_height());
                }
                else if (elements[element_index]->get_max_height_px() != 0 && max_row_height > elements[element_index]->get_max_height_px())
                {
                    uniform_row = false;
                    max_row_height = elements[element_index]->get_max_height_px();
                }
            }
        }

        if (hidden_row)
        {
            max_row_height = 0;
            row_height += element_padding;
            uniform_row = false;
        }

        if (!uniform_row)
        {
            row_height -= max_row_height;
            row_heights[x] = max_row_height;

            auto_sizeable_rows--;

            if (auto_sizeable_rows > 0)
            {
                standard_row_height = row_height / auto_sizeable_rows;
            }
        }
    }

    for (uint16_t x = 0; x < rows; x++)
    {
        if (row_heights[x] == -1)
        {
            row_heights[x] = standard_row_height;
        }
    }

    return row_heights[row];
}

uint16_t GUI_Grid::get_rows()
{
    if (elements.size() == 0 || !(attributes & GRID_ATTRIBUTE_FLEX))
    {
        return 1;
    }

    double r = elements.size();
    r /= columns;

    return (uint16_t)ceil(r);
}

void GUI_Grid::adjust_sub_grids()
{
    for (uint16_t x = 0; x < elements.size(); x++)
    {
        elements[x]->set_refresh(true, false);
        if (elements[x]->get_type() == GUI_Element::Element_Type::GRID)
        {
            GUI_Grid *grid_element = static_cast<GUI_Grid *>(elements[x]);

            if (grid_type == GRID_TYPE_VERTICAL)
            {
                grid_element->set_top_border_padding(0);
                grid_element->set_bottom_border_padding(0);
            }
            else if (grid_type == GRID_TYPE_HORIZONTAL)
            {
                grid_element->set_left_border_padding(0);
                grid_element->set_right_border_padding(0);
            }

            grid_element->adjust_elements();
        }
    }
}

void GUI_Grid::adjust_x_y()
{
    uint16_t new_y = top_border_padding;
    uint16_t new_x = left_border_padding;
    uint16_t prev_col = 0;
    uint16_t prev_row = 0;

    if (grid_type == GRID_TYPE_NONE && columns == 1)
    {
        return;
    }

    uint16_t rows = get_rows();

    for (uint16_t x = 0; x < columns; x++)
    {
        if (x > col_widths.size())
        {
            continue;
        }

        if (x > 0)
        {
            if (col_widths[x - 1] != 0)
            {
                new_x += col_widths[x - 1] + element_padding;
            }
        }

        new_y = top_border_padding;

        for (uint16_t y = 0; y < rows; y++)
        {
            uint16_t element_index = (y * columns) + x;

            if (element_index >= elements.size())
            {
                continue;
            }

            if (y > 0)
            {
                if (row_heights[y - 1] != 0)
                {
                    new_y += row_heights[y - 1] + element_padding;
                }
            }

            elements[element_index]->set_y(new_y);
            elements[element_index]->set_x(new_x);
        }
    }
}

void GUI_Grid::resize_elements()
{
    uint16_t new_width;
    uint16_t new_height;

    if (!(attributes & GRID_ATTRIBUTE_FLEX))
    {
        return;
    }

    for (uint16_t x = 0; x < elements.size(); x++)
    {
        uint8_t current_col = x % columns;
        uint8_t current_row = x / columns;

        new_width = get_column_width(current_col);
        new_height = get_row_height(current_row);

        if (elements[x]->get_width_auto_sizeable())
        {
            elements[x]->set_width(new_width);
        }

        if (elements[x]->get_height_auto_sizeable())
        {
            elements[x]->set_height(new_height);
        }
#ifdef VERBOSE_ELEMENT_DEBUG
        PLATFORM_PRINTF("[%d] Setting new width %d, new height %d\n", x, elements[x]->get_width(), elements[x]->get_height());
#endif /* VERBOSE_ELEMENT_DEBUG */
    }
}

/**
 * @brief Adjust elements in grid, will resize if applicable
 */
void GUI_Grid::adjust_elements()
{
    if (elements.size() == 0)
    {
        return;
    }

    if (attributes & GRID_ATTRIBUTE_FLEX)
    {
        col_widths.clear();
        row_heights.clear();
        resize_elements();
    }

    adjust_x_y();
    adjust_sub_grids();
}

/**
 * @brief Apply colour scheme to elements.
 */
void GUI_Grid::apply_colour_scheme()
{
    if (is_colour_scheme_set())
    {
        for (uint16_t x = 0; x < elements.size(); x++)
        {
            if (elements[x]->get_type() == GUI_Element::Element_Type::GRID)
            {
                GUI_Grid *grid_element = static_cast<GUI_Grid *>(elements[x]);

                grid_element->set_colour_scheme(get_colour_scheme());

                grid_element->apply_colour_scheme();
            }
            else
            {
                elements[x]->set_colour_scheme(get_colour_scheme());
            }
        }
    }
}

/**
 * @brief Add element to grid
 *
 * @param element Element to add to grid
 */
void GUI_Grid::add_element(GUI_Element *element)
{
    if (element->get_type() == GUI_Element::Element_Type::MENU)
    {
        return;
    }

    if (is_colour_scheme_set() && !element->is_colour_scheme_set())
    {
        element->set_colour_scheme(get_colour_scheme());
    }

    if (element->is_interactable())
    {
        if (first_interactable_element_index == -1)
        {
            first_interactable_element_index = elements.size();
            last_interactable_element_index = first_interactable_element_index;
        }
        else
        {
            last_interactable_element_index = elements.size();
        }
    }

    if (element->get_width() == 0)
    {
        element->set_width_auto_sizeable(true);
    }

    if (element->get_height() == 0)
    {
        element->set_height_auto_sizeable(true);
    }

    if (element->get_type() == GUI_Element::Element_Type::GRID)
    {
        if (is_font_size_set() && !element->is_font_size_set())
        {
            element->set_font_size(get_font_size());
        }
        element->set_font_colour(get_font_colour());
    }

    if (grid_type == GRID_TYPE_HORIZONTAL)
    {
        columns = elements.size() + 1;
    }

    element->parent = this;
    elements.push_back(element);

    adjust_elements();

    refresh = true;
}

/**
 * @brief Set grid top border padding
 *
 * @param border_padding Padding in px
 */
void GUI_Grid::set_top_border_padding(uint16_t border_padding)
{
    top_border_padding = border_padding;
}

/**
 * @brief Set grid bottom border padding
 *
 * @param border_padding Padding in px
 */
void GUI_Grid::set_bottom_border_padding(uint16_t border_padding)
{
    bottom_border_padding = border_padding;
}

/**
 * @brief Set grid left border padding
 *
 * @param border_padding Padding in px
 */
void GUI_Grid::set_left_border_padding(uint16_t border_padding)
{
    left_border_padding = border_padding;
}

/**
 * @brief Set grid right border padding
 *
 * @param border_padding Padding in px
 */
void GUI_Grid::set_right_border_padding(uint16_t border_padding)
{
    right_border_padding = border_padding;
}

/**
 * @brief Reset selected elements
 *
 */
void GUI_Grid::deselect_elements()
{
    for (uint16_t x = 0; x < elements.size(); x++)
    {
        if (elements[x]->get_type() == GUI_Element::Element_Type::GRID)
        {
            GUI_Grid *grid_element = static_cast<GUI_Grid *>(elements[x]);

            grid_element->deselect_elements();
        }
        else
        {
            elements[x]->deselect();
        }
    }
}

/**
 * @brief Reselect selected elements
 *
 */
void GUI_Grid::select_elements()
{
    if (selected_element == -1)
    {
        return;
    }

    if (elements[selected_element]->get_type() == GUI_Element::Element_Type::GRID)
    {
        GUI_Grid *grid_element = static_cast<GUI_Grid *>(elements[selected_element]);

        grid_element->select_elements();
    }
    else
    {
        elements[selected_element]->select();
    }
}

bool GUI_Grid::end_of_interactable_elements()
{
    if (selected_element == -1 || selected_element > elements.size())
    {
        return false;
    }

    if (last_interactable_element_index == -1)
    {
        return true;
    }

    if (selected_element == last_interactable_element_index)
    {
        if (elements[selected_element]->get_type() == GUI_Element::Element_Type::GRID)
        {
            GUI_Grid *grid_element = static_cast<GUI_Grid *>(elements[selected_element]);

            return grid_element->end_of_interactable_elements();
        }
        else
        {
            return true;
        }
    }

    return false;
}

bool GUI_Grid::start_of_interactable_elements()
{
    if (selected_element == -1 || selected_element > elements.size())
    {
        return false;
    }

    if (first_interactable_element_index == -1)
    {
        return true;
    }

    if (selected_element == first_interactable_element_index)
    {
        if (elements[selected_element]->get_type() == GUI_Element::Element_Type::GRID)
        {
            GUI_Grid *grid_element = static_cast<GUI_Grid *>(elements[selected_element]);

            return grid_element->start_of_interactable_elements();
        }
        else
        {
            return true;
        }
    }

    return false;
}

int16_t GUI_Grid::get_next_interactable_element()
{
    GUI_Element *e = NULL;
    int16_t val = selected_element;
    uint16_t count = elements.size();

    if (elements.size() == 0)
    {
        return -1;
    }

    val++;
    val %= elements.size();

    while (count > 0)
    {
        e = elements[val];

        if (e->is_interactable() && !e->is_hidden())
        {
            if (e->get_type() == GUI_Element::Element_Type::GRID)
            {
                GUI_Grid *grid_element = static_cast<GUI_Grid *>(e);

                if (grid_element->first_interactable_element_index != -1)
                {
                    return val;
                }
            }
            else
            {
                break;
            }
        }

        val++;
        val %= elements.size();
        count--;
    }

    if (val == selected_element)
    {
        return -1;
    }

    return val;
}

int16_t GUI_Grid::get_prev_interactable_element()
{
    GUI_Element *e = NULL;
    int16_t val = selected_element;
    uint16_t count = elements.size();

    if (elements.size() == 0)
    {
        return -1;
    }

    val--;

    if (val < 0)
    {
        val = elements.size() - 1;
    }

    while (count > 0)
    {
        e = elements[val];

        if (e->is_interactable() && !e->is_hidden())
        {
            if (e->get_type() == GUI_Element::Element_Type::GRID)
            {
                GUI_Grid *grid_element = static_cast<GUI_Grid *>(e);

                if (grid_element->first_interactable_element_index != -1)
                {
                    return val;
                }
            }
            else
            {
                break;
            }
        }

        val--;
        if (val < 0)
        {
            val = elements.size() - 1;
        }
        count--;
    }

    if (val == selected_element)
    {
        return -1;
    }

    return val;
}
