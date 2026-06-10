#pragma once

#include "platform.h"

class Form_Data
{
protected:
    PLATFORM_STRING id;

public:
    enum class Data_Type
    {
        DATA_TYPE_NONE,
        DATA_TYPE_STRING,
        DATA_TYPE_NUMBER,
    };

    Form_Data() {};
    virtual ~Form_Data() = default;

    virtual Data_Type get_data_type() = 0;
    virtual void set_form_id(PLATFORM_STRING id) = 0;
};

class Form_Data_String : public Form_Data
{
private:
    PLATFORM_STRING data;

public:
    Form_Data_String(PLATFORM_STRING data) : data(data) {};
    Form_Data_String() : Form_Data_String("") {};
    ~Form_Data_String() {};

    PLATFORM_STRING get_data();
    void set_data(PLATFORM_STRING data);

    Form_Data::Data_Type get_data_type() override { return Form_Data::Data_Type::DATA_TYPE_STRING; }
    void set_form_id(PLATFORM_STRING id) override;
};

class Form_Data_Number : public Form_Data
{
private:
    int32_t data;

public:
    Form_Data_Number(int32_t data) : data(data) {};
    Form_Data_Number() : Form_Data_Number(0) {};
    ~Form_Data_Number() {};

    int32_t get_data();
    void set_data(int32_t data);

    Form_Data::Data_Type get_data_type() override { return Form_Data::Data_Type::DATA_TYPE_NUMBER; }
    void set_form_id(PLATFORM_STRING id) override;
};