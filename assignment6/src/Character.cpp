#include "Character.hpp"
#include <iostream>
#include "Game.hpp"
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
    // Checking our direction and looking at the map to see if the positions are free
    switch (dir)
    {
    case UP:
        if ((*map)[y - 1][x] != 1)
        {
            return false;
        }
        return true;

    case DOWN:
        if ((*map)[y + 1][x] != 1)
        {
            return false;
        }
        return true;

    case RIGHT:
        if (x == (*map)[0].size() - 1)
        { // If we get on the final, we are guaranteed to be allowed to move right
            return false;
        }

        // Normal checking on the map
        if ((*map)[y][x + 1] != 1)
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
        if ((*map)[y][x - 1] != 1)
        {
            return false;
        }
        return true;

    default:
        std::cout << "Error in handling direction. Direction is: " << dir
                  << ", which resulted in error." << std::endl;
        return true;
    }
}

void Character::updatePositionOnMap(std::vector<std::vector<int>> *map, Point oldPosition) const
{
    // We change old position to 0, setting it back to nothing
    //(*map)[oldPosition.y][oldPosition.x] = 0;
    (*map)[y][x] = 0;
}

// void Character::setPositionFromDir(int mapSize)
// {
//     switch (dir)
//     {
//     case UP:
//         if (game->getMap()[x][y - 1] == 2)
//         {
//             std::cout << "Dot here!" << std::endl;
//             game->removeDot(x, y - 1);
//         }
//         setPosition(x, y - 1);
//         break;

//     case DOWN:
//         if (game->getMap()[x][y + 1] == 2)
//         {
//             std::cout << "Dot here!" << std::endl;
//             game->removeDot(x, y + 1);
//         }
//         setPosition(x, y + 1);
//         break;

//     case RIGHT:
//         if (x == game->getMap()[0].size() - 1)
//         { // End of map reached, skip to other side
//             setPosition(0, y);
//         }
//         else
//         {
//             if (game->getMap()[x + 1][y] == 2)
//             {
//                 std::cout << "Dot here!" << std::endl;
//                 game->removeDot(x + 1, y);
//             }
//             setPosition(x + 1, y);
//         }
//         break;

//     case LEFT:
//         if (x == 0)
//         { // End of the map reached, skip to other side
//             setPosition(game->getMap()[0].size() - 1, y);
//         }
//         else
//         {
//             if (game->getMap()[x - 1][y] == 2)
//             {
//                 std::cout << "Calling remove Dot" << std::endl;
//                 game->removeDot(x - 1, y);
//             }
//             setPosition(x - 1, y);
//         }
//         break;

//     default: // We do not need error message here, will get it in isMoveColliding() function
//         break;
//     }
// }
void Character::setPositionFromDir(int mapSize)
{
    switch (dir)
    {
    case UP:
        setPosition(x, y - 1);
        break;

    case DOWN:
        setPosition(x, y + 1);
        break;

    case RIGHT:
        if (x == mapSize - 1)
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
            setPosition(mapSize - 1, y);
        }
        else
        {
            setPosition(x - 1, y);
        }
        break;

    default: // We do not need error message here, will get it in isMoveColliding() function
        break;
    }
}

void Character::move(Game *game)
{
    // We need to store old position so we can remove ourselves from the map
    Point oldPosition(x, y);

    if (isMoveColliding(&(game->getMap())))
    { // If move collides, we can not move, do nothing
        return;
    }

    setPositionFromDir((game->getMap())[0].size());
    updatePositionOnMap(&(game->getMap()), oldPosition);
}
