#ifndef NEGPSEUDOINSTRUCTION_HPP
#define NEGPSEUDOINSTRUCTION_HPP
#include "Instruction.hpp"
#include "SUBInstruction.hpp"

class NEGPseudoInstruction final : public Instruction {
public:
    explicit NEGPseudoInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "NEG";
        amount_operands = 2;
    }

    NEGPseudoInstruction(): NEGPseudoInstruction(std::vector<Token>()) {};

    ~NEGPseudoInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        auto temp_operands = operands;
        temp_operands.insert(temp_operands.begin(), Token(0, ValueType::REGISTER));

        const auto sub = SUBInstruction(temp_operands);
        sub.execute(engine);
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.size() != amount_operands) return false;
        return std::all_of(
            operands.begin(),
            operands.end(),
            [](const auto& operand) { return operand.value_type == ValueType::REGISTER; }
        );
    }
};

#endif //NEGPSEUDOINSTRUCTION_HPP
