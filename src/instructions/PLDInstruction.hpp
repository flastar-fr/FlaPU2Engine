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

        const PortType port_type = PORTS_TYPES[operands[0].value];
        switch (port_type) {
            case PortType::RANDOM_NB: {
                const uint8_t random_number = RandomNumberGenerator::generateRandomNumber();
                const uint8_t register_to_place = operands[1].value;

                registers[register_to_place] = random_number;
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
