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

extern std::unordered_map<std::string, std::function<std::shared_ptr<Instruction>(const std::vector<Token>&)>> instruction_factories;
constexpr size_t MAX_AMOUNT_INSTRUCTIONS = 1024;
constexpr size_t DEFAULT_SIZE_MEMORY = 255;
constexpr size_t MAX_STACK_MEMORY = 16;
constexpr char FIRST_LABEL_CHAR = '.';
const std::string DEFINITION_KEY_WORD = "define";
constexpr char COMMENT_PREFIX = '#';
constexpr char LEFT_REGISTER_VALUE_CHAR = '[';
constexpr char RIGHT_REGISTER_VALUE_CHAR = ']';
constexpr char PATTERN_REPETITION_CHAR = ':';

const std::array<std::string, 4> AVAILABLE_FLAGS = {"=", "!=", ">=", "<"};;

#endif //CONFIG_HPP
