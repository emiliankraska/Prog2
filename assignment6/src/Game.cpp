#include "Game.hpp"
#include "PointDot.hpp"
#include <iostream>
#include <array>
#include <algorithm>
void Game::addToScore(std::uint32_t points)
{
    score += points;
    if (score % 1000 == 0)
    {
        addFruit();
    }
}
void Game::setScore(std::uint32_t newScore)
{
    score = newScore;
}
void Game::update()
{
    generatePositionBuffers();
    pacman.move(this);
    blinky.move(this);
    inky.move(this);
    pinky.move(this);
    clyde.move(this);
    checkColission();

    if (getLives() <= 0)
    {
        std::cout << "Ending game, no lives left" << std::endl;
        setQuit(true);
    }
}
void Game::printMap() const
{
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[0].size(); x++)
        {
            // Check the value in the map and print accordingly
            if (map[y][x] == 0)
                std::cout << ". "; // Empty space
            else if (map[y][x] == 1)
                std::cout << "# "; // Wall
            else if (map[y][x] == 2)
                std::cout << "P "; // Dot
            else
                std::cout << "? "; // Undefined value
        }
        std::cout << std::endl; // Newline after each row
    }
}
void Game::addDots()
{
    std::size_t cols = (map.empty()) ? 0 : map[0].size();
    std::size_t rows = (map.empty()) ? 0 : map.size();

    for (int i = 0; i < rows - 1; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // && !(pacman.getPosition().x == i && pacman.getPosition().y == j)
            if (map[i][j] == 0 && !(pacman.getPosition().x == i && pacman.getPosition().y == j))
            {
                // std::cout << "Adding Dot with values: x = " << i << " j: " << j << std::endl;
                map[i][j] = 2;
                objectList.push_back(new PointDot(j, i, Type::DOT, UP));
            }
        }
    }
    std::cout << "Added dots" << std::endl;
}
bool Game::isDotOrFruit(Type type)
{
    return type == Type::DOT ||
           std::find(std::begin(fruitTypes), std::end(fruitTypes), type) != std::end(fruitTypes);
}
void Game::removeDot(int x, int y)
{
    for (auto it = objectList.begin(); it != objectList.end(); ++it)
    {
        // Check if it's a dot and matches the coordinates
        if ((*it)->getPosition().x == x && (*it)->getPosition().y == y && isDotOrFruit((*it)->getType()))
        {
            // std::cout << "Dot found at (" << x << ", " << y << ")" << std::endl;

            // Delete the object and erase from the list
            delete *it;           // Free memory if allocated dynamically
            objectList.erase(it); // Erase the element and update the iterator
            map[y][x] = 0;        // Clear the map

            // std::cout << "Dot removed at (" << x << ", " << y << ")" << std::endl;

            this->addToScore(dot_value);
            break; // Stop after removing the dot
        }
    }
}

int Game::getRandomInRange(int min, int max)
{
    return min + (std::rand() % (max - min + 1));
}

void Game::addFruit()
{
    while (1)
    {
        int x_pos = getRandomInRange(1, 25);
        int y_pos = getRandomInRange(1, 25);
        if (map[y_pos][x_pos] == 0)
        {
            map[y_pos][x_pos] = 2;
            objectList.push_back(new PointDot(x_pos, y_pos, fruitTypes[getRandomInRange(0, 5)], UP));
            break;
        }
    }
}

// Generates a buffer of the current positions of all objects. Is used right before updating positions so we have a buffer of the previous locations
// Constists of buffers for ghosts and pacman
void Game::generatePositionBuffers()
{
    // Temporary variable to add things to, later used to set ghost position buffer
    std::vector<Point> temp;

    // We go over all the objects in the object list to find the ghosts
    for (auto it = objectList.begin(); it != objectList.end(); ++it)
    {
        // If we find a ghost, we need to add its position in the form of a Point to the temp variable, to later add to the buffer
        if ((*it)->getType() == Type::BLINKY || (*it)->getType() == Type::PINKY || (*it)->getType() == Type::INKY || (*it)->getType() == Type::CLYDE)
        {
            temp.push_back((*it)->getPosition());       // We add it to temp
        }
    }
    // We set the previous buffer to the current postion buffer for the ghosts
    setGhostPositionBuffer(&temp);

    // We update the previouso pacman position buffer
    setPacmanPositionBuffer(getPacman()->getPosition());
}

// Function to see if we colided with a ghost. Needs to be called after updating all the characters
void Game::checkColission()
{
    // How this code works:
    // 2 scenarios:
    //  1) We crossed a ghost but we do not occupy the same position right now
    //  2) We occupy the same position as a ghost

    // SCENARIO 1:
    // We go over all the previous positions of the ghosts, for which we do the following:
    //  we check if the current Pacman position is on one of these positions
    //      If it is, we go over all current ghost positions
    //          if Pacmans previous position is the same as the current ghost position, we must have crossed eachother so we must lose a live

    // Go over all the ghosts' previous positions
    for (auto ghostPoint : *getGhostPositionBuffer())
    {
        // If we are not currently in one of the ghosts' previous position, we do not need to do anything, skip this loop
        if (getPacman()->getPosition() != ghostPoint)
        {
            continue;
        }

        // We are in one of the ghosts' previous positions
        // We must go over all the ghosts and see if one of them is currently on pacmans previous position
        for (auto ghostCurrent : objectList)
        {
            // Only need to check if the object type is a ghost, skip if we are not
            if (!(ghostCurrent->getType() == Type::BLINKY || ghostCurrent->getType() == Type::PINKY || ghostCurrent->getType() == Type::INKY || ghostCurrent->getType() == Type::CLYDE))
            {
                continue;
            }

            // Final logic. If ghost is in previous position of pacman, pacman is almost guaranteed to have crossed this ghost, meaning we should do deathReset()
            if (ghostCurrent->getPosition() == getPacmanPositionBuffer())
            {
                deathReset();
                return;
            }
        }
    }

    // SCENARIO 2:
    // We now check for the simpler case: we are in the same location
    // Go over all objects
    for (auto it = objectList.begin(); it != objectList.end(); ++it)
    {
        // If object is a ghost, we need to check the location of it
        if ((*it)->getType() == Type::BLINKY || (*it)->getType() == Type::PINKY || (*it)->getType() == Type::INKY || (*it)->getType() == Type::CLYDE)
        {   
            // We check if the location of the ghost is the same as that of pacman, in which case we need to deathReset()
            if ((*it)->getPosition() == getPacman()->getPosition())
            {
                deathReset();
                return;
            }
        }
    }
}

// Function for when we colide with a ghost. Removes 1 live if possible. Stops game if not.
// Also resets positions for all characters.
void Game::deathReset()
{
    setLives(getLives() - 1);           // Remove life
    if (getLives() <= 0)                // If lives are 0, stop game
    {
        setQuit(true);                  // Set quit variable to true to exit main game loop later
        std::cout << "You died! Closing game! \n" << "Your final score was: " << getScore() << std::endl;
        return;
    }

    // We are not completely dead yet, so we need to reset.
    getPacman()->setPosition(1, 1);                         // Reset pacman to initial position
    blinky.setPosition(blinky.getStartingPosition());       // Reset blinky position
    clyde.setPosition(clyde.getStartingPosition());         // Reset clyde position

    // For Pinky and Inky, we need to also set initialize to true
    pinky.setInitialized(false);                            // Set initiialize to invoke doInitialize() in findMoveDirection() 
    pinky.setPosition(pinky.getStartingPosition());         // Also set position to initial position

    inky.setInitialized(false);                             // Set initiialize to invoke doInitialize() in findMoveDirection() 
    inky.setPosition(inky.getStartingPosition());           // Also set position to initial position
}