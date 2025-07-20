#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <cstdint>
#include <ostream>

#include "../config/config_hardware.hpp"


enum class ValueType;

struct Token {
    Token(const uint8_t value, const ValueType value_type): value(value), value_type(value_type) {}

    uint8_t value;
    ValueType value_type;

    friend std::ostream& operator<<(std::ostream& lhs, const Token& t) {
        lhs << to_string(t);
        return lhs;
    }

    friend std::string to_string(const Token& token) {
        return "Token(" + to_string(token.value_type) + " : " + std::to_string(token.value) + ")";
    }
};

#endif //TOKEN_HPP
