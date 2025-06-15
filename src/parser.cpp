#include "parser.hpp"

#include <memory>

#include <iostream>

#include "utils/string_verifications.hpp"


std::unique_ptr<Instruction> parse_line(const std::string& line) {
    size_t first_space = line.find_first_of(' ');
    first_space = first_space != std::string::npos ? first_space : line.size();
    const size_t start_operand = first_space == line.size() ? line.size() : first_space + 1;
    const std::string instruction_name = line.substr(0, first_space);

    if (instruction_factories.find(instruction_name) == instruction_factories.end())
        throw std::runtime_error("Unrecognized instruction: " + instruction_name);

    const std::vector<Token> operands = extract_operands(line.substr(start_operand));

    auto instruction = instruction_factories[instruction_name](operands);

    return instruction;
}

bool parse_lines(std::vector<std::unique_ptr<Instruction>>& instructions, const std::vector<std::string>& lines) {
    for (const auto& line : lines) {
        if (const std::unique_ptr<Instruction> instruction = parse_line(line); !instruction->isCorrect()) {
            std::cerr << "Error parsing instruction : " << line << std::endl;
            return false;
        }
        instructions.push_back(parse_line(line));
    }
    return true;
}

void fill_empty(std::vector<std::unique_ptr<Instruction>>& instructions, const int to_have) {
    while (instructions.size() < to_have) {
        instructions.push_back(parse_line("NOP"));
    }
}

std::vector<Token> extract_operands(const std::string& line) {
    std::vector<Token> tokens;
    std::string operand;

    if (line.empty()) return tokens;

    for (const auto current_char : line) {
        if (current_char != ' ') {
            operand += current_char;
        } else {
            const ValueType token_type = determine_operand_type(operand);
            const uint8_t token_value = determine_operand_value(operand, token_type);
            auto token = Token(token_value, token_type);
            tokens.push_back(token);
            operand.clear();
        }
    }

    const ValueType token_type = determine_operand_type(operand);
    const uint8_t token_value = determine_operand_value(operand, token_type);
    const auto token = Token(token_value, token_type);
    tokens.push_back(token);

    return tokens;
}

ValueType determine_operand_type(const std::string& operand) {
    if (is_digits(operand)) {return ValueType::IMMEDIATE_VALUE;}
    if (is_register(operand)) {return ValueType::REGISTER;}
    if (is_register_value(operand)) {return ValueType::REGISTER_VALUE;}
    if (is_flag(operand)) {return ValueType::FLAG;}
    throw std::runtime_error("Unrecognized type: " + operand);
}

uint8_t determine_operand_value(const std::string& operand, const ValueType& type) {
    switch (type) {
        case ValueType::IMMEDIATE_VALUE: return static_cast<uint8_t>(std::stoi(operand));
        case ValueType::REGISTER: {
            const std::string value_part = operand.substr(1);
            return static_cast<uint8_t>(std::stoi(value_part));
        }
        case ValueType::REGISTER_VALUE: {
          const std::string value_part = operand.substr(2, operand.size() - 2);
          return static_cast<uint8_t>(std::stoi(value_part));
        }
        case ValueType::FLAG: {
           const auto finded = std::find(AVAILABLE_FLAGS.begin(), AVAILABLE_FLAGS.end(), operand);
           if (AVAILABLE_FLAGS.end() == finded) throw std::runtime_error("Unrecognized flag: " + operand);
           return std::distance(AVAILABLE_FLAGS.begin(), finded);

        }
        default: throw std::runtime_error("Unknown type");
    }
}
