#include "PointDot.hpp"

PointDot::PointDot(int n_x, int n_y, Type n_type, Direction n_dir)
{
    setPosition(n_x, n_y);
    setType(n_type);
    setDir(n_dir);
}