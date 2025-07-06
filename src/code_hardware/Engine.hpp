#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <stack>
#include <utility>

#include "config_hardware.hpp"
#include "Memory.hpp"
#include "Registers.hpp"
#include "instructions/HLTInstruction.hpp"


class Engine {
public:
    explicit Engine(const int memoryAmount, std::vector<std::shared_ptr<Instruction>> instructions)
    : register_amount(DEFAULT_SIZE_REGISTERS), memory_amount(memoryAmount), registers(Registers()), memory(Memory(memoryAmount)), programCounter(0), flag_states({false, false, false, false}), instructions(std::move(instructions)) {}
    explicit Engine(std::vector<std::shared_ptr<Instruction>> instructions) : Engine(DEFAULT_SIZE_MEMORY, std::move(instructions)) {}

    Registers& getRegisters() { return registers; }
    Memory& getMemory() { return memory; }
    std::vector<std::shared_ptr<Instruction>>& getInstructionsExecutionTrace() { return instructions_execution_trace; }
    [[nodiscard]] size_t getProgramCounter() const { return programCounter; }
    [[nodiscard]] std::array<bool, 4> getFlagStates() const { return flag_states; }
    void verifyFlags(const uint8_t operand1, const uint8_t operand2) {
        setFlagsStates({operand1 == operand2, operand1 != operand2, operand1 >= operand2, operand1 < operand2});
    }

    void setFlagsStates(const std::array<bool, 4> flagStates) {
        flag_states = flagStates;
    }

    void incrementProgramCounter() {
        programCounter = ++programCounter % MAX_AMOUNT_INSTRUCTIONS;
    }

    void jump(const int newAddress) {
        programCounter = newAddress % MAX_AMOUNT_INSTRUCTIONS;
    }

    void push_stack(const uint8_t address) {
        if (stack_addresses.size() > MAX_STACK_MEMORY) throw std::length_error("Stack overflow");
        stack_addresses.push(address);
    }

    void pop_stack() {
        jump(stack_addresses.top());
        stack_addresses.pop();
    }

    void executeNextInstruction() {
        const std::shared_ptr<Instruction> instruction = instructions[getProgramCounter()];
        //std::cout << *instruction << std::endl;
        instructions_execution_trace.push_back(instruction);
        instruction->execute(*this);
        incrementProgramCounter();
    }

    [[nodiscard]] bool isProgramFinished() const {
        const std::shared_ptr<Instruction> instruction = instructions[getProgramCounter()];
        const bool is_in_the_range = getProgramCounter() < MAX_AMOUNT_INSTRUCTIONS;
        const bool is_end_program = dynamic_cast<HLTInstruction*>(instruction.get()) != nullptr;

        return is_end_program || !is_in_the_range;
    }

private:
    int register_amount;
    int memory_amount;
    Registers registers;
    Memory memory;
    size_t programCounter;
    std::array<bool, 4> flag_states;
    std::stack<uint8_t> stack_addresses;
    std::vector<std::shared_ptr<Instruction>> instructions;
    std::vector<std::shared_ptr<Instruction>> instructions_execution_trace;
};
#endif //ENGINE_HPP
