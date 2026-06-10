#include "Form_Data.h"
#include "Form_Data_Register.h"

PLATFORM_STRING Form_Data_String::get_data()
{
    return data;
}

void Form_Data_String::set_data(PLATFORM_STRING data)
{
    this->data = data;
}

void Form_Data_String::set_form_id(PLATFORM_STRING id)
{
    this->id = id;
    Form_Data_Register::register_form_data_by_id(id, this);
}

int32_t Form_Data_Number::get_data()
{
    return data;
}

void Form_Data_Number::set_data(int32_t val)
{
    this->data = val;
}

void Form_Data_Number::set_form_id(PLATFORM_STRING id)
{
    this->id = id;
    Form_Data_Register::register_form_data_by_id(id, this);
}