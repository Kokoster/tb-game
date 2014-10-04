#include "Input.h"

#include "termbox.h"


Input g_input;

void Input::update() {
    key = KeyNone;

    struct tb_event event;
    if (tb_peek_event(&event, 0) == 0) {
        return;
    }

    switch(event.key) {
        case TB_KEY_ARROW_UP:
            key = KeyUpArrow;
            break;
        case TB_KEY_ARROW_DOWN:
            key = KeyDownArrow;
            break;
        case TB_KEY_ARROW_LEFT:
            key = KeyLeftArrow;
            break;
        case TB_KEY_ARROW_RIGHT:
            key = KeyRightArrow;
            break;
        case TB_KEY_ESC:
            key = KeyEsc;
            break;
    }
}

InputKey Input::getKey() {
    return key;
}