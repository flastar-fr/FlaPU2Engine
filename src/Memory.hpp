#ifndef MEMORY_HPP
#define MEMORY_HPP
#include <vector>

#include "MemoryCell.hpp"

inline constexpr size_t DEFAULT_SIZE_MEMORY = 255;

class Memory {
public:
    explicit Memory(const int memoryAmount) {
        memory.reserve(memoryAmount);
        for (int i = 0; i < memoryAmount; ++i) {
            memory.emplace_back();
        }
    }

    Memory(): Memory(DEFAULT_SIZE_MEMORY) {}

    MemoryCell& operator[](const size_t index) {
        if (index >= size())
            throw std::out_of_range("Valid index range is : 0 <= index <= " + (size() - 1));
        return memory[index];
    }

    [[nodiscard]] size_t size() const {
        return memory.size();
    }

private:
    std::vector<MemoryCell> memory;
};

#endif //MEMORY_HPP
