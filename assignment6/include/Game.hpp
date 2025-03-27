#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "GameObjectStruct.hpp"
#include "Pacman.hpp"

class Game
{
public:
    Game(const std::vector<std::vector<int>> &map)
        : map(map), pacman(1, 1, Type::PACMAN, Direction::DOWN) {} // Initialize Pacman

    void update() { pacman.move(&map); } // Game update logic

    const std::vector<std::vector<int>> &getMap() const { return map; }
    void setMap(const std::vector<std::vector<int>> &newMap) { map = newMap; }

    const std::vector<GameObjectStruct> &getObjectList() const { return objectList; }
    void setObjectList(const std::vector<GameObjectStruct> &nObjectList) { objectList = nObjectList; }

    Pacman *getPacman() { return &pacman; } // Getter for Pacman

private:
    std::vector<std::vector<int>> map;
    std::vector<GameObjectStruct> objectList;
    Pacman pacman; // Pacman is now part of the game
};

#endif // GAME_HPP
