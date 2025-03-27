#include "Ghosts.hpp"

Ghost::Ghost(int n_x, int n_y, Type n_type, Direction n_dir, Character* n_target) : Character(n_x, n_y, n_type, n_dir) {
    setTarget(n_target);
}

void Ghost::setTarget(Character* n_target) {
    target = n_target;
}

Character* Ghost::getTarget() const {
    return target;
}

void Ghost::onGhostEaten() {
    
}

// BLINKY -------------------
Blinky::Blinky(int n_x, int n_y, Direction n_dir, Character* n_target) : Ghost(n_x, n_y, BLINKY, n_dir, n_target) {}

Direction Blinky::findMoveDirection() const {

}

// PINKY
Pinky::Pinky(int n_x, int n_y, Direction n_dir, Character* n_target) : Ghost(n_x, n_y, PINKY, n_dir, n_target) {}

Direction Pinky::findMoveDirection() const {

}

// INKY
Inky::Inky(int n_x, int n_y, Direction n_dir, Character* n_target) : Ghost(n_x, n_y, INKY, n_dir, n_target) {}

Direction Inky::findMoveDirection() const {

}

// CLYDE
Clyde::Clyde(int n_x, int n_y, Direction n_dir, Character* n_target) : Ghost(n_x, n_y, CLYDE, n_dir, n_target) {}

Direction Clyde::findMoveDirection() const {
    
}