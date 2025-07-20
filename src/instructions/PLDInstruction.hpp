#ifndef PLDINSTRUCTION_HPP
#define PLDINSTRUCTION_HPP
#include "Instruction.hpp"

class PLDInstruction final : public Instruction {
public:
    explicit PLDInstruction(const std::vector<Token>& operands): Instruction(operands) {
        name = "PLD";
        amount_operands = 3;
    }

    PLDInstruction(): PLDInstruction(std::vector<Token>()) {};

    ~PLDInstruction() override = default;

    void execute(Engine& engine) const override {
        if (!isCorrect()) {
            throw std::invalid_argument("Invalid instruction");
        }

        Registers& registers = engine.getRegisters();
        Ports& ports = engine.getPorts();

        const PortType port_type = PORTS_TYPES[operands[0].value];
        switch (port_type) {
            case PortType::RANDOM_NB: {
                const uint8_t random_number = ports.random_number_generator.generateRandomNumber();
                const uint8_t register_result = operands[1].value;

                registers[register_result] = random_number;
                break;
            }
            case PortType::KEYBOARD_INPUT: {
                const Keycode keycode = ports.keyboard.popKeyCode();
                const auto keycode_id = static_cast<uint8_t>(keycode);
                const uint8_t register_result = operands[1].value;

                registers[register_result] = keycode_id;
                break;
            }
            case PortType::GET_INTERRUPT_STATE: {
                const uint8_t are_interrupts_enabled = engine.getInterruptEnabled();
                const uint8_t register_result = operands[1].value;

                registers[register_result] = are_interrupts_enabled;
                break;
            }
            default: {
                std::cerr << "Invalid port " + std::to_string(operands[0].value) + " for reading" << std::endl;
                throw std::invalid_argument("Invalid port " + std::to_string(operands[0].value) + " for reading");
            }
        }
    }

    [[nodiscard]] bool isCorrect() const override {
        const bool is_first_port = operands[0].value_type == ValueType::PORT;
        const bool is_second_reg = operands[1].value_type == ValueType::REGISTER;

        return is_first_port && is_second_reg;
    }
};

#endif //PLDINSTRUCTION_HPP
