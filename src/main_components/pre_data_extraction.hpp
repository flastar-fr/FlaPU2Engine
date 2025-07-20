#pragma once

#include "config/config_file_management.hpp"

std::vector<std::string> extract_file(const std::string& source_path);
std::vector<std::shared_ptr<Instruction>> get_instructions(const std::string& source_path);
