#pragma once

#include "GUI_Button.h"
#include "GUI_Label.h"

class GUI_Form : public GUI_Element
{
public:
    class Form_Data
    {
    private:
        uint16_t id;

    public:
        Form_Data(uint16_t id);
        ~Form_Data() {};

        enum class Form_Data_Type
        {
            STRING_DATA,
            NUMBER_DATA,
        };

        virtual Form_Data_Type get_type() = 0;

        uint16_t get_id();
    };
    class Form_Number_Data : public Form_Data
    {
    private:
        int min;
        int max;
        int value;
        std::vector<GUI_Button *> modifying_buttons;

    public:
        Form_Number_Data(uint16_t id);
        ~Form_Number_Data();

        Form_Data::Form_Data_Type get_type() override { return Form_Data::Form_Data_Type::NUMBER_DATA; }

        void set_min(int min);
        void set_max(int max);
        void set_value(int value);
        int get_min();
        int get_max();
        int get_value();
        void create_value_modify_buttons();
        void create_toggle_modify_button();
        GUI_Button *get_modify_button(uint16_t n);
    };

    class Form_String_Data : public Form_Data
    {
    private:
        GUI_Label *value;

    public:
        Form_String_Data(uint16_t id);
        ~Form_String_Data();

        Form_Data::Form_Data_Type get_type() override { return Form_Data::Form_Data_Type::STRING_DATA; }

        PLATFORM_STRING get_value();
        GUI_Label *get_input_label();
    };

    typedef bool (*form_value_update_fun)(std::vector<Form_Data *> *data_stack, char *form_value);

private:
    std::vector<Form_Data *> data_stack;
    form_value_update_fun value_update_cb;
    Form_Data *get_data_by_id(uint16_t id, GUI_Form::Form_Data::Form_Data_Type type);
    PLATFORM_STRING label;
    char *form_value[32];

public:
    GUI_Form(PLATFORM_STRING label, form_value_update_fun value_cb);
    ~GUI_Form();

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void navigate(INPUT_TYPE input, KEYBOARD_KEY key) override;
    void set_refresh(bool r, bool p) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::FORM; }

    GUI_Element *clone() const override { return new GUI_Form(*this); }

    static Form_Number_Data *get_number_form_data_by_id(std::vector<Form_Data *> *data_stack, uint16_t id);
    static Form_String_Data *get_string_form_data_by_id(std::vector<Form_Data *> *data_stack, uint16_t id);

    void create_number_form_data(uint16_t id, int min, int max, int default_value);
    GUI_Button *get_number_form_button(uint16_t id, bool increase);

    void create_toggle_form_data(uint16_t id, bool default_value);
    GUI_Toggle_Button *get_toggle_form_button(uint16_t id);

    void create_string_form_data(uint16_t id, PLATFORM_STRING placeholder, uint8_t text_size, RGB text_colour);
    GUI_Label *get_string_form_input(uint16_t id);
};
