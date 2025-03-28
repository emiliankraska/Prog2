#include "Game.hpp"
#include "PointDot.hpp"
#include <iostream>
#include <array>
#include <algorithm>
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
void Game::generatePositionBuffers()
{
    std::vector<Point> temp;

    for (auto it = objectList.begin(); it != objectList.end(); ++it)
    {
        if ((*it)->getType() == Type::BLINKY || (*it)->getType() == Type::PINKY || (*it)->getType() == Type::INKY || (*it)->getType() == Type::CLYDE)
        {
            temp.push_back((*it)->getPosition());
        }
    }
    setGhostPositionBuffer(&temp);
    setPacmanPositionBuffer(getPacman()->getPosition());
}

// Function to check colissions. Should be called after moving Pacman, then after moving ghosts we need to check again
void Game::checkColission()
{
    for (auto ghostPoint : *getGhostPositionBuffer())
    {
        if (getPacman()->getPosition() != ghostPoint)
        {
            continue;
        }
        // We are in the buffer of the ghost, now we need to see if this specific ghost is in our buffer
        for (auto ghostCurrent : objectList)
        {
            if (!(ghostCurrent->getType() == Type::BLINKY || ghostCurrent->getType() == Type::PINKY || ghostCurrent->getType() == Type::INKY || ghostCurrent->getType() == Type::CLYDE))
            {
                continue;
            }

            if (ghostCurrent->getPosition() == getPacmanPositionBuffer())
            {
                setLives(getLives() - 1);
                return;
            }
        }
    }

    for (auto it = objectList.begin(); it != objectList.end(); ++it)
    {
        if ((*it)->getType() == Type::BLINKY || (*it)->getType() == Type::PINKY || (*it)->getType() == Type::INKY || (*it)->getType() == Type::CLYDE)
        {
            if ((*it)->getPosition() == getPacman()->getPosition())
            {
                setLives(getLives() - 1);
            }
        }
    }
}