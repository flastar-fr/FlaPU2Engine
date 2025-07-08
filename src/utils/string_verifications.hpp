#ifndef STRING_VERIFICATIONS_HPP
#define STRING_VERIFICATIONS_HPP
#include <string>

bool is_digits(const std::string &str);
bool is_char(const std::string &str);
bool is_immediate(const std::string &str);
bool is_register(const std::string &str);
bool is_register_value(const std::string &str);
bool is_flag(const std::string &str);
bool is_port(const std::string &str);

#endif //STRING_VERIFICATIONS_HPP
