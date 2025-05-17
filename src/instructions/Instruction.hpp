#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include <ostream>
#include <vector>

#include "code_hardware/Engine.hpp"
#include "../Token.hpp"

class Instruction {
public:
    explicit Instruction(const std::vector<Token>& operands): operands(operands) {}
    Instruction(): operands({}) {}
    virtual ~Instruction();

    virtual void execute(Engine& engine) const;
    [[nodiscard]] virtual bool isCorrect() const;

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
