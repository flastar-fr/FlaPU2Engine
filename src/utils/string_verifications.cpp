#include "string_verifications.hpp"

#include <algorithm>
#include <array>

#include "../config/config_hardware.hpp"

bool is_digits(const std::string& str) {
    return std::all_of(str.begin(), str.end(), isdigit);
}

bool is_immediate(const std::string& str) {
    if (str.empty()) return false;

    if (str[0] == '-') return is_digits(str.substr(1));

    return is_digits(str);
}

bool is_char(const std::string& str) {
    if (str.size() != 3) return false;

    if (str[0] != '\'' || str[2] != '\'') return false;

    return std::find(CHARS_MAPPING.begin(), CHARS_MAPPING.end(), str[1]) != CHARS_MAPPING.end();
}

bool is_register(const std::string& str) {
    return std::all_of(str.begin() + 1, str.end(), isdigit) && std::tolower(str[0]) == 'r';
}

bool is_register_value(const std::string& str) {
    if (!(str[0] == LEFT_REGISTER_VALUE_CHAR && str[str.size() - 1] == RIGHT_REGISTER_VALUE_CHAR)) return false;

    return is_register(str.substr(1, str.size() - 2));
}

bool is_flag(const std::string& str) {
    return find(AVAILABLE_FLAGS.begin(), AVAILABLE_FLAGS.end(), str) != AVAILABLE_FLAGS.end();
}

bool is_port(const std::string& str) {
    return std::all_of(str.begin() + 1, str.end(), isdigit) && std::tolower(str[0]) == 'p';
}
