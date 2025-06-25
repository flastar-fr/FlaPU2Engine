#include "string_verifications.hpp"

#include <algorithm>
#include <array>

#include "config.hpp"

bool is_digits(const std::string &str) {
    return std::all_of(str.begin(), str.end(), isdigit);
}

bool is_immediate(const std::string &str) {
    if (str.empty()) return false;

    if (str[0] == '-') return is_digits(str.substr(1));

    return is_digits(str);
}

bool is_register(const std::string &str) {
    return std::all_of(str.begin() + 1, str.end(), isdigit) && std::tolower(str[0]) == 'r';
}

bool is_register_value(const std::string &str) {
  if (!(str[0] == '[' && str[str.size() - 1] == ']')) return false;

  return is_register(str.substr(1, str.size() - 2));
}

bool is_flag(const std::string &str) {
    return find(AVAILABLE_FLAGS.begin(), AVAILABLE_FLAGS.end(), str) != AVAILABLE_FLAGS.end();
}