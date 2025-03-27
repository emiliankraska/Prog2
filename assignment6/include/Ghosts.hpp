#ifndef H_GHOSTS
#define H_GHOSTS

#include "Character.hpp"

class Ghost : public Character {
    public:
    Ghost(int, int, Type, Direction, Character*);
    
    void setTarget(Character*);
    Character* getTarget() const;
    
    // When we get eaten, we must return to the starting square, this function returns us to the starting square
    void onGhostEaten();
    
    // This is the main algorithm for finding the next move, differs per ghost. Must be overwritten for every derivative of the class
    virtual Direction findMoveDirection() const = 0;            

    private:
    bool isEaten = false;
    bool isFrightened = false;
    Character* target;
};

class Blinky : public Ghost {           // Blinky is redGhost
    public:
    Blinky(int, int, Direction, Character*);
    virtual Direction findMoveDirection() const override;
};

class Pinky : public Ghost {            // Pinky is pinkGhost
    public:
    Pinky(int, int, Direction, Character*);
    virtual Direction findMoveDirection() const override;
};

class Inky : public Ghost {             // Inky is cyanGhost
    public:
    Inky(int, int, Direction, Character*);
    virtual Direction findMoveDirection() const override;
};

class Clyde : public Ghost {            // Clyde is orangeGhost
    public:
    Clyde(int, int, Direction, Character*);
    virtual Direction findMoveDirection() const override;
};

#endif