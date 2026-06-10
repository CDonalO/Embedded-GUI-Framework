#pragma once

#include "Form_Data.h"
#include <map>

class Form_Data_Register
{
private:
    Form_Data_Register() = default;
    std::map<PLATFORM_STRING, Form_Data *> form_data;

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

    static void register_form_data_by_id(PLATFORM_STRING id, Form_Data *data)
    {
        getInstance()._register_form_data_by_id(id, data);
    }
};
