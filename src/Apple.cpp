#include "Apple.h"

Apple::Apple(int x, int y) : GameObject(x, y, "Assets/gfx/snake-graphics.bmp") {
    width = 64;
    height = 64;
}

Apple::~Apple() {}

void Apple::update(Player &player) {
    GameObject::update();
}

void Apple::draw() {
    SDL_Rect appleSprite = defineSpriteSection(0, 192, width, height);
    GameObject::draw(&appleSprite);
}
