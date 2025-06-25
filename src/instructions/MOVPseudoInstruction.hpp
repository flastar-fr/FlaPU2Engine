#ifndef MOVPSEUDOINSTRUCTION_HPP
#define MOVPSEUDOINSTRUCTION_HPP
#include "Instruction.hpp"
#include "ADDInstruction.hpp"

class MOVPseudoInstruction final : public Instruction {
public:
    explicit MOVPseudoInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "MOV";
        amount_operands = 2;
    }
    MOVPseudoInstruction(): MOVPseudoInstruction(std::vector<Token>()) {};

    ~MOVPseudoInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        auto temp_operands = operands;
        temp_operands.insert(temp_operands.begin(), Token(0, ValueType::REGISTER));

        const auto add = ADDInstruction(temp_operands);
        add.execute(engine);
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

#endif //MOVPSEUDOINSTRUCTION_HPP
