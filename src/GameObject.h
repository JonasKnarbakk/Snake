#pragma once

#include "SDL/SDLBmp.h"
#include <string>

class GameObject {
  public:
    float x, y;
    int width, height;
    SDLBmp *sprite;

    GameObject();
    GameObject(int x, int y, std::string path);
    virtual ~GameObject();

    // Default update
    virtual void update();

    // Default draw
    virtual void draw();

    // Default draw for a portion of the image
    virtual void draw(SDL_Rect *rect);

    // Collision detection
    bool isColliding(GameObject other);

  protected:
    // Returns a SDL_Rect that defines what section of the spritesheet should be drawn
    SDL_Rect defineSpriteSection(int x, int y, int width, int height);
};