#pragma once

#include "Form_Data.h"
#include "GUI_Button.h"
#include <map>
#include <set>

class Form_Data_Register
{
private:
    Form_Data_Register() = default;
    std::map<PLATFORM_STRING, Form_Data *> form_data;
    std::map<PLATFORM_STRING, std::set<GUI_Radio_Button *>> radio_button_groups;

    Form_Data *_get_form_data_by_id(PLATFORM_STRING id)
    {
        auto ret = form_data.find(id);

        if (ret != form_data.end())
        {
            return ret->second;
        }

        return NULL;
    }

    void _register_form_data_by_id(PLATFORM_STRING id, Form_Data *data)
    {
        Form_Data *form = _get_form_data_by_id(id);

        if (form == NULL)
        {
            form_data.insert({id, data});
        }
    }

    void _register_radio_button(PLATFORM_STRING group, GUI_Radio_Button *button)
    {
        auto ret = radio_button_groups.find(group);

        if (ret != radio_button_groups.end())
        {
            ret->second.insert(button);
        }
        else
        {
            radio_button_groups.insert({group, {button}});
        }
    }

    std::set<GUI_Radio_Button *> *_get_radio_buttons(PLATFORM_STRING group)
    {
        auto ret = radio_button_groups.find(group);

        if (ret != radio_button_groups.end())
        {
            return &ret->second;
        }

        return NULL;
    }

public:
    Form_Data_Register(const Form_Data_Register &) = delete;
    Form_Data_Register &operator=(const Form_Data_Register &) = delete;
    Form_Data_Register(Form_Data_Register &&) = delete;
    Form_Data_Register &operator=(Form_Data_Register &&) = delete;

    static Form_Data_Register &getInstance()
    {
        static Form_Data_Register instance;
        return instance;
    }

    static Form_Data *get_form_data_by_id(PLATFORM_STRING id)
    {
        return getInstance()._get_form_data_by_id(id);
    }

    static void register_radio_button(PLATFORM_STRING group, GUI_Radio_Button *button)
    {
        getInstance()._register_radio_button(group, button);
    }

    static std::set<GUI_Radio_Button *> *get_radio_buttons(PLATFORM_STRING group)
    {
        return getInstance()._get_radio_buttons(group);
    }

    static void register_form_data_by_id(PLATFORM_STRING id, Form_Data *data)
    {
        getInstance()._register_form_data_by_id(id, data);
    }
};
