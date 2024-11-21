#include "geometry/Point.h"

#include "geometry/Vector2.h"

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
    Vector2 segment {segment_start, segment_end};
    auto [x_dir, y_dir] = segment.get_direction();

    // y = k * x + b.
    float k = y_dir / x_dir;
    float b = segment_start.y_ - k * segment_start.x_;

    return (
        std::abs(point.x_ * k + b - point.y_) < std::numeric_limits<double>::epsilon() and
        (point.x_ <= std::max(segment_start.x_, segment_end.x_) and point.x_ >= std::min(segment_start.x_, segment_end.x_)) and
        (point.y_ <= std::max(segment_start.y_, segment_end.y_) and point.y_ >= std::min(segment_start.y_, segment_end.y_)));
};
