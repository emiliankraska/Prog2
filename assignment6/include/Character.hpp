#ifndef INCLUDE_GAMEOBJECT
#define INCLUDE_GAMEOBJECT

#include <vector>
#include "GameObjectStruct.hpp"
/// These enum values denote the sprite sets available for items on screen.

class Character : public GameObjectStruct
{
public:
    Character(int, int, Type, Direction);

    void setPosition(int, int); // Sets position of current object using int inputs
    void setPosition(Point);    // Sets position of object using Pos input struct
    Point getPosition() const;  // Gets current position of current object

    void setType(Type);   // Sets type
    Type getType() const; // Gets type

    void setDir(Direction);   // Sets direction
    Direction getDir() const; // Gets direction

    virtual void move(std::vector<std::vector<int>> *);                     // Moves one tile in current facing direction, needs map input
    void updatePositionOnMap(std::vector<std::vector<int>> *, Point) const; //
    void setPositionFromDir(int);

    bool isMoveColliding(const std::vector<std::vector<int>> *) const;
private:
};

#endif