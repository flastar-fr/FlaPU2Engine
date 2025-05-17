#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Memory.hpp"
#include "Registers.hpp"


class Engine {
public:
    explicit Engine(const int memoryAmount)
    : registerAmount(DEFAULT_SIZE_REGISTERS), memoryAmount(memoryAmount), registers(Registers()), memory(Memory(memoryAmount)) {}
    Engine() : Engine(DEFAULT_SIZE_MEMORY) {}

    Registers& getRegisters() { return registers; }
    Memory& getMemory() { return memory; }

private:
    int registerAmount;
    int memoryAmount;
    Registers registers;
    Memory memory;
};
#endif //ENGINE_HPP
