#ifndef ROLINSTRUCTION_HPP
#define ROLINSTRUCTION_HPP
#include <algorithm>

#include "Instruction.hpp"

class ROLInstruction final : public Instruction {
public:
    explicit ROLInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "ROL";
        amount_operands = 2;
    }

    ROLInstruction(): ROLInstruction(std::vector<Token>()) {};

    ~ROLInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        Registers& registers = engine.getRegisters();
        const uint8_t register_to_nor = operands[0].value;
        const uint8_t register_result = operands[1].value;

        registers[register_result] = ROL(registers[register_to_nor], 1);
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

#endif //ROLINSTRUCTION_HPP
