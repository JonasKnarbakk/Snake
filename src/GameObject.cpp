#include "GameObject.h"

GameObject::GameObject() {
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    sprite = nullptr;
}

GameObject::GameObject(int x, int y, std::string path) {
    this->x = x;
    this->y = y;
    sprite = new SDLBmp(path);
    width = sprite->getWidth();
    height = sprite->getHeight();
}

GameObject::~GameObject() {}

void GameObject::update() {}

void GameObject::draw() {
    if (sprite != nullptr) {
        sprite->x = x;
        sprite->y = y;
        sprite->draw();
    }
}

void GameObject::draw(SDL_Rect *rect) {
    if (sprite != nullptr) {
        sprite->x = x;
        sprite->y = y;
        sprite->draw(rect);
    }
}

bool GameObject::isColliding(GameObject other) {
    return (this->x > other.x && this->x < other.x + other.width) &&
           (this->y > other.y && this->y < other.y + other.height);
}

SDL_Rect GameObject::defineSpriteSection(int x, int y, int width, int height) {
    SDL_Rect section;
    section.x = x;
    section.y = y;
    section.w = width;
    section.h = height;
    return section;
}
