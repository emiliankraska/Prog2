#include "Ghosts.hpp"
#include <ctime>
#include "Game.hpp"
#include <bits/stdc++.h>

Ghost::Ghost(int n_x, int n_y, Type n_type, Direction n_dir, Character *n_target) : Character(n_x, n_y, n_type, n_dir)
{
    setTarget(n_target);
}

void Ghost::setTarget(Character *n_target)
{
    target = n_target;
}

Character *Ghost::getTarget() const
{
    return target;
}

void Ghost::onGhostEaten()
{
}

Direction Ghost::findMoveDirection(std::vector<std::vector<int>> *map)
{
    // Place holder so we can overwrite move() function for all subsequent ghosts
    return Direction::UP;
}

void Ghost::move(Game *game)
{
    dir = findMoveDirection(&(game->getMap())); // Finding direction from overwritten function for every ghost
    if (isMoveColliding(&(game->getMap())))
    { // If move collides with wall, we should just stop
        return;
    }
    Point oldPosition = Point(x, y);                     // Remembering old position
    setPositionFromDir((game->getMap())[0].size());      // Setting our position from the direction we are facing
    updatePositionOnMap(&(game->getMap()), oldPosition); // Updating the map position
}

// BLINKY -------------------
Blinky::Blinky(int n_x, int n_y, Direction n_dir, Character *n_target) : Ghost(n_x, n_y, BLINKY, n_dir, n_target)
{
    setStartingPosition(Point(n_x, n_y));
}

Direction Blinky::findMoveDirection(std::vector<std::vector<int>> *map)
{

    // Getting a unit vector between the ghost and pacman
    const double angle = Point(x, y).getAngle(getTarget()->getPosition());
    const double PI = 3.1415;

    // std::cout << "Running through findMoveDirection() for Blinky!" << std::endl;

    // Checking right cone angles
    //  /
    // .
    //  \ 

    if (angle > -PI / 4 && angle < PI / 4)
    {
        return Direction::RIGHT;
    }

    // Checking top cone angles
    // \   /
    //   .

    if (angle <= -PI / 4 && angle >= -3 * PI / 4)
    {
        return Direction::UP;
    }

    // Checking left cone angles
    // \ 
    //  .
    // /

    if (angle < -3 * PI / 4 || angle > 3 * PI / 4)
    {
        return Direction::LEFT;
    }

    // Checking down cone angles
    //   .
    // /   \ 

    if (angle <= 3 * PI / 4 && angle >= PI / 4)
    {
        return Direction::DOWN;
    }

    std::cout << "Error! Did not find direction for Blinky!" << std::endl;
    // If something goes wrong, we simply just go down always
    return Direction::DOWN;
}

// PINKY
Pinky::Pinky(int n_x, int n_y, Direction n_dir, Character *n_target) : Ghost(n_x, n_y, PINKY, n_dir, n_target)
{
    setStartingPosition(Point(n_x, n_y));
}

// Function to generate the patrol route taken by Pinky
void Pinky::doInitialize()
{

    // Top left: (9, 11)
    // Top right: (18, 11)
    // Bottom right (18, 15)
    // Bottom left (9, 15)

    // Setting all corner positions, which we will return from this function
    setPatrolRoute({Point(9, 11), Point(9, 15), Point(18, 15), Point(18, 11)});

    // Generating initializationRoute variable, which is a constant
    pushInitializationRoute(Direction::UP);
    pushInitializationRoute(Direction::UP);
    pushInitializationRoute(Direction::LEFT);
    pushInitializationRoute(Direction::LEFT);
    pushInitializationRoute(Direction::LEFT);
    pushInitializationRoute(Direction::LEFT);

    // Setting first stage
    setStage(0);
    setInitialized(true);
}

Direction Pinky::findMoveDirection(std::vector<std::vector<int>> *map)
{

    if (!getInitialized())
    {
        doInitialize();
    }

    // Setting up difference point to 0,0
    Point difference = Point(0, 0);

    // If our initialization is not finished, we should follow that path
    if (getInitialRouteLength() != 0)
    {
        return pullFromInitializationQueue();
    }
    else
    {
        // We first check if we have reached the end of the stage
        if (getPosition() == getPatrolRoute()[getStage()])
        {
            // If stage is final stage, go back to first one
            if (getStage() == 3)
            {
                setStage(0);
            }
            // Otherwise, just add 1 to stage to indicate next stage
            else
            {
                setStage(getStage() + 1);
            }
        }

        difference = getPatrolRoute()[getStage()] - getPosition();
    }

    // Logic for setting direction
    // Since difference will always be (dx, 0) or (dy, 0), we can just use if statements:
    if (difference.x != 0)
    {
        if (difference.x < 0)
        {
            return Direction::RIGHT;
        }
        else
        {
            return Direction::LEFT;
        }
    }
    else
    {
        if (difference.y < 0)
        {
            return Direction::DOWN;
        }
        else
        {
            return Direction::UP;
        }
    }
}

// INKY
Inky::Inky(int n_x, int n_y, Direction n_dir, Character *n_target) : Pinky(n_x, n_y, n_dir, n_target)
{
    setType(INKY);
    setStartingPosition(Point(n_x, n_y));
}

void Inky::doInitialize()
{
    // Setting patrol route corners
    setPatrolRoute({Point(6, 5), Point(21, 5), Point(21, 21), Point(6, 21)});

    pushInitializationRoute(Direction::UP);
    pushInitializationRoute(Direction::UP);
    pushInitializationRoute(Direction::LEFT);
    pushInitializationRoute(Direction::LEFT);
    pushInitializationRoute(Direction::UP);
    pushInitializationRoute(Direction::UP);
    pushInitializationRoute(Direction::UP);
    pushInitializationRoute(Direction::LEFT);
    pushInitializationRoute(Direction::LEFT);
    pushInitializationRoute(Direction::LEFT);
    pushInitializationRoute(Direction::UP);
    pushInitializationRoute(Direction::UP);
    pushInitializationRoute(Direction::UP);
    pushInitializationRoute(Direction::LEFT);
    pushInitializationRoute(Direction::LEFT);
    pushInitializationRoute(Direction::LEFT);

    // Printing resulting queue
    std::queue<Direction> temp = getInitializationRoute();
    std::cout << "Initialized queue to: (";
    for (int i = 0; i < getInitialRouteLength(); i++)
    {
        std::cout << temp.front() << " ";
        temp.pop();
    }
    std::cout << ")" << std::endl;

    setStage(0);
    setInitialized(true);
}

// CLYDE
Clyde::Clyde(int n_x, int n_y, Direction n_dir, Character *n_target) : Ghost(n_x, n_y, CLYDE, n_dir, n_target)
{
    setStartingPosition(Point(n_x, n_y));
}

Direction Clyde::findMoveDirection(std::vector<std::vector<int>> *map)
{
    // Random algorithm
    Direction randomDir;

    if (moveBuffer > 0)
    { // If move buffer is still not 0, we need to keep moving in this direction
        moveBuffer--;
        randomDir = dir;
    }
    else
    {
        // Setting random seed at current time
        std::srand(time(0));

        // Generating a number of moves that it should make before changing direction, based on random number!
        setMoveBuffer(std::rand() % 5);
        randomDir = static_cast<Direction>(rand() % Direction::RIGHT);
    }

    // while (isMoveColliding(map)) {
    //     randomDir = static_cast<Direction>(3 - static_cast<int>(dir));
    // }

    return randomDir;
}
