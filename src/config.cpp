#include "config.hpp"

#include "instructions/ADDInstruction.hpp"
#include "instructions/ADIInstruction.hpp"
#include "instructions/ANDInstruction.hpp"
#include "instructions/HLTInstruction.hpp"
#include "instructions/LDIInstruction.hpp"
#include "instructions/NOPInstruction.hpp"
#include "instructions/NORInstruction.hpp"
#include "instructions/RSHInstruction.hpp"
#include "instructions/RORInstruction.hpp"
#include "instructions/ROLInstruction.hpp"
#include "instructions/SUBInstruction.hpp"
#include "instructions/XORInstruction.hpp"
#include "instructions/JMPInstruction.hpp"
#include "instructions/Instruction.hpp"
#include "instructions/BRHInstruction.hpp"
#include "instructions/CALInstruction.hpp"
#include "instructions/RETInstruction.hpp"
#include "instructions/LODInstruction.hpp"
#include "Token.hpp"
#include "instructions/STRInstruction.hpp"

std::ostream& operator<<(std::ostream & lhs, const ValueType rhs) {
    std::string value_string;
    switch (rhs) {
        case ValueType::IMMEDIATE_VALUE: {
                value_string = "IMMEDIATE_VALUE";
                break;
        }
        case ValueType::REGISTER: {
                value_string = "REGISTER";
                break;
        }
        case ValueType::REGISTER_VALUE: {
                value_string = "REGISTER_VALUE";
                break;
        }
        case ValueType::FLAG: {
            value_string = "FLAG";
            break;
        }
    }

    lhs << value_string;
    return lhs;
}

std::unordered_map<std::string, std::function<std::unique_ptr<Instruction>(const std::vector<Token>&)>> instruction_factories = {
    {"NOP", [](const std::vector<Token>& operands) { return std::make_unique<NOPInstruction>(operands); }},
    {"ADD", [](const std::vector<Token>& operands) { return std::make_unique<ADDInstruction>(operands); }},
    {"SUB", [](const std::vector<Token>& operands) { return std::make_unique<SUBInstruction>(operands); }},
    {"HLT", [](const std::vector<Token>& operands) { return std::make_unique<HLTInstruction>(operands); }},
    {"LDI", [](const std::vector<Token>& operands) { return std::make_unique<LDIInstruction>(operands); }},
    {"ADI", [](const std::vector<Token>& operands) { return std::make_unique<ADIInstruction>(operands); }},
    {"NOR", [](const std::vector<Token>& operands) { return std::make_unique<NORInstruction>(operands); }},
    {"XOR", [](const std::vector<Token>& operands) { return std::make_unique<XORInstruction>(operands); }},
    {"AND", [](const std::vector<Token>& operands) { return std::make_unique<ANDInstruction>(operands); }},
    {"RSH", [](const std::vector<Token>& operands) { return std::make_unique<RSHInstruction>(operands); }},
    {"ROR", [](const std::vector<Token>& operands) { return std::make_unique<RORInstruction>(operands); }},
    {"ROL", [](const std::vector<Token>& operands) { return std::make_unique<ROLInstruction>(operands); }},
    {"JMP", [](const std::vector<Token>& operands) { return std::make_unique<JMPInstruction>(operands); }},
    {"BRH", [](const std::vector<Token>& operands) { return std::make_unique<BRHInstruction>(operands); }},
    {"CAL", [](const std::vector<Token>& operands) { return std::make_unique<CALInstruction>(operands); }},
    {"RET", [](const std::vector<Token>& operands) { return std::make_unique<RETInstruction>(operands); }},
    {"LOD", [](const std::vector<Token>& operands) { return std::make_unique<LODInstruction>(operands); }},
    {"STR", [](const std::vector<Token>& operands) { return std::make_unique<STRInstruction>(operands); }},
};
