#pragma once

#ifdef GUI_DATE_PICKER_SUPPORT

#include "GUI_Grid.h"
#include "Form_Data.h"
#include <set>

class GUI_Datepicker : public GUI_Element, public Form_Data_Date
{
private:
    uint8_t day;
    uint8_t month;
    uint16_t year;
    bool needs_update;
    GUI_Grid *date_grid;
    PLATFORM_STRING radio_group_str;

    std::set<std::uintptr_t> date_cb_objs;

    void free_date_cb_objs();

    void add_day_button(uint8_t day_value, uint8_t month_value, uint16_t year_value, bool filler_day);
    void setup_calendar_grid();

public:
    GUI_Datepicker(uint16_t current_year, uint8_t current_month);
    ~GUI_Datepicker();

    void set_date_year_month(uint16_t year, uint8_t month);
    uint16_t get_date_year();
    uint8_t get_date_month();

    GUI_Element::Element_Type get_type() override { return GUI_Element::Element_Type::DATE_PICKER; }
    GUI_Element *clone() const override { return new GUI_Datepicker(*this); }

    void draw(display_driver *display) override;
    void navigate(int16_t x_pos, int16_t y_pos) override;
    void navigate(INPUT_TYPE input, KEYBOARD_KEY key) override;
    void set_refresh(bool r, bool p) override;
    void calculate_sizing(display_driver *display) override;
};

#endif /* GUI_DATE_PICKER_SUPPORT */
