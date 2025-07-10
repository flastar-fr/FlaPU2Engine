#pragma once
#include <random>

class RandomNumberGenerator {
public:
    static uint8_t generateRandomNumber() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 255);

        const auto random_value = static_cast<uint8_t>(dist(gen));

        return random_value;
    }
};
