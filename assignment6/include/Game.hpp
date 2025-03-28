#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "GameObjectStruct.hpp"
#include "Pacman.hpp"
#include "PointDot.hpp"

class Game
{
public:
    Game(const std::vector<std::vector<int>> &map)
        : map(map), pacman(1, 1, Type::PACMAN, Direction::DOWN) // Initialize PacMan
    {
        objectList.push_back(&pacman); // Store Pacman pointer in objectList
    }

    void update() { pacman.move(this); } // Game update logic
    void printMap() const;
    std::vector<std::vector<int>> &getMap() { return map; }
    void setMap(const std::vector<std::vector<int>> &newMap) { map = newMap; }
    void removeDot(int x, int y);
    std::vector<GameObjectStruct *> &getObjectList() { return objectList; }
    void addObjectList(GameObjectStruct *nObject) { objectList.push_back(nObject); }
    void addDots();
    Pacman *getPacman() { return &pacman; } // Getter for Pacman

private:
    std::vector<std::vector<int>> map;
    std::vector<GameObjectStruct *> objectList;
    Pacman pacman; // Pacman is now part of the game
};

#endif // GAME_HPP
