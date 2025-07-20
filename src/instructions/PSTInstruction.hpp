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
        Ports& ports = engine.getPorts();

        const PortType port_type = PORTS_TYPES[operands[0].value];
        switch (port_type) {
            case PortType::WRITE_CHAR: {
                const char char_to_write = CHARS_MAPPING[registers[operands[1].value].getValue()];
                ports.text_display.addChar(char_to_write);
                break;
            }
            case PortType::CLEAR_CHARS: {
                ports.text_display.clear();
                break;
            }
            case PortType::PRINT_CHARS: {
                ports.text_display.print();
                break;
            }
            case PortType::WRITE_NUMBER: {
                const uint8_t high_value = registers[operands[1].value].getValue();
                const uint8_t low_value = registers[operands[2].value].getValue();
                ports.number_display.addNumber(high_value, low_value);
                break;
            }
            case PortType::CLEAR_NUMBER: {
                ports.number_display.clear();
                break;
            }
            case PortType::PRINT_NUMBER: {
                ports.number_display.print();
                break;
            }
            case PortType::ADD_X1: {
                const uint8_t high_value = registers[operands[1].value].getValue();
                const uint8_t low_value = registers[operands[2].value].getValue();
                ports.screen.addX1(high_value, low_value);
                break;
            }
            case PortType::ADD_Y1: {
                const uint8_t high_value = registers[operands[1].value].getValue();
                const uint8_t low_value = registers[operands[2].value].getValue();
                ports.screen.addY1(high_value, low_value);
                break;
            }
            case PortType::ADD_X2: {
                const uint8_t high_value = registers[operands[1].value].getValue();
                const uint8_t low_value = registers[operands[2].value].getValue();
                ports.screen.addX2(high_value, low_value);
                break;
            }
            case PortType::ADD_Y2: {
                const uint8_t high_value = registers[operands[1].value].getValue();
                const uint8_t low_value = registers[operands[2].value].getValue();
                ports.screen.addY2(high_value, low_value);
                break;
            }
            case PortType::DRAW_PIXEL: {
                ports.screen.drawPixel();
                break;
            }
            case PortType::DRAW_RECT: {
                ports.screen.drawRectangle();
                break;
            }
            case PortType::CLEAR_PIXEL: {
                ports.screen.clearPixel();
            }
            case PortType::CLEAR_RECT: {
                ports.screen.clearRectangle();
                break;
            }
            case PortType::CLEAR_SCREEN: {
                ports.screen.clearScreen();
                break;
            }
            case PortType::PRINT_SCREEN: {
                ports.screen.pushBuffer();
                break;
            }
            case PortType::ADD_RNG_RANGE: {
                const uint8_t high_value = registers[operands[1].value].getValue();
                const uint8_t low_value = registers[operands[2].value].getValue();
                ports.random_number_generator.addRange(high_value, low_value);
                break;
            }
            case PortType::INPUT_TIMER_MS: {
                const uint8_t high_value = registers[operands[1].value].getValue();
                const uint8_t low_value = registers[operands[2].value].getValue();
                engine.setPeriodicTimerDuration((high_value << AMOUNT_BITS_PER_CELL) + low_value);
                break;
            }
            case PortType::SWITCH_INTERRUPT: {
                engine.setInterruptionEnabledState(!engine.getInterruptEnabled());
                break;
            }
            case PortType::PIXEL_COLOR: {
                const uint8_t red_value = registers[operands[1].value].getValue();
                const uint8_t green_value = registers[operands[2].value].getValue();
                const uint8_t blue_value = registers[operands[3].value].getValue();
                ports.screen.addColor(red_value, green_value, blue_value);
                break;
            }
            default: {
                std::cerr << "Invalid port " + std::to_string(operands[0].value) + " for writting" << std::endl;
                throw std::invalid_argument("Invalid port " + std::to_string(operands[0].value) + " for writting");
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
            case PortType::SWITCH_INTERRUPT:
            case PortType::DRAW_PIXEL:
            case PortType::DRAW_RECT:
            case PortType::CLEAR_PIXEL:
            case PortType::CLEAR_RECT:
            case PortType::CLEAR_SCREEN:
            case PortType::PRINT_SCREEN:
            case PortType::CLEAR_NUMBER:
            case PortType::PRINT_NUMBER:
            case PortType::CLEAR_CHARS:
            case PortType::PRINT_CHARS: return operands.size() == 1;
            case PortType::INPUT_TIMER_MS:
            case PortType::ADD_RNG_RANGE:
            case PortType::ADD_X1:
            case PortType::ADD_Y1:
            case PortType::ADD_X2:
            case PortType::ADD_Y2:
            case PortType::WRITE_NUMBER: {
                if (operands.size() != amount_operands + 1) return false;
                return std::all_of(operands.begin() + 1,
                                   operands.end(),
                                   [](const auto& operand) { return operand.value_type == ValueType::REGISTER_VALUE; });
            }
            case PortType::PIXEL_COLOR: {
                if (operands.size() != amount_operands + 2) return false;
                return std::all_of(operands.begin() + 1,
                                   operands.end(),
                                   [](const auto& operand) { return operand.value_type == ValueType::REGISTER_VALUE; });
            }

            default: return false;
        }
    }
};
