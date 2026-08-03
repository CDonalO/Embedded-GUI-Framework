#include "platform.h"

class Coordinates
{
private:
    int16_t x;
    int16_t y;

public:
    Coordinates();
    Coordinates(int16_t x, int16_t y);
    ~Coordinates();

    int16_t get_x() const;
    int16_t get_y() const;

    void set_x(int16_t x);
    void set_y(int16_t y);
};
