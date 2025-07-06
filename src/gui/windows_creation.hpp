#pragma once
#include "code_hardware/Engine.hpp"

void display_registers(const Registers &registers);
void display_memory(Memory &memory);
void display_instruction_executed_trace(Engine &engine);
