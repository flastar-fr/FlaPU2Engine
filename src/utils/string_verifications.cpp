#include "string_verifications.hpp"

#include <algorithm>

bool is_digits(const std::string &str) {
    return std::all_of(str.begin(), str.end(), isdigit);
}

bool is_register(const std::string &str) {

    return std::all_of(str.begin() + 1, str.end(), isdigit) && str[0] == 'r';
}
