#include "config_file_management.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "main_config.hpp"
#include "../main_components/pre_data_extraction.hpp"

void create_default_json_file(const std::string& config_file_name) {
    std::string selected_path = open_file_dialog();

    if (selected_path.empty()) {
        std::cerr << "No file selected" << std::endl;
        throw std::runtime_error("No file selected");
    }

    const json default_json = {
        {SOURCE_PATH_KEY, selected_path},
        {CLOCK_SPEED_KEY, 10}
    };

    if (auto file = std::ofstream(config_file_name)) {
        file << default_json.dump(4);
    }
    else {
        std::cerr << "Cannot create file" << std::endl;
        throw std::runtime_error("Cannot create file");
    }
}

json open_config_file(const std::string& config_file_name) {
    if (!std::filesystem::exists(config_file_name)) {
        create_default_json_file(config_file_name);
    }
    return open_json_file(config_file_name);
}

void save_config_file(const std::string& config_file_name, EngineRunner& engine_runner, json json_file) {
    json_file[CLOCK_SPEED_KEY] = engine_runner.getEngineStatus().op_per_second;
    json_file[SOURCE_PATH_KEY] = json_file[SOURCE_PATH_KEY];

    auto file = std::ofstream(config_file_name);
    if (!file) {
        std::cerr << "Cannot open file" << std::endl;
        throw std::runtime_error("Cannot open file");
    }

    file << json_file.dump(4);
}

void change_executed_file(const std::string& new_source_path, EngineRunner& engine_runner, const json& json_file) {
    const auto instructions = get_instructions(new_source_path);
    engine_runner.changeExecutedProgram(instructions, new_source_path);
    save_config_file(JSON_CONFIG_PATH, engine_runner, json_file);
}
