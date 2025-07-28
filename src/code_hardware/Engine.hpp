#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <chrono>
#include <stack>

#include "../config/config_hardware.hpp"
#include "InterruptVectorTable.hpp"
#include "Memory.hpp"
#include "Ports.hpp"
#include "Registers.hpp"


class Engine {
public:
    explicit Engine(const int memoryAmount, const size_t amountInterrupts)
        : register_amount(DEFAULT_SIZE_REGISTERS), memory_amount(memoryAmount), registers(Registers()),
          memory(Memory(memoryAmount)), program_counter(0), flag_states({false, false, false, false}),
          ports(Ports(SCREEN_SIZE)), ivt(amountInterrupts) {
        start_period = std::chrono::steady_clock::now();
    }

    Engine() : Engine(DEFAULT_SIZE_MEMORY, AMOUNT_INTERRUPTS) {}

    Registers& getRegisters() { return registers; }
    Memory& getMemory() { return memory; }
    [[nodiscard]] size_t getProgramCounter() const { return program_counter; }
    [[nodiscard]] std::array<bool, 4> getFlagStates() const { return flag_states; }
    [[nodiscard]] Ports& getPorts() { return ports; }
    [[nodiscard]] InterruptVectorTable& getInterruptVectorTable() { return ivt; }
    [[nodiscard]] bool getInterruptEnabled() const { return interruption_enabled; }

    void verifyFlags(const uint8_t operand1, const uint8_t operand2) {
        setFlagsStates({operand1 == operand2, operand1 != operand2, operand1 >= operand2, operand1 < operand2});
    }

    void setFlagsStates(const std::array<bool, 4> flagStates) {
        flag_states = flagStates;
    }

    void incrementProgramCounter() {
        program_counter = ++program_counter % MAX_AMOUNT_INSTRUCTIONS;
    }

    void jump(const size_t new_address) {
        program_counter = new_address % MAX_AMOUNT_INSTRUCTIONS;
    }

    void pushStack(const size_t address) {
        if (stack_addresses.size() > MAX_STACK_MEMORY) throw std::length_error("Stack overflow");
        stack_addresses.push(address);
    }

    void popStack() {
        jump(stack_addresses.top());
        stack_addresses.pop();
    }

    void setInterruptionEnabledState(const bool new_state) {
        interruption_enabled = new_state;
    }

    void triggerInterrupt(const uint8_t interrupt_code, const bool reexecute_last_instruction) {
        if (!interruption_enabled) return;

        const size_t new_address = ivt.getInterruptionISRAddress(interrupt_code);

        const int offset_stack = reexecute_last_instruction ? 1 : 0;
        const int offset_jump = reexecute_last_instruction ? 0 : 1;
        pushStack(getProgramCounter() - offset_stack);

        jump(new_address - offset_jump);
        setInterruptionEnabledState(false);
    }

    void checkPeriodicInterrupt() {
        const auto now = std::chrono::steady_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_period);

        if (duration.count() >= periodic_timer_duration_ms) {
            start_period = std::chrono::steady_clock::now();

            triggerInterrupt(PERIODIC_INTERRUPT_CODE, true);
        }
    }

    void setPeriodicTimerDuration(const int duration) {
        periodic_timer_duration_ms = duration;
    }

private:
    int register_amount;
    int memory_amount;
    Registers registers;
    Memory memory;
    size_t program_counter;
    std::array<bool, 4> flag_states;
    bool interruption_enabled = false;
    std::stack<size_t> stack_addresses;
    Ports ports;
    InterruptVectorTable ivt;
    std::chrono::steady_clock::time_point start_period;
    int periodic_timer_duration_ms = DEFAULT_PERIODIC_TIMER_DURATION_MS;
};
#endif //ENGINE_HPP
