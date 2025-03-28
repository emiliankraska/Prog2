#ifndef H_GHOSTS
#define H_GHOSTS

#include <queue>
#include "Character.hpp"

class Ghost : public Character {
    public:
    Ghost(int, int, Type, Direction, Character*);
    
    void setTarget(Character*);
    Character* getTarget() const;
    
    // When we get eaten, we must return to the starting square, this function returns us to the starting square
    void onGhostEaten();
    
    // This is the main algorithm for finding the next move, differs per ghost. Must be overwritten for every derivative of the class
    virtual Direction findMoveDirection(std::vector<std::vector<int>> *);            
    virtual void move(std::vector<std::vector<int>> *) override;
    
    bool getIsEaten() const {return isEaten;};
    void setIsEaten(bool n_isEaten) {isEaten = n_isEaten;};

    bool getIsFrightened() const {return isFrightened;};
    void setIsFrightened(bool n_isFrightened) {isFrightened = n_isFrightened;};

    Point getStartingPosition() const {return startingPosition;};
    void setStartingPosition(Point n_startingPosition) {startingPosition = n_startingPosition;};

    private:
    bool isEaten = false;
    bool isFrightened = false;
    Character* target;
    Point startingPosition = Point(0, 0); // x = 12, 13, 14, 15 , y = 13 for ghosts
};

// BLINKY -----
class Blinky : public Ghost {           // Blinky is redGhost
    public:
    Blinky(int, int, Direction, Character*);
    virtual Direction findMoveDirection(std::vector<std::vector<int>> *) override;

};

// PINKY -----
class Pinky : public Ghost {            // Pinky is pinkGhost
    public:
    Pinky(int, int, Direction, Character*);
    virtual Direction findMoveDirection(std::vector<std::vector<int>> *) override;
    virtual void doInitialize();

    void setPatrolRoute(std::vector<Point> n_patrolRoute) {patrolRoute = n_patrolRoute;};
    std::vector<Point> getPatrolRoute() {return patrolRoute;};
    
    void pushInitializationRoute(Direction n_dir) {initializationRoute.push(n_dir);};
    std::queue<Direction> getInitializationRoute() {return initializationRoute;};

    Direction pullFromInitializationQueue() {Direction n_dir = initializationRoute.front(); initializationRoute.pop(); return n_dir;};
    int getInitialRouteLength() {return initializationRoute.size();};

    void setStage(int n_stage) {stage = n_stage;};
    int getStage() const {return stage;};

    void setInitialized(bool n_initialized) {initialized = n_initialized;};
    bool getInitialized() const {return initialized;};

    private:
    std::queue<Direction> initializationRoute;
    std::vector<Point> patrolRoute;
    int stage;
    bool initialized;
};

// INKY -----
class Inky : public Pinky {             // Inky is cyanGhost
    public:
    Inky(int, int, Direction, Character*);
    void doInitialize() override;
};

// CLYDE -----
class Clyde : public Ghost {            // Clyde is orangeGhost
    public:
    Clyde(int, int, Direction, Character*);
    virtual Direction findMoveDirection(std::vector<std::vector<int>> *) override;

    int getMoveBuffer() const {return moveBuffer;};
    void setMoveBuffer(int n_moveBuffer) {moveBuffer = n_moveBuffer;};

    private:
    int moveBuffer = 0;     // Buffer to keep track of number of moves before changing direction randomly. Set in the findMoveDirection() function
};

#endif