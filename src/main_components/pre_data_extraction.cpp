#include "pre_data_extraction.hpp"

#include "main_components/parser.hpp"
#include "Preprocessor.hpp"

std::vector<std::string> extract_file(const std::string& source_path) {
    std::vector<std::string> result;

    const bool is_open = read_file(source_path, result);
    if (!is_open) {
        std::cerr << "Could not read source file" << std::endl;
        throw std::runtime_error("Could not read source file");
    }

    auto preprocessor = Preprocessor(result);
    result = preprocessor.preprocess();

    return result;
}

std::vector<std::shared_ptr<Instruction>> get_instructions(const std::string& source_path) {
    std::vector<std::shared_ptr<Instruction>> instructions;

    const auto result = extract_file(source_path);

    instructions.reserve(MAX_AMOUNT_INSTRUCTIONS);
    const bool all_corrects = parse_lines(instructions, result);
    if (!all_corrects) {
        throw std::runtime_error("Invalid instruction");
    }

    fill_empty(instructions, MAX_AMOUNT_INSTRUCTIONS);

    return instructions;
}
