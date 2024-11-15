#ifndef VECTOR2_H
#define VECTOR2_H

#include "geometry/Point.h"

#include <cmath>

class Vector2 final {
public:
    Vector2(Point a, Point b);

    float length() const;
    bool  intersect(Vector2 other) const;
    float distance_to(Point other) const;
    float distance_to(Vector2 other) const;
    float cross_product(Vector2 other) const;
    float dot_product(Vector2 other) const;

    // get direction vector
    std::pair<float, float> get_direction() const;
private:
    Point begin_, end_;
    
};

#endif  // !LINE_H
