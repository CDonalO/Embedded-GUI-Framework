#ifndef _GUI_Button_H_
#define _GUI_Button_H_

#include "GUI.h"

typedef enum
{
    BUTTON_NO_STYLE,
    BUTTON_ROUND_STYLE,
    BUTTON_ROUND_STYLE_UP_ARROW,
    BUTTON_ROUND_STYLE_DOWN_ARROW,
    BUTTON_ROUND_STYLE_LEFT_ARROW,
    BUTTON_ROUND_STYLE_RIGHT_ARROW,
    BUTTON_ICON_STYLE,
    BUTTON_SQUARE_STYLE,
} BUTTON_STYLE;

typedef enum
{
    TOGGLE_BUTTON_NO_STYLE,
    TOGGLE_BUTTON_ROUND_STYLE,
} TOGGLE_BUTTON_STYLE;

class GUI_Button : public GUI_Element
{
private:
    char *text[32];
    BUTTON_STYLE button_style;
    uint8_t border_radius;
    TEXT_ALIGN align_value;
    uint8_t *icon_bitmap;
    uint8_t icon_width;
    uint8_t icon_height;
    RGB icon_bg_colour;
    RGB disabled_bg_colour;
    RGB disabled_trim_colour;
    RGB disabled_text_colour;

protected:
    click_cb_fun click_cb;
    void *user_data;
    bool disabled;

public:
    GUI_Button(BUTTON_STYLE style, const char *button_str, click_cb_fun _click_cb = NULL, void *_user_data = NULL, TEXT_ALIGN _align = ALIGN_CENTER);
    ~GUI_Button();

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void set_refresh(bool r, bool p) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::BUTTON; }

    GUI_Element *clone() const { return new GUI_Button(*this); }

    void set_button_style(BUTTON_STYLE style);
    void set_button_str(const char *button_str);
    void set_icon_bitmap(uint8_t *_bitmap, uint8_t _width, uint8_t _height, RGB _icon_bg_colour);
    void set_click_user_cb(click_cb_fun _click_cb, void *_user_data);
    void set_disabled(bool disable);
    bool is_disabled();
    void set_disabled_colours(RGB _disabled_bg_colour, RGB _disabled_trim_colour, RGB _disabled_text_colour);
};

typedef void (*linked_button_update_fun)(GUI_Element *linked_element, bool toggle_value);

static void disable_on_toggle(GUI_Element *linked_element, bool toggle_value)
{
    GUI_Button *linked_button = NULL;

    if (linked_element->get_type() == GUI_Element::Element_Type::BUTTON || linked_element->get_type() == GUI_Element::Element_Type::TOGGLE_BUTTON)
    {
        linked_button = static_cast<GUI_Button *>(linked_element);
    }
    else
    {
        return;
    }

    if (toggle_value)
    {
        linked_button->set_disabled(true);
    }
    else
    {
        linked_button->set_disabled(false);
    }
}

static void enable_on_toggle(GUI_Element *linked_element, bool toggle_value)
{
    GUI_Button *linked_button = NULL;

    if (linked_element->get_type() == GUI_Element::Element_Type::BUTTON || linked_element->get_type() == GUI_Element::Element_Type::TOGGLE_BUTTON)
    {
        linked_button = static_cast<GUI_Button *>(linked_element);
    }
    else
    {
        return;
    }

    if (toggle_value)
    {
        linked_button->set_disabled(false);
    }
    else
    {
        linked_button->set_disabled(true);
    }
}

static void hide_on_toggle(GUI_Element *linked_element, bool toggle_value)
{
    if (toggle_value)
    {
        linked_element->hide();
    }
    else
    {
        linked_element->show();
    }
}

static void show_on_toggle(GUI_Element *linked_element, bool toggle_value)
{
    if (toggle_value)
    {
        linked_element->show();
    }
    else
    {
        linked_element->hide();
    }
}

static void select_on_toggle(GUI_Element *linked_element, bool toggle_value)
{
    if (toggle_value)
    {
        linked_element->select();
    }
    else
    {
        linked_element->deselect();
    }
}

static void deselect_on_toggle(GUI_Element *linked_element, bool toggle_value)
{
    if (toggle_value)
    {
        linked_element->deselect();
    }
    else
    {
        linked_element->select();
    }
}

class GUI_Toggle_Button : public GUI_Button
{
private:
    class Button_Links
    {
    private:
        std::vector<GUI_Element *> linked_elements;
        std::vector<linked_button_update_fun> linked_functions;

    public:
        Button_Links() {}
        ~Button_Links() {}

        void add_button_link(GUI_Element *element, linked_button_update_fun link_function)
        {
            linked_elements.push_back(element);
            linked_functions.push_back(link_function);
        }

        void trigger_links(bool toggle_value)
        {
            for (int x = 0; x < linked_elements.size(); x++)
            {
                GUI_Element *old_element = linked_elements[x]->clone();
                linked_functions[x](linked_elements[x], toggle_value);
                if (*old_element == *linked_elements[x])
                {
                    linked_elements[x]->set_refresh(true, false);
                }
                else
                {
                    linked_elements[x]->set_refresh(true, true);
                }

                delete old_element;
            }
        }
    };

    TOGGLE_BUTTON_STYLE button_style;
    bool value;
    RGB toggled_colour;
    RGB non_toggled_colour;
    RGB toggle_element_colour;
    Button_Links links;

public:
    GUI_Toggle_Button(TOGGLE_BUTTON_STYLE style, const char *button_str, click_cb_fun _click_cb = NULL, bool default_value = false, TEXT_ALIGN _align = ALIGN_CENTER);

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::TOGGLE_BUTTON; }

    GUI_Element *clone() const { return new GUI_Toggle_Button(*this); }

    void link_button_state(GUI_Element *element, linked_button_update_fun linked_function);
    void set_toggle_button_style(TOGGLE_BUTTON_STYLE style);
    void toggle();
    bool get_toggled();
    void set_toggled_colours(RGB _toggled_colour, RGB _non_toggled_colour, RGB _toggle_element_colour);
};

#endif /* _GUI_Button_H_ */
