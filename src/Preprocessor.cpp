#include "Preprocessor.hpp"
#include "utils/string_manipulations.hpp"

#include <iostream>


char FIRST_LABEL_CHAR = '.';

std::string extract_label(std::string& line) {
    const size_t first_space = line.find(' ');
    if (first_space == std::string::npos) {
        std::string label = line;
        line.clear();
        return label;
    }

    std::string label = line.substr(0, first_space);
    line = line.substr(first_space + 1);
    return label;
}

std::vector<std::string>& Preprocessor::preprocess() {
    uniformize();
    for (auto& line : lines) {
        std::cout << line << std::endl;
    }
    findLabels();
    replaceLabels();
    return lines;
}

void Preprocessor::uniformize() {
    std::vector<std::string> new_lines = {};
    for (size_t i = 0; i < lines.size(); ++i) {
        auto trimmed_line = trim(lines[i]);

        if (trimmed_line.empty()) continue;

        if (trimmed_line[0] == FIRST_LABEL_CHAR) {
            const auto label = extract_label(trimmed_line);
            while (trimmed_line.empty()) {
                ++i;
                trimmed_line = trim(lines[i]);
            }
            auto temp_trimmed_line = trimmed_line;
            trimmed_line = label;
            trimmed_line.append(" " + temp_trimmed_line);
        }

        new_lines.push_back(trimmed_line);
    }

    lines = new_lines;
}

void Preprocessor::findLabels() {
    size_t amount_line = 0;
    for (auto& line: lines) {
        auto trimed_line = trim(line);

        if (trimed_line[0] == FIRST_LABEL_CHAR) {
            auto label = extract_label(trimed_line);
            labels[label] = std::to_string(amount_line);
        }

        line = std::move(trimed_line);
        ++amount_line;
    }
}

void Preprocessor::replaceLabels() {
    for (auto& line : lines) {
        for (auto const& [key, val] : labels) {
            replace_all(line, key, val);
        }
    }
}
