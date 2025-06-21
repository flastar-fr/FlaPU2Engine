#include <string>
#include <algorithm>
#include <cctype>

std::string ltrim(const std::string &s) {
    auto start = std::find_if(s.begin(), s.end(), [](const unsigned char ch) {
        return !std::isspace(ch);
    });
    return {start, s.end()};
}

std::string rtrim(const std::string &s) {
    auto end = std::find_if(s.rbegin(), s.rend(), [](const unsigned char ch) {
        return !std::isspace(ch);
    }).base();
    return {s.begin(), end};
}

std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

void replace_all(std::string& str, const std::string& from, const std::string& to) {
    size_t start = 0;
    size_t pos = 0;
    while ((pos = str.find(from, start)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        start = pos + to.length();
    }
}