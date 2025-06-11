#ifndef XORINSTRUCTION_HPP
#define XORINSTRUCTION_HPP
#include <algorithm>

#include "Instruction.hpp"

class XORInstruction final : public Instruction {
public:
    explicit XORInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "XOR";
        amount_operands = 3;
    }

    XORInstruction(): XORInstruction(std::vector<Token>()) {};

    ~XORInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        Registers& registers = engine.getRegisters();
        const uint8_t first_register_to_xor = operands[0].value;
        const uint8_t second_register_to_xor = operands[1].value;
        const uint8_t register_result = operands[2].value;

        const auto result_xor = registers[first_register_to_xor] ^ registers[second_register_to_xor];

        registers[register_result] = result_xor;
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

#endif //XORINSTRUCTION_HPP
