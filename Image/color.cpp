#include "color.h"

Color::Color(uint8_t blue, uint8_t green, uint8_t red) : blue(blue), green(green), red(red) {
}

void Color::ColorSetter(uint8_t blue_inp, uint8_t green_inp, uint8_t red_inp) {
    blue = blue_inp;
    green = green_inp;
    red = red_inp;
}
