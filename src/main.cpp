#include <iostream>
#include <ostream>
#include "parser.hpp"
#include <string>

#include "Preprocessor.hpp"
#include "code_hardware/Engine.hpp"
#include "utils/io_manipulations.hpp"
#include "instructions/HLTInstruction.hpp"

void execute_instructions(const std::vector<std::shared_ptr<Instruction>>& instructions, Engine& engine) {
    std::shared_ptr<Instruction> next_instruction = instructions[engine.getProgramCounter()];
    bool is_in_the_range = true;
    bool is_end_program = dynamic_cast<HLTInstruction*>(next_instruction.get()) != nullptr;

    while (is_in_the_range && !is_end_program) {
        engine.execute_next_instruction();

        next_instruction = instructions[engine.getProgramCounter()];
        is_in_the_range = engine.getProgramCounter() < MAX_AMOUNT_INSTRUCTIONS;
        is_end_program = dynamic_cast<HLTInstruction*>(next_instruction.get()) != nullptr;
    }

    std::cout << engine.getRegisters()[0] << std::endl;
    std::cout << engine.getRegisters()[1] << std::endl;
    std::cout << engine.getRegisters()[2] << std::endl;
    std::cout << engine.getRegisters()[3] << std::endl;
    std::cout << engine.getRegisters()[4] << std::endl;
    std::cout << engine.getRegisters()[5] << std::endl;
}

int main() {
    std::vector<std::string> result;

    if (const bool is_open = read_file("ressources/source.asm", result); !is_open) {
        return 1;
    }

    auto preprocessor = Preprocessor(result);
    result = preprocessor.preprocess();

    std::vector<std::shared_ptr<Instruction>> instructions;
    instructions.reserve(MAX_AMOUNT_INSTRUCTIONS);
    if (const bool all_corrects = parse_lines(instructions, result); !all_corrects) {
        return 2;
    }

    fill_empty(instructions, MAX_AMOUNT_INSTRUCTIONS);

    auto engine = Engine(instructions);
    execute_instructions(instructions, engine);

    return 0;
}
