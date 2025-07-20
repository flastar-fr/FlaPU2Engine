#ifndef LDIINSTRUCTION_HPP
#define LDIINSTRUCTION_HPP
#include "Instruction.hpp"

class LDIInstruction final : public Instruction {
public:
    explicit LDIInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "LDI";
        amount_operands = 2;
    }

    LDIInstruction(): LDIInstruction(std::vector<Token>()) {};

    ~LDIInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        Registers& registers = engine.getRegisters();
        const bool first_is_register = operands[0].value_type == ValueType::REGISTER;
        const uint8_t register_value = first_is_register ? operands[0].value : registers[operands[0].value].getValue();
        const uint8_t value_to_set = operands[1].value;
        if (register_value < registers.size()) registers[register_value] = value_to_set;
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.size() != amount_operands) return false;
        const bool first_is_register = operands[0].value_type == ValueType::REGISTER;
        const bool second_is_immediate = operands[1].value_type == ValueType::IMMEDIATE_VALUE;
        const bool is_register_n_imm = first_is_register && second_is_immediate;

        const bool first_is_register_value = operands[0].value_type == ValueType::REGISTER_VALUE;
        const bool is_register_value_n_imm = first_is_register_value && second_is_immediate;
        return is_register_n_imm || is_register_value_n_imm;
    }
};

#endif //LDIINSTRUCTION_HPP
