#ifndef LODINSTRUCTION_HPP
#define LODINSTRUCTION_HPP
#include "Instruction.hpp"

class LDIInstruction final : public Instruction {
public:
    explicit LDIInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "LDI";
        amount_operands = 3;
    }
    LDIInstruction(): LDIInstruction(std::vector<Token>()) {};

    ~LDIInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        Registers& registers = engine.getRegisters();
        const uint8_t register_value = operands[0].value;
        const uint8_t value_to_set = operands[1].value;
        registers[register_value] = value_to_set;
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.size() != 2) return false;
        const bool first_is_register = operands[0].value_type == ValueType::REGISTER;
        const bool second_is_immediate = operands[1].value_type == ValueType::IMMEDIATE_VALUE;
        return first_is_register && second_is_immediate;
    }
};

#endif //LODINSTRUCTION_HPP
