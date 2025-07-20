#pragma once
#include <vector>

#include "../config/config_hardware.hpp"
#include "Pixel.hpp"
#include "utils/Vector2.hpp"

constexpr auto BLACK_PIXEL = Pixel(0, 0, 0);

class Screen {
public:
    explicit Screen(const Vector2<uint16_t> screen_size) : pos1(Vector2<uint16_t>(0, 0)), pos2(Vector2<uint16_t>(0, 0)),
                                                           screen_size(screen_size),
                                                           current_pixel_color(Pixel(0, 0, 0)) {
        screen_buffer.resize(screen_size.x * screen_size.y, Pixel(0, 0, 0));
        displayed_screen.resize(screen_size.x * screen_size.y, Pixel(0, 0, 0));
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

    void addColor(const uint8_t red, const uint8_t green, const uint8_t blue) {
        current_pixel_color = Pixel(red, green, blue);
    }

    void drawPixel() {
        screen_buffer[getPixelIndexFrom2D(pos1.x, pos1.y)] = current_pixel_color;
        is_buffer_empty = false;
    }

    void drawRectangle() {
        changePixelRectangle(pos1, pos2, current_pixel_color);
        is_buffer_empty = false;
    }

    void clearPixel() {
        screen_buffer[getPixelIndexFrom2D(pos1.x, pos1.y)] = BLACK_PIXEL;
    }

    void clearRectangle() {
        changePixelRectangle(pos1, pos2, BLACK_PIXEL);
    }

    void clearScreen() {
        for (auto&& pixel : screen_buffer) {
            pixel = BLACK_PIXEL;
        }
        is_buffer_empty = true;
    }

    void pushBuffer() {
        displayed_screen = screen_buffer;
        is_screen_empty = is_buffer_empty;
    }

    [[nodiscard]] std::vector<Pixel>& getDisplayedScreen() { return displayed_screen; }

    [[nodiscard]] int getPixelIndexFrom2D(const uint16_t x, const uint16_t y) const {
        return y * screen_size.x + x;
    }

    [[nodiscard]] Vector2<uint16_t>& getScreenSize() { return screen_size; }

    void changePixelRectangle(const Vector2<uint16_t> pos1_rect, const Vector2<uint16_t> pos2_rect,
                              const Pixel value_to_assign) {
        for (uint16_t x = pos1_rect.x; x <= pos2_rect.x; ++x) {
            for (uint16_t y = pos1_rect.y; y <= pos2_rect.y; ++y) {
                screen_buffer[getPixelIndexFrom2D(x, y)] = value_to_assign;
            }
        }
    }

    [[nodiscard]] bool getIsScreenEmpty() const {
        volatile bool tmp = is_screen_empty; // fix CLion complaining about an always true value
        return tmp;
    }

private:
    Vector2<uint16_t> pos1;
    Vector2<uint16_t> pos2;
    Vector2<uint16_t> screen_size;
    Pixel current_pixel_color;

    std::vector<Pixel> screen_buffer;
    std::vector<Pixel> displayed_screen;

    bool is_buffer_empty = true;
    bool is_screen_empty = true;
};
