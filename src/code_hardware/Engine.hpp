#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "config.hpp"
#include "Memory.hpp"
#include "Registers.hpp"


class Engine {
public:
    explicit Engine(const int memoryAmount)
    : registerAmount(DEFAULT_SIZE_REGISTERS), memoryAmount(memoryAmount), registers(Registers()), memory(Memory(memoryAmount)), programCounter(0) {}
    Engine() : Engine(DEFAULT_SIZE_MEMORY) {}

    Registers& getRegisters() { return registers; }
    Memory& getMemory() { return memory; }
    [[nodiscard]] size_t getProgramCounter() const { return programCounter; }

    void incrementProgramCounter() {
        ++programCounter;
        if (programCounter >= MAX_AMOUNT_INSTRUCTIONS) programCounter = 0;
    }

    void jump(const int newAddress) {
        programCounter = newAddress;
    }

private:
    int registerAmount;
    int memoryAmount;
    Registers registers;
    Memory memory;
    size_t programCounter;
};
#endif //ENGINE_HPP
