#include "Form_Data.h"
#include "Form_Data_Register.h"

void Form_Data_String::set_form_id(PLATFORM_STRING id)
{
    this->id = id;
    Form_Data_Register::register_form_data_by_id(id, this);
}

void Form_Data_Number::set_form_id(PLATFORM_STRING id)
{
    this->id = id;
    Form_Data_Register::register_form_data_by_id(id, this);
}

void Form_Data_Date::set_form_id(PLATFORM_STRING id)
{
    this->id = id;
    Form_Data_Register::register_form_data_by_id(id, this);
}