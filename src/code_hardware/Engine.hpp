#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <stack>

#include "config.hpp"
#include "Memory.hpp"
#include "Registers.hpp"


class Engine {
public:
    explicit Engine(const int memoryAmount)
    : registerAmount(DEFAULT_SIZE_REGISTERS), memoryAmount(memoryAmount), registers(Registers()), memory(Memory(memoryAmount)), programCounter(0), flag_states({false, false, false, false}) {}
    Engine() : Engine(DEFAULT_SIZE_MEMORY) {}

    Registers& getRegisters() { return registers; }
    Memory& getMemory() { return memory; }
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

private:
    int registerAmount;
    int memoryAmount;
    Registers registers;
    Memory memory;
    size_t programCounter;
    std::array<bool, 4> flag_states;
    std::stack<uint8_t> stack_addresses;
};
#endif //ENGINE_HPP
