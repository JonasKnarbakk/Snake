#pragma once

#include <vector>
#include "GameObject.h"
#include "Apple.h"

class Spawner {
  public:
    Spawner();
    ~Spawner();

    // Spawn a new gameobject
    void spawn(GameObject *object);

    // Removes an gameobject from the spawned vector
    void despawn(GameObject *object);

    // Calls the update function of every spawned object
    void update();

    // Calls the draw function of every spawned object
    void draw();

    // Free all the allocated memeory in the spawned vector
    void cleanUp();

    const std::vector<GameObject *> &getVector() const;

  private:
    std::vector<GameObject *> spawned;
    std::vector<GameObject *>::iterator it;
};