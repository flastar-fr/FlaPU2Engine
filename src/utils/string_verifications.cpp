#include "string_verifications.hpp"

#include <algorithm>

bool is_digits(const std::string &str) {
    return std::all_of(str.begin(), str.end(), isdigit);
}

bool is_register(const std::string &str) {
    return std::all_of(str.begin() + 1, str.end(), isdigit) && str[0] == 'r';
}

bool is_register_value(const std::string &str) {
  if (!(str[0] == '[' && str[str.size() - 1] == ']')) return false;

  return is_register(str.substr(1, str.size() - 2));
}
