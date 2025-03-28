#ifndef INCLUDE_GAMEOBJECT
#define INCLUDE_GAMEOBJECT

#include <vector>
#include "GameObjectStruct.hpp"

/// These enum values denote the sprite sets available for items on screen.
class Game;
class Character : public GameObjectStruct
{
public:
    Character(int, int, Type, Direction);

    virtual void move(Game *);                                              // Moves one tile in current facing direction, needs map input
    void updatePositionOnMap(std::vector<std::vector<int>> *, Point) const; //

private:
    bool isMoveColliding(const std::vector<std::vector<int>> *) const;
};

#endif