#include "windows_creation.hpp"

#include <imgui.h>

#include "config_gui.hpp"
#include "helper_functions.hpp"

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
    const auto& instructions_execution_trace = engine_runner.getInstructionsExecutionTrace();

    ImGui::Begin("Instruction Trace");
    ImGui::Text("Amount executed instructions: %lld, FPS: %f", engine_runner.getAmountExecutedInstructions(), ImGui::GetIO().Framerate);
    ImGui::Text("Instruction Trace: ");

    for (size_t i = 0; i < instructions_execution_trace.size() && i <= MAX_INSTRUCTION_TO_DISPLAY; ++i) {
        const auto& instruction = instructions_execution_trace[i];
        ImGui::Text("Instruction : %s", instruction->tostring().c_str());
    }

    ImGui::SetWindowSize(ImVec2(950, 200));
    ImGui::End();
}

void create_flags_table(const Engine& engine) {
    ImGui::BeginTable("Flags", 4);

    ImGui::TableSetupColumn("eq", ImGuiTableColumnFlags_WidthFixed, 50.0f);
    ImGui::TableSetupColumn("ne", ImGuiTableColumnFlags_WidthFixed, 50.0f);
    ImGui::TableSetupColumn("ge", ImGuiTableColumnFlags_WidthFixed, 50.0f);
    ImGui::TableSetupColumn("lt", ImGuiTableColumnFlags_WidthFixed, 50.0f);
    ImGui::TableHeadersRow();

    for (const auto& flag : engine.getFlagStates()) {
        ImGui::TableNextColumn();
        ImGui::Text(flag ? "true" : "false");
    }

    ImGui::EndTable();
}

void display_flags_n_pc(const Engine &engine) {
    ImGui::Begin("Flags and Program Counter");
    ImGui::Text("Flags: ");
    ImGui::SameLine();

    create_flags_table(engine);

    ImGui::Text("Program Counter: %d", engine.getProgramCounter());

    ImGui::SetWindowSize(ImVec2(300, 90));
    ImGui::End();
}

void create_buttons_controllers(EngineStatus &engineStatus) {
    if (ImGui::Button("Play")) {
        if (engineStatus.running_status == EngineRunningStatus::PAUSED) {
            engineStatus.running_status = EngineRunningStatus::RUNNING;
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Pause")) {
        engineStatus.running_status = EngineRunningStatus::PAUSED;
    }

    ImGui::SameLine();

    if (ImGui::Button("Stop")) {
        engineStatus.running_status = EngineRunningStatus::STOPPED;
    }
}

void display_controls(EngineRunner &engine_runner) {
    ImGui::Begin("Controls");
    ImGui::Text("Controls: ");

    EngineStatus& engine_status = engine_runner.getEngineStatus();

    create_buttons_controllers(engine_status);

    ImGui::Text("Operation /seconds:");
    ImGui::SliderInt("##Slider", &engine_status.op_per_second, 0, MAX_SPEED_EXECUTION);
    ImGui::SameLine();
    ImGui::InputInt("##Input", &engine_status.op_per_second, 1);

    ImGui::Text("FPS : %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("Executed : %lld", engine_runner.getAmountExecutedInstructions());

    ImGui::SetWindowSize(ImVec2(165, 155));
    ImGui::End();
}

void display_text_n_number(Engine &engine) {
    ImGui::Begin("Text and Number");
    ImGui::Text("Text: %s", engine.getPorts().text_display.getDisplayedText().c_str());
    ImGui::Text("Number: %d", engine.getPorts().number_display.getDisplayedNumber());
    ImGui::End();
}

void display_debug_windows(EngineRunner &engine_runner) {
    const auto &registers = engine_runner.getEngine().getRegisters();
    auto &memory = engine_runner.getEngine().getMemory();
    const auto &engine = engine_runner.getEngine();

    display_registers(registers);
    display_memory(memory);
    display_instruction_executed_trace(engine_runner);
    display_flags_n_pc(engine);
}

void render_main_window_content(Screen& screen) {
    const auto& screen_pixels = screen.getDisplayedScreen();
    const auto screen_size = screen.getScreenSize();
    const size_t width = screen_size.x;
    const size_t height = screen_size.y;

    for (size_t index = 0, y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x, ++index) {
            if (!screen_pixels[index]) continue;
            draw_pixel(ImVec2(static_cast<float>(x), static_cast<float>(y)), IM_COL32(255, 255, 255, 255));
        }
    }
}
