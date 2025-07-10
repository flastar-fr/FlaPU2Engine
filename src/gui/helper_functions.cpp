#include "helper_functions.hpp"

void draw_pixel(const ImVec2 pos, const ImU32 color) {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 origin = viewport->Pos;
    const auto pixel_pos = ImVec2(pos.x + origin.x, pos.y + origin.y);

    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    draw_list->AddRectFilled(pixel_pos, ImVec2(pixel_pos.x + 1, pixel_pos.y + 1), color);
}
