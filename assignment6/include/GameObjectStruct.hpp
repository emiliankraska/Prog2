/// \file
/// GameObjectStruct.h

#ifndef SRC_GAMEOBJECTSTRUCT_H
#define SRC_GAMEOBJECTSTRUCT_H

/// These enum values denote the sprite sets available for items on screen.
enum Type
{
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
enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
struct Point
{
    int x;
    int y;

    // Struct constructor
    Point(int n_x, int n_y)
    {
        x = n_x;
        y = n_y;
    };
};
/// This represents an item that is drawn onto the screen.
struct GameObjectStruct
{
    /// x-position of the item.
    int x;
    /// y-position of the item.
    int y;
    /// The appearance of the item (sprite set).
    Type type;
    /// The direction of the item (sprite selection).
    Direction dir;

    // ✅ Setters
    void setPosition(int newX, int newY)
    {
        x = newX;
        y = newY;
    }
    void setPosition(Point p)
    {
        x = p.x;
        y = p.y;
    }
    void setType(Type newType) { type = newType; }
    void setDir(Direction newDir) { dir = newDir; }

    // ✅ Getters
    Point getPosition() const { return {x, y}; }
    Type getType() const { return type; }
    Direction getDir() const { return dir; }
};

#endif // SRC_GAMEOBJECTSTRUCT_H
