#ifndef INCLUDE_GAMEOBJECT
#define INCLUDE_GAMEOBJECT

#include <vector>

/// These enum values denote the sprite sets available for items on screen.
enum Type {
    PACMAN,
    BLINKY,
    PINKY,
    INKY,
    CLYDE,
    SCARED,
    SCAREDINV,
    CHERRY,
    STRAWBERRY,
    ORANGE,
    LEMON,
    APPLE,
    GRAPES,
    DOT,
    ENERGIZER,
    WALL,
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE
};

/// An enum to denote the direction of an item on screen.
enum Direction { UP, DOWN, LEFT, RIGHT };

struct Point {
    int x;
    int y;

    // Struct constructor
    Point(int n_x, int n_y) {x = n_x; y = n_y;};
};

class Character {
    public:
    
    Character(int, int, Type, Direction);

    void setPosition(int, int);                     // Sets position of current object using int inputs
    void setPosition(Point);                          // Sets position of object using Pos input struct
    Point getPosition() const;                        // Gets current position of current object
    
    void setType(Type);                             // Sets type
    Type getType() const;                           // Gets type

    void setDir(Direction);                         // Sets direction
    Direction getDir() const;                       // Gets direction

    virtual void move(std::vector<std::vector<int>>*);                             // Moves one tile in current facing direction, needs map input
    void updatePositionOnMap(std::vector<std::vector<int>>*, Point) const;                           // 

    private:

    int x;
    int y;
    Type type;
    Direction dir;

    bool isMoveColliding(const std::vector<std::vector<int>>*) const;

};

#endif