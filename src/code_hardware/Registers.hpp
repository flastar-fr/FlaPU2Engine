#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <array>
#include "MemoryCell.hpp"
#include "MemoryCellNull.hpp"

inline constexpr size_t DEFAULT_SIZE_REGISTERS = 16;

class Registers {
public:
    Registers() {
        cells.fill(MemoryCell());
    }

    MemoryCell& operator[](const size_t index) {
        if (index > DEFAULT_SIZE_REGISTERS - 1)
            throw std::out_of_range("Valid index range is : 0 <= index <= " + (DEFAULT_SIZE_REGISTERS - 1));
        if (index == 0) return memoryCellNull;
        return cells[index - 1];
    }

    const MemoryCell& operator[](const size_t index) const {
        if (index > DEFAULT_SIZE_REGISTERS - 1)
            throw std::out_of_range("Valid index range is : 0 <= index <= " + (DEFAULT_SIZE_REGISTERS - 1));
        if (index == 0) return memoryCellNull;
        return cells[index - 1];
    }

    [[nodiscard]] size_t size() const {
        return cells.size() + 1;
    }

private:
    std::array<MemoryCell, DEFAULT_SIZE_REGISTERS - 1> cells;
    MemoryCellNull memoryCellNull;
};

#endif // REGISTERS_HPP
