#ifndef NOPINSTRUCTION_HPP
#define NOPINSTRUCTION_HPP
#include "Instruction.hpp"

class NOPInstruction final : public Instruction {
public:
    explicit NOPInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "NOP";
        amount_operands = 0;
    }
    NOPInstruction(): NOPInstruction(std::vector<Token>()) {};

    ~NOPInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }
    }

    [[nodiscard]] bool isCorrect() const override {
        return operands.empty();
    }
};

#endif //NOPINSTRUCTION_HPP
