#ifndef POLYGON_H
#define POLYGON_H

#include "geometry/Point.h"

#include <initializer_list>
#include <vector>

class Polygon {
public:
    Polygon(std::initializer_list<Point> points): points_(points) {}

    virtual ~Polygon() = default;
    virtual float             square() const;
    const std::vector<Point> &get_points() const { return points_; }

private:
    std::vector<Point> points_;
};

#endif
