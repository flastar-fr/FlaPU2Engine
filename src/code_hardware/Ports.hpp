#pragma once
#include "NumberDisplay.hpp"
#include "Screen.hpp"
#include "TextDisplay.hpp"

struct Ports {
    explicit Ports(const Vector2<uint16_t> screen_size): screen(Screen(screen_size)) {}

    TextDisplay text_display;
    NumberDisplay number_display;
    Screen screen;
};
