#include "Preprocessor.hpp"
#include "utils/string_manipulations.hpp"

#include <iostream>

#include "config.hpp"


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

std::pair<std::string, std::string> extract_definition(const std::string& line) {
    const auto splitted_line = split(line, " ");
    if (splitted_line.size() != 3) throw std::invalid_argument("Wrong definition format");

    return {splitted_line[1], splitted_line[2]};
}

std::vector<std::string>& Preprocessor::preprocess() {
    uniformize();
    findDefinition();
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

    lines = std::move(new_lines);
}

void Preprocessor::findDefinition() {
    std::vector<std::string> new_lines = {};
    for (auto& line : lines) {
        if (line.size() < DEFINITION_KEY_WORD.size()) {
            new_lines.push_back(line);
            continue;
        }

        if (line.substr(0, DEFINITION_KEY_WORD.size()) == DEFINITION_KEY_WORD) {
            auto [definition, value] = extract_definition(line);
            labels_n_definitions[definition] = value;
        } else {
            new_lines.push_back(line);
        }
    }

    lines = std::move(new_lines);
}

void Preprocessor::findLabels() {
    size_t amount_line = 0;
    for (auto& line: lines) {
        auto trimed_line = trim(line);

        if (trimed_line[0] == FIRST_LABEL_CHAR) {
            auto label = extract_label(trimed_line);
            labels_n_definitions[label] = std::to_string(amount_line);
        }

        line = std::move(trimed_line);
        ++amount_line;
    }
}

void Preprocessor::replaceLabels() {
    for (auto& line : lines) {
        for (auto const& [key, val] : labels_n_definitions) {
            replace_all(line, key, val);
        }
    }
}
