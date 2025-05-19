#ifndef RSHINSTRUCTION_HPP
#define RSHINSTRUCTION_HPP
#include <algorithm>

#include "Instruction.hpp"

class RSHInstruction final : public Instruction {
public:
    explicit RSHInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "RSH";
        amount_operands = 2;
    }

    RSHInstruction(): RSHInstruction(std::vector<Token>()) {};

    ~RSHInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        Registers& registers = engine.getRegisters();
        const uint8_t register_to_nor = operands[0].value;
        const uint8_t register_result = operands[1].value;

        registers[register_result] = registers[register_to_nor].getValue() >> 1;
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.size() != amount_operands) return false;
        return std::all_of(
            operands.begin(),
            operands.end(),
            [](const auto& operand) {return operand.value_type == ValueType::REGISTER;}
            );
    }
};

#endif //RSHINSTRUCTION_HPP
