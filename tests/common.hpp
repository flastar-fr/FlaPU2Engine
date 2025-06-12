#pragma once
#include <vector>

#include "Token.hpp"

extern uint8_t ALTERNATIVE_TEST_VALUE;
extern uint8_t NULL_VALUE;

extern uint8_t FIRST_REGISTER_TO_USE;
extern uint8_t SECOND_REGISTER_TO_USE;
extern uint8_t REGISTER_RESULT;
extern uint8_t FIRST_REGISTER;

extern std::vector<Token> VALID_OPERANDS_3_REGISTERS_CLASSIC;
extern std::vector<Token> VALID_OPERANDS_3_REGISTERS_0_RESULT;
extern std::vector<Token> VALID_OPERANDS_3_REGISTERS_0_OPERAND_RIGHT;
extern std::vector<Token> VALID_OPERANDS_3_REGISTERS_0_OPERAND_LEFT;

extern std::vector<Token> VALID_OPERANDS_2_REGISTERS_CLASSIC;
extern std::vector<Token> VALID_OPERANDS_2_REGISTERS_0_RESULT;
extern std::vector<Token> VALID_OPERANDS_2_REGISTERS_0_OPERAND;

extern std::vector<Token> VALID_OPERANDS_2_REGISTER_IMM_CLASSIC;
extern std::vector<Token> VALID_OPERANDS_2_REGISTER_IMM_0_REGISTER;
extern std::vector<Token> VALID_OPERANDS_2_REGISTER_IMM_0_OPERAND;