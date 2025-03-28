#include "Game.hpp"
#include "PointDot.hpp"
#include <iostream>
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
                std::cout << "Adding Dot with values: x = " << i << " j: " << j << std::endl;
                map[i][j] = 2;
                objectList.push_back(new PointDot(j, i, Type::DOT, UP));
            }
        }
    }
    std::cout << "Added dots" << std::endl;
}
void Game::removeDot(int x, int y)
{
    for (auto it = objectList.begin(); it != objectList.end(); ++it)
    {
        // Check if it's a dot and matches the coordinates
        if (((*it)->getType() == Type::DOT) && ((*it)->getPosition().x == x && (*it)->getPosition().y == y))
        {
            std::cout << "Dot found at (" << x << ", " << y << ")" << std::endl;

            // Delete the object and erase from the list
            delete *it;           // Free memory if allocated dynamically
            objectList.erase(it); // Erase the element and update the iterator
            map[y][x] = 0;        // Clear the map

            std::cout << "Dot removed at (" << x << ", " << y << ")" << std::endl;

            break; // Stop after removing the dot
        }
    }
}