#pragma once
#include <random>

class RandomNumberGenerator {
public:
    RandomNumberGenerator() : gen(std::random_device{}()) {}

    void addRange(const uint8_t low, const uint8_t high) {
        low_value = low;
        high_value = high;
    }

    [[nodiscard]] uint8_t generateRandomNumber() {
        std::uniform_int_distribution<> dist(low_value, high_value);
        const auto random_value = static_cast<uint8_t>(dist(gen));

        return random_value;
    }

private:
    uint8_t low_value = 0;
    uint8_t high_value = 255;
    std::mt19937 gen;
};
