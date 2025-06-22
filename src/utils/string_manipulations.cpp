#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

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

std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
    size_t pos_start = 0;
    size_t pos_end;
    const size_t delim_len = delimiter.length();
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        std::string token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

void replace_token(std::string& str, const std::string& from, const std::string& to) {
    const std::string delimiter = " ";
    const auto tokens = split(str, delimiter);
    std::string new_str;
    for (auto& token : tokens) {
        if (token == from) {
            new_str += to;
            new_str += delimiter;
        } else {
            new_str += delimiter;
        }
    }

    str = new_str;
}