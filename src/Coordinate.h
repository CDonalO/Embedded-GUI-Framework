#include "platform.h"

/// @brief Class to store X and Y coordinates
class Coordinates
{
private:
    int16_t x;
    int16_t y;

public:
    /// @brief Coordinate constructor
    /// @param x X value
    /// @param y Y value
    Coordinates(int16_t x, int16_t y) : x(x), y(y) {}

    /// @brief Coordinate constructor
    Coordinates() : Coordinates(0, 0) {}

    ~Coordinates() {}

    /// @brief Get X value
    /// @return X value
    int16_t get_x() const
    {
        return x;
    }

    /// @brief Get Y value
    /// @return Y value
    int16_t get_y() const
    {
        return y;
    }

    /// @brief Set X value
    /// @param x
    void set_x(int16_t x)
    {
        this->x = x;
    }

    /// @brief Set Y value
    /// @param y
    void set_y(int16_t y)
    {
        this->y = y;
    }
};
