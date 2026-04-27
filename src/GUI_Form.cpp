#include "GUI.h"

GUI_Form::GUI_Form(const char *_label, form_value_update_fun value_cb) : GUI_Element()
{
    value_update_cb = value_cb;
    strncpy((char *)label, _label, sizeof(label));
}

GUI_Form::~GUI_Form()
{
    while (!data_stack.empty())
    {
        Form_Number_Data *d = data_stack[data_stack.size() - 1];
        data_stack.pop_back();

        delete d;
    }
}

void GUI_Form::draw(Adafruit_GFX *display)
{
    uint16_t text_y = center_text_vertical((char *)label, get_height(), get_y(), display);
    uint16_t trim_color = get_trim_colour();
    uint16_t bg_color = get_background_colour();
    bool update_value = false;

    if (refresh)
    {
        update_value = true;
    }

    if (value_update_cb != NULL)
    {
        char *old_value[32];
        strncpy((char *)old_value, (char *)form_value, sizeof(form_value));
        value_update_cb(&data_stack, (char *)form_value);

        if (strcmp((char *)old_value, (char *)form_value))
        {
            update_value = true;
        }
    }

    if (!is_hidden() && refresh)
    {
        display->fillRoundRect(get_x(), get_y(), get_width(), get_height(), 10, trim_color);
        display->fillRoundRect(get_x() + 1, get_y() + 1, get_width() - 2, get_height() - 2, 10, bg_color);
        display->setCursor(get_x() + 10, text_y);
        display->setTextColor(get_text_colour());
        display->println((char *)label);
    }

    if (!is_hidden())
    {
        if (update_value)
        {
            int16_t temp;
            uint16_t text_width, text_height;
            display->getTextBounds((char *)form_value, 0, 0, &temp, &temp, &text_width, &text_height);
            text_y = center_text_vertical((char *)form_value, get_height(), get_y(), display);
            uint16_t text_x = get_x() + get_width() - text_width - 10;
            display->setCursor(text_x, text_y);
            display->setTextColor(get_text_colour());
            // Draw a box over the old text to prevent needing to redraw the whole element.
            display->fillRoundRect(text_x - 4, get_y() + 2, (get_x() + get_width()) - text_x, get_height() - 4, 10, bg_color);
            display->println((char *)form_value);
        }
    }

    refresh = false;
}

void GUI_Form::navigate(int16_t x_pos, int16_t y_pos)
{
}

void GUI_Form::set_refresh(bool r)
{
    refresh = r;
}

bool increment_value(void *user_data)
{
    GUI_Form::Form_Number_Data *val = (GUI_Form::Form_Number_Data *)user_data;

    if (val->get_value() >= val->get_max())
    {
        val->set_value(val->get_max());
    }
    else
    {
        val->set_value(val->get_value() + 1);
    }

    return false;
}

bool decrement_value(void *user_data)
{
    GUI_Form::Form_Number_Data *val = (GUI_Form::Form_Number_Data *)user_data;
    if (val->get_value() <= val->get_min())
    {
        val->set_value(val->get_min());
    }
    else
    {
        val->set_value(val->get_value() - 1);
    }

    return false;
}

bool toggle_value(void *user_data)
{
    GUI_Form::Form_Number_Data *val = (GUI_Form::Form_Number_Data *)user_data;

    val->set_value(!val->get_value());

    return true;
}

GUI_Form::Form_Number_Data::Form_Number_Data(uint32_t _id)
{
    id = _id;
    min = 0;
    max = 0;
    value = 0;
}

GUI_Form::Form_Number_Data::~Form_Number_Data()
{
    while (!modifying_buttons.empty())
    {
        GUI_Button *b = modifying_buttons.back();
        modifying_buttons.pop_back();
        delete b;
    }
}

uint32_t GUI_Form::Form_Number_Data::get_id()
{
    return id;
}

void GUI_Form::Form_Number_Data::set_min(int _min)
{
    min = _min;
}

void GUI_Form::Form_Number_Data::set_max(int _max)
{
    max = _max;
}

void GUI_Form::Form_Number_Data::set_value(int _value)
{
    value = _value;
}

int GUI_Form::Form_Number_Data::get_max()
{
    return max;
}

int GUI_Form::Form_Number_Data::get_min()
{
    return min;
}

int GUI_Form::Form_Number_Data::get_value()
{
    return value;
}

void GUI_Form::Form_Number_Data::create_value_modify_buttons()
{
    if (modifying_buttons.size() == 0)
    {
        GUI_Button *increase_button = new GUI_Button(BUTTON_ROUND_STYLE_UP_ARROW, "", increment_value, this);
        GUI_Button *decrease_button = new GUI_Button(BUTTON_ROUND_STYLE_DOWN_ARROW, "", decrement_value, this);
        modifying_buttons.push_back(increase_button);
        modifying_buttons.push_back(decrease_button);
    }
}

void GUI_Form::Form_Number_Data::create_toggle_modify_button()
{
    if (modifying_buttons.size() == 0)
    {
        GUI_Toggle_Button *toggle_button = new GUI_Toggle_Button(TOGGLE_BUTTON_NO_STYLE, "");
        toggle_button->set_click_user_cb(toggle_value, this);
        modifying_buttons.push_back(toggle_button);
    }
}

GUI_Button *GUI_Form::Form_Number_Data::get_modify_button(uint16_t n)
{
    if (modifying_buttons.size() - 1 < n)
    {
        return NULL;
    }
    else
    {
        return modifying_buttons[n];
    }
}

GUI_Form::Form_Number_Data *GUI_Form::get_form_data_by_id(std::vector<Form_Number_Data *> *data_stack, uint32_t id)
{
    for (int x = 0; x < data_stack->size(); x++)
    {
        Form_Number_Data *v = data_stack->at(x);

        if (v->get_id() == id)
        {
            return v;
        }
    }

    return NULL;
}

GUI_Form::Form_Number_Data *GUI_Form::get_data_by_id(uint32_t id)
{
    for (int x = 0; x < data_stack.size(); x++)
    {
        Form_Number_Data *v = data_stack[x];
        if (v->get_id() == id)
        {
            return v;
        }
    }

    Form_Number_Data *ret = new Form_Number_Data(id);

    data_stack.push_back(ret);

    return ret;
}

void GUI_Form::create_number_form_data(uint32_t id, int min, int max, int default_value)
{
    Form_Number_Data *number_data = get_data_by_id(id);

    number_data->set_max(max);
    number_data->set_min(min);
    number_data->set_value(default_value);
    number_data->create_value_modify_buttons();
}

GUI_Button *GUI_Form::get_number_form_button(uint32_t id, bool increase)
{
    Form_Number_Data *number_data = get_data_by_id(id);

    if (increase)
    {
        return number_data->get_modify_button(0);
    }
    else
    {
        return number_data->get_modify_button(1);
    }

    return NULL;
}

void GUI_Form::create_toggle_form_data(uint32_t id, bool default_value)
{
    Form_Number_Data *number_data = get_data_by_id(id);

    number_data->set_max(1);
    number_data->set_min(0);
    number_data->set_value(default_value);
    number_data->create_toggle_modify_button();
}

GUI_Toggle_Button *GUI_Form::get_toggle_form_button(uint32_t id)
{
    Form_Number_Data *number_data = get_data_by_id(id);

    GUI_Button *btn = number_data->get_modify_button(0);
    if (btn != NULL && btn->get_type() == GUI_Element::Element_Type::TOGGLE_BUTTON)
    {
        GUI_Toggle_Button *toggle_btn = static_cast<GUI_Toggle_Button *>(btn);
        return toggle_btn;
    }

    return NULL;
}
