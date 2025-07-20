#ifndef JLTPSEUDOINSTRUCTION_HPP
#define JLTPSEUDOINSTRUCTION_HPP
#include "Instruction.hpp"
#include "BRHInstruction.hpp"

class JLTPseudoInstruction final : public Instruction {
public:
    explicit JLTPseudoInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "JLT";
        amount_operands = 1;
    }

    JLTPseudoInstruction(): JLTPseudoInstruction(std::vector<Token>()) {};

    ~JLTPseudoInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        auto temp_operands = operands;
        temp_operands.insert(temp_operands.begin(), Token(3, ValueType::FLAG));

        const auto brh = BRHInstruction(temp_operands);
        brh.execute(engine);
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.size() != amount_operands) return false;
        return std::all_of(
            operands.begin(),
            operands.end(),
            [](const auto& operand) { return operand.value_type == ValueType::IMMEDIATE_VALUE; }
        );
    }
};

#endif //JLTPSEUDOINSTRUCTION_HPP
