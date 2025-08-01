#ifndef LODINSTRUCTION_HPP
#define LODINSTRUCTION_HPP
#include "Instruction.hpp"

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
            executeIsRegsAndOffset(registers, memory);
        }
        else if (isRegAndImmediate()) {
            executeIsRegAndImmediate(registers, memory);
        }
        else if (isAddressesRegValuesHighLow()) {
            executeIsAddressesRegValuesHighLow(registers, memory);
        }
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands.size() != amount_operands && operands.size() != amount_operands - 1) return false;

        return isRegsAndOffset() || isRegAndImmediate() || isAddressesRegValuesHighLow();
    }

    [[nodiscard]] bool isRegsAndOffset() const {
        const bool first_is_register = operands[0].value_type == ValueType::REGISTER;
        const bool second_is_register_value = operands[1].value_type == ValueType::REGISTER_VALUE;
        bool is_offset_ok = true;
        if (operands.size() == 3) is_offset_ok = operands[2].value_type == ValueType::IMMEDIATE_VALUE;

        return first_is_register && second_is_register_value && is_offset_ok;
    }

    [[nodiscard]] bool isRegAndImmediate() const {
        if (operands.size() == amount_operands) return false;

        const bool first_is_register = operands[0].value_type == ValueType::REGISTER;
        const bool second_is_immediate = operands[1].value_type == ValueType::IMMEDIATE_VALUE;

        return first_is_register && second_is_immediate;
    }

    [[nodiscard]] bool isAddressesRegValuesHighLow() const {
        if (operands.size() != amount_operands) return false;

        const bool first_is_register = operands[0].value_type == ValueType::REGISTER;
        const bool second_is_register_value_high = operands[1].value_type == ValueType::REGISTER_VALUE;
        const bool third_is_register_value_low = operands[2].value_type == ValueType::REGISTER_VALUE;

        return first_is_register && second_is_register_value_high && third_is_register_value_low;
    }

    void executeIsRegsAndOffset(Registers& registers, Memory& memory) const {
        uint8_t offset_value = 0;
        if (operands.size() == amount_operands) offset_value += operands[2].value;

        const uint8_t register_to_modify = operands[0].value;
        const uint8_t address_to_read_from = registers[operands[1].value].getValue();
        registers[register_to_modify] = memory[address_to_read_from + offset_value];
    }

    void executeIsRegAndImmediate(Registers& registers, Memory& memory) const {
        const uint8_t register_to_modify = operands[0].value;
        const uint8_t address_to_read_from = operands[1].value;
        registers[register_to_modify] = memory[address_to_read_from];
    }

    void executeIsAddressesRegValuesHighLow(Registers& registers, Memory& memory) const {
        const uint8_t register_to_modify = operands[0].value;
        const uint8_t high_address_value = registers[operands[1].value].getValue();
        const uint8_t low_address_value = registers[operands[2].value].getValue();

        const uint16_t address_to_read_from = (high_address_value << AMOUNT_BITS_PER_CELL) + low_address_value;

        registers[register_to_modify] = memory[address_to_read_from];
    }
};

#endif //LODINSTRUCTION_HPP
