#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

class Instruction;
struct Token;

enum class ValueType {
    IMMEDIATE_VALUE,
    REGISTER,
    REGISTER_VALUE
};

std::ostream& operator<<(std::ostream & lhs, ValueType rhs);

extern std::unordered_map<std::string, std::function<std::unique_ptr<Instruction>(const std::vector<Token>&)>> instruction_factories;
extern constexpr size_t MAX_AMOUNT_INSTRUCTIONS = 1024;
extern constexpr size_t DEFAULT_SIZE_MEMORY = 255;

#endif //CONFIG_HPP
