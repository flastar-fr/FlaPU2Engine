#pragma once
#include <memory>
#include <utility>
#include <vector>

#include "Engine.hpp"
#include "EngineStatus.hpp"
#include "instructions/HLTInstruction.hpp"
#include "instructions/Instruction.hpp"

class EngineRunner {
public:
    EngineRunner(Engine engine, std::vector<std::shared_ptr<Instruction>> instructions) : engine(std::move(engine)), instructions(std::move(instructions)), instructions_execution_trace({}), engine_status({}) {};

    [[nodiscard]] Engine& getEngine() { return engine; }
    [[nodiscard]] EngineStatus& getEngineStatus() { return engine_status; }
    std::vector<std::shared_ptr<Instruction>>& getInstructionsExecutionTrace() { return instructions_execution_trace; }

    void executeNextInstruction() {
        const auto& instruction = instructions[engine.getProgramCounter()];
        instructions_execution_trace.push_back(instruction);
        instruction->execute(engine);
        engine.incrementProgramCounter();
    }

    [[nodiscard]] bool isProgramFinished() const {
        const std::shared_ptr<Instruction> instruction = instructions[engine.getProgramCounter()];
        const bool is_in_the_range = engine.getProgramCounter() < MAX_AMOUNT_INSTRUCTIONS;
        const bool is_end_program = dynamic_cast<HLTInstruction*>(instruction.get()) != nullptr;

        return is_end_program || !is_in_the_range;
    }

private:
    Engine engine;
    std::vector<std::shared_ptr<Instruction>> instructions;
    std::vector<std::shared_ptr<Instruction>> instructions_execution_trace;
    EngineStatus engine_status;
};
