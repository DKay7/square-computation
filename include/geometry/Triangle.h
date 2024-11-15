#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"
#include "Polygon.h"

#include <cmath>

class Triangle final : public Polygon {
public:
    explicit Triangle(Point a, Point b, Point c);
    explicit Triangle(Polygon poly);
    virtual float square() const override;

    const Point& a() const;
    const Point& b() const;
    const Point& c() const;
    
    bool is_point_inside(Point d) const;
};

#endif  // !TRIANGLE_H
