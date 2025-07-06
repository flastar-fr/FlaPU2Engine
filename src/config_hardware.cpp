#include "config_hardware.hpp"

#include "instructions/Instruction.hpp"

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
#include "instructions/BRHInstruction.hpp"
#include "instructions/CALInstruction.hpp"
#include "instructions/RETInstruction.hpp"
#include "instructions/LODInstruction.hpp"
#include "instructions/STRInstruction.hpp"

#include "instructions/CMPPseudoInstruction.hpp"
#include "instructions/MOVPseudoInstruction.hpp"
#include "instructions/LSHPseudoInstruction.hpp"
#include "instructions/INCPseudoInstruction.hpp"
#include "instructions/DECPseudoInstruction.hpp"
#include "instructions/NOTPseudoInstruction.hpp"
#include "instructions/NEGPseudoInstruction.hpp"
#include "instructions/JNEPseudoInstruction.hpp"
#include "instructions/JEQPseudoInstruction.hpp"
#include "instructions/JGEPseudoInstruction.hpp"
#include "instructions/JLTPseudoInstruction.hpp"

#include "Token.hpp"

std::ostream& operator<<(std::ostream & lhs, const ValueType rhs) {
    lhs << to_string(rhs);
    return lhs;
}

std::string to_string(const ValueType value_type) {
    switch (value_type) {
        case ValueType::IMMEDIATE_VALUE: {
            return "IMMEDIATE_VALUE";
        }
        case ValueType::REGISTER: {
            return"REGISTER";
        }
        case ValueType::REGISTER_VALUE: {
            return "REGISTER_VALUE";
        }
        case ValueType::FLAG: {
            return "FLAG";
        }
    }
    return "???";
}

std::unordered_map<std::string, std::function<std::shared_ptr<Instruction>(const std::vector<Token>&)>> instruction_factories = {
    {"NOP", [](const std::vector<Token>& operands) { return std::make_shared<NOPInstruction>(operands); }},
    {"ADD", [](const std::vector<Token>& operands) { return std::make_shared<ADDInstruction>(operands); }},
    {"SUB", [](const std::vector<Token>& operands) { return std::make_shared<SUBInstruction>(operands); }},
    {"HLT", [](const std::vector<Token>& operands) { return std::make_shared<HLTInstruction>(operands); }},
    {"LDI", [](const std::vector<Token>& operands) { return std::make_shared<LDIInstruction>(operands); }},
    {"ADI", [](const std::vector<Token>& operands) { return std::make_shared<ADIInstruction>(operands); }},
    {"NOR", [](const std::vector<Token>& operands) { return std::make_shared<NORInstruction>(operands); }},
    {"XOR", [](const std::vector<Token>& operands) { return std::make_shared<XORInstruction>(operands); }},
    {"AND", [](const std::vector<Token>& operands) { return std::make_shared<ANDInstruction>(operands); }},
    {"RSH", [](const std::vector<Token>& operands) { return std::make_shared<RSHInstruction>(operands); }},
    {"ROR", [](const std::vector<Token>& operands) { return std::make_shared<RORInstruction>(operands); }},
    {"ROL", [](const std::vector<Token>& operands) { return std::make_shared<ROLInstruction>(operands); }},
    {"JMP", [](const std::vector<Token>& operands) { return std::make_shared<JMPInstruction>(operands); }},
    {"BRH", [](const std::vector<Token>& operands) { return std::make_shared<BRHInstruction>(operands); }},
    {"CAL", [](const std::vector<Token>& operands) { return std::make_shared<CALInstruction>(operands); }},
    {"RET", [](const std::vector<Token>& operands) { return std::make_shared<RETInstruction>(operands); }},
    {"LOD", [](const std::vector<Token>& operands) { return std::make_shared<LODInstruction>(operands); }},
    {"STR", [](const std::vector<Token>& operands) { return std::make_shared<STRInstruction>(operands); }},
    {"CMP", [](const std::vector<Token>& operands) { return std::make_shared<CMPPseudoInstruction>(operands); }},
    {"MOV", [](const std::vector<Token>& operands) { return std::make_shared<MOVPseudoInstruction>(operands); }},
    {"LSH", [](const std::vector<Token>& operands) { return std::make_shared<LSHPseudoInstruction>(operands); }},
    {"INC", [](const std::vector<Token>& operands) { return std::make_shared<INCPseudoInstruction>(operands); }},
    {"DEC", [](const std::vector<Token>& operands) { return std::make_shared<DECPseudoInstruction>(operands); }},
    {"NOT", [](const std::vector<Token>& operands) { return std::make_shared<NOTPseudoInstruction>(operands); }},
    {"NEG", [](const std::vector<Token>& operands) { return std::make_shared<NEGPseudoInstruction>(operands); }},
    {"JNE", [](const std::vector<Token>& operands) { return std::make_shared<JNEPseudoInstruction>(operands); }},
    {"JEQ", [](const std::vector<Token>& operands) { return std::make_shared<JEQPseudoInstruction>(operands); }},
    {"JGE", [](const std::vector<Token>& operands) { return std::make_shared<JGEPseudoInstruction>(operands); }},
    {"JLT", [](const std::vector<Token>& operands) { return std::make_shared<JLTPseudoInstruction>(operands); }},
};
