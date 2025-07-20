#pragma once
#include <cstdint>

struct Pixel {
    constexpr Pixel(const uint8_t red, const uint8_t green, const uint8_t blue) : red(red), green(green), blue(blue) {}

    uint8_t red;
    uint8_t green;
    uint8_t blue;
    bool operator==(const Pixel& pixel) const {
        return red ==  pixel.red && green == pixel.green && blue == pixel.blue;
    }
};