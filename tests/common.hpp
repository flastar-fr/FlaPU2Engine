#pragma once
#include <cstdint>
#include <vector>

#include "Token.hpp"

extern uint8_t ALTERNATIVE_TEST_VALUE;
extern uint8_t NULL_VALUE;

extern uint8_t FIRST_REGISTER_TO_ADD;
extern uint8_t SECOND_REGISTER_TO_ADD;
extern uint8_t REGISTER_RESULT;
extern uint8_t FIRST_REGISTER;

extern std::vector<Token> VALID_OPERANDS_CLASSIC;
extern std::vector<Token> VALID_OPERANDS_0_RESULT;
extern std::vector<Token> VALID_OPERANDS_0_OPERAND_RIGHT;
extern std::vector<Token> VALID_OPERANDS_0_OPERAND_LEFT;