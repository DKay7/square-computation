#ifndef POINT_H
#define POINT_H

#include <cstdlib>

class Point final {
public:
    Point(float x, float y): x_(x), y_(y) {}
    explicit Point(float both): x_(both), y_(both) {}

    bool operator==(const Point &other) const = default;

    float x_ = 0;
    float y_ = 0;

    enum class OrientationType {
        COLLINEAR         = 0,
        CLOCKWISE         = 1,
        COUNTER_CLOCKWISE = 2
    };
    
    // find orientation of ordered triple (p, q, r)
    static OrientationType triple_orientation(const Point p, const Point q, const Point r);

    // check if point on [segment_start, segment_end]
    static bool is_on_segment(const Point segment_start, const Point segment_end, const Point point);

};

#endif
