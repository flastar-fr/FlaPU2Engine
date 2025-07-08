#pragma once
#include "Instruction.hpp"

class PSTInstruction final : public Instruction {
public:
    explicit PSTInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "PST";
        amount_operands = 2;
    }
    PSTInstruction(): PSTInstruction(std::vector<Token>()) {};

    ~PSTInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        Registers& registers = engine.getRegisters();

        const PortType port_type = PORTS_TYPES[operands[0].value];
        switch (port_type) {
            case PortType::WRITE_CHAR: {
                const char char_to_write = CHARS_MAPPING[registers[operands[1].value].getValue()];
                engine.getPorts().text_display.addChar(char_to_write);
                break;
            }
            case PortType::CLEAR_CHARS: {
                engine.getPorts().text_display.clear();
                break;
            }
            case PortType::PRINT_CHARS: {
                engine.getPorts().text_display.print();
                break;
            }
            case PortType::WRITE_NUMBER: {
                const uint8_t high_value = registers[operands[1].value].getValue();
                const uint8_t low_value = registers[operands[2].value].getValue();
                engine.getPorts().number_display.addNumber(high_value, low_value);
                break;
            }
            case PortType::CLEAR_NUMBER: {
                engine.getPorts().number_display.clear();
                break;
            }
            case PortType::PRINT_NUMBER: {
                engine.getPorts().number_display.print();
                break;
            }
        }
    }

    [[nodiscard]] bool isCorrect() const override {
        if (operands[0].value_type != ValueType::PORT) return false;

        const PortType port_type = PORTS_TYPES[operands[0].value];
        switch (port_type) {
            case PortType::WRITE_CHAR: {
                if (operands.size() != amount_operands) return false;
                return operands[1].value_type == ValueType::REGISTER_VALUE;
            }
            case PortType::CLEAR_NUMBER:
            case PortType::PRINT_NUMBER:
            case PortType::CLEAR_CHARS:
            case PortType::PRINT_CHARS: return operands.size() == 1;
            case PortType::WRITE_NUMBER: {
                if (operands.size() != amount_operands + 1) return false;
                return std::all_of( operands.begin() + 1,
                    operands.end(),
                    [](const auto& operand) {return operand.value_type == ValueType::REGISTER_VALUE;});
            }
            default: return false;
        }
    }
};
