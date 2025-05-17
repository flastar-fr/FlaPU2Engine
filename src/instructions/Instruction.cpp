#include "Instruction.hpp"

Instruction::~Instruction() = default;
void Instruction::execute(Engine& engine) const {}
bool Instruction::isCorrect() const { return false; }
