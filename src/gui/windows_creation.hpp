#pragma once
#include "code_hardware/Engine.hpp"
#include "EngineRunner.hpp"
#include "helper_functions.hpp"

void display_registers(const Registers& registers);
void display_memory(Memory& memory);
void display_instruction_executed_trace(EngineRunner& engine_runner);
void display_flags_n_pc(const Engine& engine);

void display_controls(EngineRunner& engine_runner, const json& json_file);
void display_text_n_number(Engine& engine);

void display_debug_windows(EngineRunner& engine_runner);

void render_main_window_content(Screen& screen);
