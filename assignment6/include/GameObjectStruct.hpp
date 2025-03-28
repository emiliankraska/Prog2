/// \file
/// GameObjectStruct.h

#ifndef SRC_GAMEOBJECTSTRUCT_H
#define SRC_GAMEOBJECTSTRUCT_H

#include <cmath>
#include <iostream>

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

    // Rewriting the != operator, since we need to compare them
    bool operator!=(Point const compare) 
    {
        return (this->x != compare.x || this->y != compare.y);
    }

    bool operator==(Point const compare)
    {
        return (this->x == compare.x && this->y == compare.y);
    }

    // Rewriting - operator, since we will use it in Ghost.h for finding difference vector between Ghost and Pacman
    Point operator-(Point const compare) 
    {
        return Point(compare.x - this->x, compare.y - this->y);
    }

    Point operator/(double const divide)
    {
        return Point(this->x / divide, this->y / divide);
    }

    double getLength() 
    {
        return sqrt((this->x * this->x) + (this->y * this->y));
    }

    Point getUnitVector()
    {
        return Point(this->x / this->getLength(), this->y / this->getLength());
    }

    double getAngle(Point target)
    {
        Point relative = Point(target.x - this->x, target.y - this->y);
        if (relative.x > -1 && relative.x < 1) {
            // std::cout << "Got small x with value: " << relative.x << " with sign: " << relative.y/abs(relative.y) << std::endl;
            if (relative.y / abs(relative.y) < 0)
            {
                // Returning 1.5pi, since we at bottom
                return 1.5  * 3.1415; 
            } 
            else
            {
                // Returning 0.5pi
                return 0.5 * 3.1415;
            }
        }
        // std::cout << "Got angle: " << atan2(relative.y, relative.x) << " for coordinates : (" << relative.x << ", " << relative.y << ")" << std::endl;
        // No edge case, we just return the angle from tan
        return atan2(relative.y, relative.x);
    }
};

#endif // SRC_GAMEOBJECTSTRUCT_H
