#pragma once
#include <vector>

#include "config_hardware.hpp"
#include "utils/Vector2.hpp"

class Screen {
public:
    explicit Screen(const Vector2<uint16_t> screen_size) : pos1(Vector2<uint16_t>(0, 0)), pos2(Vector2<uint16_t>(0, 0)), screen_size(screen_size) {
        screen_buffer.resize(screen_size.x * screen_size.y, false);
        displayed_screen.resize(screen_size.x * screen_size.y, false);
    }

    void addX1(const uint8_t high_x, const uint8_t low_x) {
        pos1.x = (high_x << AMOUNT_BITS_PER_CELL) + low_x;
    }

    void addY1(const uint8_t high_y, const uint8_t low_y) {
        pos1.y = (high_y << AMOUNT_BITS_PER_CELL) + low_y;
    }

    void addX2(const uint8_t high_x, const uint8_t low_x) {
        pos2.x = (high_x << AMOUNT_BITS_PER_CELL) + low_x;
    }

    void addY2(const uint8_t high_y, const uint8_t low_y) {
        pos2.y = (high_y << AMOUNT_BITS_PER_CELL) + low_y;
    }

    void drawPixel() {
        screen_buffer[getPixelIndexFrom2D(pos1.x, pos1.y)] = true;
    }

    void drawRectangle() {
        changePixelRectangle(pos1, pos2, true);
    }

    void clearPixel() {
        screen_buffer[getPixelIndexFrom2D(pos1.x, pos1.y)] = false;
    }

    void clearRectangle() {
        changePixelRectangle(pos1, pos2, false);
    }

    void clearScreen() {
        for (auto &&pixel : screen_buffer) {
            pixel = false;
        }
    }

    void pushBuffer() {
        displayed_screen = screen_buffer;
    }

    [[nodiscard]] std::vector<bool>& getDisplayedScreen() { return displayed_screen; }

    [[nodiscard]] int getPixelIndexFrom2D(const uint16_t x, const uint16_t y) const {
        return y * screen_size.x + x;
    }

    [[nodiscard]] Vector2<uint16_t>& getScreenSize() { return screen_size; }

    void changePixelRectangle(const Vector2<uint16_t> pos1_rect, const Vector2<uint16_t> pos2_rect, const bool value_to_assign) {
        for (uint16_t x = pos1_rect.x; x <= pos2_rect.x; ++x) {
            for (uint16_t y = pos1_rect.y; y <= pos2_rect.y; ++y) {
                screen_buffer[getPixelIndexFrom2D(x, y)] = value_to_assign;
            }
        }
    }

private:
    Vector2<uint16_t> pos1;
    Vector2<uint16_t> pos2;
    Vector2<uint16_t> screen_size;

    std::vector<bool> screen_buffer;
    std::vector<bool> displayed_screen;
};
