#ifndef RORINSTRUCTION_HPP
#define RORINSTRUCTION_HPP
#include <algorithm>

#include "Instruction.hpp"

class RORInstruction final : public Instruction {
public:
    explicit RORInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "ROR";
        amount_operands = 2;
    }

    RORInstruction(): RORInstruction(std::vector<Token>()) {};

    ~RORInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        Registers& registers = engine.getRegisters();
        const uint8_t register_to_nor = operands[0].value;
        const uint8_t register_result = operands[1].value;

        registers[register_result] = ROR(registers[register_to_nor], 1);
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

#endif //RORINSTRUCTION_HPP
