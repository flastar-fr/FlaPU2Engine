#ifndef NORINSTRUCTION_HPP
#define NORINSTRUCTION_HPP
#include <algorithm>

#include "Instruction.hpp"

class NORInstruction final : public Instruction {
public:
    explicit NORInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "NOR";
        amount_operands = 3;
    }

    NORInstruction(): NORInstruction(std::vector<Token>()) {};

    ~NORInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        Registers& registers = engine.getRegisters();
        const uint8_t first_register_to_nor = operands[0].value;
        const uint8_t second_register_to_nor = operands[1].value;
        const uint8_t register_result = operands[2].value;

        const auto result_nor = registers[first_register_to_nor] | registers[second_register_to_nor];

        registers[register_result] = !result_nor;
        engine.verifyFlags(registers[first_register_to_nor].getValue(), registers[second_register_to_nor].getValue());
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

#endif //NORINSTRUCTION_HPP
