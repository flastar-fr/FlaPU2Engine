#ifndef STRINSTRUCTION_HPP
#define STRINSTRUCTION_HPP
#include "Instruction.hpp"

class STRInstruction final : public Instruction {
public:
    explicit STRInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "STR";
        amount_operands = 3;
    }
    STRInstruction(): STRInstruction(std::vector<Token>()) {};

    ~STRInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        Registers& registers = engine.getRegisters();
        Memory& memory = engine.getMemory();

        if (isRegsAndOffset()) {
            uint8_t offset_value = 0;
            if (operands.size() == amount_operands) offset_value += operands[2].value;

            const uint8_t address_to_store_in = registers[operands[0].value].getValue();
            const uint8_t value_to_store = registers[operands[1].value].getValue();
            memory[address_to_store_in + offset_value] = value_to_store;
        }

        if (isRegAndImmediate()) {
            const uint8_t address_to_store_in = operands[0].value;
            const uint8_t value_to_store = registers[operands[1].value].getValue();
            memory[address_to_store_in] = value_to_store;
        }
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.size() != amount_operands && operands.size() != amount_operands - 1) return false;

        return isRegsAndOffset() || isRegAndImmediate();
    }

    [[nodiscard]] bool isRegsAndOffset() const {
        const bool first_is_register = operands[0].value_type == ValueType::REGISTER_VALUE;
        const bool second_is_register = operands[1].value_type == ValueType::REGISTER_VALUE;
        bool is_offset_ok = true;
        if (operands.size() == 3) is_offset_ok = operands[2].value_type == ValueType::IMMEDIATE_VALUE;

        return first_is_register && second_is_register && is_offset_ok;
    }

    [[nodiscard]] bool isRegAndImmediate() const {
        if (operands.size() == amount_operands) return false;

        const bool first_is_register = operands[0].value_type == ValueType::IMMEDIATE_VALUE;
        const bool second_is_immediate = operands[1].value_type == ValueType::REGISTER_VALUE;

        return first_is_register && second_is_immediate;
    }
};

#endif //STRINSTRUCTION_HPP
