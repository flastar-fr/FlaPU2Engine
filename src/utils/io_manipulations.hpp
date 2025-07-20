#pragma once
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool read_file(const std::string& file_path, std::vector<std::string>& result);
std::string open_file_dialog();
json open_json_file(const std::string& config_file_name);