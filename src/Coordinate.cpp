#include "Coordinate.h"

Coordinates::Coordinates(int16_t x, int16_t y) : x(x), y(y) {}

Coordinates::Coordinates() : Coordinates(0, 0) {}

Coordinates::~Coordinates() {}

int16_t Coordinates::get_x() const
{
    return x;
}

int16_t Coordinates::get_y() const
{
    return y;
}

void Coordinates::set_x(int16_t x)
{
    this->x = x;
}

void Coordinates::set_y(int16_t y)
{
    this->y = y;
}