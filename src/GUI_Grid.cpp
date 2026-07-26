#include "GUI_Grid.h"

#include <cmath>

GUI_Grid::GUI_Grid(GRID_TYPE type, uint16_t border_padding, uint16_t element_padding, uint8_t grid_attributes, uint16_t columns) : GUI_Element(), columns(columns), grid_type(type), attributes(grid_attributes)
{
    this->element_padding = element_padding;
    set_padding(border_padding, border_padding, border_padding, border_padding);
    selected_element = -1;
    first_interactable_element_index = -1;
    last_interactable_element_index = -1;
    rows = 0;
    set_interactable(true);
}

GUI_Grid::~GUI_Grid()
{
    for (Grid_Element *e : elements)
    {
        delete e;
    }

    elements.clear();
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

    for (Grid_Element *g : elements)
    {
        GUI_Element *e = g->get_element();

        e->draw(display);
        e->set_refresh(false, false);
    }

#ifdef VISUAL_ELEMENT_DEBUG
    display->draw_line(get_x(), get_center_y(), get_x() + get_width(), get_center_y(), RED);
    display->draw_line(get_center_x(), get_y(), get_center_x(), get_y() + get_height(), RED);
#endif /* VISUAL_ELEMENT_DEBUG */
}

void GUI_Grid::navigate(int16_t x_pos, int16_t y_pos)
{
    for (Grid_Element *g : elements)
    {
        GUI_Element *e = g->get_element();
        if (e->within_bounds(x_pos, y_pos))
        {
            e->navigate(x_pos, y_pos);
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
            elements[selected_element]->get_element()->navigate(input, key);
        }
        return;
    }

    int16_t new_selected_element = -1;
    if (selected_element != -1 && elements[selected_element]->get_element()->is_interactable())
    {
        if (elements[selected_element]->get_element()->get_type() == GUI_Element::Element_Type::GRID || elements[selected_element]->get_element()->get_type() == GUI_Element::Element_Type::DATE_PICKER)
        {
            GUI_Grid *grid_element = static_cast<GUI_Grid *>(elements[selected_element]->get_element());

            if (grid_element->first_interactable_element_index != -1)
            {
                if (input == INPUT_UP && !grid_element->start_of_interactable_elements())
                {
                    elements[selected_element]->get_element()->navigate(input, key);
                    in_grid = false;
                }
                else if (input == INPUT_DOWN && !grid_element->end_of_interactable_elements())
                {
                    elements[selected_element]->get_element()->navigate(input, key);
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
                elements[selected_element]->get_element()->deselect();
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

        if (elements[selected_element]->get_element()->get_type() == GUI_Element::Element_Type::GRID)
        {
            GUI_Grid *grid_element = static_cast<GUI_Grid *>(elements[selected_element]->get_element());

            if (input == INPUT_UP)
            {
                if (grid_element->selected_element != grid_element->last_interactable_element_index)
                {
                    elements[selected_element]->get_element()->navigate(input, key);
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
                    elements[selected_element]->get_element()->navigate(input, key);
                }
                else
                {
                    grid_element->select_elements();
                }
            }
        }
        else
        {
            elements[selected_element]->get_element()->select();
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
        for (Grid_Element *e : elements)
        {
            e->get_element()->set_refresh(r, false);
        }
    }
}

void GUI_Grid::calculate_sizing(display_driver *display)
{
    if (!refresh)
    {
        return;
    }

    adjust_elements();

    for (Grid_Element *g : elements)
    {
        GUI_Element *e = g->get_element();
        if (!e->is_font_size_set() && is_font_size_set())
        {
            e->set_font_size(get_font_size());
        }
        e->set_x_offset(get_x());
        e->set_y_offset(get_y());
        e->calculate_sizing(display);
    }

    uint16_t min_width = get_min_width_px();
    uint16_t min_height = get_min_height_px();

    if (get_max_width_px())
    {
        min_width = min(min_width, get_max_width_px());
    }

    if (get_max_height_px())
    {
        min_height = min(min_height, get_max_height_px());
    }

    set_min_width_px(min_width);
    set_min_height_px(min_height);
}

uint16_t GUI_Grid::get_column_width(uint16_t col)
{
    GUI_Element *e = NULL;
    uint16_t col_width = get_width() - get_left_padding() - get_right_padding();
    uint16_t total_min_col_width = 0;

    if (col < col_widths.size())
    {
        return col_widths[col];
    }

    if (elements.size() == 1)
    {
        total_min_col_width = elements[0]->get_element()->get_min_width_px();

        if (elements[0]->get_element()->get_max_width_px() != 0)
        {
            col_widths.push_back(elements[0]->get_element()->get_max_width_px());
        }
        else
        {
            col_widths.push_back(col_width);
        }

        set_min_width_px(total_min_col_width);

        return col_widths[0];
    }

    col_width -= (columns - 1) * element_padding;
    uint16_t standard_col_width = col_width / columns;
    uint16_t auto_sizeable_cols = columns;

    for (uint16_t x = 0; x < columns; x++)
    {
        col_widths.push_back(-1);
    }

    for (uint16_t x = 0; x < columns; x++)
    {
        bool uniform_col = true;
        bool hidden_col = true;
        uint16_t min_col_width = 0;
        uint32_t max_col_width = standard_col_width;

        for (uint16_t y = 0; y < rows; y++)
        {
            Grid_Element *g = get_grid_element(x, y);

            if (g != NULL)
            {
                e = g->get_element();

                if (hidden_col && !e->is_hidden())
                {
                    hidden_col = false;
                }

                if (!e->get_width_auto_sizeable())
                {
                    uniform_col = false;
                    max_col_width = min(max_col_width, (e->get_total_width() / g->get_col_span()));
                }
                else if (e->get_max_width_px() != 0 && max_col_width > e->get_max_width_px())
                {
                    uniform_col = false;
                    max_col_width = e->get_max_width_px();
                }
                else if (e->get_min_width_px() != 0 && max_col_width < e->get_min_width_px())
                {
                    uniform_col = false;
                    max_col_width = e->get_min_width_px();
                }

                min_col_width = max(min_col_width, e->get_min_width_px());
            }
        }

        if (hidden_col)
        {
            max_col_width = 0;
            min_col_width = 0;
            col_width += element_padding;
            uniform_col = false;
        }
        else
        {
            total_min_col_width += element_padding;
        }

        if (!uniform_col && columns > 1)
        {
            col_width -= max_col_width;
            col_widths[x] = max_col_width;

            auto_sizeable_cols--;

            if (auto_sizeable_cols > 0)
            {
                standard_col_width = col_width / auto_sizeable_cols;
            }
        }
        total_min_col_width += min_col_width;
    }

    for (uint16_t x = 0; x < columns; x++)
    {
        if (col_widths[x] == -1)
        {
            col_widths[x] = standard_col_width;
        }
    }

    total_min_col_width -= element_padding;

    set_min_width_px(total_min_col_width);

    return col_widths[col];
}

uint16_t GUI_Grid::get_row_height(uint16_t row)
{
    GUI_Element *e = NULL;
    uint16_t row_height = get_height() - get_top_padding() - get_bottom_padding();
    uint16_t total_min_row_height = 0;

    if (row < row_heights.size())
    {
        return row_heights[row];
    }

    if (elements.size() == 1)
    {
        total_min_row_height = elements[0]->get_element()->get_min_height_px();

        if (elements[0]->get_element()->get_max_height_px() != 0)
        {
            row_heights.push_back(elements[0]->get_element()->get_max_height_px());
        }
        else
        {
            row_heights.push_back(row_height);
        }

        set_min_height_px(total_min_row_height);

        return row_heights[0];
    }

    row_height -= (rows - 1) * element_padding;
    uint16_t standard_row_height = row_height / rows;
    uint16_t auto_sizeable_rows = rows;

    for (uint16_t x = 0; x < rows; x++)
    {
        row_heights.push_back(-1);
    }

    for (uint16_t x = 0; x < rows; x++)
    {
        bool uniform_row = true;
        bool hidden_row = true;
        uint32_t max_row_height = standard_row_height;
        uint16_t min_row_height = 0;

        for (uint16_t y = 0; y < columns; y++)
        {
            Grid_Element *g = get_grid_element(y, x);

            if (g != NULL)
            {
                e = g->get_element();

                if (hidden_row && !e->is_hidden())
                {
                    hidden_row = false;
                }

                if (!e->get_height_auto_sizeable())
                {
                    uniform_row = false;
                    max_row_height = min(max_row_height, (e->get_total_height() / g->get_row_span()));
                }
                else if (e->get_max_height_px() != 0 && max_row_height > e->get_max_height_px())
                {
                    uniform_row = false;
                    max_row_height = e->get_max_height_px();
                }
                else if (e->get_min_height_px() != 0 && max_row_height < e->get_min_height_px())
                {
                    uniform_row = false;
                    max_row_height = e->get_min_height_px();
                }

                min_row_height = max(min_row_height, e->get_min_height_px());
            }
        }

        if (hidden_row)
        {
            max_row_height = 0;
            min_row_height = 0;
            row_height += element_padding;
            uniform_row = false;
        }
        else
        {
            total_min_row_height += element_padding;
        }

        if (!uniform_row && rows > 1)
        {
            row_height -= max_row_height;
            row_heights[x] = max_row_height;

            auto_sizeable_rows--;

            if (auto_sizeable_rows > 0)
            {
                standard_row_height = row_height / auto_sizeable_rows;
            }
        }

        total_min_row_height += min_row_height;
    }

    for (uint16_t x = 0; x < rows; x++)
    {
        if (row_heights[x] == -1)
        {
            row_heights[x] = standard_row_height;
        }
    }

    total_min_row_height -= element_padding;
    set_min_height_px(total_min_row_height);

    return row_heights[row];
}

bool GUI_Grid::can_grid_element_fit(uint16_t col, uint16_t row, uint16_t col_span, uint16_t row_span)
{
    if (col >= columns || col + col_span > columns)
    {
        return false;
    }

    for (Grid_Element *g : elements)
    {
        uint16_t g_col = g->get_current_col();
        uint16_t g_row = g->get_current_row();

        if (col >= g_col && col < (g_col + g->get_col_span()))
        {
            if (row >= g_row && row < (g_row + g->get_row_span()))
            {
                return false;
            }
        }
    }

    return true;
}

GUI_Grid::Grid_Element *GUI_Grid::get_grid_element(uint16_t col, uint16_t row)
{
    for (Grid_Element *g : elements)
    {
        uint16_t current_col = g->get_current_col();
        uint16_t current_row = g->get_current_row();

        if ((col >= current_col && col < (current_col + g->get_col_span())) && (row >= current_row && row < (current_row + g->get_row_span())))
        {
            return g;
        }
    }

    return NULL;
}

void GUI_Grid::set_grid_element_col_row(Grid_Element *g)
{
    if (elements.size() == 0)
    {
        g->set_current_col(0);
        g->set_current_row(0);
        rows++;
        return;
    }

    Grid_Element *prev_element = elements[elements.size() - 1];

    uint16_t current_col = prev_element->get_current_col() + prev_element->get_col_span();
    uint16_t current_row = prev_element->get_current_row();

    while (!can_grid_element_fit(current_col, current_row, g->get_col_span(), g->get_row_span()))
    {
        current_col++;

        if (current_col >= columns)
        {
            current_col = 0;
            current_row++;
        }
    }

    g->set_current_col(current_col);
    g->set_current_row(current_row);

    if (rows < g->get_current_row() + g->get_row_span())
    {
        rows = g->get_current_row() + g->get_row_span();
    }
}

uint16_t GUI_Grid::get_col_x(uint16_t col)
{
    uint16_t col_x = get_left_padding();

    for (uint16_t x = 0; x < col; x++)
    {
        if (col_widths[x] != 0)
        {
            col_x += col_widths[x] + element_padding;
        }
    }

    return col_x;
}

uint16_t GUI_Grid::get_row_y(uint16_t row)
{
    uint16_t row_x = get_top_padding();

    for (uint16_t x = 0; x < row; x++)
    {
        if (row_heights[x] != 0)
        {
            row_x += row_heights[x] + element_padding;
        }
    }

    return row_x;
}

void GUI_Grid::adjust_x_y()
{
    uint16_t new_y = 0;
    uint16_t new_x = 0;

    if (grid_type == GRID_TYPE_NONE && columns == 1)
    {
        return;
    }

    if (col_widths.size() != columns || row_heights.size() != rows)
    {
        return;
    }

    for (Grid_Element *g : elements)
    {
        GUI_Element *e = g->get_element();

        new_x = get_col_x(g->get_current_col());
        new_y = get_row_y(g->get_current_row());

        e->set_x(new_x);
        e->set_y(new_y);
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

    for (Grid_Element *g : elements)
    {
        GUI_Element *e = g->get_element();

        uint16_t current_col = g->get_current_col();
        uint16_t current_row = g->get_current_row();

        new_width = get_column_width(current_col);
        new_height = get_row_height(current_row);

        for (uint16_t x = 1; x < g->get_col_span(); x++)
        {
            new_width += get_column_width(current_col + x) + element_padding;
        }

        for (uint16_t x = 1; x < g->get_row_span(); x++)
        {
            new_height += get_row_height(current_row + x) + element_padding;
        }

        e = g->get_element();

        if (columns == 1 && e->get_max_width_px() != 0 && new_width > e->get_max_width_px())
        {
            new_width = e->get_max_width_px() - e->get_left_padding() - e->get_right_padding();
        }

        if (rows == 1 && e->get_max_height_px() != 0 && new_height > e->get_max_height_px())
        {
            new_height = e->get_max_height_px() - e->get_top_padding() - e->get_bottom_padding();
        }

        if (e->get_width_auto_sizeable())
        {
            new_width -= e->get_left_padding();
            new_width -= e->get_right_padding();
            if (new_width < e->get_min_width_px())
            {
                new_width = e->get_min_width_px();
            }
        }
        else
        {
            new_width = e->get_width();
            new_width -= e->get_left_padding();
            new_width -= e->get_right_padding();

            if (new_width < e->get_min_width_px())
            {
                new_width = e->get_min_width_px();
            }
        }

        e->set_width(new_width);

        if (e->get_height_auto_sizeable())
        {
            new_height -= e->get_top_padding();
            new_height -= e->get_bottom_padding();

            if (new_height < e->get_min_height_px())
            {
                new_height = e->get_min_height_px();
            }
        }
        else
        {
            new_height = e->get_height();
            new_height -= e->get_top_padding();
            new_height -= e->get_bottom_padding();

            if (new_height < e->get_min_height_px())
            {
                new_height = e->get_min_height_px();
            }
        }

        e->set_height(new_height);

        if (e->get_type() == GUI_Element::Element_Type::GRID)
        {
            GUI_Grid *grid_element = static_cast<GUI_Grid *>(e);

            grid_element->adjust_elements();
        }

#ifdef VERBOSE_ELEMENT_DEBUG
        PLATFORM_PRINTF("[%d] Setting new width %d, new height %d\n", 0, e->get_width(), e->get_height());
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
        set_refresh(true, false);
        col_widths.clear();
        row_heights.clear();
        resize_elements();
    }

    adjust_x_y();
}

/**
 * @brief Apply colour scheme to elements.
 */
void GUI_Grid::apply_colour_scheme()
{
    if (is_colour_scheme_set())
    {
        for (Grid_Element *g : elements)
        {
            GUI_Element *e = g->get_element();

            if (e->get_type() == GUI_Element::Element_Type::GRID)
            {
                GUI_Grid *grid_element = static_cast<GUI_Grid *>(e);

                grid_element->set_colour_scheme(get_colour_scheme());

                grid_element->apply_colour_scheme();
            }
            else
            {
                e->set_colour_scheme(get_colour_scheme());
            }
        }
    }
}

/**
 * @brief Get rows in grid
 *
 * @return Rows in grid
 */
uint16_t GUI_Grid::get_rows()
{
    return rows;
}

/**
 * @brief Clear elements in grid
 */
void GUI_Grid::clear()
{
    for (Grid_Element *e : elements)
    {
        delete e;
    }

    elements.clear();

    elements.shrink_to_fit();

    selected_element = -1;
    first_interactable_element_index = -1;
    last_interactable_element_index = -1;
    rows = 0;
}

void GUI_Grid::add_element(GUI_Element *element, uint16_t col_span, uint16_t row_span)
{
    if (col_span > columns)
    {
        col_span = columns;
    }

    if (element->get_type() == GUI_Element::Element_Type::MENU)
    {
        return;
    }

    Grid_Element *grid_e = new Grid_Element(element, col_span, row_span);

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
    element->increase_ref();

    set_grid_element_col_row(grid_e);

    elements.push_back(grid_e);

    refresh = true;
}

/**
 * @brief Add element to grid
 *
 * @param element Element to add to grid
 */
void GUI_Grid::add_element(GUI_Element *element)
{
    add_element(element, 1, 1);
}

/**
 * @brief Reset selected elements
 *
 */
void GUI_Grid::deselect_elements()
{
    for (Grid_Element *g : elements)
    {
        GUI_Element *e = g->get_element();

        if (e->get_type() == GUI_Element::Element_Type::GRID)
        {
            GUI_Grid *grid_element = static_cast<GUI_Grid *>(e);

            grid_element->deselect_elements();
        }
        else
        {
            e->deselect();
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

    if (elements[selected_element]->get_element()->get_type() == GUI_Element::Element_Type::GRID)
    {
        GUI_Grid *grid_element = static_cast<GUI_Grid *>(elements[selected_element]->get_element());

        grid_element->select_elements();
    }
    else
    {
        elements[selected_element]->get_element()->select();
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
        if (elements[selected_element]->get_element()->get_type() == GUI_Element::Element_Type::GRID)
        {
            GUI_Grid *grid_element = static_cast<GUI_Grid *>(elements[selected_element]->get_element());

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
        if (elements[selected_element]->get_element()->get_type() == GUI_Element::Element_Type::GRID)
        {
            GUI_Grid *grid_element = static_cast<GUI_Grid *>(elements[selected_element]->get_element());

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

    if (count == 0)
    {
        return -1;
    }

    val++;
    val %= elements.size();

    while (count > 0)
    {
        e = elements[val]->get_element();

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

    if (count == 0)
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
        e = elements[val]->get_element();

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
