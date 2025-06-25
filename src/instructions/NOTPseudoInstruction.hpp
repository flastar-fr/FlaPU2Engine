#ifndef NOTPSEUDOINSTRUCTION_HPP
#define NOTPSEUDOINSTRUCTION_HPP
#include "Instruction.hpp"
#include "NORInstruction.hpp"

class NOTPseudoInstruction final : public Instruction {
public:
    explicit NOTPseudoInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "NOT";
        amount_operands = 2;
    }
    NOTPseudoInstruction(): NOTPseudoInstruction(std::vector<Token>()) {};

    ~NOTPseudoInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        auto temp_operands = operands;
        temp_operands.insert(temp_operands.begin() + 1, Token(0, ValueType::REGISTER));

        const auto nor = NORInstruction(temp_operands);
        nor.execute(engine);
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

#endif //NOTPSEUDOINSTRUCTION_HPP
