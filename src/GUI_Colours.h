#pragma once

#include "platform.h"

/// @brief Class for represeting RGB colours
class RGB
{
private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

public:
    /// @brief Constructor for RGB class
    /// @param r Red value
    /// @param g Green value
    /// @param b Blue value
    /// @param a Alpha value
    RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    /// @brief Constructor for RGB class
    /// @param r Red value
    /// @param g Green value
    /// @param b Blue value
    RGB(uint8_t r, uint8_t g, uint8_t b);

    /// @brief Constructor for RGB class
    /// @param hex_string Hex string value
    RGB(PLATFORM_STRING hex_string);

    /// @brief Constructor for RGB class
    RGB();

    /// @brief Constructor for RGB class
    /// @param c
    RGB(const RGB &c);

    ~RGB() {}

    RGB operator=(const RGB &c);

    /// @brief Get red value
    /// @return Red value
    uint8_t get_red();

    /// @brief Get green value
    /// @return Green value
    uint8_t get_green();

    /// @brief Get blue value
    /// @return Blue value
    uint8_t get_blue();

    /// @brief Get alpha value
    /// @return Alpha value
    uint8_t get_alpha();
};

/// @brief Class for storing an elements colour scheme
class GUI_Colour_Scheme
{
private:
    RGB background_colour;
    RGB active_background_colour;
    RGB trim_colour;
    RGB active_trim_colour;
    RGB font_colour;
    RGB active_font_colour;

    bool background_colour_set;
    bool active_background_colour_set;
    bool trim_colour_set;
    bool active_trim_colour_set;
    bool font_colour_set;
    bool active_font_colour_set;

public:
    GUI_Colour_Scheme(RGB background_colour, RGB active_background_colour, RGB trim_colour, RGB active_trim_colour, RGB font_colour, RGB active_font_colour);
    GUI_Colour_Scheme(RGB background_colour, RGB active_background_colour, RGB trim_colour, RGB active_trim_colour, RGB font_colour);
    GUI_Colour_Scheme(RGB background_colour, RGB active_background_colour, RGB trim_colour, RGB active_trim_colour);
    GUI_Colour_Scheme(RGB background_colour, RGB active_background_colour, RGB trim_colour);
    GUI_Colour_Scheme(RGB background_colour, RGB active_background_colour);
    GUI_Colour_Scheme(RGB background_colour);
    GUI_Colour_Scheme();

    ~GUI_Colour_Scheme() {}

    /// @brief Get colour schemes background colour
    /// @return RGB of background
    RGB get_background_colour();
    /// @brief Get colour schemes active background colour
    /// @return RGB of active background
    RGB get_active_background_colour();
    /// @brief Get colour schemes trim colour
    /// @return RGB of trim colour
    RGB get_trim_colour();
    /// @brief Get colour schemes active trim colour
    /// @return RGB of active trim colour
    RGB get_active_trim_colour();
    /// @brief Get colour schemes font colour
    /// @return RGB of font colour
    RGB get_font_colour();
    /// @brief Get colour schemes active font colour
    /// @return RGB of active font colour
    RGB get_active_font_colour();

    /// @brief Check if background colour has been set
    /// @return True if set otherwise false
    bool is_background_colour_set();
    /// @brief Check if active background colour has been set
    /// @return True if set otherwise false
    bool is_active_background_colour_set();
    /// @brief Check if trim colour has been set
    /// @return True if set otherwise false
    bool is_trim_colour_set();
    /// @brief Check if active trim colour has been set
    /// @return True if set otherwise false
    bool is_active_trim_colour_set();
    /// @brief Check if font colour has been set
    /// @return True if set otherwise false
    bool is_font_colour_set();
    /// @brief Check if active font colour has been set
    /// @return True if set otherwise false
    bool is_active_font_colour_set();
};
