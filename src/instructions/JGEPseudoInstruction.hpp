#ifndef JGEPSEUDOINSTRUCTION_HPP
#define JGEPSEUDOINSTRUCTION_HPP
#include "Instruction.hpp"
#include "BRHInstruction.hpp"

class JGEPseudoInstruction final : public Instruction {
public:
    explicit JGEPseudoInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "JGE";
        amount_operands = 1;
    }

    JGEPseudoInstruction(): JGEPseudoInstruction(std::vector<Token>()) {};

    ~JGEPseudoInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        auto temp_operands = operands;
        temp_operands.insert(temp_operands.begin(), Token(2, ValueType::FLAG));

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

#endif //JGEPSEUDOINSTRUCTION_HPP
