#ifndef CALINSTRUCTION_HPP
#define CALINSTRUCTION_HPP
#include "Instruction.hpp"

class CALInstruction final : public Instruction {
public:
    explicit CALInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "CAL";
        amount_operands = 1;
    }
    CALInstruction(): CALInstruction(std::vector<Token>()) {}

    ~CALInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        engine.pushStack(engine.getProgramCounter());
        engine.jump(operands[0].value - 1);
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.empty()) return false;
        return operands[0].value_type == ValueType::IMMEDIATE_VALUE;;
    }
};

#endif //CALINSTRUCTION_HPP
