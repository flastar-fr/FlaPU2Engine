#pragma once
#include <vector>

class InterruptVectorTable {
public:
    explicit InterruptVectorTable(const size_t amount_interrupts) {
        interrupt_vector_table.resize(amount_interrupts);
    }

    void setInterruptionISRAddress(const size_t interrupt_code, const size_t isr_address) {
        interrupt_vector_table[interrupt_code] = isr_address;
    }

    [[nodiscard]] size_t getInterruptionISRAddress(const size_t interrupt_code) const {
        return interrupt_vector_table[interrupt_code];
    }

private:
    std::vector<size_t> interrupt_vector_table;
};
