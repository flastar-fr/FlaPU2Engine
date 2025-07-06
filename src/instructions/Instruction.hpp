#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include <ostream>
#include <vector>

#include "Token.hpp"
#include "code_hardware/Registers.hpp"

class Engine;

class Instruction {
public:
    explicit Instruction(const std::vector<Token>& operands): operands(operands) {}
    Instruction(): operands({}) {}
    virtual ~Instruction() = default;

    virtual void execute(Engine& engine) const = 0;
    [[nodiscard]] virtual bool isCorrect() const = 0;

    [[nodiscard]] std::string getName() const {
        return name;
    }

    [[nodiscard]] std::string tostring() const {
        std::string desc = "Instruction[name : " + name + ", Operands : { ";
        for (const auto& operand : operands) {
            desc += to_string(operand) + " ";
        }
        desc += "}]";

        return desc;
    }

    friend std::ostream& operator<<(std::ostream & lhs, const Instruction& rhs) {
        lhs << rhs.tostring();
        return lhs;
    }

protected:
    std::string name;
    size_t amount_operands = 0;
    std::vector<Token> operands;
};

#endif //INSTRUCTION_HPP
