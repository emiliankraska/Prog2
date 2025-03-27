#include "Character.hpp"
#include <iostream>

// Constructor for class
Character::Character(int n_x, int n_y, Type n_type, Direction n_dir)
{
    setPosition(n_x, n_y);
    setType(n_type);
    setDir(n_dir);
}

// Checks around the current position, using direction of the object to determine if we can move in the given direction
bool Character::isMoveColliding(const std::vector<std::vector<int>> *map) const
{

    // Checking our direction and looking at the map to see if the postiions are free
    switch (dir)
    {

    // For UP and DOWN we can simply check, since we can not go over border on top and bottom
    case UP:
        if ((*map)[y - 1][x] == 0)
        {
            return false;
        }
        return true;

    case DOWN:
        if ((*map)[y + 1][x] == 0)
        {
            return false;
        }
        return true;

    // For right and left, we have to be more careful, and also check over the border, depending on our position
    case RIGHT:
        if (x == (*map)[0].size() - 1)
        { // If we get on the final, we are for guaranteed to be allowed to move right
            return false;
        }

        // Normal checking on the map
        if ((*map)[y][x + 1] == 0)
        {
            return false;
        }
        return true;

    case LEFT:
        if (x == 0)
        { // If we are all the way left, we are guaranteed to be allowed to move left
            return false;
        }

        // Normal checking on the map
        if ((*map)[y][x - 1] == 0)
        {
            return false;
        }
        return true;

    default:
        std::cout << "Error in handling direction. Direction is: " << dir << ", which resulted in error." << std::endl;
        return true;
    }
}

void Character::updatePositionOnMap(std::vector<std::vector<int>> *map, Point oldPosition) const
{
    // We change old position to 0, setting it back to nothing
    (*map)[oldPosition.y][oldPosition.x] = 0;
    (*map)[y][x] = getType();
}

void Character::move(std::vector<std::vector<int>> *map)
{
    // We need to store old position so we can remove ourselves from the map
    Point oldPosition(x, y);

    if (isMoveColliding(map))
    { // If move collides, we can not move, do nothing
        return;
    }

    switch (dir)
    {
    case UP:
        setPosition(x, y - 1);
        break;

    case DOWN:
        setPosition(x, y + 1);
        break;

    case RIGHT:
        if (x == (*map)[0].size() - 1)
        { // End of map reached, skip to other side
            setPosition(0, y);
        }
        else
        {
            setPosition(x + 1, y);
        }
        break;

    case LEFT:
        if (x == 0)
        { // End of the map reached, skip to other side
            setPosition((*map)[0].size() - 1, y);
        }
        else
        {
            setPosition(x - 1, y);
        }
        break;

    default: // We do not need error message here, will get it in isMoveColliding() function
        break;
    }

    updatePositionOnMap(map, oldPosition);
}
