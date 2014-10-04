#include "Player.h"
#include <iostream>
#include "termbox.h"
#include "Input.h"

Player::Player() {
    x = tb_width()/2;
    y = tb_height()/2;

    size.width = 2;
    size.height = 3;
}

void Player::update() {
    switch(g_input.getKey()) {
        case KeyUpArrow:
            if (y > 0) {
                y--;
            }
            break;
        case KeyDownArrow:
            if (y + size.height < tb_height()) {
                y++;
            }
            break;
        case KeyLeftArrow:
            if (x > 0) {
                x--;
            }
            break;
        case KeyRightArrow:
            if (x + size.width < tb_width()) {
                x++;
            }
            break;
        case KeyEsc:
            tb_shutdown();
            exit(0);
            break;
        default:
            break;
    }
}

void Player::render(){
    tb_change_cell(x,     y,     '*', TB_WHITE | TB_BOLD, TB_RED);
    tb_change_cell(x + 1, y,     '*', TB_WHITE | TB_BOLD, TB_RED);
    tb_change_cell(x,     y + 1, ' ', TB_WHITE | TB_BOLD, TB_RED);
    tb_change_cell(x + 1, y + 1, ' ', TB_WHITE | TB_BOLD, TB_RED);
    tb_change_cell(x,     y + 2, ' ', TB_WHITE | TB_BOLD, TB_RED);
    tb_change_cell(x + 1, y + 2, ' ', TB_WHITE | TB_BOLD, TB_RED);
}

