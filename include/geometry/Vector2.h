#ifndef VECTOR2_H
#define VECTOR2_H

#include "geometry/Point.h"

#include <cmath>

class Vector2 final {
public:
    Vector2(Point a, Point b);

    float length() const;
    bool  intersect(Vector2 other);


private:
    Point begin_, end_;
};

#endif  // !LINE_H
