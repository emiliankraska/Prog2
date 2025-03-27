#include "Game.hpp"
#include "PointDot.hpp"
#include <iostream>
void Game::addDots()
{
    std::size_t cols = (map.empty()) ? 0 : map[0].size();
    std::size_t rows = (map.empty()) ? 0 : map.size();

    for (int i = 0; i < cols - 1; i++)
    {
        for (int j = 0; j < rows - 1; j++)
        {

            if (map[i][j] == 0 && !(pacman.getPosition().x == i && pacman.getPosition().y == j))
            {
                std::cout << "Adding Dot with values: x = " << i << " j: " << j << std::endl;
                objectList.push_back(new PointDot(j, i, Type::DOT, UP));
            }
        }
    }
    std::cout << "Added dots" << std::endl;
}