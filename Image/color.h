#pragma once

#include <cstdint>

struct Color {
    Color() = default;
    Color(uint8_t blue, uint8_t green, uint8_t red);
    uint8_t blue = 0;
    uint8_t green = 0;
    uint8_t red = 0;

    void ColorSetter(uint8_t blue_int, uint8_t green_inp, uint8_t red_inp);
};
