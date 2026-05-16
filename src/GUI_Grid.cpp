#include "GUI_Grid.h"

GUI_Grid::GUI_Grid(GRID_TYPE type, uint16_t border_padding, uint16_t element_padding, uint8_t grid_attributes)
{
    this->element_padding = element_padding;
    top_border_padding = border_padding;
    bottom_border_padding = border_padding;
    right_border_padding = border_padding;
    left_border_padding = border_padding;
    grid_type = type;
    attributes = grid_attributes;
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
    for (int x = 0; x < elements.size(); x++)
    {
        elements[x]->set_x_offset(get_x());
        elements[x]->set_y_offset(get_y());
        elements[x]->draw(display);
        elements[x]->set_refresh(false, false);
    }

#ifdef VISUAL_ELEMENT_DEBUG
    display->draw_line(get_x(), get_y() + (get_height() / 2), get_x() + get_width(), get_y() + (get_height() / 2), RED);
    display->draw_line(get_x() + (get_width() / 2), get_y(), get_x() + (get_width() / 2), get_y() + get_height(), RED);
#endif /* VISUAL_ELEMENT_DEBUG */
}

void GUI_Grid::navigate(int16_t x_pos, int16_t y_pos)
{
    for (int x = 0; x < elements.size(); x++)
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

    if (input == INPUT_ENTER || input == INPUT_KEYBOARD)
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
            elements[selected_element]->deselect();
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
        for (int x = 0; x < elements.size(); x++)
        {
            elements[x]->set_refresh(r, false);
        }
    }
}

/**
 * @brief Adjust elements in grid, will resize if applicable
 */
void GUI_Grid::adjust_elements()
{
    uint16_t new_y = top_border_padding;
    uint16_t new_x = left_border_padding;
    uint16_t new_width = get_width() - (left_border_padding + right_border_padding);
    uint16_t new_height = get_height() - (top_border_padding + bottom_border_padding);

    if (elements.size() == 0 || grid_type == GRID_TYPE_NONE)
    {
        return;
    }

    if (elements.size() == 1)
    {
        elements[0]->set_x(left_border_padding);
        elements[0]->set_y(top_border_padding);

        if (attributes & GRID_ATTRIBUTE_FLEX)
        {
            if (elements[0]->get_height_auto_sizeable())
            {
                if (elements[0]->get_max_height_px() != 0 && new_height > elements[0]->get_max_height_px())
                {
                    new_height = elements[0]->get_max_height_px();
                }
                elements[0]->set_height(new_height);
            }

            if (elements[0]->get_width_auto_sizeable())
            {
                if (elements[0]->get_max_width_px() != 0 && new_width > elements[0]->get_max_width_px())
                {
                    new_width = elements[0]->get_max_width_px();
                }
                elements[0]->set_width(new_width);
            }

            elements[0]->set_refresh(true, false);
        }
        return;
    }

    if (attributes & GRID_ATTRIBUTE_FLEX)
    {
        uint16_t auto_sizeable_elements = elements.size();

        if (grid_type == GRID_TYPE_VERTICAL)
        {
            new_height -= (elements.size() - 1) * element_padding;
        }
        else if (grid_type == GRID_TYPE_HORIZONTAL)
        {
            new_width -= (elements.size() - 1) * element_padding;
        }

        for (int x = 0; x < elements.size(); x++)
        {
            if (elements[x]->is_hidden())
            {
                auto_sizeable_elements--;
                continue;
            }

            if (grid_type == GRID_TYPE_VERTICAL)
            {
                if (!elements[x]->get_height_auto_sizeable())
                {
                    new_height -= elements[x]->get_height();
                    auto_sizeable_elements--;
                }
            }
            else if (grid_type == GRID_TYPE_HORIZONTAL)
            {
                if (!elements[x]->get_width_auto_sizeable())
                {
                    new_width -= elements[x]->get_width();
                    auto_sizeable_elements--;
                }
            }
        }

        if (auto_sizeable_elements > 0)
        {
            uint16_t new_element_height = new_height;
            uint16_t new_element_width = new_width;

            if (grid_type == GRID_TYPE_VERTICAL)
            {
                new_height /= (auto_sizeable_elements);
            }
            else if (grid_type == GRID_TYPE_HORIZONTAL)
            {
                new_width /= (auto_sizeable_elements);
            }

            for (int x = 0; x < elements.size(); x++)
            {
                if (elements[x]->is_hidden())
                {
                    continue;
                }

                if (grid_type == GRID_TYPE_VERTICAL && elements[x]->get_max_height_px() != 0 && new_height > elements[x]->get_max_height_px())
                {
                    auto_sizeable_elements--;
                    new_element_height -= elements[x]->get_max_height_px();
                    if (auto_sizeable_elements > 0)
                    {
                        new_height = new_element_height / auto_sizeable_elements;
                    }
                    else
                    {
                        new_height = new_element_height;
                    }
                }
                else if (grid_type == GRID_TYPE_HORIZONTAL && elements[x]->get_max_width_px() != 0 && new_width > elements[x]->get_max_width_px())
                {
                    auto_sizeable_elements--;
                    new_element_width -= elements[x]->get_max_width_px();
                    if (auto_sizeable_elements > 0)
                    {
                        new_width = new_element_width / auto_sizeable_elements;
                    }
                    else
                    {
                        new_width = new_element_width;
                    }
                }
            }
        }

        for (int x = 0; x < elements.size(); x++)
        {
            if (elements[x]->get_height_auto_sizeable())
            {
                if (elements[x]->get_max_height_px() != 0 && new_height > elements[x]->get_max_height_px())
                {
                    elements[x]->set_height(elements[x]->get_max_height_px());
                    if (grid_type == GRID_TYPE_HORIZONTAL && attributes & GRID_ATTRIBUTE_CENTER_FLEX)
                    {
                        uint16_t centered_y = top_border_padding + (get_height() / 2) - (elements[x]->get_height() / 2);
                        elements[x]->set_y(centered_y);
                    }
                }
                else
                {
                    elements[x]->set_height(new_height);
                }
            }

            if (elements[x]->get_width_auto_sizeable())
            {
                if (elements[x]->get_max_width_px() != 0 && new_width > elements[x]->get_max_width_px())
                {
                    elements[x]->set_width(elements[x]->get_max_width_px());
                    if (grid_type == GRID_TYPE_VERTICAL && attributes & GRID_ATTRIBUTE_CENTER_FLEX)
                    {
                        uint16_t centered_x = left_border_padding + (get_width() / 2) - (elements[x]->get_width() / 2);
                        elements[x]->set_x(centered_x);
                    }
                }
                else
                {
                    elements[x]->set_width(new_width);
                }
            }
#ifdef VERBOSE_ELEMENT_DEBUG
            PLATFORM_PRINTF("[%d] Setting new width %d, new height %d\n", x, elements[x]->get_width(), elements[x]->get_height());
#endif /* VERBOSE_ELEMENT_DEBUG */
        }
    }

    for (int x = 1; x < elements.size(); x++)
    {
        if (grid_type == GRID_TYPE_VERTICAL)
        {
            if (!elements[x - 1]->is_hidden())
            {
                new_y += elements[x - 1]->get_height() + element_padding;
            }
        }
        else if (grid_type == GRID_TYPE_HORIZONTAL)
        {
            if (!elements[x - 1]->is_hidden())
            {
                new_x += elements[x - 1]->get_width() + element_padding;
            }
        }

        elements[x]->set_x(new_x);
        elements[x]->set_y(new_y);
    }

    for (int x = 0; x < elements.size(); x++)
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
        element->set_font_size(get_font_size());
        element->set_font_colour(get_font_colour());
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
    for (int i = 0; i < elements.size(); i++)
    {
        if (elements[i]->get_type() == GUI_Element::Element_Type::GRID)
        {
            GUI_Grid *grid_element = static_cast<GUI_Grid *>(elements[i]);

            grid_element->deselect_elements();
        }
        else
        {
            elements[i]->deselect();
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

        if (e->is_interactable())
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

        if (e->is_interactable())
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
