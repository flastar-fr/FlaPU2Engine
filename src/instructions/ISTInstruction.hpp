#ifndef ISTINSTRUCTION_HPP
#define ISTINSTRUCTION_HPP

#include "Instruction.hpp"
#include "code_hardware/Engine.hpp"

class ISTInstruction final : public Instruction {
public:
    explicit ISTInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "IST";
        amount_operands = 2;
    }

    ISTInstruction(): ISTInstruction(std::vector<Token>()) {};

    ~ISTInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        const size_t interrupt_code = operands[0].value;
        const size_t isr_address = operands[1].value;

        InterruptVectorTable& ivt = engine.getInterruptVectorTable();
        ivt.setInterruptionISRAddress(interrupt_code, isr_address);
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.size() != amount_operands) return false;

        return operands[0].value_type == ValueType::IMMEDIATE_VALUE && operands[1].value_type ==
            ValueType::IMMEDIATE_VALUE;
    }
};

#endif //ISTINSTRUCTION_HPP
