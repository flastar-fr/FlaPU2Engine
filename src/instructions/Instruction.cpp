#include "Instruction.hpp"
#include "code_hardware/Engine.hpp"

void Instruction::execute(Engine& engine) const {}
bool Instruction::isCorrect() const { return false; }

[[nodiscard]] std::string Instruction::tostring() const {
    std::string desc = "Instruction[name : " + name + ", Operands : { ";
    for (const auto& operand : operands) {
        desc += to_string(operand) + " ";
    }
    desc += "}]";

    return desc;
}

std::ostream& operator<<(std::ostream & lhs, const Instruction& rhs) {
    lhs << rhs.tostring();
    return lhs;
}