#ifndef H_GHOSTS
#define H_GHOSTS

#include <queue>
#include "Character.hpp"

class Ghost : public Character
{
public:
    // Constructor
    Ghost(int, int, Type, Direction, Character *);

    void setTarget(Character *);            // Sets taget variable
    Character *getTarget() const;           // Gets target variable pointer

    
    virtual Direction findMoveDirection(std::vector<std::vector<int>> *);   // This is the bread and butter of the move() function. Finds next move direction based on algorithm, differs per ghost
    void move(Game *) override;                                             // Main bread and butter. Invokes findMoveDirection(), changes coordinates of ghost and updates the map

    Point getStartingPosition() const { return startingPosition; };                                     // gets starting position, for resetting position when we die
    void setStartingPosition(Point n_startingPosition) { startingPosition = n_startingPosition; };      // Sets starting postion. Must keep track for when PacMan dies

private:
    Character *target;  // Ghost target variable, in our case, always Pacman
    Point startingPosition = Point(0, 0); // x = 12, 13, 14, 15 , y = 13 for ghosts
};

// BLINKY -----
class Blinky : public Ghost
{ // Blinky is redGhost
public:
    Blinky(int, int, Direction, Character *);
    virtual Direction findMoveDirection(std::vector<std::vector<int>> *) override;  // We override findMoveDirection() to update algorithm for this ghost
};

// PINKY -----
class Pinky : public Ghost
{ // Pinky is pinkGhost
public:
    Pinky(int, int, Direction, Character *);
    virtual Direction findMoveDirection(std::vector<std::vector<int>> *) override;  // We override findMoveDirection() to update algorithm for this ghost
    virtual void doInitialize();                                                    // Initializes intializationRoute and patrolRoute based on ghost type

    void setPatrolRoute(std::vector<Point> n_patrolRoute) { patrolRoute = n_patrolRoute; };     // Sets partolRoute
    std::vector<Point> getPatrolRoute() { return patrolRoute; };                                // Gets partrolRoute

    void pushInitializationRoute(Direction n_dir) { initializationRoute.push(n_dir); };         // Pushes one item to the back of initializationRoute queue
    std::queue<Direction> getInitializationRoute() { return initializationRoute; };             // Gets intializaitonRoute
    Direction pullFromInitializationQueue();                                                    // Gets a value from intializationRoute queue and pops it form this queue
    int getInitialRouteLength() { return initializationRoute.size(); };                         // Gets the length of the initializationRoute queue   

    void setStage(int n_stage) { stage = n_stage; };                    // Sets current stage of the patrol algorithm
    int getStage() const { return stage; };                             // Gets current stage of patrol algorithm

    void setInitialized(bool n_initialized) { initialized = n_initialized; };   // Sets wether the initialization is done
    bool getInitialized() const { return initialized; };                        // Gets wether the initialization is done

    void resetInitializeRoute();                // Resets intializationRoute variable to empty queue

private:
    std::queue<Direction> initializationRoute;      // Used for determining the route required before we can run the standard patroling algorithm
    std::vector<Point> patrolRoute;                 // The patrol route, characterized by 4 Points
    int stage;                                      // Stage of the patrol algorithm
    bool initialized;                               // Wether the initializationRoute has been finished or not
};

// INKY -----
class Inky : public Pinky
{ // Inky is cyanGhost
public:
    Inky(int, int, Direction, Character *);
    void doInitialize() override;                   // We override doInitialize() to make for a different patroling algorithm
};

// CLYDE -----
class Clyde : public Ghost
{ // Clyde is orangeGhost
public:
    Clyde(int, int, Direction, Character *);
    virtual Direction findMoveDirection(std::vector<std::vector<int>> *) override;      // Override for different algorithm, random algorithm with number of moves in this case

    int getMoveBuffer() const { return moveBuffer; };                       // Sets move buffer
    void setMoveBuffer(int n_moveBuffer) { moveBuffer = n_moveBuffer; };    // Gets move buffer

private:
    int moveBuffer = 0; // Buffer to keep track of number of moves before changing direction randomly. Set in the findMoveDirection() function
};

#endif