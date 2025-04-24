#ifndef MEMORYCELL_HPP
#define MEMORYCELL_HPP
#include <cstdint>
#include <ostream>


class MemoryCell {
public:
    explicit MemoryCell(const uint8_t value): value(value) {}
    MemoryCell(): value(0) {};
    virtual ~MemoryCell() = default;

    virtual MemoryCell & operator=(const uint8_t operand) {
        this->value = operand;
        return *this;
    }

    virtual MemoryCell & operator=(const MemoryCell& operand) = default;

    virtual MemoryCell& operator++() {
        ++value;
        return *this;
    }

    virtual MemoryCell& operator++(int) {
        ++value;
        return *this;
    }

    virtual MemoryCell& operator--() {
        --value;
        return *this;
    }

    virtual MemoryCell& operator--(int) {
        --value;
        return *this;
    }

    virtual MemoryCell & operator+=(const uint8_t operand) {
        this->value = static_cast<uint8_t>(this->value + operand);
        return *this;
    }

    virtual MemoryCell & operator-=(const uint8_t operand) {
        this->value = static_cast<uint8_t>(this->value - operand);
        return *this;
    }

    virtual MemoryCell operator+(const uint8_t operand) const {
        MemoryCell temp = *this;
        temp += operand;
        return temp;
    }

    virtual MemoryCell operator-(const uint8_t operand) const {
        MemoryCell temp = *this;
        temp -= operand;
        return temp;
    }

    virtual MemoryCell & operator+=(const MemoryCell& operand) {
        this->value = static_cast<uint8_t>(this->value + operand.value);
        return *this;
    }

    virtual MemoryCell & operator-=(const MemoryCell& operand) {
        this->value = static_cast<uint8_t>(this->value - operand.value);
        return *this;
    }

    virtual MemoryCell operator+(const MemoryCell& operand) const {
        MemoryCell temp = *this;
        temp += operand;;
        return temp;
    }

    virtual MemoryCell operator-(const MemoryCell& operand) const {
        MemoryCell temp = *this;
        temp -= operand;
        return temp;
    }

    virtual MemoryCell operator-() const {
        const auto new_value = static_cast<uint8_t>(-this->value);
        return MemoryCell(new_value);
    }

    bool operator==(const MemoryCell& operand) const {
        return this->value == operand.value;
    }

    bool operator==(const uint8_t operand) const {
        return this->value == operand;
    }

    friend std::ostream& operator<<(std::ostream & lhs, const MemoryCell & m) {
        lhs << static_cast<int>(m.value);
        return lhs;
    }

    [[nodiscard]] virtual bool isNull() const noexcept {
        return false;
    }

    [[nodiscard]] uint8_t getValue() const noexcept {return value;}

protected:
    uint8_t value;
};

#endif //MEMORYCELL_HPP
