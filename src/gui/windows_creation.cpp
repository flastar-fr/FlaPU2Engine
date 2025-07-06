#include "windows_creation.hpp"

#include <imgui.h>

#include "config_gui.hpp"
#include "code_hardware/EngineStatus.hpp"
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

void display_instruction_executed_trace(EngineRunner &engine_runner) {
    const auto instructions_execution_trace = engine_runner.getInstructionsExecutionTrace();

    ImGui::Begin("Instruction Trace");
    ImGui::Text("Amount executed instructions: %d", instructions_execution_trace.size());
    ImGui::Text("Instruction Trace: ");

    for (const auto& instruction : instructions_execution_trace) {
        ImGui::Text("Instruction : %s", instruction->tostring().c_str());
    }

    ImGui::SetWindowSize(ImVec2(950, 200));
    ImGui::End();
}

void create_buttons_controllers(EngineStatus &engineStatus) {
    if (ImGui::Button("Play")) {
        if (engineStatus.runningStatus == EngineRunningStatus::PAUSED) {
            engineStatus.runningStatus = EngineRunningStatus::RUNNING;
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Pause")) {
        engineStatus.runningStatus = EngineRunningStatus::PAUSED;
    }

    ImGui::SameLine();

    if (ImGui::Button("Stop")) {
        engineStatus.runningStatus = EngineRunningStatus::STOPPED;
    }
}

void display_controls(EngineStatus &engineStatus) {
    ImGui::Begin("Controls");
    ImGui::Text("Controls: ");

    create_buttons_controllers(engineStatus);

    ImGui::Text("Position:");
    ImGui::SliderInt("##Slider", &engineStatus.opPerSecond, 0, MAX_SPEED_EXECUTION);
    ImGui::SameLine();
    ImGui::InputInt("##Input", &engineStatus.opPerSecond, 1);

    ImGui::Spacing();

    ImGui::SetWindowSize(ImVec2(145, 115));
    ImGui::End();
}

void display_debug_windows(EngineRunner& engine_runner) {
    const auto& registers = engine_runner.getEngine().getRegisters();
    auto& memory = engine_runner.getEngine().getMemory();

    display_registers(registers);
    display_memory(memory);
    display_instruction_executed_trace(engine_runner);
}