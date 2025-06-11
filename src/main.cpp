#include <iostream>
#include <ostream>
#include "parser.hpp"
#include <string>
#include <instructions/HLTInstruction.hpp>

#include "io_manipulations.hpp"


constexpr int MAX_INSTRUCTION_AMOUNT = 1024;

void execute_instructions(std::vector<std::unique_ptr<Instruction>>& instructions, Engine& engine) {
    int i = 0;
    std::unique_ptr<Instruction> instruction = std::move(instructions[i]);
    bool is_in_the_range = true;
    bool is_end_program = dynamic_cast<HLTInstruction*>(instruction.get()) != nullptr;

    while (is_in_the_range && !is_end_program) {
        std::cout << *instruction << std::endl;
        instruction->execute(engine);

        ++i;
        instruction = std::move(instructions[i]);
        is_in_the_range = i < MAX_INSTRUCTION_AMOUNT;
        is_end_program = dynamic_cast<HLTInstruction*>(instruction.get()) != nullptr;
    }

    std::cout << engine.getRegisters()[0] << std::endl;
    std::cout << engine.getRegisters()[1] << std::endl;
    std::cout << engine.getRegisters()[2] << std::endl;
    std::cout << engine.getRegisters()[3] << std::endl;
}

int main() {
    Engine engine;
    std::vector<std::string> result;

    if (const bool is_open = read_file("ressources/source.asm", result); !is_open) {
        return 1;
    }

    std::vector<std::unique_ptr<Instruction>> instructions;
    instructions.reserve(MAX_INSTRUCTION_AMOUNT);
    if (const bool all_corrects = parse_lines(instructions, result); !all_corrects) {
        return 2;
    }

    fill_empty(instructions, MAX_INSTRUCTION_AMOUNT);

    execute_instructions(instructions, engine);

    return 0;
}
