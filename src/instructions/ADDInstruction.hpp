#ifndef ADDINSTRUCTION_HPP
#define ADDINSTRUCTION_HPP
#include <algorithm>

#include "Instruction.hpp"
#include "code_hardware/Engine.hpp"

class ADDInstruction final : public Instruction {
public:
    explicit ADDInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "ADD";
        amount_operands = 3;
    }
    ADDInstruction(): ADDInstruction(std::vector<Token>()) {};

    ~ADDInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        Registers& registers = engine.getRegisters();
        const uint8_t first_register_to_add = operands[0].value;
        const uint8_t second_register_to_add = operands[1].value;
        const uint8_t register_result = operands[2].value;

        registers[register_result] = registers[first_register_to_add] + registers[second_register_to_add];
        engine.verifyFlags(registers[first_register_to_add].getValue(), registers[second_register_to_add].getValue());
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

#endif //ADDINSTRUCTION_HPP
