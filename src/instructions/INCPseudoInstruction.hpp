#ifndef INCPSEUDOINSTRUCTION_HPP
#define INCPSEUDOINSTRUCTION_HPP
#include "Instruction.hpp"
#include "ADIInstruction.hpp"

class INCPseudoInstruction final : public Instruction {
public:
    explicit INCPseudoInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "INC";
        amount_operands = 1;
    }

    INCPseudoInstruction(): INCPseudoInstruction(std::vector<Token>()) {};

    ~INCPseudoInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        auto temp_operands = operands;
        temp_operands.emplace_back(1, ValueType::IMMEDIATE_VALUE);

        const auto adi = ADIInstruction(temp_operands);
        adi.execute(engine);
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.size() != amount_operands) return false;
        return std::all_of(
            operands.begin(),
            operands.end(),
            [](const auto& operand) { return operand.value_type == ValueType::REGISTER; }
        );
    }
};

#endif //INCPSEUDOINSTRUCTION_HPP
