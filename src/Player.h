#pragma once
#include "GameObject.h"
#include "TailSegment.h"
#include <vector>

enum direction { DIR_RIGHT, DIR_LEFT, DIR_UP, DIR_DOWN };

class Player : public GameObject {
  public:
    Player();
    Player(int x, int y, const std::string &path);
    ~Player();

    // Draw the snake to the screen
    void draw();

    // Update the snake position
    void update();

    // Set the direction of the snake
    void setDirection(int direction);

    // Set the direction of the snake
    int getDirection();

    // Add one to the lenght of the snakes tail
    void increaseSize();

    // Subtract one from the snakes tail
    void decreaseSize();

    // Get the size of the snake tail
    int getSize();

    // Returns if the player should be dead or not due to collision with it's own tail
    bool isDead();

    // Returns wether or not the given gameobject collides with the snake
    bool collides(GameObject *other);

    // This will prevent the head from turning straight back into its neck
    bool canTurn(int direction);

  private:
    int direction, size, turntype;
    float oldX, oldY, oldDir;
    std::vector<TailSegment *> tail;

    // Draw the tail of the snake
    void drawTailSegment();

    // Finds out how the tail portions of the snake should be drawn
    void figureOutBends(GameObject *infront, TailSegment *current, GameObject *after);

    // Helper tests for figureOutBends since they got a little complicated
    bool topToRight(GameObject *infront, TailSegment *current, GameObject *after);
    bool topToLeft(GameObject *infront, TailSegment *current, GameObject *after);
    bool bottomToRight(GameObject *infront, TailSegment *current, GameObject *after);
    bool bottomToLeft(GameObject *infront, TailSegment *current, GameObject *after);

    // Edge cases for when the current part is alone in a corner
    bool topLeftEdgeCase(GameObject *infront, TailSegment *current, GameObject *after);
    bool topRightEdgeCase(GameObject *infront, TailSegment *current, GameObject *after);
    bool bottomLeftEdgeCase(GameObject *infront, TailSegment *current, GameObject *after);
    bool bottomRightEdgeCase(GameObject *infront, TailSegment *current, GameObject *after);
};
