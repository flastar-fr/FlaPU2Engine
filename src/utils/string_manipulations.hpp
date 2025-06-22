#ifndef STRING_MANIPULATIONS_HPP
#define STRING_MANIPULATIONS_HPP
#include <string>


std::string trim(const std::string &s);
std::string ltrim(const std::string &s);
std::string rtrim(const std::string &s);
std::vector<std::string> split(const std::string& s, const std::string& delimiter);
void replace_token(std::string& str, const std::string& from, const std::string& to);

#endif //STRING_MANIPULATIONS_HPP
