#include "Preprocessor.hpp"

#include <iostream>
#include <stdexcept>

#include "utils/string_manipulations.hpp"

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
    if (splitted_line.size() != 3) {
        std::cerr << "Wrong definition format, should follow : define <definition name> <definition value>" << std::endl;
        throw std::invalid_argument("Wrong definition format");
    }

    return {splitted_line[1], splitted_line[2]};
}

std::vector<std::string> extract_labels_and_find_next_line(std::string& trimmed_line, const std::vector<std::string>& lines, size_t& current_line) {
    std::vector<std::string> labels_to_add = {};
    auto label = extract_label(trimmed_line);
    labels_to_add.push_back(label);
    while (trimmed_line.empty() || trimmed_line[0] == FIRST_LABEL_CHAR) {
        if (trimmed_line.empty()) {
            ++current_line;
            trimmed_line = trim(lines[current_line]);
        } else {
            label = extract_label(trimmed_line);
            labels_to_add.push_back(label);
        }
    }

    return labels_to_add;
}

void remove_comments(std::string& line) {
    const size_t first_space = line.find(COMMENT_PREFIX);
    if (first_space == std::string::npos) {
        return;
    }

    line = line.substr(0, first_space - 1);
}

void merge_labels(std::string& trimmed_line, const std::vector<std::string>& lines, size_t& i) {
    if (trimmed_line[0] == FIRST_LABEL_CHAR) {
        auto labels_to_add = extract_labels_and_find_next_line(trimmed_line, lines, i);
        const auto temp_trimmed_line = trimmed_line;
        trimmed_line.clear();
        for (const auto& label_to_add : labels_to_add) {
            trimmed_line += label_to_add + " ";
        }
        trimmed_line += temp_trimmed_line;
        labels_to_add.clear();
    }
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

        remove_comments(trimmed_line);

        merge_labels(trimmed_line, lines, i);

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

        while (trimed_line[0] == FIRST_LABEL_CHAR) {
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
            replace_token(line, key, val);
        }
    }
}
