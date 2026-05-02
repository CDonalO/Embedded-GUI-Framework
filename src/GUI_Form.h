#ifndef _GUI_Form_H_
#define _GUI_Form_H_

#include "GUI.h"

class GUI_Form : public GUI_Element
{
public:
    class Form_Number_Data
    {
    private:
        uint32_t id;
        int min;
        int max;
        int value;
        std::vector<GUI_Button *> modifying_buttons;

    public:
        Form_Number_Data(uint32_t _id);
        ~Form_Number_Data();

        uint32_t get_id();
        void set_min(int _min);
        void set_max(int _max);
        void set_value(int _value);
        int get_min();
        int get_max();
        int get_value();
        void create_value_modify_buttons();
        void create_toggle_modify_button();
        GUI_Button *get_modify_button(uint16_t n);
    };

    typedef bool (*form_value_update_fun)(std::vector<Form_Number_Data *> *data_stack, char *form_value);

private:
    std::vector<Form_Number_Data *> data_stack;
    form_value_update_fun value_update_cb;
    Form_Number_Data *get_data_by_id(uint16_t id);
    char *label[32];
    char *form_value[32];

public:
    GUI_Form(const char *_label, form_value_update_fun value_cb);
    ~GUI_Form();

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void set_refresh(bool r, bool p) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::FORM; }

    GUI_Element *clone() const { return new GUI_Form(*this); }

    static Form_Number_Data *get_form_data_by_id(std::vector<Form_Number_Data *> *data_stack, uint32_t id);
    Form_Number_Data *get_data_by_id(uint32_t id);

    void create_number_form_data(uint32_t id, int min, int max, int default_value);
    GUI_Button *get_number_form_button(uint32_t id, bool increase);

    void create_toggle_form_data(uint32_t id, bool default_value);
    GUI_Toggle_Button *get_toggle_form_button(uint32_t id);
};

#endif /* _GUI_Form_H_ */