#pragma once
#include <imgui.h>

#include "config/config_file_management.hpp"

void draw_pixel(ImVec2 pos, ImU32 color);
void ask_to_change_executed_file_path(EngineRunner& engine_runner, const json& json_file);
