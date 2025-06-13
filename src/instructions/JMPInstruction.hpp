#ifndef JMPINSTRUCTION_HPP
#define JMPINSTRUCTION_HPP
#include <iostream>

#include "Instruction.hpp"

class JMPInstruction final : public Instruction {
public:
    explicit JMPInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "JMP";
        amount_operands = 1;
    }
    JMPInstruction(): JMPInstruction(std::vector<Token>()) {}

    ~JMPInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        engine.jump(operands[0].value - 1);
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.empty()) return false;
        return operands[0].value_type == ValueType::IMMEDIATE_VALUE;;
    }
};

#endif //JMPINSTRUCTION_HPP
