#ifndef TRIANGLE_H

#include "Point.h"
#include "Polygon.h"

class Triangle final : public Polygon {
public:
    Triangle(Point a, Point b, Point c): Polygon({a, b, c}) {}
    float square() const override;
};

#endif // !TRIANGLE_H
