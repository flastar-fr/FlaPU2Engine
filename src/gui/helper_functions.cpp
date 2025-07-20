#include "helper_functions.hpp"

void draw_pixel(const ImVec2 pos, const ImU32 color) {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 origin = viewport->Pos;
    const auto pixel_pos = ImVec2(pos.x + origin.x, pos.y + origin.y);

    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    draw_list->AddRectFilled(pixel_pos, ImVec2(pixel_pos.x + 1, pixel_pos.y + 1), color);
}

void ask_to_change_executed_file_path(EngineRunner& engine_runner, const json& json_file) {
    const std::string new_source_path = open_file_dialog();
    if (!new_source_path.empty()) {
        change_executed_file(new_source_path, engine_runner, json_file);
    }
}
