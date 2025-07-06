#include "windows_creation.hpp"

#include <imgui.h>

#include "code_hardware/Engine.hpp"

void display_registers(const Registers &registers) {
    ImGui::Begin("Registers");
    ImGui::Text("Registers: ");

    for (size_t i = 0; i < registers.size(); ++i) {
        const auto& reg = registers[i];
        ImGui::Text("Register %d : %d", i, reg.getValue());
    }

    ImGui::SetWindowSize(ImVec2(150, 320));
    ImGui::End();
}

void display_memory(Memory &memory) {
    ImGui::Begin("Memory");
    ImGui::Text("Memory: ");

    for (size_t i = 0; i < memory.size(); ++i) {
        const auto& cell = memory[i];
        ImGui::Text("Memory %d : %d", i, cell.getValue());
    }

    ImGui::SetWindowSize(ImVec2(150, 300));
    ImGui::End();
}

void display_instruction_executed_trace(Engine &engine) {
    ImGui::Begin("Instruction Trace");
    ImGui::Text("Instruction Trace: ");

    const auto instructions_execution_trace = engine.getInstructionsExecutionTrace();

    for (const auto& instruction : instructions_execution_trace) {
        ImGui::Text("Instruction : %s", instruction->tostring().c_str());
    }

    ImGui::SetWindowSize(ImVec2(950, 200));
    ImGui::End();
}

void display_debug_windows(Engine& engine) {
    display_registers(engine.getRegisters());
    display_memory(engine.getMemory());
    display_instruction_executed_trace(engine);
}