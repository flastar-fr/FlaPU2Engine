#ifndef INTINSTRUCTION_HPP
#define INTINSTRUCTION_HPP

#include "Instruction.hpp"
#include "code_hardware/Engine.hpp"

class INTInstruction final : public Instruction {
public:
    explicit INTInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "INT";
        amount_operands = 1;
    }
    INTInstruction(): INTInstruction(std::vector<Token>()) {};

    ~INTInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        if (!engine.getInterruptionEnabled()) return;

        const uint8_t interrupt_code = operands[0].value;
        const InterruptVectorTable& ivt = engine.getInterruptVectorTable();

        const size_t new_address = ivt.getInterruptionISRAddress(interrupt_code);

        engine.pushStack(engine.getProgramCounter());

        engine.jump(new_address - 1);
        engine.setInterruptionEnabledState(false);
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.size() != amount_operands) return false;

        return operands[0].value_type == ValueType::IMMEDIATE_VALUE;
    }
};

#endif //INTINSTRUCTION_HPP
