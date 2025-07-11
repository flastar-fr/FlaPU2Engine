#pragma once
#include <vector>

#include "config_gui.hpp"
#include "gui/EngineStatus.hpp"
#include "instructions/HLTInstruction.hpp"
#include "instructions/Instruction.hpp"

class EngineRunner {
public:
    EngineRunner(Engine engine, std::vector<std::shared_ptr<Instruction>> instructions) : engine(std::move(engine)), instructions(std::move(instructions)), engine_status({}) {}

    [[nodiscard]] Engine& getEngine() { return engine; }
    [[nodiscard]] EngineStatus& getEngineStatus() { return engine_status; }
    std::deque<std::shared_ptr<Instruction>>& getInstructionsExecutionTrace() { return instructions_execution_trace; }
    [[nodiscard]] long getAmountExecutedInstructions() const { return amount_executed_instructions; }

    void executeNextInstruction() {
        const auto& instruction = instructions[engine.getProgramCounter()];
        registerInstruction(instruction);
        instruction->execute(engine);
        engine.incrementProgramCounter();
    }

    [[nodiscard]] bool isProgramFinished() const {
        const std::shared_ptr<Instruction> instruction = instructions[engine.getProgramCounter()];
        const bool is_in_the_range = engine.getProgramCounter() < MAX_AMOUNT_INSTRUCTIONS;
        const bool is_end_program = dynamic_cast<HLTInstruction*>(instruction.get()) != nullptr;

        return is_end_program || !is_in_the_range;
    }

    void registerInstruction(const std::shared_ptr<Instruction>& instruction) {
        ++amount_executed_instructions;

        if constexpr (!SHOW_DEBUG) return;
        instructions_execution_trace.push_front(instruction);

        if (instructions_execution_trace.size() > MAX_INSTRUCTION_TO_DISPLAY) {
            instructions_execution_trace.pop_back();
        }
    }

private:
    Engine engine;
    std::vector<std::shared_ptr<Instruction>> instructions;
    std::deque<std::shared_ptr<Instruction>> instructions_execution_trace;
    long amount_executed_instructions = 0;
    EngineStatus engine_status;
};
