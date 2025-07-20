#ifndef IRTINSTRUCTION_HPP
#define IRTINSTRUCTION_HPP
#include "Instruction.hpp"

class IRTInstruction final : public Instruction {
public:
    explicit IRTInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "IRT";
        amount_operands = 0;
    }

    IRTInstruction(): IRTInstruction(std::vector<Token>()) {};

    ~IRTInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        engine.popStack();

        engine.setInterruptionEnabledState(true);
    }

    [[nodiscard]] bool isCorrect() const override {
        return operands.empty();
    }
};

#endif //IRTINSTRUCTION_HPP
