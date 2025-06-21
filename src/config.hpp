#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include <array>

class Instruction;
struct Token;

enum class ValueType {
    IMMEDIATE_VALUE,
    REGISTER,
    REGISTER_VALUE,
    FLAG
};

enum class FlagType {
    EQUALS,
    NOT_EQUALS,
    GREATER_OR_EQUALS,
    LESS
};

std::ostream& operator<<(std::ostream & lhs, ValueType rhs);

extern std::unordered_map<std::string, std::function<std::unique_ptr<Instruction>(const std::vector<Token>&)>> instruction_factories;
extern constexpr size_t MAX_AMOUNT_INSTRUCTIONS = 1024;
extern constexpr size_t DEFAULT_SIZE_MEMORY = 255;
extern constexpr size_t MAX_STACK_MEMORY = 16;
extern constexpr char FIRST_LABEL_CHAR = '.';
inline extern const std::string DEFINITION_KEY_WORD = "define";

const std::array<std::string, 4> AVAILABLE_FLAGS = {"=", "!=", ">=", "<"};;

#endif //CONFIG_HPP
