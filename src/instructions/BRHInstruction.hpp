#ifndef BRHINSTRUCTION_HPP
#define BRHINSTRUCTION_HPP

#include "Instruction.hpp"
#include "utils/string_verifications.hpp"

class BRHInstruction final : public Instruction {
public:
    explicit BRHInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "BRH";
        amount_operands = 2;
    }

    BRHInstruction(): BRHInstruction(std::vector<Token>()) {}

    ~BRHInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) throw std::invalid_argument("Invalid instruction");

        if (operands[0].value >= AVAILABLE_FLAGS.size()) throw std::invalid_argument("Invalid operand");

        if (engine.getFlagStates()[operands[0].value]) engine.jump(operands[1].value - 1);
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.empty()) return false;
        return operands[0].value_type == ValueType::FLAG && operands[1].value_type == ValueType::IMMEDIATE_VALUE;
    }
};

#endif //BRHINSTRUCTION_HPP
