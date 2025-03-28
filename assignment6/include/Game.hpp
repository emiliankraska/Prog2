#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "GameObjectStruct.hpp"
#include "Pacman.hpp"
#include "PointDot.hpp"
#include "Ghosts.hpp"
// Blinky
// Pinky pinky(13, 13, Direction::UP, pacman);
// Inky inky(14, 13, Direction::UP, pacman);
// Clyde clyde(15, 13, Direction::UP, pacman);
class Game
{
public:
    Game(const std::vector<std::vector<int>> &map)
        : map(map), pacman(1, 1, Type::PACMAN, Direction::DOWN), blinky(12, 13, Direction::UP, &pacman), pinky(13, 13, Direction::UP, &pacman), inky(14, 13, Direction::UP, &pacman), clyde(15, 13, Direction::UP, &pacman) // Initialize PacMan
    {
        objectList.push_back(&pacman); // Store Pacman pointer in objectList
        objectList.push_back(&blinky);
        objectList.push_back(&pinky);
        objectList.push_back(&inky);
        objectList.push_back(&clyde);
    }

    void update(); // Game update logic
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
    Blinky blinky;
    Pinky pinky;
    Inky inky;
    Clyde clyde;
};

#endif // GAME_HPP
