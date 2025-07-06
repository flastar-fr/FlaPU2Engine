#include "parser.hpp"
#include <string>

#include "Preprocessor.hpp"
#include "gui/gui_handling.hpp"
#include "utils/io_manipulations.hpp"

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

    auto engineRunner = EngineRunner(Engine(), instructions);
    create_window(engineRunner);

    return 0;
}
