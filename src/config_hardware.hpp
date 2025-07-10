#ifndef CONFIG_HARDWARE_HPP
#define CONFIG_HARDWARE_HPP
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include <array>
#include <cstdint>

#include "utils/Vector2.hpp"

class Instruction;
struct Token;

enum class ValueType {
    IMMEDIATE_VALUE,
    REGISTER,
    REGISTER_VALUE,
    FLAG,
    PORT
};

enum class FlagType {
    EQUALS,
    NOT_EQUALS,
    GREATER_OR_EQUALS,
    LESS
};

enum class PortType {
    WRITE_CHAR,
    CLEAR_CHARS,
    PRINT_CHARS,
    WRITE_NUMBER,
    CLEAR_NUMBER,
    PRINT_NUMBER,
    ADD_X1,
    ADD_Y1,
    ADD_X2,
    ADD_Y2,
    DRAW_PIXEL,
    DRAW_RECT,
    CLEAR_PIXEL,
    CLEAR_RECT,
    CLEAR_SCREEN,
    PRINT_SCREEN
};

std::ostream& operator<<(std::ostream & lhs, ValueType rhs);
std::string to_string(ValueType value_type);

extern std::unordered_map<std::string, std::function<std::shared_ptr<Instruction>(const std::vector<Token>&)>> instruction_factories;
constexpr size_t MAX_AMOUNT_INSTRUCTIONS = 1024;
constexpr size_t DEFAULT_SIZE_MEMORY = 65535;
constexpr size_t MAX_STACK_MEMORY = 16;
constexpr size_t AMOUNT_BITS_PER_CELL = 8;
constexpr size_t MAX_AMOUNT_CHARS_DISPLAY = 20;
constexpr char FIRST_LABEL_CHAR = '.';
const std::string DEFINITION_KEY_WORD = "define";
constexpr char COMMENT_PREFIX = '#';
constexpr char LEFT_REGISTER_VALUE_CHAR = '[';
constexpr char RIGHT_REGISTER_VALUE_CHAR = ']';
constexpr char PATTERN_REPETITION_CHAR = ':';
const Vector2<uint16_t> SCREEN_SIZE = {1280, 720};

const std::array<std::string, 4> AVAILABLE_FLAGS = {"=", "!=", ">=", "<"};

extern std::unordered_map<std::string, std::string> PORTS_MAP_LABELS;

extern std::vector<PortType> PORTS_TYPES;
extern std::vector<char> CHARS_MAPPING;

#endif //CONFIG_HARDWARE_HPP
