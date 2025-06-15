#ifndef LODINSTRUCTION_HPP
#define LODINSTRUCTION_HPP
#include "Instruction.hpp"
#include <ostream>
#include <iostream>

class LODInstruction final : public Instruction {
public:
    explicit LODInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "LOD";
        amount_operands = 3;
    }
    LODInstruction(): LODInstruction(std::vector<Token>()) {};

    ~LODInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        Registers& registers = engine.getRegisters();
        Memory& memory = engine.getMemory();

        if (isRegsAndOffset()) {
            uint8_t offset_value = 0;
            if (operands.size() == amount_operands) offset_value += operands[2].value;

            const uint8_t register_to_modify = operands[0].value;
            const uint8_t address_to_read_from = registers[operands[1].value].getValue();
            registers[register_to_modify] = memory[address_to_read_from + offset_value];
        }

        if (isRegAndImmediate()) {
            const uint8_t register_to_modify = operands[0].value;
            const uint8_t address_to_read_from = operands[1].value;
            registers[register_to_modify] = memory[address_to_read_from];
        }
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.size() != amount_operands && operands.size() != amount_operands - 1) return false;

        return isRegsAndOffset() || isRegAndImmediate();
    }

    [[nodiscard]] bool isRegsAndOffset() const {
        const bool first_is_register = operands[0].value_type == ValueType::REGISTER;
        const bool second_is_register = operands[1].value_type == ValueType::REGISTER_VALUE;
        bool is_offset_ok = true;
        if (operands.size() == 3) is_offset_ok = operands[2].value_type == ValueType::IMMEDIATE_VALUE;

        return first_is_register && second_is_register && is_offset_ok;
    }

    [[nodiscard]] bool isRegAndImmediate() const {
        if (operands.size() == amount_operands) return false;

        const bool first_is_register = operands[0].value_type == ValueType::REGISTER;
        const bool second_is_immediate = operands[1].value_type == ValueType::IMMEDIATE_VALUE;

        return first_is_register && second_is_immediate;
    }
};

#endif //LODINSTRUCTION_HPP
