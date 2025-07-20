#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include <vector>

#include "../main_components/Token.hpp"
#include "code_hardware/Engine.hpp"

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

    [[nodiscard]] std::string tostring() const;
    friend std::ostream& operator<<(std::ostream& lhs, const Instruction& rhs);

protected:
    std::string name;
    size_t amount_operands = 0;
    std::vector<Token> operands;
};

#endif //INSTRUCTION_HPP
