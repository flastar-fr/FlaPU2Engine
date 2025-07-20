#ifndef HLTINSTRUCTION_HPP
#define HLTINSTRUCTION_HPP
#include "Instruction.hpp"

class HLTInstruction final : public Instruction {
public:
    explicit HLTInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "HLT";
        amount_operands = 0;
    }

    HLTInstruction(): HLTInstruction(std::vector<Token>()) {};

    ~HLTInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }
    }

    [[nodiscard]] bool isCorrect() const override {
        return operands.empty();
    }
};

#endif //HLTINSTRUCTION_HPP
