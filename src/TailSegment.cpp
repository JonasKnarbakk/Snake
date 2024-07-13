#include "TailSegment.h"
#include "Player.h"

TailSegment::TailSegment() : GameObject(0, 0, "Assets/gfx/snake-graphics.bmp") {
    width = 64;
    height = 64;
    direction = DIR_RIGHT;
}

TailSegment::~TailSegment() {}

void TailSegment::draw(int type) {
    if (type == DIR_RIGHT || type == DIR_LEFT) {
        SDL_Rect tailSegmentSprite = defineSpriteSection(64, 0, width, height);
        GameObject::draw(&tailSegmentSprite);
    } else if (type == DIR_UP || type == DIR_DOWN) {
        SDL_Rect tailSegmentSprite = defineSpriteSection(128, 64, width, height);
        GameObject::draw(&tailSegmentSprite);
    } else {
        // Draw the turn segments
        switch (type) {
            // top to right segment
        case 4: {
            SDL_Rect tailSegmentSprite = defineSpriteSection(0, 64, width, height);
            GameObject::draw(&tailSegmentSprite);
            break;
            // left to top segment
        }
        case 5: {
            SDL_Rect tailSegmentSprite = defineSpriteSection(128, 128, width, height);
            GameObject::draw(&tailSegmentSprite);
            break;
            // bottom to right segment
        }
        case 6: {
            SDL_Rect tailSegmentSprite = defineSpriteSection(0, 0, width, height);
            GameObject::draw(&tailSegmentSprite);
            break;
            // left to down segment
        }
        case 7: {
            SDL_Rect tailSegmentSprite = defineSpriteSection(128, 0, width, height);
            GameObject::draw(&tailSegmentSprite);
            break;
        }
        }
    }
}

void TailSegment::drawTip() {
    switch (direction) {
    case DIR_RIGHT: {
        SDL_Rect tailSegmentSprite = defineSpriteSection(256, 128, width, height);
        GameObject::draw(&tailSegmentSprite);
        break;
    }
    case DIR_LEFT: {
        SDL_Rect tailSegmentSprite = defineSpriteSection(192, 192, width, height);
        GameObject::draw(&tailSegmentSprite);
        break;
    }
    case DIR_UP: {
        SDL_Rect tailSegmentSprite = defineSpriteSection(192, 128, width, height);
        GameObject::draw(&tailSegmentSprite);
        break;
    }
    case DIR_DOWN: {
        SDL_Rect tailSegmentSprite = defineSpriteSection(256, 192, width, height);
        GameObject::draw(&tailSegmentSprite);
        break;
    }
    }
}

int TailSegment::getDirection() {
    return direction;
}

void TailSegment::setDirection(int dir) {
    direction = dir;
}
