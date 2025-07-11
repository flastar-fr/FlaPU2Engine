#ifndef SUBINSTRUCTION_HPP
#define SUBINSTRUCTION_HPP
#include <algorithm>

#include "Instruction.hpp"

class SUBInstruction final : public Instruction {
public:
    explicit SUBInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "SUB";
        amount_operands = 3;
    }
    SUBInstruction(): SUBInstruction(std::vector<Token>()) {};

    ~SUBInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        Registers& registers = engine.getRegisters();
        const uint8_t first_register_to_sub = operands[0].value;
        const uint8_t second_register_to_sub = operands[1].value;
        const uint8_t register_result = operands[2].value;

        engine.verifyFlags(registers[first_register_to_sub].getValue(), registers[second_register_to_sub].getValue());
        registers[register_result] = registers[first_register_to_sub] - registers[second_register_to_sub];
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

#endif //SUBINSTRUCTION_HPP
