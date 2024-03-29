#ifndef GAME_CLASSES_H
#define GAME_CLASSES_H

#include <iostream>

/// Some direction on the compass rose.
enum class Direction
{
    N,
    S,
    E,
    W
};

/// A 2d natural coordinate.
struct Point
{
    int x;
    int y;
    
    Point() = default;
    
    Point(int x_, int y_);
    bool operator==(const Point& rhs) const;
    bool operator!=(const Point& rhs) const;
    Point& operator=(const Point& rhs);
};

/// Negate direction
Direction operator!(Direction& rhs);

/// Direction by 2 points
Direction operator*(Point src, Point dest);

/// Print Direction
std::ostream& operator<<(std::ostream& os, const Direction& rhs);

/// Direction rotate 90
Direction& operator++(Direction& rhs);

#include "game_classes.cpp"


#endif
