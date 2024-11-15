#include "geometry/Point.h"

#include <cmath>
#include <limits>

Point::OrientationType Point::triple_orientation(const Point p, const Point q, const Point r) {
    float product = (q.y_ - p.y_) * (r.x_ - q.x_) - (q.x_ - p.x_) * (r.y_ - q.y_);

    bool is_zero = std::fabs(product) < std::numeric_limits<double>::epsilon();

    if (is_zero)
        return OrientationType::COLLINEAR;

    return product > 0 ? OrientationType::CLOCKWISE : OrientationType::COUNTER_CLOCKWISE;
};

bool Point::is_on_segment(const Point segment_start, const Point segment_end, const Point point) {
    return (
        (point.x_ <= std::max(segment_start.x_, segment_end.x_) and point.x_ >= std::min(segment_start.x_, segment_end.x_)) and
        (point.y_ <= std::max(segment_start.y_, segment_end.y_) and point.y_ >= std::min(segment_start.y_, segment_end.y_)));
};
