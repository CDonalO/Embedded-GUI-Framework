#include "GUI.h"

GUI_Grid::GUI_Grid(GRID_TYPE type, uint16_t border_padding, uint16_t _element_padding, uint8_t grid_attributes)
{
    top_border_padding = border_padding;
    bottom_border_padding = border_padding;
    right_border_padding = border_padding;
    left_border_padding = border_padding;
    element_padding = _element_padding;
    grid_type = type;
    attributes = grid_attributes;
}

GUI_Grid::~GUI_Grid()
{
}

void GUI_Grid::draw(Adafruit_GFX *display)
{
    for (int x = 0; x < elements.size(); x++)
    {
        elements[x]->set_x_offset(get_x());
        elements[x]->set_y_offset(get_y());
        elements[x]->draw(display);
    }
}

bool GUI_Grid::navigate(int16_t x_pos, int16_t y_pos)
{
    for (int x = 0; x < elements.size(); x++)
    {
        if (elements[x]->within_bounds(x_pos, y_pos))
        {
            return elements[x]->navigate(x_pos, y_pos);
        }
    }

    return false;
}

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
            elements[0]->set_width(new_width);
            elements[0]->set_height(new_height);
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
            if (grid_type == GRID_TYPE_VERTICAL)
            {
                new_height /= (auto_sizeable_elements);
            }
            else if (grid_type == GRID_TYPE_HORIZONTAL)
            {
                new_width /= (auto_sizeable_elements);
            }
        }

        for (int x = 0; x < elements.size(); x++)
        {
            if (elements[x]->get_height_auto_sizeable())
            {
                elements[x]->set_height(new_height);
            }

            if (elements[x]->get_width_auto_sizeable())
            {
                elements[x]->set_width(new_width);
            }
        }
    }

    for (int x = 1; x < elements.size(); x++)
    {
        if (grid_type == GRID_TYPE_VERTICAL)
        {
            new_y += elements[x - 1]->get_height() + element_padding;
        }
        else if (grid_type == GRID_TYPE_HORIZONTAL)
        {
            new_x += elements[x - 1]->get_width() + element_padding;
        }

        elements[x]->set_x(new_x);
        elements[x]->set_y(new_y);
    }
}

void GUI_Grid::add_element(GUI_Element *element)
{
    if (element->get_width() == 0)
    {
        element->set_width_auto_sizeable(true);
    }

    if (element->get_height() == 0)
    {
        element->set_height_auto_sizeable(true);
    }

    elements.push_back(element);

    adjust_elements();
}

void GUI_Grid::set_top_border_padding(uint16_t border_padding)
{
    top_border_padding = border_padding;
}

void GUI_Grid::set_bottom_border_padding(uint16_t border_padding)
{
    bottom_border_padding = border_padding;
}

void GUI_Grid::set_left_border_padding(uint16_t border_padding)
{
    left_border_padding = border_padding;
}

void GUI_Grid::set_right_border_padding(uint16_t border_padding)
{
    right_border_padding = border_padding;
}
