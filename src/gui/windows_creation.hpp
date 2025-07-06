#pragma once
#include "EngineStatus.hpp"
#include "code_hardware/Engine.hpp"

void display_registers(const Registers &registers);
void display_memory(Memory &memory);
void display_instruction_executed_trace(Engine &engine);
void display_flags_n_pc(Engine &engine);

void display_controls(EngineStatus &engineStatus);

void display_debug_windows(Engine& engine);