#include "GUI.h"

GUI_Form::GUI_Form(const char *_label, form_value_update_fun value_cb) : GUI_Element()
{
    value_update_cb = value_cb;
    strncpy((char *)label, _label, sizeof(label));
    memset(&data, 0, sizeof(form_data));
}

GUI_Form::~GUI_Form()
{
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
        strncpy((char *)old_value, (char *)data.form_value, sizeof(data.form_value));
        value_update_cb(&data);

        if (strcmp((char *)old_value, (char *)data.form_value))
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
            display->getTextBounds((char *)data.form_value, 0, 0, &temp, &temp, &text_width, &text_height);
            text_y = center_text_vertical((char *)data.form_value, get_height(), get_y(), display);
            uint16_t text_x = get_x() + get_width() - text_width - 10;
            display->setCursor(text_x, text_y);
            display->setTextColor(get_text_colour());
            // Draw a box over the old text to prevent needing to redraw the whole element.
            display->fillRoundRect(text_x - 4, get_y() + 2, (get_x() + get_width()) - text_x, get_height() - 4, 10, bg_color);
            display->println((char *)data.form_value);
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
    form_number_data *val = (form_number_data *)user_data;

    if (val->value >= val->max)
    {
        val->value = val->max;
    }
    else
    {
        val->value += 1;
    }

    return false;
}

bool decrement_value(void *user_data)
{
    form_number_data *val = (form_number_data *)user_data;
    if (val->value <= val->min)
    {
        val->value = val->min;
    }
    else
    {
        val->value += -1;
    }

    return false;
}

bool toggle_value(void *user_data)
{
    form_number_data *val = (form_number_data *)user_data;

    val->value = !val->value;

    return true;
}

form_number_data *GUI_Form::get_data_by_id(uint16_t id)
{
    for (int i = 0; i < data.data_stack.size(); i++)
    {
        form_number_data *v = data.data_stack[i];
        if (v->id == id)
        {
            return v;
        }
    }

    form_number_data *ret = (form_number_data *)malloc(sizeof(form_number_data));
    memset(ret, 0, sizeof(form_number_data));
    ret->id = id;

    data.data_stack.push_back(ret);

    return ret;
}

void GUI_Form::create_number_form_data(uint32_t id, int min, int max, int default_value)
{
    form_number_data *number_data = get_data_by_id(id);

    number_data->max = max;
    number_data->min = min;
    number_data->value = default_value;

    if (number_data->modifying_buttons.size() == 0)
    {
        GUI_Button *increase_button = new GUI_Button(BUTTON_ROUND_STYLE_UP_ARROW, "", increment_value, number_data);
        GUI_Button *decrease_button = new GUI_Button(BUTTON_ROUND_STYLE_DOWN_ARROW, "", decrement_value, number_data);
        number_data->modifying_buttons.push_back(increase_button);
        number_data->modifying_buttons.push_back(decrease_button);
    }
}

GUI_Button *GUI_Form::get_number_form_button(uint32_t id, bool increase)
{
    form_number_data *number_data = get_data_by_id(id);

    if (number_data->modifying_buttons.size() == 2)
    {
        if (increase)
        {
            return number_data->modifying_buttons[0];
        }
        else
        {
            return number_data->modifying_buttons[1];
        }
    }

    return NULL;
}

void GUI_Form::create_toggle_form_data(uint32_t id, bool default_value)
{
    form_number_data *number_data = get_data_by_id(id);

    number_data->max = 1;
    number_data->min = 0;
    number_data->value = default_value;

    if (number_data->modifying_buttons.size() == 0)
    {
        GUI_Toggle_Button *toggle_button = new GUI_Toggle_Button(TOGGLE_BUTTON_NO_STYLE, "");
        toggle_button->set_click_user_cb(toggle_value, number_data);
        number_data->modifying_buttons.push_back(toggle_button);
    }
}

GUI_Toggle_Button *GUI_Form::get_toggle_form_button(uint32_t id)
{
    form_number_data *number_data = get_data_by_id(id);

    if (number_data->modifying_buttons.size() == 1)
    {
        GUI_Button *btn = number_data->modifying_buttons[0];
        if (btn->get_type() == GUI_Element::Element_Type::TOGGLE_BUTTON)
        {
            GUI_Toggle_Button *toggle_btn = static_cast<GUI_Toggle_Button *>(btn);
            return toggle_btn;
        }
    }

    return NULL;
}
