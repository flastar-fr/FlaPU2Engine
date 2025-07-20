#ifndef MEMORYCELLNULL_HPP
#define MEMORYCELLNULL_HPP

#include "MemoryCell.hpp"


class MemoryCellNull final : public MemoryCell {
public:
    MemoryCellNull() = default;
    explicit MemoryCellNull(const MemoryCell&): MemoryCell(0) {}

    MemoryCellNull& operator=(uint8_t) override {
        return *this;
    }

    MemoryCellNull& operator=(const MemoryCell&) noexcept override {
        return *this;
    }

    MemoryCellNull& operator++() override {
        return *this;
    }

    MemoryCellNull& operator++(int) override {
        return *this;
    }

    MemoryCellNull& operator--() override {
        return *this;
    }

    MemoryCellNull& operator--(int) override {
        return *this;
    }

    MemoryCellNull& operator+=(uint8_t operand) override {
        return *this;
    }

    MemoryCellNull& operator-=(uint8_t operand) override {
        return *this;
    }

    MemoryCell operator+(const uint8_t& operand) const {
        return MemoryCell(operand);
    }

    MemoryCellNull operator-(uint8_t&) const {
        return *this;
    }

    MemoryCellNull& operator+=(const MemoryCell&) override {
        return *this;
    }

    MemoryCellNull& operator-=(const MemoryCell&) override {
        return *this;
    }

    MemoryCell operator+(const MemoryCell& operand) const override {
        return operand;
    }

    MemoryCell operator-(const MemoryCell& operand) const override {
        return -operand;
    }

    [[nodiscard]] bool isNull() const noexcept override {
        return true;
    }
};

#endif //MEMORYCELLNULL_HPP
