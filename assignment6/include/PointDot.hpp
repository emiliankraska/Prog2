#ifndef DOT_HPP
#define DOT_HPP
#include <vector>
#include "GameObjectStruct.hpp"
class PointDot : public GameObjectStruct
{
public:
    PointDot(int, int, Type, Direction);
    int getPointValue() const
    {
        return point_value;
    }
    void setPointValue(int newPointValue)
    {
        point_value = newPointValue;
    }

private:
    int point_value = 100;
};

#endif