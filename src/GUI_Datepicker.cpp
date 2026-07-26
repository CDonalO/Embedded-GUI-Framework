#include "GUI_Datepicker.h"

#ifdef GUI_DATE_PICKER_SUPPORT

#include <format>
#include <chrono>
#include <iostream>

#include "GUI_Label.h"
#include "GUI_Button.h"
#include "Form_Data_Register.h"

typedef struct set_date_cb
{
    GUI_Datepicker *datepicker;
    uint8_t _d;
    uint8_t _m;
    uint16_t _y;
} _set_date_cb;

uint8_t get_days_in_month(uint16_t year, uint8_t month)
{
    std::chrono::year y{year};
    std::chrono::month m{month};
    std::chrono::year_month_day_last ymdl = y / m / std::chrono::last;

    uint8_t days_in_month = static_cast<unsigned>(ymdl.day());

    return days_in_month;
}

uint8_t get_first_day_in_month(uint16_t year, uint8_t month)
{
    std::chrono::year y{year};
    std::chrono::month m{month};
    std::chrono::year_month_day first_day = y / m / 1d;
    std::chrono::weekday wd{std::chrono::sys_days{first_day}};

    return wd.c_encoding();
}

PLATFORM_STRING get_month_year_string(uint8_t month, uint16_t year)
{
    std::chrono::month m{month};

    return std::format("{:%B} {}", m, year);
}

bool set_day_button_cb(void *user_data)
{
    set_date_cb *set_date_data = (set_date_cb *)user_data;

    GUI_Datepicker *datepicker = set_date_data->datepicker;

    uint8_t current_month = datepicker->get_date_month();

    datepicker->set_day(set_date_data->_d);
    datepicker->set_month(set_date_data->_m);
    datepicker->set_year(set_date_data->_y);

    if (current_month != set_date_data->_m)
    {
        datepicker->set_date_year_month(set_date_data->_y, set_date_data->_m);
    }

    return false;
}

void GUI_Datepicker::free_date_cb_objs()
{
    for (uintptr_t p : date_cb_objs)
    {
        set_date_cb *e = reinterpret_cast<set_date_cb *>(p);
        free(e);
    }

    date_cb_objs.clear();
}

void GUI_Datepicker::add_day_button(uint8_t day_value, uint8_t month_value, uint16_t year_value, bool filler_day)
{
    PLATFORM_STRING day_str;

    set_date_cb *set_date_data = (set_date_cb *)malloc(sizeof(set_date_cb));

    day_str = std::format("{}", day_value);

    GUI_Button *l = NULL;

    if (filler_day)
    {
        l = new GUI_Button(BUTTON_NO_STYLE, day_str, 3);
    }
    else
    {
        l = new GUI_Radio_Button(day_str, radio_group_str);
        l->set_button_border_radius(3);
    }

    set_date_data->datepicker = this;
    set_date_data->_d = day_value;
    set_date_data->_m = month_value;
    set_date_data->_y = year_value;
    l->set_click_user_cb(set_day_button_cb, set_date_data);

    date_cb_objs.insert((uintptr_t)set_date_data);

    date_grid->add_element(l);
}

void get_previous_m_y(uint8_t current_month, uint16_t current_year, uint8_t *ret_month, uint16_t *ret_year)
{
    uint8_t prev_month = current_month - 1;
    uint16_t prev_year = current_year;

    if (current_month == 1)
    {
        prev_year--;
        prev_month = 12;
    }

    *ret_month = prev_month;
    *ret_year = prev_year;
}

void get_next_m_y(uint8_t current_month, uint16_t current_year, uint8_t *ret_month, uint16_t *ret_year)
{
    uint8_t next_month = current_month + 1;
    uint16_t next_year = current_year;

    if (current_month >= 12)
    {
        next_year++;
        next_month = 1;
    }

    *ret_month = next_month;
    *ret_year = next_year;
}

bool next_month_button_cb(void *user_data)
{
    GUI_Datepicker *d = (GUI_Datepicker *)user_data;
    uint8_t next_month;
    uint16_t next_year;

    get_next_m_y(d->get_date_month(), d->get_date_year(), &next_month, &next_year);

    d->set_date_year_month(next_year, next_month);
    return true;
}

bool prev_month_button_cb(void *user_data)
{
    GUI_Datepicker *d = (GUI_Datepicker *)user_data;
    uint8_t prev_month;
    uint16_t prev_year;

    get_previous_m_y(d->get_date_month(), d->get_date_year(), &prev_month, &prev_year);

    d->set_date_year_month(prev_year, prev_month);
    return true;
}

void GUI_Datepicker::setup_calendar_grid()
{
    static PLATFORM_STRING week_days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    uint8_t added_elements = 0;
    uint8_t x = 0;

    uint8_t next_month, prev_month;
    uint16_t next_year, prev_year;

    get_next_m_y(month, year, &next_month, &next_year);
    get_previous_m_y(month, year, &prev_month, &prev_year);

    date_grid->clear();

    std::set<GUI_Radio_Button *> *radio_buttons = Form_Data_Register::get_radio_buttons(radio_group_str);

    if (radio_buttons != NULL)
    {
        radio_buttons->clear();
    }

    GUI_Grid *navigation_grid = new GUI_Grid(GRID_TYPE_NONE, 0, 5, GRID_ATTRIBUTE_FLEX, 3);
    GUI_Label *month_label = new GUI_Label(get_month_year_string(month, year));
    GUI_Button *left_button = new GUI_Button(BUTTON_STYLE_LEFT_ARROW, "", 2, prev_month_button_cb, this);
    GUI_Button *right_button = new GUI_Button(BUTTON_STYLE_RIGHT_ARROW, "", 2, next_month_button_cb, this);

    left_button->set_max_width_px(50);
    right_button->set_max_width_px(50);

    navigation_grid->set_max_height_px(65);

    navigation_grid->add_element(left_button);
    navigation_grid->add_element(month_label);
    navigation_grid->add_element(right_button);

    date_grid->add_element(navigation_grid, 7, 1);

    for (PLATFORM_STRING day : week_days)
    {
        GUI_Label *day_label = new GUI_Label(day);
        day_label->set_font_colour(WHITE);
        date_grid->add_element(day_label);
    }

    uint8_t first_day_in_month = get_first_day_in_month(year, month);
    uint8_t days_in_prev_month = get_days_in_month(prev_year, prev_month);

    if (first_day_in_month != 0)
    {
        for (x = 1; x <= first_day_in_month; x++)
        {
            add_day_button(days_in_prev_month - first_day_in_month + x, prev_month, prev_year, true);
            added_elements++;
        }
    }
    else
    {
        for (x = 0; x < 7; x++)
        {
            add_day_button(days_in_prev_month - 6 + x, prev_month, prev_year, true);
            added_elements++;
        }
    }

    for (x = 1; x <= get_days_in_month(year, month); x++)
    {
        add_day_button(x, month, year, false);
        added_elements++;
    }

    uint16_t rows = date_grid->get_rows() - 2;

    if (rows != 7)
    {
        uint16_t filler_days = (7 * 7) - added_elements;
        for (x = 1; x <= filler_days; x++)
        {
            add_day_button(x, next_month, next_year, true);
        }
    }
}

GUI_Datepicker::GUI_Datepicker(uint16_t current_year, uint8_t current_month) : GUI_Element(), Form_Data_Date(1, current_month, current_year), year(current_year), month(current_month)
{
    date_grid = new GUI_Grid(GRID_TYPE_NONE, 3, 4, GRID_ATTRIBUTE_FLEX, 7);
    needs_update = false;
    setup_calendar_grid();

    radio_group_str = std::format("{}_date_picker", static_cast<void *>(this));
}

GUI_Datepicker::~GUI_Datepicker()
{
    free_date_cb_objs();
    delete date_grid;
}

void GUI_Datepicker::set_date_year_month(uint16_t year, uint8_t month)
{
    if (this->year != year)
    {
        needs_update = true;
    }

    this->year = year;

    if (this->month != month)
    {
        needs_update = true;
    }

    this->month = month;

    if (needs_update)
    {
        set_refresh(true, true);
    }
}

uint16_t GUI_Datepicker::get_date_year()
{
    return year;
}

uint8_t GUI_Datepicker::get_date_month()
{
    return month;
}

void GUI_Datepicker::draw(display_driver *display)
{
    if (!refresh)
    {
        return;
    }

    if (needs_update)
    {
        setup_calendar_grid();
        needs_update = false;
        set_refresh(true, false);
        calculate_sizing(display);
    }

    date_grid->set_x(get_x());
    date_grid->set_y(get_y());

    date_grid->draw(display);
}

void GUI_Datepicker::navigate(int16_t x_pos, int16_t y_pos)
{
    date_grid->navigate(x_pos, y_pos);
}

void GUI_Datepicker::navigate(INPUT_TYPE input, KEYBOARD_KEY key)
{
    date_grid->navigate(input, key);
}

void GUI_Datepicker::set_refresh(bool r, bool p)
{
    date_grid->set_refresh(r, p);

    if (p && parent != NULL)
    {
        parent->set_refresh(r, true);
    }
}

void GUI_Datepicker::calculate_sizing(display_driver *display)
{
    if (!refresh)
    {
        return;
    }

    date_grid->set_width(get_width());
    date_grid->set_height(get_height());
    date_grid->set_x(get_x());
    date_grid->set_y(get_y());
    date_grid->set_font_size(get_font_size());
    date_grid->set_colour_scheme(get_colour_scheme());
    date_grid->apply_colour_scheme();
    date_grid->calculate_sizing(display);
    set_min_height_px(date_grid->get_min_height_px());
    set_min_width_px(date_grid->get_min_width_px());
}

#endif /* GUI_DATE_PICKER_SUPPORT */
