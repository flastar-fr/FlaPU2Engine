#ifndef JNEPSEUDOINSTRUCTION_HPP
#define JNEPSEUDOINSTRUCTION_HPP
#include "Instruction.hpp"
#include "BRHInstruction.hpp"

class JNEPseudoInstruction final : public Instruction {
public:
    explicit JNEPseudoInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "JNE";
        amount_operands = 1;
    }
    JNEPseudoInstruction(): JNEPseudoInstruction(std::vector<Token>()) {};

    ~JNEPseudoInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        auto temp_operands = operands;
        temp_operands.insert(temp_operands.begin(), Token(1, ValueType::FLAG));

        const auto brh = BRHInstruction(temp_operands);
        brh.execute(engine);
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.size() != amount_operands) return false;
        return std::all_of(
            operands.begin(),
            operands.end(),
            [](const auto& operand) {return operand.value_type == ValueType::IMMEDIATE_VALUE;}
            );
    }
};

#endif //JNEPSEUDOINSTRUCTION_HPP
