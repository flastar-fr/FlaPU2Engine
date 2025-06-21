#ifndef STRING_MANIPULATIONS_HPP
#define STRING_MANIPULATIONS_HPP
#include <string>


std::string trim(const std::string &s);
std::string ltrim(const std::string &s);
std::string rtrim(const std::string &s);
void replace_all(std::string& str, const std::string& from, const std::string& to);
std::vector<std::string> split(const std::string& s, const std::string& delimiter);

#endif //STRING_MANIPULATIONS_HPP
