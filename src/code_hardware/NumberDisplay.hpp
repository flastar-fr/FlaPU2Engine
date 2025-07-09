#pragma once
#include <cstdint>

class NumberDisplay {
public:
    void addNumber(const uint8_t high_value, const uint8_t low_value) {
        value = (high_value << AMOUNT_BITS_PER_CELL) + low_value;
    }

    void clear() {
        value = 0;
    }

    void print() {
        displayed_value = value;
    }

    [[nodiscard]] uint16_t getDisplayedNumber() const noexcept { return displayed_value; }

private:
    uint16_t value = 0;
    uint16_t displayed_value = 0;
};
