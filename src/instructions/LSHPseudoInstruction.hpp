#ifndef LSHPSEUDOINSTRUCTION_HPP
#define LSHPSEUDOINSTRUCTION_HPP
#include "Instruction.hpp"
#include "ADDInstruction.hpp"

class LSHPseudoInstruction final : public Instruction {
public:
    explicit LSHPseudoInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "LSH";
        amount_operands = 2;
    }

    LSHPseudoInstruction(): LSHPseudoInstruction(std::vector<Token>()) {};

    ~LSHPseudoInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        auto temp_operands = operands;
        temp_operands.insert(temp_operands.begin(), operands[0]);

        const auto add = ADDInstruction(temp_operands);
        add.execute(engine);
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

#endif //LSHPSEUDOINSTRUCTION_HPP
