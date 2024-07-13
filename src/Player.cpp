#include "Player.h"
#include "SDL/SDLManager.h"
#include <cmath>
#include <iostream>

Player::Player() : GameObject() {
    height = 0;
    width = 0;
    direction = DIR_RIGHT;
    size = 0;
}

Player::Player(int x, int y, const std::string &path) : GameObject(x, y, path) {
    height = 64;
    width = 64;
    direction = DIR_RIGHT;
    size = 0;
    increaseSize();
}

Player::~Player() {
    if (tail.size() >= 1) {
        // Free all the memory allocated for the tail
        std::vector<TailSegment *>::iterator it;

        for (it = tail.begin(); it != tail.end(); ++it) {

            GameObject *current = *it;

            if (current != nullptr) {
                // Free the allocated memory
                delete current;
            }
        }
        tail.clear();
    }
}

// Draw the snake to the screen
void Player::draw() {
    // Draw head depending on which direction the player is facing
    switch (direction) {
    case DIR_RIGHT: {
        SDL_Rect playerSprite = defineSpriteSection(256, 0, width, height);
        GameObject::draw(&playerSprite);
        break;
    }
    case DIR_LEFT: {
        SDL_Rect playerSprite = defineSpriteSection(192, 64, width, height);
        GameObject::draw(&playerSprite);
        break;
    }
    case DIR_UP: {
        SDL_Rect playerSprite = defineSpriteSection(192, 0, width, height);
        GameObject::draw(&playerSprite);
        break;
    }
    case DIR_DOWN: {
        SDL_Rect playerSprite = defineSpriteSection(256, 64, width, height);
        GameObject::draw(&playerSprite);
        break;
    }
    }

    // Draw the tail parts
    drawTailSegment();
}

// Update the snake position
void Player::update() {
    // Update the tail positions before moving the head
    float tempX, tempY, tempDir;
    for (int i = 0; i < size; i++) {
        if (i > 0) {
            tempX = tail.at(i)->x;
            tempY = tail.at(i)->y;
            tempDir = tail.at(i)->getDirection();
            tail.at(i)->x = oldX;
            tail.at(i)->y = oldY;
            tail.at(i)->setDirection(oldDir);
            oldX = tempX;
            oldY = tempY;
            oldDir = tempDir;
            tail.at(i)->update();
        } else {
            oldX = tail.at(0)->x;
            oldY = tail.at(0)->y;
            oldDir = tail.at(0)->getDirection();
            tail.at(0)->x = x;
            tail.at(0)->y = y;
            tail.at(0)->setDirection(direction);
            tail.at(0)->update();
        }
    }

    // Move the head of the snake
    switch (direction) {
    case DIR_RIGHT:
        x += width;
        break;
    case DIR_LEFT:
        x -= width;
        break;
    case DIR_UP:
        y -= height;
        break;
    case DIR_DOWN:
        y += height;
        break;
    }

    // If we go outside the screen reappear on the opposite side
    if (x >= SDLManager::Instance().getWindowWidth()) {
        x = 0;
    } else if (x < 0) {
        x = SDLManager::Instance().getWindowWidth();
        // Fit to the grid
        x = round(x / 64) * 64;
        x -= width;
    } else if (y >= SDLManager::Instance().getWindowHeight()) {
        y = 0;
    } else if (y < 0) {
        y = SDLManager::Instance().getWindowHeight();
        // Fit to the grid
        y = round(y / 64) * 64;
        y -= height;
    }
}

// Set the direction of the snake
void Player::setDirection(int direction) {
    this->direction = direction;
}

// Set the direction of the snake
int Player::getDirection() {
    return direction;
}

// Add one to the lenght of the snakes tail
void Player::increaseSize() {
    TailSegment *tailSegment = new TailSegment;

    // Make sure the new segment spawns at the right location
    tailSegment->x = oldX;
    tailSegment->y = oldY;
    tailSegment->setDirection(oldDir);

    tail.push_back(tailSegment);
    size++;
}

// Subtract one from the snakes tail
void Player::decreaseSize() {
    if (tail.size() > 1) {
        delete tail.back();
        tail.pop_back();
        size--;
    }
}

// Get the size of the snake tail
int Player::getSize() {
    return tail.size();
}

// Returns if the player should be dead or not due to collision with it's own tail
bool Player::isDead() {
    std::vector<TailSegment *>::iterator it;

    // Check each tailsegment for a crash with the head
    for (it = tail.begin(); it != tail.end(); ++it) {
        TailSegment *tail = *it;
        if (tail != nullptr) {
            if (tail->x == x && tail->y == y) {
                return true;
            }
        }
    }

    // Live to fight another day
    return false;
}

// Returns wether or not the given gameobject collides with the snake
bool Player::collides(GameObject *other) {
    // Does other collide with the head
    if ((x == other->x) && (y == other->y)) {
        return true;
    }

    // Check if other collides with any parts of the tail
    std::vector<TailSegment *>::iterator it;
    for (it = tail.begin(); it != tail.end(); ++it) {
        TailSegment *tail = *it;

        if (tail != nullptr) {
            if ((tail->x == other->x) && (tail->y == other->y)) {
                return true;
            }
        }
    }

    return false;
}

// This will prevent the head from turning straight back into its neck
bool Player::canTurn(int direction) {
    switch (direction) {
    case DIR_RIGHT:
        if ((x == (tail.at(0)->x - width) && y == tail.at(0)->y) ||
            ((x == (SDLManager::Instance().getWindowWidth() - width)) && (tail.at(0)->x == 0)) &&
                (y == tail.at(0)->y)) {
            return false;
        }
        break;
    case DIR_DOWN:
        if ((x == tail.at(0)->x && y == (tail.at(0)->y - height)) ||
            ((y == (SDLManager::Instance().getWindowHeight() - height)) && (tail.at(0)->y == 0)) &&
                (x == tail.at(0)->x)) {
            return false;
        }
        break;
    case DIR_LEFT:
        if ((x == (tail.at(0)->x + width)) && (y == tail.at(0)->y) ||
            ((x == 0) && (tail.at(0)->x == SDLManager::Instance().getWindowWidth() - width)) && (y == tail.at(0)->y)) {
            return false;
        }
        break;
    case DIR_UP:
        if ((x == tail.at(0)->x && y == (tail.at(0)->y + height)) ||
            ((y == 0) && (tail.at(0)->y == SDLManager::Instance().getWindowHeight() - height)) &&
                (x == tail.at(0)->x)) {
            return false;
        }
        break;
    }

    return true;
}

void Player::drawTailSegment() {
    std::vector<TailSegment *>::iterator it;
    for (it = tail.begin(); it != tail.end(); ++it) {
        // Draw the tail tip if we are at the last element
        if (it != tail.end() && it + 1 == tail.end()) {
            TailSegment *snaketail = *it;
            if (snaketail != nullptr) {
                snaketail->drawTip();
            }
        }
        // Draw the mid sections
        else if (it != tail.begin()) {
            TailSegment *snaketail = *it;
            if (snaketail != nullptr) {
                TailSegment *prevSegment = *(it - 1);
                if (prevSegment != nullptr) {
                    TailSegment *nextSegment = *(it + 1);
                    if (nextSegment != nullptr) {
                        figureOutBends(prevSegment, snaketail, nextSegment);
                    }
                }
            }
        }
        // Draw the first piece
        else {
            TailSegment *snaketail = *it;
            if (snaketail != nullptr) {
                TailSegment *nextSegment = *(it + 1);
                if (nextSegment != nullptr) {
                    figureOutBends(this, snaketail, nextSegment);
                }
            }
        }
    }
}

// Finds out how the tail portions of the snake should be drawn
void Player::figureOutBends(GameObject *infront, TailSegment *current, GameObject *after) {
    if (topToRight(infront, current, after)) {
        current->draw(4);
    } else if (topToLeft(infront, current, after)) {
        current->draw(5);
    } else if (bottomToRight(infront, current, after)) {
        current->draw(6);
    } else if (bottomToLeft(infront, current, after)) {
        current->draw(7);
    } else {
        current->draw(current->getDirection());
    }
}

// Return true if the combination of infront, current and after needs a top to right bend
bool Player::topToRight(GameObject *infront, TailSegment *current, GameObject *after) {
    return ((infront->x == current->x + current->width) && (infront->y == current->y) &&
            ((after->x == current->x) && (after->y == current->y - current->height))) ||
           ((after->x == (current->x + current->width) && after->y == current->y) &&
            ((infront->x == current->x) && (infront->y == current->y - current->height))) ||
           ((infront->x == current->x) &&
            (infront->y == current->y + SDLManager::Instance().getWindowHeight() - current->height) &&
            (after->x == current->x + current->width)) ||
           ((after->x == current->x) &&
            (after->y == current->y + SDLManager::Instance().getWindowHeight() - current->height) &&
            (infront->x == current->x + current->width)) ||
           ((infront->x == current->x - SDLManager::Instance().getWindowWidth() + current->width) &&
            (infront->y == current->y) && (after->x == current->x) && (after->y == current->y - current->height)) ||
           ((after->x == current->x - SDLManager::Instance().getWindowWidth() + current->width) &&
            (after->y == current->y) && (infront->x == current->x) && (infront->y == current->y - current->height)) ||
           (topRightEdgeCase(infront, current, after));
}

// Return true if the combination of infront, current and after needs a top to left bend
bool Player::topToLeft(GameObject *infront, TailSegment *current, GameObject *after) {
    return ((infront->x == (current->x - current->width) && infront->y == current->y) &&
            ((after->x == current->x) && (after->y == current->y - current->height))) ||
           ((after->x == (current->x - current->width) && after->y == current->y) &&
            ((infront->x == current->x) && (infront->y == current->y - current->height))) ||
           ((infront->x == current->x) &&
            (infront->y == current->y + SDLManager::Instance().getWindowHeight() - current->height) &&
            (after->x == current->x - current->width)) ||
           ((after->x == current->x) &&
            (after->y == current->y + SDLManager::Instance().getWindowHeight() - current->height) &&
            (infront->x == current->x - current->width)) ||
           ((infront->x == current->x + SDLManager::Instance().getWindowWidth() - current->width) &&
            (infront->y == current->y) && (after->y == current->y - current->height)) ||
           ((after->x == current->x + SDLManager::Instance().getWindowWidth() - current->width) &&
            (after->y == current->y) && (infront->y == current->y - current->height)) ||
           (topLeftEdgeCase(infront, current, after));
}

// Return true if the combination of infront, current and after needs a bottom to right bend
bool Player::bottomToRight(GameObject *infront, TailSegment *current, GameObject *after) {
    return ((infront->x == (current->x + current->width) && infront->y == current->y) &&
            ((after->x == current->x) && (after->y == current->y + current->height))) ||
           ((after->x == (current->x + current->width) && after->y == current->y) &&
            ((infront->x == current->x) && (infront->y == current->y + current->height))) ||
           ((infront->x == current->x) &&
            (infront->y == current->y - SDLManager::Instance().getWindowHeight() + current->height) &&
            (after->x == current->x + current->width) && (after->y == current->y)) ||
           ((after->x == current->x) &&
            (after->y == current->y - SDLManager::Instance().getWindowHeight() + current->height) &&
            (infront->x == current->x + current->width) && (infront->y == current->y)) ||
           ((infront->x == current->x - SDLManager::Instance().getWindowWidth() + current->width) &&
            (infront->y == current->y) && (after->x == current->x) && (after->y == current->y + current->height)) ||
           ((after->x == current->x - SDLManager::Instance().getWindowWidth() + current->width) &&
            (after->y == current->y) && (infront->x == current->x) && (infront->y == current->y + current->height)) ||
           (bottomRightEdgeCase(infront, current, after));
}

// Return true if the combination of infront, current and after needs a bottom to left bend
bool Player::bottomToLeft(GameObject *infront, TailSegment *current, GameObject *after) {
    return ((infront->x == (current->x - current->width) && infront->y == current->y) &&
            ((after->x == current->x) && (after->y == current->y + current->height))) ||
           ((after->x == (current->x - current->width) && after->y == current->y) &&
            ((infront->x == current->x) && infront->y == current->y + current->height)) ||
           ((infront->x == current->x) &&
            (infront->y == current->y - SDLManager::Instance().getWindowHeight() + current->height) &&
            (after->x == current->x - current->width) && (after->y == current->y)) ||
           ((after->x == current->x) &&
            (after->y == current->y - SDLManager::Instance().getWindowHeight() + current->height) &&
            (infront->x == current->x - current->width) && (infront->y == current->y)) ||
           ((infront->x == current->x + SDLManager::Instance().getWindowWidth() - current->width) &&
            (infront->y == current->y) && (after->x == current->x) && (after->y == current->y + current->height)) ||
           ((after->x == current->x + SDLManager::Instance().getWindowWidth() - current->width) &&
            (after->y == current->y) && (infront->x == current->x) && (infront->y == current->y + current->height)) ||
           (bottomLeftEdgeCase(infront, current, after));
}

bool Player::topLeftEdgeCase(GameObject *infront, TailSegment *current, GameObject *after) {
    return (infront->x == SDLManager::Instance().getWindowWidth() - width && infront->y == 0) &&
               (current->x == 0 && current->y == 0) &&
               (after->x == 0 && after->y == SDLManager::Instance().getWindowHeight() - height) ||
           (after->x == SDLManager::Instance().getWindowWidth() - width && after->y == 0) &&
               (current->x == 0 && current->y == 0) &&
               (infront->x == 0 && infront->y == SDLManager::Instance().getWindowHeight() - height);
    ;
}

bool Player::topRightEdgeCase(GameObject *infront, TailSegment *current, GameObject *after) {
    return (infront->x == 0 && infront->y == 0) &&
               (current->x == SDLManager::Instance().getWindowWidth() - width && current->y == 0) &&
               (after->x == SDLManager::Instance().getWindowWidth() - width &&
                after->y == SDLManager::Instance().getWindowHeight() - height) ||
           (after->x == 0 && after->y == 0) &&
               (current->x == SDLManager::Instance().getWindowWidth() - width && current->y == 0) &&
               (infront->x == SDLManager::Instance().getWindowWidth() - width &&
                infront->y == SDLManager::Instance().getWindowHeight() - height);
}

bool Player::bottomLeftEdgeCase(GameObject *infront, TailSegment *current, GameObject *after) {
    return (infront->x == 0) && (infront->y == 0) && (current->x == 0) &&
               (current->y == SDLManager::Instance().getWindowHeight() - height) &&
               (after->x == SDLManager::Instance().getWindowWidth() - width) &&
               (after->y == SDLManager::Instance().getWindowHeight() - height) ||
           (after->x == 0) && (after->y == 0) && (current->x == 0) &&
               (current->y == SDLManager::Instance().getWindowHeight() - height) &&
               (infront->x == SDLManager::Instance().getWindowWidth() - width) &&
               (infront->y == SDLManager::Instance().getWindowHeight() - height);
}

bool Player::bottomRightEdgeCase(GameObject *infront, TailSegment *current, GameObject *after) {
    return (infront->x == SDLManager::Instance().getWindowWidth() - width) && (infront->y == 0) &&
               (current->x == SDLManager::Instance().getWindowWidth() - width) &&
               (current->y == SDLManager::Instance().getWindowHeight() - height) && (after->x == 0) &&
               (after->y == SDLManager::Instance().getWindowHeight() - height) ||
           (after->x == SDLManager::Instance().getWindowWidth() - width) && (after->y == 0) &&
               (current->x == SDLManager::Instance().getWindowWidth() - width) &&
               (current->y == SDLManager::Instance().getWindowHeight() - height) && (infront->x == 0) &&
               (infront->y == SDLManager::Instance().getWindowHeight() - height);
}
