#pragma once
#include "code_hardware/EngineStatus.hpp"
#include "code_hardware/Engine.hpp"
#include "code_hardware/EngineRunner.hpp"

void display_registers(const Registers &registers);
void display_memory(Memory &memory);
void display_instruction_executed_trace(EngineRunner &engine_runner);
void display_flags_n_pc(const Engine &engine);

void display_controls(EngineStatus &engineStatus);
void display_text_n_number(Engine &engine);

void display_debug_windows(EngineRunner& engine_runner);

void render_main_window_content(Screen& screen);