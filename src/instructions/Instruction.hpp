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

    friend std::ostream& operator<<(std::ostream & lhs, const Instruction& rhs) {
        lhs << "Instruction[name : " + rhs.name + ", Operands : { ";
        for (const auto& operand : rhs.operands) {
            lhs << operand << " ";
        }
        lhs << "}]";
        return lhs;
    }

protected:
    std::string name;
    size_t amount_operands = 0;
    std::vector<Token> operands;
};



#endif //INSTRUCTION_HPP
