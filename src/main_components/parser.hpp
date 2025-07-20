#ifndef PARSER_HPP
#define PARSER_HPP
#include <memory>
#include <string>
#include <vector>
#include "../instructions/Instruction.hpp"


std::shared_ptr<Instruction> parse_line(const std::string& line);
bool parse_lines(std::vector<std::shared_ptr<Instruction>>& instructions, const std::vector<std::string>& lines);
void fill_empty(std::vector<std::shared_ptr<Instruction>>& instructions, int to_have);
std::vector<Token> extract_operands(const std::string& line);
ValueType determine_operand_type(const std::string& operand);
uint8_t determine_operand_value(const std::string& operand, const ValueType& type);

#endif //PARSER_HPP
