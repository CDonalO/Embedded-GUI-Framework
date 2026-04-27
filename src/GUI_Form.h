#ifndef _GUI_Form_H_
#define _GUI_Form_H_

#include "GUI.h"

class GUI_Form : public GUI_Element
{
private:
    form_data data;
    form_value_update_fun value_update_cb;
    form_number_data *get_data_by_id(uint16_t id);
    char *label[32];

public:
    GUI_Form(const char *_label, form_value_update_fun value_cb);
    ~GUI_Form();

    void draw(Adafruit_GFX *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void set_refresh(bool r) override;
    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::FORM; }

    void create_number_form_data(uint32_t id, int min, int max, int default_value);
    GUI_Button *get_number_form_button(uint32_t id, bool increase);

    void create_toggle_form_data(uint32_t id, bool default_value);
    GUI_Toggle_Button *get_toggle_form_button(uint32_t id);
};

#endif /* _GUI_Form_H_ */