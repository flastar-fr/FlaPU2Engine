#ifndef CMPPSEUDOINSTRUCTION_HPP
#define CMPPSEUDOINSTRUCTION_HPP
#include "Instruction.hpp"
#include "SUBInstruction.hpp"

class CMPPseudoInstruction final : public Instruction {
public:
    explicit CMPPseudoInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "CMP";
        amount_operands = 2;
    }
    CMPPseudoInstruction(): CMPPseudoInstruction(std::vector<Token>()) {};

    ~CMPPseudoInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        auto temp_operands = operands;
        temp_operands.emplace_back(0, ValueType::REGISTER);

        const auto sub = SUBInstruction(temp_operands);
        sub.execute(engine);
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.size() != amount_operands) return false;
        return std::all_of(
            operands.begin(),
            operands.end(),
            [](const auto& operand) {return operand.value_type == ValueType::REGISTER;}
            );
    }
};

#endif //CMPPSEUDOINSTRUCTION_HPP
