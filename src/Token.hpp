#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <ostream>

#include "config.hpp"


enum class ValueType;

struct Token {
    Token(const uint8_t value, const ValueType value_type): value(value), value_type(value_type) {}

    uint8_t value;
    ValueType value_type;

    friend std::ostream& operator<<(std::ostream & lhs, const Token & t) {
        lhs << "Token(";
        lhs << t.value_type;
        lhs << " : ";
        lhs << static_cast<int>(t.value);
        lhs << ")";
        return lhs;
    }
};

#endif //TOKEN_HPP
