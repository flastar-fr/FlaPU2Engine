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
    PRINT_SCREEN,
    ADD_RNG_RANGE,
    RANDOM_NB,
    KEYBOARD_INPUT,
    INPUT_TIMER_MS,
    SWITCH_INTERRUPT,
    GET_INTERRUPT_STATE
};

enum class Keycode {
    NONE = 0,
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    A = 10,
    B = 11,
    C = 12,
    D = 13,
    E = 14,
    F = 15,
    G = 16,
    H = 17,
    I = 18,
    J = 19,
    K = 20,
    M = 21,
    N = 22,
    O = 23,
    P = 24,
    Q = 25,
    R = 26,
    S = 27,
    T = 28,
    U = 29,
    V = 30,
    W = 31,
    X = 32,
    Y = 33,
    Z = 34,
    UP = 35,
    DOWN = 36,
    LEFT = 37,
    RIGHT = 38,
    SPACE = 39,
};

std::ostream& operator<<(std::ostream & lhs, ValueType rhs);
std::string to_string(ValueType value_type);

extern std::unordered_map<std::string, std::function<std::shared_ptr<Instruction>(const std::vector<Token>&)>> instruction_factories;
constexpr size_t MAX_AMOUNT_INSTRUCTIONS = 1024;
constexpr uint16_t DEFAULT_SIZE_MEMORY = 65535;
constexpr size_t MAX_STACK_MEMORY = 16;
constexpr size_t AMOUNT_BITS_PER_CELL = 8;
constexpr size_t MAX_AMOUNT_CHARS_DISPLAY = 20;
constexpr char FIRST_LABEL_CHAR = '.';
const std::string DEFINITION_KEY_WORD = "define";
constexpr char COMMENT_PREFIX = '#';
constexpr char LEFT_REGISTER_VALUE_CHAR = '[';
constexpr char RIGHT_REGISTER_VALUE_CHAR = ']';
constexpr char PATTERN_REPETITION_CHAR = ':';
constexpr int DEFAULT_PERIODIC_TIMER_DURATION_MS = 1000;
constexpr uint8_t PERIODIC_INTERRUPT_CODE = 0;
const Vector2<uint16_t> SCREEN_SIZE = {1280, 720};
const int AMOUNT_INTERRUPTS = static_cast<int>(std::pow(2, AMOUNT_BITS_PER_CELL) - 1);

const std::array<std::string, 4> AVAILABLE_FLAGS = {"=", "!=", ">=", "<"};

extern std::vector<std::string> PORTS_MAP_LABELS;

extern std::vector<PortType> PORTS_TYPES;
extern std::vector<char> CHARS_MAPPING;

#endif //CONFIG_HARDWARE_HPP
