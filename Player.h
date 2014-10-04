#pragma once

struct Size{
    int width;
    int height;
};

class Player {
public:
    Player();
    void update();
    void render();
private:
    int x;
    int y;
    Size size;
};