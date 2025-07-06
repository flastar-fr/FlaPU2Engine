#include "windows_creation.hpp"

#include <imgui.h>

void display_registers(const Registers& registers) {
    ImGui::Begin("Registers");
    ImGui::Text("Registers: ");

    for (size_t i = 0; i < registers.size(); ++i) {
        const auto& reg = registers[i];
        ImGui::Text("Register %d : %d", i, reg.getValue());
    }

    ImGui::SetWindowSize(ImVec2(150, 320));
    ImGui::End();
}

void display_memory(Memory& memory) {
    ImGui::Begin("Memory");
    ImGui::Text("Memory: ");

    for (size_t i = 0; i < memory.size(); ++i) {
        const auto& cell = memory[i];
        ImGui::Text("Memory %d : %d", i, cell.getValue());
    }

    ImGui::SetWindowSize(ImVec2(150, 300));
    ImGui::End();
}
