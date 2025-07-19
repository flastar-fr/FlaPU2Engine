#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <stack>

#include "config_hardware.hpp"
#include "InterruptVectorTable.hpp"
#include "Memory.hpp"
#include "Ports.hpp"
#include "Registers.hpp"


class Engine {
public:
    explicit Engine(const int memoryAmount, const size_t amountInterrupts)
        : register_amount(DEFAULT_SIZE_REGISTERS), memory_amount(memoryAmount), registers(Registers()),
          memory(Memory(memoryAmount)), programCounter(0), flag_states({false, false, false, false}),
          ports(Ports(SCREEN_SIZE)), ivt(amountInterrupts) {}

    Engine() : Engine(DEFAULT_SIZE_MEMORY, AMOUNT_INTERRUPTS) {}

    Registers& getRegisters() { return registers; }
    Memory& getMemory() { return memory; }
    [[nodiscard]] size_t getProgramCounter() const { return programCounter; }
    [[nodiscard]] std::array<bool, 4> getFlagStates() const { return flag_states; }
    [[nodiscard]] Ports& getPorts() { return ports; }
    [[nodiscard]] InterruptVectorTable& getInterruptVectorTable() { return ivt; }
    [[nodiscard]] bool getInterruptionEnabled() const { return interruption_enabled; }

    void verifyFlags(const uint8_t operand1, const uint8_t operand2) {
        setFlagsStates({operand1 == operand2, operand1 != operand2, operand1 >= operand2, operand1 < operand2});
    }

    void setFlagsStates(const std::array<bool, 4> flagStates) {
        flag_states = flagStates;
    }

    void incrementProgramCounter() {
        programCounter = ++programCounter % MAX_AMOUNT_INSTRUCTIONS;
    }

    void jump(const size_t new_address) {
        programCounter = new_address % MAX_AMOUNT_INSTRUCTIONS;
    }

    void pushStack(const uint8_t address) {
        if (stack_addresses.size() > MAX_STACK_MEMORY) throw std::length_error("Stack overflow");
        stack_addresses.push(address);
    }

    void popStack() {
        jump(stack_addresses.top());
        stack_addresses.pop();
    }

    void setInterruptionEnabledState(const bool enabled) {
        interruption_enabled = enabled;
    }

private:
    int register_amount;
    int memory_amount;
    Registers registers;
    Memory memory;
    size_t programCounter;
    std::array<bool, 4> flag_states;
    bool interruption_enabled = true;
    std::stack<uint8_t> stack_addresses;
    Ports ports;
    InterruptVectorTable ivt;
};
#endif //ENGINE_HPP
