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

/**
 * @brief Draw form
 *
 * @param display Display to draw form on
 */
void GUI_Form::draw(display_driver *display)
{
    uint16_t text_y = display->center_text_vertical((char *)label, get_height(), get_y());
    RGB trim_color = get_trim_colour();
    RGB bg_color = get_background_colour();
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
        display->draw_filled_round_rect(get_x(), get_y(), get_width(), get_height(), 10, trim_color);
        display->draw_filled_round_rect(get_x() + 1, get_y() + 1, get_width() - 2, get_height() - 2, 10, bg_color);
        display->set_text_colour(get_text_colour());
        display->draw_text(get_x() + 10, text_y, (char *)label);
    }

    if (!is_hidden())
    {
        if (update_value)
        {
            int16_t temp;
            uint16_t text_width, text_height;
            display->get_text_bounds((char *)form_value, 0, 0, &temp, &temp, &text_width, &text_height);
            text_y = display->center_text_vertical((char *)form_value, get_height(), get_y());
            uint16_t text_x = get_x() + get_width() - text_width - 10;
            display->set_text_colour(get_text_colour());
            // Draw a box over the old text to prevent needing to redraw the whole element.
            display->draw_filled_round_rect(text_x - 4, get_y() + 2, (get_x() + get_width()) - text_x, get_height() - 4, 10, bg_color);
            display->draw_text(text_x, text_y, (char *)form_value);
        }
    }

    refresh = false;
}

void GUI_Form::navigate(int16_t x_pos, int16_t y_pos)
{
}

/**
 * @brief Set form refresh value
 *
 * @param r Value to decide if form should be redrawn
 * @param p Value to decide if need to update parents refresh
 */
void GUI_Form::set_refresh(bool r, bool p)
{
    refresh = r;

    if (p && parent != NULL)
    {
        parent->set_refresh(r, p);
    }
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

GUI_Form::Form_Number_Data::Form_Number_Data(uint32_t id)
{
    this->id = id;
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

/**
 * @brief Get id of form number data
 *
 * @return Form number data id
 */
uint32_t GUI_Form::Form_Number_Data::get_id()
{
    return id;
}

/**
 * @brief Set form number data minimum value
 *
 * @param min Form number data minimum value
 */
void GUI_Form::Form_Number_Data::set_min(int min)
{
    this->min = min;
}

/**
 * @brief Set form number data maximum value
 *
 * @param max Form number data maximum value
 */
void GUI_Form::Form_Number_Data::set_max(int max)
{
    this->max = max;
}

/**
 * @brief Set form number data value
 *
 * @param value Form number data value
 */
void GUI_Form::Form_Number_Data::set_value(int value)
{
    this->value = value;
}

/**
 * @brief Get form number data maximum value
 *
 * @return Form number data maximum value
 */
int GUI_Form::Form_Number_Data::get_max()
{
    return max;
}

/**
 * @brief Get form number data minimum value
 *
 * @return Form number data minimum value
 */
int GUI_Form::Form_Number_Data::get_min()
{
    return min;
}

/**
 * @brief Get form number data value
 *
 * @return Form number data value
 */
int GUI_Form::Form_Number_Data::get_value()
{
    return value;
}

/**
 * @brief Create buttons to modify form number value
 */
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

/**
 * @brief Create toggle button to modify form number value
 */
void GUI_Form::Form_Number_Data::create_toggle_modify_button()
{
    if (modifying_buttons.size() == 0)
    {
        GUI_Toggle_Button *toggle_button = new GUI_Toggle_Button(TOGGLE_BUTTON_NO_STYLE, "");
        toggle_button->set_click_user_cb(toggle_value, this);
        modifying_buttons.push_back(toggle_button);
    }
}

/**
 * @brief Get button to modify form number value
 *
 * @param n array position of button
 * @return Form value modifying button
 */
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

/**
 * @brief Get form number data by id (External)
 *
 * @param data_stack Form's number data
 * @param id Form number data id
 * @return Form number data if id match or null
 */
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

/**
 * @brief Get form number data by id (Internal)
 *
 * @param id Form number data id
 * @return Form number data if id match or null
 */
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

/**
 * @brief Create form number data by id
 *
 * @param id Form number data id
 * @param min Form number data minimum value
 * @param max Form number data maximum value
 * @param default_value Form number data default value
 */
void GUI_Form::create_number_form_data(uint32_t id, int min, int max, int default_value)
{
    Form_Number_Data *number_data = get_data_by_id(id);

    number_data->set_max(max);
    number_data->set_min(min);
    number_data->set_value(default_value);
    number_data->create_value_modify_buttons();
}

/**
 * @brief Get button to modify form number data by id
 *
 * @param id Form number data id
 * @param increase If true get button to increase else decrease
 * @return Button that modifies form number data
 */
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

/**
 * @brief Create toggle form number data by id
 *
 * @param id Form number data id
 * @param default_value Form number data default value
 */
void GUI_Form::create_toggle_form_data(uint32_t id, bool default_value)
{
    Form_Number_Data *number_data = get_data_by_id(id);

    number_data->set_max(1);
    number_data->set_min(0);
    number_data->set_value(default_value);
    number_data->create_toggle_modify_button();
}

/**
 * @brief Get toggle button to modify form number data by id
 *
 * @param id Form number data id
 * @return Toggle button that modifies form number data
 */
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
