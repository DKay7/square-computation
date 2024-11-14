#ifndef LINE_H
#define LINE_H

#include "Point.h"

class Vector2 final {
public:
    Vector2(Point a, Point b): begin_(a), end_(b) {}
    float length() const;
private:
    Point begin_, end_;
};

#endif  // !LINE_H
