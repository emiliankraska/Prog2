#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "GameObjectStruct.hpp"
#include "Pacman.hpp"
#include "PointDot.hpp"
#include "Ghosts.hpp"
#include <random>
#include <array>
#include <cstdlib>
#include <ctime>

// Blinky
// Pinky pinky(13, 13, Direction::UP, pacman);
// Inky inky(14, 13, Direction::UP, pacman);
// Clyde clyde(15, 13, Direction::UP, pacman);
class Game
{
public:
    Game(const std::vector<std::vector<int>> &map)
        : map(map), pacman(1, 1, Type::PACMAN, Direction::DOWN), blinky(12, 13, Direction::UP, &pacman), pinky(13, 13, Direction::UP, &pacman), inky(14, 13, Direction::UP, &pacman), clyde(15, 13, Direction::UP, &pacman)
    {
        setLives(3);
        setQuit(false);
        objectList.push_back(&pacman); // Store Pacman pointer in objectList
        objectList.push_back(&blinky);
        objectList.push_back(&pinky);
        objectList.push_back(&inky);
        objectList.push_back(&clyde);
        setGhostMap(map);
        generatePositionBuffers();
    }
    bool isDotOrFruit(Type type);
    void update(); // Game update logic
    void printMap() const;
    int getRandomInRange(int, int);
    std::vector<std::vector<int>> &getMap() { return map; }
    void setMap(const std::vector<std::vector<int>> &newMap) { map = newMap; }
    std::vector<std::vector<int>> &getGhostMap() { return ghostMap; };
    void setGhostMap(const std::vector<std::vector<int>> newMap) { ghostMap = newMap; };
    void removeDot(int x, int y);
    std::vector<GameObjectStruct *> &getObjectList() { return objectList; }
    void addObjectList(GameObjectStruct *nObject) { objectList.push_back(nObject); }
    void addDots();
    Pacman *getPacman() { return &pacman; } // Getter for Pacman
    void addFruit();

    std::uint32_t getScore() const
    {
        return score;
    }

    // Setter for score
    void setScore(std::uint32_t);
    void addToScore(std::uint32_t);

        void checkColission();
    int getLives() { return lives; };
    void setLives(int newLives) { lives = newLives; };
    bool getQuit() { return quit; };
    void setQuit(bool newQuit) { quit = newQuit; };
    Point getPacmanPositionBuffer() const { return pacmanPositionBuffer; };
    void setPacmanPositionBuffer(Point newBuffer) { pacmanPositionBuffer = newBuffer; };
    std::vector<Point> *getGhostPositionBuffer() { return &ghostPositionBuffer; };
    void setGhostPositionBuffer(std::vector<Point> *newGhostPositionBuffer) { ghostPositionBuffer = *newGhostPositionBuffer; };
    void generatePositionBuffers();
    void deathReset();

private:
    int dot_value = 100;
    std::uint32_t score = 0;
    std::vector<std::vector<int>> map;
    std::vector<std::vector<int>> ghostMap;
    std::vector<GameObjectStruct *> objectList;
    Pacman pacman; // Pacman is now part of the game
    Blinky blinky;
    Pinky pinky;
    Inky inky;
    Clyde clyde;
    const std::array<Type, 6> fruitTypes = {
        CHERRY,
        STRAWBERRY,
        ORANGE,
        LEMON,
        APPLE,
        GRAPES};
    // Uniform distribution
    int lives;
    bool quit;
    Point pacmanPositionBuffer = Point(0, 0);
    std::vector<Point> ghostPositionBuffer;
};

#endif // GAME_HPP
