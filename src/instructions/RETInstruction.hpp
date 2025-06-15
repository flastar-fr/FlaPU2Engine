#ifndef RETINSTRUCTION_HPP
#define RETINSTRUCTION_HPP
#include "Instruction.hpp"

class RETInstruction final : public Instruction {
public:
    explicit RETInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "RET";
        amount_operands = 0;
    }
    RETInstruction(): RETInstruction(std::vector<Token>()) {};

    ~RETInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        engine.pop_stack();
    }

    [[nodiscard]] bool isCorrect() const override {
        return operands.empty();
    }
};

#endif //RETINSTRUCTION_HPP
