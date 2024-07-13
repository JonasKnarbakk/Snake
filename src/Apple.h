#pragma once
#include "GameObject.h"
#include "Player.h"
class Apple : public GameObject {
  public:
    Apple(int x, int y);
    ~Apple();

    // Update apple
    void update(Player &player);

    // Draw the game object to the screeen
    void draw();
};