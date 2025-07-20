#pragma once
#include <nlohmann/json.hpp>

#include "gui/EngineRunner.hpp"
#include "utils/io_manipulations.hpp"

using json = nlohmann::json;

void create_default_json_file(const std::string& config_file_name);
json open_config_file(const std::string& config_file_name);
void save_config_file(const std::string& config_file_name, EngineStatus& engine_runner, json json_file);
void change_executed_file(const std::string& new_source_path, EngineRunner& engine_runner, const json& json_file);
