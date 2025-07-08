#pragma once
#include <string>

#include "config_hardware.hpp"

class TextDisplay {
public:
    TextDisplay() {
        clear();
        print();
    }

    void addChar(const char char_to_add) {
        if (current_char_index >= MAX_AMOUNT_CHARS_DISPLAY) return;
        text[current_char_index] = char_to_add;
        current_char_index++;
    }

    void clear() {
        text.clear();
        text.resize(MAX_AMOUNT_CHARS_DISPLAY);
        for (size_t i = 0; i < MAX_AMOUNT_CHARS_DISPLAY; ++i) {
            text[i] = '_';
        }
        current_char_index = 0;
    }

    void print() {
        displayed_text = text;
    }

    [[nodiscard]] std::string getDisplayedText() const noexcept { return displayed_text; }

private:
    std::string text;
    size_t current_char_index = 0;
    std::string displayed_text;
};
