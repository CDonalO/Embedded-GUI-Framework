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
        DATA_TYPE_DATE,
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

    PLATFORM_STRING get_data() { return data; };
    void set_data(PLATFORM_STRING data) { this->data = data; };

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

    int32_t get_data() { return data; };
    void set_data(int32_t data) { this->data = data; };

    Form_Data::Data_Type get_data_type() override { return Form_Data::Data_Type::DATA_TYPE_NUMBER; }
    void set_form_id(PLATFORM_STRING id) override;
};

class Form_Data_Date : public Form_Data
{
private:
    uint8_t day;
    uint8_t month;
    uint16_t year;

public:
    Form_Data_Date(uint8_t day, uint8_t month, uint16_t year) : day(day), month(month), year(year) {};
    Form_Data_Date() : Form_Data_Date(0, 0, 0) {};
    ~Form_Data_Date() {};

    void set_day(uint8_t day) { this->day = day; };
    void set_month(uint8_t month) { this->month = month; };
    void set_year(uint16_t year) { this->year = year; };

    uint8_t get_day() { return day; };
    uint8_t get_month() { return month; };
    uint16_t get_year() { return year; };

    Form_Data::Data_Type get_data_type() override { return Form_Data::Data_Type::DATA_TYPE_DATE; }
    void set_form_id(PLATFORM_STRING id) override;
};
