#ifndef H_PLAYEROBJECT
#define H_PLAYEROBJECT

#include "Character.hpp"
class Pacman : public Character
{
public:
    Pacman(int x, int y, Type type, Direction dir);
};

#endif