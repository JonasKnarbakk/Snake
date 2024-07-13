#include "Spawner.h"

Spawner::Spawner() {}

Spawner::~Spawner() {}

// Spawn a new gameobject
void Spawner::spawn(GameObject *object) {
    spawned.push_back(object);
}

// Removes an gameobject from the spawned vector
void Spawner::despawn(GameObject *object) {
    std::vector<GameObject *>::iterator toRemove;

    // Find the object to remove
    for (it = spawned.begin(); it != spawned.end(); ++it) {
        GameObject *current = *it;

        if (current != nullptr) {
            if (current == object) {
                // Free the allocated memory
                delete current;

                // Save the reference to remove later
                toRemove = it;
            }
        }
    }

    // Remove the object
    spawned.erase(toRemove);
}

// Calls the update function of every spawned object
void Spawner::update() {
    for (it = spawned.begin(); it != spawned.end(); ++it) {
        GameObject *object = *it;

        if (object != nullptr) {
            object->update();
        }
    }
}

// Calls the draw function of every spawned object
void Spawner::draw() {
    for (it = spawned.begin(); it != spawned.end(); ++it) {
        GameObject *object = *it;

        if (object != nullptr) {
            object->draw();
        }
    }
}

// Free all the allocated memeory in the spawned vector
void Spawner::cleanUp() {
    for (it = spawned.begin(); it != spawned.end(); ++it) {

        GameObject *current = *it;

        if (current != nullptr) {
            // Free the allocated memory
            delete current;
        }
    }

    spawned.clear();
}

const std::vector<GameObject *> &Spawner::getVector() const {
    return spawned;
}
