#include <iostream>

#include "termbox.h"
#include "Input.h"
#include "Player.h"

int main(int argc, char const *argv[])
{
    tb_init();
    Player player;

    while (1) {
        g_input.update();
        player.update();

        tb_clear();
        player.render();
        tb_present();
    }

    tb_shutdown();
    return 0;
}