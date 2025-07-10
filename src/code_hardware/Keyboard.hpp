#pragma once
#include <queue>

class Keyboard {
public:
    void pushKeyCode(const Keycode keycode) {
        pressed_queue.push(keycode);
    }

    Keycode popKeyCode() {
        if (!pressed_queue.empty()) {
            const Keycode top_keycode = pressed_queue.front();
            pressed_queue.pop();
            return top_keycode;
        }

        return Keycode::NONE;
    }

private:
    std::queue<Keycode> pressed_queue;
};
