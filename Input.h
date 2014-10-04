#pragma once

enum InputKey {
    KeyNone,
    KeyLeftArrow,
    KeyUpArrow,
    KeyRightArrow,
    KeyDownArrow,
    KeyEsc
};

class Input{
public:
    void update();
    InputKey getKey();
private:
    InputKey key;
};

extern Input g_input;
