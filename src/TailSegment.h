#pragma once
#include "GameObject.h"

class TailSegment : public GameObject {
  public:
    TailSegment();
    ~TailSegment();

    // Draw a tail segment, type defines what part
    void draw(int type);

    // Draw the tail tip
    void drawTip();

    // Returns the direction of the tail segment
    int getDirection();

    // Sets the direction of the tail segment
    void setDirection(int dir);

  private:
    int direction;
};