#ifndef ANDINSTRUCTION_HPP
#define ANDINSTRUCTION_HPP
#include <algorithm>

#include "Instruction.hpp"

class ANDInstruction final : public Instruction {
public:
    explicit ANDInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "AND";
        amount_operands = 3;
    }

    ANDInstruction(): ANDInstruction(std::vector<Token>()) {};

    ~ANDInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        Registers& registers = engine.getRegisters();
        const uint8_t first_register_to_and = operands[0].value;
        const uint8_t second_register_to_and = operands[1].value;
        const uint8_t register_result = operands[2].value;

        engine.verifyFlags(registers[first_register_to_and].getValue(), registers[second_register_to_and].getValue());
        registers[register_result] = registers[first_register_to_and] & registers[second_register_to_and];
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.size() != amount_operands) return false;
        return std::all_of(
            operands.begin(),
            operands.end(),
            [](const auto& operand) { return operand.value_type == ValueType::REGISTER; }
        );
    }
};

#endif //ANDINSTRUCTION_HPP
