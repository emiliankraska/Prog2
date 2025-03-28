#include "Ghosts.hpp"
#include <ctime>
#include "Game.hpp"
#include <bits/stdc++.h>

Ghost::Ghost(int n_x, int n_y, Type n_type, Direction n_dir, Character *n_target) : Character(n_x, n_y, n_type, n_dir)
{
    // We initialize target, since this is shared between all derivate classes
    setTarget(n_target);
}

// Sets target
void Ghost::setTarget(Character *n_target)
{
    target = n_target;
}

// Gets target
Character *Ghost::getTarget() const
{
    return target;
}

// Finds move direction for next move. This just returns UP for standard ghost
Direction Ghost::findMoveDirection(std::vector<std::vector<int>> *map)
{
    // Place holder so we can overwrite move() function for all subsequent ghosts
    return Direction::UP;
}

// Main bread and butter, performs the move. Is the same for every derived class, since only findMoveDirection() really changes
// Takes the Game object to use the map, returns nothing. For this class, uses the ghostMap isntead of normal map, since we are dealing with ghosts
void Ghost::move(Game *game)
{
    dir = findMoveDirection(&(game->getGhostMap())); // Finding direction from overwritten function for every ghost
    if (isMoveColliding(&(game->getGhostMap())))
    { // If move collides with wall, we should just stop
        return;
    }
    Point oldPosition = Point(x, y);                     // Remembering old position
    setPositionFromDir((game->getGhostMap())[0].size());      // Setting our position from the direction we are facing
    updatePositionOnMap(&(game->getGhostMap()), oldPosition); // Updating the map position
}

// BLINKY -------------------
Blinky::Blinky(int n_x, int n_y, Direction n_dir, Character *n_target) : Ghost(n_x, n_y, BLINKY, n_dir, n_target)
{
    setStartingPosition(Point(n_x, n_y));
}

// Function that finds the direction it needs to move in based on the angle between the target and itself
Direction Blinky::findMoveDirection(std::vector<std::vector<int>> *map)
{

    // Find the angle between the ghost and the target. See GameObjectStruct.hpp for Point functions such as getAngle()
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

// Function to reset the intiializationRoute for the patroling algorithm ghosts.
// Simply pops all the values from the queue until none remain, then exits. Returns nothing.
void Pinky::resetInitializeRoute()
{
    while (getInitialRouteLength() > 0)
    {
        initializationRoute.pop();
    }
}

// Returns front value from the intializationRoute queue and pops it
Direction Pinky::pullFromInitializationQueue()
{
    Direction n_dir = initializationRoute.front();
    initializationRoute.pop();
    return n_dir;
};

// Function to generate the patrol route taken by Pinky
void Pinky::doInitialize()
{
    // Route parameters
    // Top left: (9, 11)
    // Top right: (18, 11)
    // Bottom right (18, 15)
    // Bottom left (9, 15)

    // Setting all corner positions, which we will return from this function
    setPatrolRoute({Point(9, 11), Point(9, 15), Point(18, 15), Point(18, 11)});

    // Deleting old entries if they exist, from intitializationRoute queue
    resetInitializeRoute();

    // Generating initializationRoute variable, which is a constant
    pushInitializationRoute(Direction::UP);
    pushInitializationRoute(Direction::UP);
    pushInitializationRoute(Direction::LEFT);
    pushInitializationRoute(Direction::LEFT);
    pushInitializationRoute(Direction::LEFT);
    pushInitializationRoute(Direction::LEFT);

    // Setting first stage
    setStage(0);

    // Enabling the fact that we are intialized and can move on
    setInitialized(true);
}

Direction Pinky::findMoveDirection(std::vector<std::vector<int>> *map)
{
    // If we are not yet initialized, we need to call doInitialize() to set some variables we need
    if (!getInitialized())
    {
        doInitialize();
    }

    // Setting up difference point to 0,0 so we can acces throughout function
    Point difference = Point(0, 0);

    // If our initialization is not finished, we should follow the intializationRoute
    if (getInitialRouteLength() != 0)
    {
        return pullFromInitializationQueue();
    }
    else    // Otherwise, we just use the algorithm we decided on, in this case patroling
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

        // Get difference between required position and current postion
        difference = getPatrolRoute()[getStage()] - getPosition();  
    }

    // Since difference will always be (dx, 0) or (dy, 0), we can just use if statements:
    if (difference.x != 0)
    {   // Simply checking where we need to go based on difference
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
    setType(INKY);      // Setting type to INKY, since we are derived from PINKY
    setStartingPosition(Point(n_x, n_y));
}

// This function is devoid of comments.
// If you need more comments on how this works, see Pinky::doInitialize(), it is just the same
void Inky::doInitialize()
{
    // Setting patrol route corners
    setPatrolRoute({Point(6, 5), Point(21, 5), Point(21, 21), Point(6, 21)});

    resetInitializeRoute();

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

    setStage(0);
    setInitialized(true);
}

// CLYDE
Clyde::Clyde(int n_x, int n_y, Direction n_dir, Character *n_target) : Ghost(n_x, n_y, CLYDE, n_dir, n_target)
{
    setStartingPosition(Point(n_x, n_y));
}

// Function for the random direction moving for Clyde. Returns a Direction based on the map
Direction Clyde::findMoveDirection(std::vector<std::vector<int>> *map)
{
    // Random algorithm using a buffer, so it chooses direction and sticks with that direction for a random number of moves between 0 and 5
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

    // Returning this random direction
    return randomDir;
}
