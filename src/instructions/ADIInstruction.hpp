#ifndef ADIINSTRUCTION_HPP
#define ADIINSTRUCTION_HPP
#include "Instruction.hpp"

class ADIInstruction final : public Instruction {
public:
    explicit ADIInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "ADI";
        amount_operands = 2;
    }
    ADIInstruction(): ADIInstruction(std::vector<Token>()) {};

    ~ADIInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        Registers& registers = engine.getRegisters();
        const uint8_t register_to_add_to = operands[0].value;
        const uint8_t immediate_value_to_add = operands[1].value;

        registers[register_to_add_to] = registers[register_to_add_to] + immediate_value_to_add;
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.size() != amount_operands) return false;
        const bool first_is_register = operands[0].value_type == ValueType::REGISTER;
        const bool second_is_immediate = operands[1].value_type == ValueType::IMMEDIATE_VALUE;
        return first_is_register && second_is_immediate;
    }
};

#endif //ADIINSTRUCTION_HPP
